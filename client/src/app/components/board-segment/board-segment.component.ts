import { AfterContentInit, Component, Host } from "@angular/core";
import { SegmentLogic } from "../segment-logic";
import { GameBoardComponent } from "../game-board/game-board.component";
import { GameMasterService } from "src/app/services/game-master.service";
import { Segment } from "src/app/structs";

@Component({
	selector: "board-segment",
	templateUrl: "./board-segment.component.html",
	styleUrls: ["./board-segment.component.css"],
})
export class BoardSegmentComponent extends SegmentLogic implements AfterContentInit {
	constructor(@Host() parent: GameBoardComponent, private master: GameMasterService) {
		super();
		this.parent = parent;
	}

	override ngAfterContentInit(): void {
		this.id = this.setId;
		this.parent.subscribe(this);
	}

	onClick() {
		this.ownerSign = this.master.playerSign;
		this.master.playerMadeMove = true;
		// if (this.parent.id !== undefined && this.id !== undefined) {
		// 	this.master.makeMove(this.parent.id, this.id);
		// }
	}

	update(state: Segment): void {
		this.ownerSign = state.winner;
	}
}
