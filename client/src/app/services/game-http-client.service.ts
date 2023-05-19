import { HttpClient } from "@angular/common/http";
import { Injectable } from "@angular/core";
import { Observable, of } from "rxjs";
import { GameBoard, GameMode, GameStage, GameState, Sign } from "../structs";

/*
GETBoardState -> zwraca cała plansza z podplanszami i segmentami oraz ich znakami
GETGameState -> kto wygrywa jaką podplanszę + kto teraz wykonuje ruch (metadane rozgrywki)
POSTMakeMove -> jak nazwa wskazuje
POSTCreateGame -> tworzy planszę z wybranym przeciwnikiem
GETStartGame -> rozpoczyna rozgrywkę
GETEndGame -> jak nazwa wskazuje
GETTestConnection -> sprawdza czy serwer pod danym url odpowiada
*/

@Injectable({
	providedIn: "root",
})
export class GameHttpClient {
	private url: string = "http://localhost:1337";

	constructor(private httpClient: HttpClient) {}

	setServerUrl(url: string): void {
		this.url = "http://" + url;
	}

	//#region POST
	postMakeMove(boardId: number, segmentId: number): Observable<any> {
		return this.httpClient.post<any>(this.url + "MakeMove", {
			boardId: boardId,
			segmentId: segmentId,
		});
	}
	postCreateGame(mode: GameMode, sign: Sign, size: number): Observable<boolean> {
		//MOCK
		return of(true);
	}
	postPickSegment(segmentNumber: number): Observable<boolean> {
		//MOCK
		return of(true);
	}
	postEndGame(): Observable<boolean> {
		//MOCk
		return of(true);
	}
	//#endregion

	//#region GET
	getBoardState(): Observable<GameBoard> {
		return this.httpClient.get<GameBoard>(this.url + "/BoardState");
	}
	getServerStatus(): Observable<boolean> {
		//MOCK
		return of(true);
	}
	getGameState(mockState: GameState): Observable<GameState> {
		//MOCK
		return of(mockState);
	}
	getGameStage(mockStage: GameStage): Observable<GameStage> {
		//TODO: Change to be http based
		return of(mockStage);
	}
	//#endregion
}
