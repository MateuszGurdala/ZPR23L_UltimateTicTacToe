import { HttpClient } from "@angular/common/http";
import { Injectable } from "@angular/core";
import { Observable } from "rxjs";
import { GameBoard } from "../structs";

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

	mockFun() {
		console.log("click");
		this.getBoardState();
	}
}
