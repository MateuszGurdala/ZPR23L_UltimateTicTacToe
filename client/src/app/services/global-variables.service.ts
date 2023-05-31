import { Injectable } from "@angular/core";
import { GameMode, GameStage, GameState, Sign } from "../structs";
import { firstValueFrom } from "rxjs";
import { GameHttpClient } from "./game-http-client.service";

@Injectable({
	providedIn: "root",
})
export class GlobalVariablesService {
	private gameStage: GameStage = GameStage.Unknown;
	private gameState: GameState = GameState.Unknown;
	isGameOngoing: boolean;
	isProcessing: boolean;
	playerMadeMove: boolean;
	playerChoseSegment: boolean;
	currentSegment: number | undefined = 5;
	boardSize: number = 3;
	playerSign: Sign = Sign.X;
	gameMode: GameMode = GameMode.SinglePlayer;

	//TODO: Remove
	gameStagePub: GameStage = GameStage.PlayerChooseSegment;
	enemySign: Sign = Sign.O;

	constructor(private readonly httpClient: GameHttpClient) {}

	isPlayerTurn(): boolean {
		return this.gameStage === GameStage.PlayerTurn;
	}

	playerChooseSegment(): boolean {
		return this.gameStage === GameStage.PlayerChooseSegment;
	}

	async canStartGame(): Promise<boolean> {
		if (this.gameState === GameState.Unknown) {
			this.gameState = await this.getGameState();
		}
		return this.gameState === GameState.Ready;
	}
	async isPlayer(): Promise<boolean> {
		if (this.gameState === GameState.Unknown) {
			await this.getGameState();
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
	async getGameState(): Promise<GameState> {
		this.gameState = await firstValueFrom(await this.httpClient.getGameState());
		switch (this.gameState) {
			case GameState.PlayerSolo:
			case GameState.PlayerX:
			case GameState.PlayerO:
				this.isGameOngoing = true;
				break;
		}
		return this.gameState;
	}
	async getGameStage(): Promise<GameStage> {
		this.gameStage = await firstValueFrom(await this.httpClient.getGameStage());
		this.gameStagePub = this.gameStage;
		console.log(this.gameStagePub);
		return this.gameStage;
	}
}
