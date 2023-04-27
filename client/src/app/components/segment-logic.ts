import { AfterContentInit, Component, Input } from "@angular/core";
import { GameBoardComponent } from "./game-board/game-board.component";

@Component({
	selector: "",
	template: "",
})
export class SegmentLogic implements AfterContentInit {
	@Input("id") setId: number;
	parent: GameBoardComponent;

	id: number | undefined = undefined;
	isActive: boolean | undefined = undefined;
	ownerSign: "X" | "O" | undefined = undefined;

	ngAfterContentInit(): void {
		this.id = this.setId;
	}
}
