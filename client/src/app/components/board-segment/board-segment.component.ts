import { AfterContentInit, Component, Host } from "@angular/core";
import { SegmentLogic } from "../segment-logic";
import { GameBoardComponent } from "../game-board/game-board.component";
import { GameMasterService } from "src/app/services/game-master.service";
import { Segment } from "src/app/structs";
import { GlobalVariablesService } from "../../services/global-variables.service";

@Component({
	selector: "board-segment",
	templateUrl: "./board-segment.component.html",
	styleUrls: ["./board-segment.component.css"],
})
export class BoardSegmentComponent extends SegmentLogic implements AfterContentInit {
	pseudoHoverState: boolean = false;

	constructor(
		@Host() parent: GameBoardComponent,
		private readonly master: GameMasterService,
		private readonly gVars: GlobalVariablesService
	) {
		super();
		this.parent = parent;
	}

	override ngAfterContentInit(): void {
		this.id = this.setId;
		this.parent.subscribe(this);
	}

	onClick() {
		if (!this.gVars.isPlayerTurn()) {
			return;
		}

		if (this.isActive) {
			this.ownerSign = this.gVars.playerSign;
			this.master.signalPlayerMove();
		}
		this.setIsActive(false);
		//TODO: Send POST to server
	}

	update(state: Segment): void {
		this.ownerSign = state.winner;
	}
}
