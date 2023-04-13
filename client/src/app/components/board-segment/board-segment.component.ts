import { AfterContentInit, Component, Host, Input } from "@angular/core";
import { SegmentLogic } from "../segment-logic";
import { GameBoardComponent } from "../game-board/game-board.component";
import { GameHttpClient } from "src/app/services/game-http-client.service";

@Component({
	selector: "board-segment",
	templateUrl: "./board-segment.component.html",
	styleUrls: ["./board-segment.component.css"],
})
export class BoardSegmentComponent extends SegmentLogic implements AfterContentInit {
	private parent: GameBoardComponent;

	constructor(@Host() parent: GameBoardComponent, private gameClient: GameHttpClient) {
		super();
		this.parent = parent;
	}

	onClick() {
		if (this.parent.id !== undefined && this.id !== undefined) {
			this.gameClient.postMove(this.parent.id, this.id);
		}
	}
}
