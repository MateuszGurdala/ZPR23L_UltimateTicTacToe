import { Injectable } from "@angular/core";
import { GameMode, GameStage, GameState, Sign } from "../structs";

@Injectable({
	providedIn: "root",
})
export class GlobalVariablesService {
	gameStage: GameStage;
	isGameOngoing: boolean;
	isProcessing: boolean;
	playerMadeMove: boolean;
	playerChooseSegment: boolean;
	currentSegment: number | undefined;
	gameState: GameState = GameState.Unknown;
	boardSize: number = 3;
	playerSign: Sign = Sign.X;
	gameMode: GameMode = GameMode.SinglePlayer;

	constructor() {}
}
