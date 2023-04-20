import { AfterContentInit, Component, Input } from "@angular/core";
import { SegmentLogic } from "../segment-logic";

@Component({
	selector: "game-board",
	templateUrl: "./game-board.component.html",
	styleUrls: ["./game-board.component.css"],
})
export class GameBoardComponent extends SegmentLogic implements AfterContentInit {
	@Input("type") boardClass: "Motherboard" | "Daughterboard";
	@Input() size: number;

	isMotherboard: boolean = false;
	childrenCount: number[];

	override ngAfterContentInit(): void {
		this.id = this.setId;

		this.isMotherboard = this.boardClass == "Motherboard" ? true : false;
		this.childrenCount = Array.from({ length: this.size * this.size }, (x, i) => ++i);
	}
}
