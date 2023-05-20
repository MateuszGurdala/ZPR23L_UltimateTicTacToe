import { AfterContentInit, Component, Input } from "@angular/core";
import { SegmentLogic } from "../segment-logic";
import { DaughterBoard, GameBoard } from "src/app/structs";
import { BoardSegmentComponent } from "../board-segment/board-segment.component";
import { GameMasterService } from "src/app/services/game-master.service";
import { GlobalVariablesService } from "../../services/global-variables.service";
import { GameStage } from "../../structs";

@Component({
	selector: "game-board",
	templateUrl: "./game-board.component.html",
	styleUrls: ["./game-board.component.css"],
})
export class GameBoardComponent extends SegmentLogic implements AfterContentInit {
	@Input("type") boardClass: "Motherboard" | "Daughterboard"; //Can't be enum
	@Input("parent") parentComponent: GameBoardComponent | undefined = undefined;
	@Input() size: number;

	childrenCount: number[];
	segments: Array<GameBoardComponent | BoardSegmentComponent>;
	segmentChoosing: boolean = false;

	constructor(private readonly master: GameMasterService, private readonly gVars: GlobalVariablesService) {
		super();
	}

	override ngAfterContentInit(): void {
		this.id = this.setId;
		this.childrenCount = Array.from({ length: this.size * this.size }, (x, i) => ++i);

		if (this.boardClass == "Motherboard") {
			this.master.setBoardComponent(this);
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
			let segmentComponent = this.segments.at(segment.id);
			if (segmentComponent !== undefined) {
				segmentComponent.update(segment);
			}
		});
	}

	isMotherBoard(): boolean {
		return this.boardClass === "Motherboard";
	}

	isDaughterBoard(): boolean {
		return this.boardClass === "Daughterboard";
	}

	override setIsActive(value: boolean): void {
		this.segments.forEach((segment: GameBoardComponent | BoardSegmentComponent) => {
			segment.setIsActive(value);
		});
	}

	override unlockSegment(number: number): void {
		switch (this.boardClass) {
			case "Motherboard":
				this.segments[number - 1].unlockSegment(number);
				break;
			case "Daughterboard":
				if (!this.isOwned()) {
					this.segments.forEach((segment: any) => {
						segment.unlockSegment(number);
					});
				}
				break;
		}
	}

	unlockSegmentChoosing(): void {
		if (this.isMotherBoard()) {
			this.segments.forEach((segment) => {
				segment.unlockSegment(-1);
			});
		}
	}

	onEnter(): void {
		if (this.isDaughterBoard() && this.gVars.playerChooseSegment()) {
			this.segments.forEach((segment) => {
				(<BoardSegmentComponent>segment).pseudoHoverState = true;
			});
		}
	}
	onLeave(): void {
		if (this.isDaughterBoard() && this.gVars.playerChooseSegment()) {
			this.segments.forEach((segment) => {
				(<BoardSegmentComponent>segment).pseudoHoverState = false;
			});
		}
	}

	onDaughterboardClick(): void {
		if (this.gVars.playerChooseSegment()) {
			this.gVars.currentSegment = this.id;
			this.master.signalPlayerChoseSegment();
		}
	}
}
