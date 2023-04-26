import { AfterContentInit, Component, Host, Input, Optional } from "@angular/core";
import { SegmentLogic } from "../segment-logic";
import { DaughterBoard, GameBoard, Segment } from "src/app/structs";
import { BoardSegmentComponent } from "../board-segment/board-segment.component";
import { GameMasterService } from "src/app/services/game-master.service";

@Component({
	selector: "game-board",
	templateUrl: "./game-board.component.html",
	styleUrls: ["./game-board.component.css"],
})
export class GameBoardComponent extends SegmentLogic implements AfterContentInit {
	@Input("type") boardClass: "Motherboard" | "Daughterboard";
	@Input("parent") parentComponent: GameBoardComponent | undefined = undefined;
	@Input() size: number;

	isMotherboard: boolean = false;
	childrenCount: number[];
	segments: Array<GameBoardComponent | BoardSegmentComponent>;

	constructor(private game: GameMasterService) {
		super();
	}

	override ngAfterContentInit(): void {
		this.id = this.setId;
		this.isMotherboard = this.boardClass == "Motherboard" ? true : false;
		this.childrenCount = Array.from({ length: this.size * this.size }, (x, i) => ++i);

		if (this.boardClass == "Motherboard") {
			this.game.setBoardComponent(this);
			this.segments = Array<GameBoardComponent>();
		} else {
			this.segments = Array<BoardSegmentComponent>();
		}

		if (this.parentComponent !== undefined) {
			this.parent = this.parentComponent;
			this.parent.subscribe(this);
		}
	}

	subscribe(board: GameBoardComponent | BoardSegmentComponent): void {
		this.segments.push(board);
	}

	update(state: GameBoard | DaughterBoard): void {
		state.segments.forEach((segment: any) => {
			let segmentComponent = this.segments.at(segment.id - 1);
			if (segmentComponent !== undefined) {
				segmentComponent.update(segment);
			}
		});
	}
}
