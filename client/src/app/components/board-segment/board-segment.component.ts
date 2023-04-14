import { AfterContentInit, Component, Host } from "@angular/core";
import { SegmentLogic } from "../segment-logic";
import { GameBoardComponent } from "../game-board/game-board.component";
import { GameMasterService } from "src/app/services/game-master.service";

@Component({
	selector: "board-segment",
	templateUrl: "./board-segment.component.html",
	styleUrls: ["./board-segment.component.css"],
})
export class BoardSegmentComponent extends SegmentLogic implements AfterContentInit {
	private parent: GameBoardComponent;

	constructor(@Host() parent: GameBoardComponent, private gameMaster: GameMasterService) {
		super();
		this.parent = parent;
	}

	onClick() {
		// if (!this.isActive) {
		// 	return;
		// }

		this.ownerSign = "O";

		if (this.parent.id !== undefined && this.id !== undefined) {
			this.gameMaster.makeMove(this.parent.id, this.id);
		}
	}
}
