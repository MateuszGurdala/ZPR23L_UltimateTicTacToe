import { Injectable } from "@angular/core";
import { GameHttpClient } from "./game-http-client.service";
import { GameBoardComponent } from "../components/game-board/game-board.component";
import { GameMode, GameStage, GameStageResponse, GameState, Segment, Sign } from "../structs";
import { first, firstValueFrom } from "rxjs";
import { Router } from "@angular/router";
import { SettingsBarComponent } from "../components/settings-bar/settings-bar.component";
import { GlobalVariablesService } from "./global-variables.service";
import { BoardSegmentComponent } from "../components/board-segment/board-segment.component";

@Injectable({
	providedIn: "root",
})
export class GameMasterService {
	//Refs
	private gameBoard: GameBoardComponent;
	private settingsBoard: SettingsBarComponent;

	//Const/Vars
	private readonly enemyTimeout: number = 1000;
	private readonly playerTimeout: number = 1000;
	private readonly standardTimeout: number = 1000;
	private readonly initTimeout: number = 100;

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
	async waitFor(condition: Function, timeout: number = this.standardTimeout) {
		if (condition()) {
			await this.sleep(timeout);
			await this.waitFor(condition, timeout);
		}
		return;
	}
	//#endregion

	//#region GameUtils
	async tryStartNewGame(): Promise<any> {
		let retVal: any;
		switch (await this.gVars.getGameState()) {
			case GameState.Ready:
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
	async tryJoinGame(): Promise<boolean | Sign> {
		return await firstValueFrom(this.httpClient.getJoinGame());
	}
	async endGame(): Promise<void> {
		await firstValueFrom(await this.httpClient.getEndGame());
		await this.gVars.getGameState();
		this.gVars.isGameOngoing = false;
		this.router.navigate(["/Start"]);
		window.location.reload();
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
		await firstValueFrom(await this.httpClient.postMakeMove(boardId - 1, segmentId - 1));
	}
	async updateBoard(): Promise<void> {
		let result = await firstValueFrom(this.httpClient.getBoardState());
		this.gameBoard.update(result);
		result.segments.forEach((segment) => {
			this.settingsBoard.updateLookup(segment.id, segment.winner);
		});
	}
	private async playerTurn(): Promise<void> {
		this.setIsProcessing(false);
		this.gameBoard.setIsActive(false);
		await this.updateBoard();
		await this.gVars.getCurrentSegment();
		if (this.gVars.currentSegment !== undefined) {
			this.gameBoard.unlockSegment(this.gVars.currentSegment);
		}
		await this.waitFor(() => {
			return !this.gVars.playerMadeMove;
		}, this.playerTimeout);
		this.gVars.playerMadeMove = false;
	}
	private async playerChooseSegment(): Promise<void> {
		this.setIsProcessing(false);
		await this.updateBoard();
		this.gameBoard.unlockSegmentChoosing();
		await this.waitFor(() => {
			return !this.gVars.playerChoseSegment;
		}, this.playerTimeout);
		this.gVars.playerChoseSegment = false;
		this.gVars.gameStage = GameStage.PlayerTurn;
		await this.playerTurn();
	}
	private async waitForEnemy(): Promise<void> {
		this.gameBoard.setIsActive(false);
		this.setIsProcessing(true);
		await this.sleep(this.enemyTimeout);
	}
	private async finishGame(): Promise<void> {
		this.setIsProcessing(false);
		this.gameBoard.setIsActive(false);
		this.gVars.isGameOngoing = false;
	}
	async mainGameLoop(): Promise<void> {
		await this.waitFor(() => {
			return this.gameBoard === undefined || this.settingsBoard === undefined;
		}, this.initTimeout);
		while (this.gVars.isGameOngoing) {
			this.setIsProcessing(true);
			switch (await this.gVars.getGameStage()) {
				case GameStage.PlayerTurn:
					await this.playerTurn();
					break;
				case GameStage.PlayerChooseSegment:
					await this.playerChooseSegment();
					break;
				case GameStage.EnemyTurn:
				case GameStage.EnemyChooseSegment:
					await this.waitForEnemy();
					break;
				case GameStage.Finished:
					await this.finishGame();
					break;
				default:
					break;
			}
			this.gVars.currentSegment = undefined;
		}
	}
	//#endregion
}
