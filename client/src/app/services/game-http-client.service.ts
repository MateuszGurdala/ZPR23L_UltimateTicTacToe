import { HttpClient, HttpHeaders } from "@angular/common/http";
import { Injectable } from "@angular/core";

@Injectable({
	providedIn: "root",
})
export class GameHttpClient {
	constructor(private httpClient: HttpClient) {}

	postMove(boardId: number, segmentId: number): void {
		this.httpClient
			.post<any>(
				"http://localhost:1337",
				{
					boardId: boardId,
					segmentId: segmentId,
				},
				{
					headers: {
						"Content-Type": "application/json",
					},
				}
			)
			.subscribe((next) => {
				console.log(next);
			});
	}
}
