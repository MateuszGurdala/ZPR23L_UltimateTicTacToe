import { Injectable } from "@angular/core";
import { GameHttpClient } from "./game-http-client.service";
import { GameBoardComponent } from "../components/game-board/game-board.component";
import { GameMode, GameStage, GameState, Sign } from "../structs";
import { firstValueFrom } from "rxjs";
import { Router } from "@angular/router";
import { SettingsBarComponent } from "../components/settings-bar/settings-bar.component";

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
	gameState: GameState;
	isGameOngoing: boolean = false;
	isProcessing: boolean = false;
	playerMadeMove: boolean = false;
	playerChooseSegment: boolean = false;

	//GameSettings
	boardSize: number = 3;
	playerSign: Sign = Sign.X;
	gameMode: GameMode = GameMode.SinglePlayer;

	/* 
	Ready - new game can be created
	Waiting - game in player vs player mode, waiting for second player
	Ongoing - as the name suggests
	PlayerSolo - client is a player that created new game vs AI
	PlayerX - client is an X player in player vs player game
	PlayerO - look above
	*/

	constructor(private httpClient: GameHttpClient, private router: Router) {
		this.gameState = GameState.Unknown;
	}

	//#region Setters
	setBoardComponent(component: GameBoardComponent): void {
		this.gameBoard = component;
	}
	setBoardSize(size: number): void {
		this.boardSize = size;
	}
	setPlayerSign(sign: Sign): void {
		this.playerSign = sign;
	}
	setGameMode(mode: GameMode): void {
		this.gameMode = mode;
	}
	setSettingsBarComponent(component: SettingsBarComponent) {
		this.settingsBoard = component;
	}
	//#endregion

	//#region Utils
	async getGameState(mockState: GameState): Promise<GameState> {
		this.gameState = await firstValueFrom(this.httpClient.getGameState(mockState));
		return this.gameState;
	}
	async canStartGame(): Promise<boolean> {
		if (this.gameState === GameState.Unknown) {
			this.gameState = await this.getGameState(GameState.Ready);
		}
		return this.gameState === GameState.Ready;
	}
	async isPlayer(): Promise<boolean> {
		if (this.gameState === GameState.Unknown) {
			await this.getGameState(GameState.Ready);
		}

		switch (this.gameState) {
			case GameState.Ready:
			case GameState.Waiting:
			case GameState.Ongoing:
			case GameState.Unknown:
				return false;
			case GameState.PlayerSolo:
			case GameState.PlayerX:
			case GameState.PlayerO:
				return true;
		}
	}
	checkServerIsAlive(url: string): Promise<boolean> {
		this.httpClient.setServerUrl(url);
		return firstValueFrom(this.httpClient.getServerStatus());
	}
	setIsProcessing(value: boolean): void {
		this.isProcessing = value;
	}
	sleep(ms: number): Promise<void> {
		return new Promise((resolve) => setTimeout(resolve, ms));
	}
	//#endregion

	//#region GameUtils
	async tryStartNewGame(): Promise<any> {
		let retVal: any;
		switch (await this.getGameState(GameState.Ready)) {
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
		if (
			await firstValueFrom(this.httpClient.postCreateGame(this.gameMode, this.playerSign, this.boardSize))
		) {
			await this.getGameState(GameState.PlayerSolo);
			this.isGameOngoing = true;
			this.router.navigate(["/Game"]);
			await this.mainGameLoop();
		}
	}
	async endGame(): Promise<void> {
		await firstValueFrom(this.httpClient.postEndGame());
		await this.getGameState(GameState.Ready);
		this.isGameOngoing = false;
		this.router.navigate(["/Start"]);
	}
	async waitForPlayerMove(): Promise<void> {
		if (!this.playerMadeMove) {
			console.log("Waiting for player to make move.");
			await this.sleep(this.playerTimeout);
			await this.waitForPlayerMove();
		}
		console.log("PLAYER MADE MOVE!!!!");
		this.playerMadeMove = false;
		return;
	}
	async waitForPlayerChooseSegment(): Promise<void> {
		if (!this.playerChooseSegment) {
			console.log("Waiting for player to choose segment.");
			await this.sleep(this.playerTimeout);
			await this.waitForPlayerChooseSegment();
		}
		console.log("PLAYER CHOOSE SEGMENT!!!!");
		this.playerChooseSegment = false;
		return;
	}
	//#endregion

	//#region CoreGameMethods
	async makeMove(boardId: number, segmentId: number): Promise<void> {
		let result = await firstValueFrom(this.httpClient.postMakeMove(boardId, segmentId));
	}
	async updateBoard(): Promise<void> {
		let result = await firstValueFrom(this.httpClient.getBoardState());
		this.gameBoard.update(result);
	}
	//#endregion

	async mainGameLoop(): Promise<void> {
		console.log("Starting game main loop");
		while (this.isGameOngoing) {
			this.setIsProcessing(true);
			console.log("Running loop iteration");
			switch (await firstValueFrom(this.httpClient.getGameStage(GameStage.EnemyTurn))) {
				case GameStage.PlayerTurn:
					this.setIsProcessing(false);
					// await this.updateBoard();
					await this.waitForPlayerMove();
					//UnlockSegment
					//WaitForUserToMakeMove
					break;
				case GameStage.PlayerChooseSegment:
					this.setIsProcessing(false);
					// await this.updateBoard();
					//UnlockSegmentChoosing
					//WaitForUserToChooseSegment
					break;
				case GameStage.EnemyTurn:
				case GameStage.EnemyChooseSegment:
					this.setIsProcessing(true);
					await this.sleep(this.enemyTimeout);
					break;
				case GameStage.Finished:
					this.setIsProcessing(false);
					this.isGameOngoing = false;
					break;
			}
		}
	}
}
