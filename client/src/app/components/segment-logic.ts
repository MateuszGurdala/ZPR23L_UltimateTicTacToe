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
	isActive: boolean;
	ownerSign: "X" | "O" | " " = " ";

	ngAfterContentInit(): void {
		this.id = this.setId;
	}

	setIsActive(value: boolean): void {
		this.isActive = value;
	}

	isOwned(): boolean {
		return this.ownerSign !== " ";
	}

	unlockSegment(number: number): void {
		if (!this.isOwned()) {
			this.setIsActive(true);
		}
	}
}
