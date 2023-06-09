import { HttpClient } from "@angular/common/http";
import { Injectable } from "@angular/core";
import { Observable, catchError, firstValueFrom, of } from "rxjs";
import {
	EndGameResponse,
	GameBoard,
	GameMode,
	GameStageResponse,
	GameState,
	MoveResponse,
	Sign,
} from "../structs";

@Injectable({
	providedIn: "root",
})
export class GameHttpClient {
	// private url: string = "http://{reverse_proxy_ip}:12345/backend";
	private url: string = "http://localhost:1337/";

	constructor(private httpClient: HttpClient) {}

	setServerUrl(url: string): void {
		this.url = "http://" + url;
	}

	//#region POST
	async postMakeMove(boardId: number, segmentId: number): Promise<Observable<boolean>> {
		let response: MoveResponse = await firstValueFrom(
			this.httpClient.get<MoveResponse>(this.url + "MakeMove", {
				withCredentials: true,
				params: {
					boardId: boardId,
					segmentId: segmentId,
				},
			})
		);

		return of(response.isMoveValid);
	}
	async postCreateGame(mode: GameMode, sign: Sign, size: number): Promise<boolean> {
		await new Promise((r) => setTimeout(r, 1000));

		return await firstValueFrom(
			this.httpClient.get<boolean>(this.url + "CreateGame", {
				withCredentials: true,
				params: {
					gameMode: mode,
					playerSign: sign,
					boardSize: size,
				},
			})
		);
	}
	postPickSegment(segmentNumber: number): Observable<boolean> {
		/* Deprecated */
		return this.httpClient.get<boolean>(this.url + "/PickSegment", {
			withCredentials: true,
			params: {
				segmentId: segmentNumber,
			},
		});
	}
	//#endregion

	//#region GET
	getBoardState(): Observable<GameBoard> {
		return this.httpClient.get<GameBoard>(this.url + "BoardState", { withCredentials: true });
	}
	getServerStatus(): Observable<boolean> {
		return this.httpClient.get<any>(this.url + "ServerStatus");
	}
	async getGameState(): Promise<Observable<GameState>> {
		return await this.httpClient.get<GameState>(this.url + "ServerState", { withCredentials: true });
	}
	async getGameStage(): Promise<GameStageResponse> {
		return (await firstValueFrom(
			this.httpClient.get(this.url + "GameStage", {
				withCredentials: true,
				responseType: "text",
			})
		)) as GameStageResponse;
	}
	async getEndGame(): Promise<Observable<boolean>> {
		await firstValueFrom(
			this.httpClient.get<EndGameResponse>(this.url + "EndGame", { withCredentials: true })
		);
		return of(true);
	}
	getJoinGame(): Observable<boolean | Sign> {
		return this.httpClient.get<any>(this.url + "JoinGame", { withCredentials: true });
	}
	getCurrentSegment(): Observable<number> {
		return this.httpClient.get<number>(this.url + "CurrentSegment", { withCredentials: true });
	}
	getBoardSize(): Observable<number> {
		return this.httpClient.get<number>(this.url + "BoardSize");
	}
	//#endregion
}
