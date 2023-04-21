import { HttpClient } from "@angular/common/http";
import { Injectable } from "@angular/core";
import { Observable } from "rxjs";
import { GameBoard } from "../structs";

@Injectable({
	providedIn: "root",
})
export class GameHttpClient {
	url: string = "http://localhost:1337";

	constructor(private httpClient: HttpClient) {}

	postMove(boardId: number, segmentId: number): Observable<any> {
		return this.httpClient.post<any>(this.url, {
			boardId: boardId,
			segmentId: segmentId,
		});
	}

	getBoardState(): Observable<GameBoard> {
		return this.httpClient.get<GameBoard>(this.url + "/BoardState");
	}
}
