import { AfterContentInit, Component, Input } from "@angular/core";

@Component({
	selector: "game-board",
	templateUrl: "./game-board.component.html",
	styleUrls: ["./game-board.component.css"],
})
export class GameBoardComponent implements AfterContentInit {
	@Input("type") boardClass: "Motherboard" | "Daughterboard";
	@Input() size: number;

	isMotherboard: boolean = false;
	childrenCount: number[];

	constructor() {}

	ngAfterContentInit(): void {
		this.isMotherboard = this.boardClass == "Motherboard" ? true : false;
		this.childrenCount = Array.from({ length: this.size * this.size }, (x, i) => ++i);
		console.log();
	}
}
