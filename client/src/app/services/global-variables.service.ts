import { Injectable } from "@angular/core";
import { GameMode, GameStage, GameState, Sign } from "../structs";
import { firstValueFrom } from "rxjs";
import { GameHttpClient } from "./game-http-client.service";

@Injectable({
	providedIn: "root",
})
export class GlobalVariablesService {
	private gameStage: GameStage;
	private gameState: GameState = GameState.Unknown;
	isGameOngoing: boolean;
	isProcessing: boolean;
	playerMadeMove: boolean;
	playerChoseSegment: boolean;
	currentSegment: number | undefined = 5;
	boardSize: number = 3;
	playerSign: Sign = Sign.X;
	gameMode: GameMode = GameMode.SinglePlayer;

	gameStagePub: GameStage = GameStage.PlayerChooseSegment; //TODO: Remove

	constructor(private readonly httpClient: GameHttpClient) {}

	isPlayerTurn(): boolean {
		return this.gameStage === GameStage.PlayerTurn;
	}

	playerChooseSegment(): boolean {
		return this.gameStage === GameStage.PlayerChooseSegment;
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
	async getGameState(mockState: GameState): Promise<GameState> {
		this.gameState = await firstValueFrom(this.httpClient.getGameState(mockState));
		return this.gameState;
	}
	async getGameStage(mockStage: GameStage): Promise<GameStage> {
		this.gameStage = await firstValueFrom(this.httpClient.getGameStage(mockStage));
		this.gameStagePub = this.gameStage;
		return this.gameStage;
	}
}
