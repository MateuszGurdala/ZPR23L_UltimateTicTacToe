import { HttpClient } from "@angular/common/http";
import { Injectable } from "@angular/core";
import { Observable } from "rxjs";

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

	getBoardState(): Observable<any> {
		return this.httpClient.get<any>(this.url + "Board");
	}

	getGameState(): Observable<any> {
		return this.httpClient.get<any>(this.url + "State");
	}
}
