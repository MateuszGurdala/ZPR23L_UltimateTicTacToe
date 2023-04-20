import { Injectable } from "@angular/core";
import { GameHttpClient } from "./game-http-client.service";

/*
GetGameState
GetBoardState
MakeMove
CreateBoard
EndGame
*/

@Injectable({
	providedIn: "root",
})
export class GameMasterService {
	constructor(private httpClient: GameHttpClient) {}

	makeMove(boardId: number, segmentId: number): void {
		this.httpClient.postMove(boardId, segmentId).subscribe((next) => {
			console.log(next);
		});
	}

	getGameState(): void {}
}
