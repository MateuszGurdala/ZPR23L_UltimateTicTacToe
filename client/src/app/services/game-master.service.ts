import { Injectable } from "@angular/core";
import { GameHttpClient } from "./game-http-client.service";
import { GameBoardComponent } from "../components/game-board/game-board.component";
import { GameMode, GameStage, GameState, Segment, Sign } from "../structs";
import { firstValueFrom } from "rxjs";
import { Router } from "@angular/router";
import { SettingsBarComponent } from "../components/settings-bar/settings-bar.component";
import { GlobalVariablesService } from "./global-variables.service";
import { BoardSegmentComponent } from "../components/board-segment/board-segment.component";

@Injectable({
	providedIn: "root",
})
export class GameMasterService {
	//Refs
	gameBoard: GameBoardComponent;
	settingsBoard: SettingsBarComponent;

	//Const/Vars
	readonly enemyTimeout: number = 500;
	readonly playerTimeout: number = 500;
	readonly initTimeout: number = 100;

	constructor(
		private readonly httpClient: GameHttpClient,
		private readonly router: Router,
		private readonly gVars: GlobalVariablesService
	) {}

	//#region Setters
	setBoardComponent(component: GameBoardComponent): void {
		this.gameBoard = component;
	}
	setSettingsBarComponent(component: SettingsBarComponent): void {
		this.settingsBoard = component;
	}
	setBoardSize(size: number): void {
		this.gVars.boardSize = size;
	}
	setPlayerSign(sign: Sign): void {
		this.gVars.playerSign = sign;
	}
	setGameMode(mode: GameMode): void {
		this.gVars.gameMode = mode;
	}
	setIsProcessing(value: boolean): void {
		this.gVars.isProcessing = value;
	}
	//#endregion

	//#region Utils
	checkServerIsAlive(url: string): Promise<boolean> {
		this.httpClient.setServerUrl(url);
		return firstValueFrom(this.httpClient.getServerStatus());
	}
	sleep(ms: number): Promise<void> {
		return new Promise((resolve) => setTimeout(resolve, ms));
	}
	async waitForGameInit(): Promise<void> {
		if (this.gameBoard === undefined) {
			console.log("Waiting for init.");
			await this.sleep(this.playerTimeout);
			await this.waitForGameInit();
		}
		console.log("Game initialized.");
		return;
	}
	//#endregion

	//#region GameUtils
	async tryStartNewGame(): Promise<any> {
		let retVal: any;
		switch (await this.gVars.getGameState()) {
			case GameState.Ready:
				//TODO: Start game based on an chosen enemy
				await this.startNewSoloGame();
				break;
			case GameState.Ongoing:
				retVal = "The game is already ongoing.";
				break;
			case GameState.Waiting:
				retVal = "Someone has already created a new game. Maybe you should join him?";
				break;
			default:
				this.router.navigate(["/Game"]);
				break;
		}
		return retVal;
	}
	async startNewSoloGame(): Promise<void> {
		let response = await this.httpClient.postCreateGame(
			this.gVars.gameMode,
			this.gVars.playerSign,
			this.gVars.boardSize
		);
		if (response) {
			this.router.navigate(["/Game"]);
			await this.mainGameLoop();
		}
	}
	async endGame(): Promise<void> {
		await firstValueFrom(await this.httpClient.getEndGame());
		await this.gVars.getGameState();
		this.gVars.isGameOngoing = false;
		this.router.navigate(["/Start"]);
		window.location.reload(); //TODO: Temporary solution?
	}
	async waitForPlayerMove(): Promise<void> {
		if (!this.gVars.playerMadeMove) {
			console.log("Waiting for player to make move.");
			await this.sleep(this.playerTimeout);
			await this.waitForPlayerMove();
		}
		this.gVars.playerMadeMove = false;
		return;
	}
	async waitForPlayerChooseSegment(): Promise<void> {
		if (!this.gVars.playerChoseSegment) {
			console.log("Waiting for player to choose segment.");
			await this.sleep(this.playerTimeout);
			await this.waitForPlayerChooseSegment();
		}
		this.gVars.playerChoseSegment = false;
		return;
	}
	signalPlayerMove(): void {
		this.gVars.playerMadeMove = true;
	}
	signalPlayerChoseSegment(): void {
		this.gVars.playerChoseSegment = true;
	}
	//#endregion

	//#region CoreGameMethods
	async makeMove(boardId: number, segmentId: number): Promise<void> {
		let result = await firstValueFrom(await this.httpClient.postMakeMove(boardId, segmentId));
	}
	async updateBoard(): Promise<void> {
		let result = await firstValueFrom(this.httpClient.getBoardState());
		this.gameBoard.update(result);
	}
	//#endregion

	async mainGameLoop(): Promise<void> {
		await this.waitForGameInit();
		console.log("Starting game main loop.");
		while (this.gVars.isGameOngoing) {
			this.setIsProcessing(true);
			console.log("Running loop iteration.");
			switch (await this.gVars.getGameStage()) {
				case GameStage.PlayerTurn:
					this.setIsProcessing(false);
					this.gameBoard.setIsActive(false);
					// await this.updateBoard();
					if (this.gVars.currentSegment !== undefined) {
						this.gameBoard.unlockSegment(this.gVars.currentSegment);
					}
					await this.waitForPlayerMove();
					//TODO: Something more should be added here?
					break;
				case GameStage.PlayerChooseSegment:
					this.setIsProcessing(false);
					// await this.updateBoard();
					this.gameBoard.unlockSegmentChoosing();
					await this.waitForPlayerChooseSegment();
					this.gVars.gameStagePub = GameStage.PlayerTurn;
					break;
				case GameStage.EnemyTurn:
				case GameStage.EnemyChooseSegment:
					this.gameBoard.setIsActive(false);
					this.setIsProcessing(true);
					await this.sleep(this.enemyTimeout);
					break;
				case GameStage.Finished:
					this.setIsProcessing(false);
					this.gameBoard.setIsActive(false);
					this.gVars.isGameOngoing = false;
					break;
				default:
					break;
			}
		}
	}
}
