import { Injectable } from "@angular/core";
import { GameHttpClient } from "./game-http-client.service";
import { GameBoardComponent } from "../components/game-board/game-board.component";

@Injectable({
	providedIn: "root",
})
export class GameMasterService {
	gameBoard: GameBoardComponent;
	gameState: "Ready" | "Waiting" | "Ongoing" | "PlayerSolo" | "PlayerX" | "PlayerO";

	constructor(private httpClient: GameHttpClient) {
		this.gameState = "Ready";
	}

	setBoardComponent(component: GameBoardComponent): void {
		this.gameBoard = component;
	}

	setServerUrl(url: string): void {
		this.httpClient.url = "http://" + url;
	}

	makeMove(boardId: number, segmentId: number): void {
		this.httpClient.postMove(boardId, segmentId).subscribe((next) => {
			console.log(next);
		});
	}

	updateBoard(): void {
		this.httpClient.getBoardState().subscribe((next) => {
			this.gameBoard.update(next);
		});
	}

	mockFun() {
		return this.httpClient.mockFun();
	}

	CanStartGame(): boolean {
		return this.gameState == "Ready";
	}
}
