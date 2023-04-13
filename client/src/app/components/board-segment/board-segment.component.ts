import { AfterContentInit, Component, Host, Input } from "@angular/core";
import { SegmentLogic } from "../segment-logic";
import { GameBoardComponent } from "../game-board/game-board.component";

@Component({
	selector: "board-segment",
	templateUrl: "./board-segment.component.html",
	styleUrls: ["./board-segment.component.css"],
})
export class BoardSegmentComponent extends SegmentLogic implements AfterContentInit {
	private parent: GameBoardComponent;

	constructor(@Host() parent: GameBoardComponent) {
		super();
		this.parent = parent;
	}

	onClick() {
		console.log("ParentId: " + this.parent.id);
		console.log("SelfId: " + this.id);
	}
}
