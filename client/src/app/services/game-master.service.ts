import { Injectable } from "@angular/core";
import { GameHttpClient } from "./game-http-client.service";
import { GameBoardComponent } from "../components/game-board/game-board.component";
import { GameMode, GameState, Sign } from "../structs";
import { firstValueFrom } from "rxjs";
import { Router } from "@angular/router";

@Injectable({
	providedIn: "root",
})
export class GameMasterService {
	gameBoard: GameBoardComponent;
	gameState: GameState;
	boardSize: number;
	playerSign: Sign;

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
	//#endregion

	//#region Utils
	async getGameState(): Promise<GameState> {
		this.gameState = await firstValueFrom(this.httpClient.getGameState());
		return this.gameState;
	}
	async canStartGame(): Promise<boolean> {
		if (this.gameState === GameState.Unknown) {
			this.gameState = await this.getGameState();
		}
		return this.gameState === GameState.Ready;
	}
	async isPlayer(): Promise<boolean> {
		if (this.gameState === GameState.Unknown) {
			this.gameState = await this.getGameState();
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
	//#endregion

	//#region CoreGameMethods
	async makeMove(boardId: number, segmentId: number): Promise<void> {
		let result = await firstValueFrom(this.httpClient.postMove(boardId, segmentId));
	}
	async updateBoard(): Promise<void> {
		let result = await firstValueFrom(this.httpClient.getBoardState());
		this.gameBoard.update(result);
	}
	//#endregion

	async startNewSoloGame(): Promise<void> {
		if (await firstValueFrom(this.httpClient.postRequestGameCreation(GameMode.SinglePlayer))) {
			// await this.getGameState();
			this.gameState = GameState.PlayerSolo;
			this.router.navigate(["/Game"]);
			await this.mainGameLoop();
		}
	}
	endGame(): void {
		this.gameState = GameState.Ready;
		this.router.navigate(["/Start"]);
	}

	async mainGameLoop(): Promise<void> {}
}
