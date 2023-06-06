import { Injectable } from "@angular/core";
import { GameMode, GameStage, GameStageResponse, GameState, Sign } from "../structs";
import { firstValueFrom } from "rxjs";
import { GameHttpClient } from "./game-http-client.service";

@Injectable({
	providedIn: "root",
})
export class GlobalVariablesService {
	readonly baseSignSize: number = 9;
	private gameState: GameState = GameState.Unknown;
	gameStage: GameStage = GameStage.Unknown;
	isGameOngoing: boolean;
	isProcessing: boolean;
	playerMadeMove: boolean;
	playerChoseSegment: boolean;
	currentSegment: number | undefined;
	boardSize: number = 3;
	playerSign: Sign = Sign.X;
	gameMode: GameMode = GameMode.SinglePlayer;

	constructor(private readonly httpClient: GameHttpClient) {}

	isPlayerTurn(): boolean {
		return this.gameStage === GameStage.PlayerTurn;
	}

	playerChooseSegment(): boolean {
		return this.gameStage === GameStage.PlayerChooseSegment;
	}

	async canStartGame(): Promise<boolean> {
		this.gameState = await this.getGameState();
		return this.gameState === GameState.Ready;
	}
	async isPlayer(): Promise<boolean> {
		await this.getGameState();

		switch (this.gameState) {
			case GameState.Ready:
			case GameState.Waiting:
			case GameState.Ongoing:
			case GameState.Unknown:
				return false;
			case GameState.PlayerSolo:
			case GameState.PlayerX:
			case GameState.PlayerO:
				await this.updateBoardSize();
				return true;
		}
	}
	async getGameState(): Promise<GameState> {
		this.gameState = await firstValueFrom(await this.httpClient.getGameState());
		switch (this.gameState) {
			case GameState.PlayerSolo:
				this.isGameOngoing = true;
				break;
			case GameState.PlayerX:
				this.playerSign = Sign.X;
				this.isGameOngoing = true;
				break;
			case GameState.PlayerO:
				this.playerSign = Sign.O;
				this.isGameOngoing = true;
				break;
		}
		return this.gameState;
	}
	async getGameStage(): Promise<GameStage> {
		this.gameStage = this.parseResponseGameStage(await this.httpClient.getGameStage());
		return this.gameStage;
	}

	async getCurrentSegment(): Promise<number> {
		if (this.currentSegment === undefined) {
			this.currentSegment = await firstValueFrom(this.httpClient.getCurrentSegment());
			this.currentSegment += 1;
		}
		return this.currentSegment;
	}
	parseResponseGameStage(response: GameStageResponse): GameStage {
		switch (response) {
			case GameStageResponse.Unknown:
				return GameStage.Unknown;
			case GameStageResponse.Finished:
				return GameStage.Finished;
			case GameStageResponse.PlayerX:
			case GameStageResponse.PlayerO:
				return response[7] == this.playerSign ? GameStage.PlayerTurn : GameStage.EnemyTurn;
			case GameStageResponse.PlayerXSegment:
			case GameStageResponse.PlayerOSegment:
				return response[7] == this.playerSign ? GameStage.PlayerChooseSegment : GameStage.EnemyChooseSegment;
		}
	}
	async updateBoardSize(): Promise<void> {
		this.boardSize = await firstValueFrom(this.httpClient.getBoardSize());
		this.boardSize = this.boardSize === -1 ? 3 : this.boardSize;
	}
}
