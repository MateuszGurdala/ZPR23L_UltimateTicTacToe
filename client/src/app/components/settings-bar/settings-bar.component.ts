import { AfterViewInit, Component, ElementRef, QueryList, ViewChildren } from "@angular/core";
import { GameMasterService } from "src/app/services/game-master.service";
import { GlobalVariablesService } from "src/app/services/global-variables.service";

@Component({
	selector: "settings-bar",
	templateUrl: "./settings-bar.component.html",
	styleUrls: ["./settings-bar.component.css"],
})
export class SettingsBarComponent implements AfterViewInit {
	@ViewChildren("segmentLookup") segmentsLookup: QueryList<any>;
	isExtended: boolean = true;
	childrenCount: number[];
	boardSize: number = this.gVars.boardSize;

	//#region CoreComponentMethods
	constructor(private master: GameMasterService, readonly gVars: GlobalVariablesService) {
		this.master.setSettingsBarComponent(this);
	}
	ngAfterViewInit(): void {
		this.childrenCount = Array.from({ length: this.boardSize * this.boardSize }, (x, i) => ++i);
		console.log(this.segmentsLookup);
	}
	//#endregion

	//#region Utils
	extend(): void {
		this.isExtended = !this.isExtended;
	}
	endGame(): void {
		this.master.endGame();
	}
	updateLookup(segment: number, value: string): void {
		let element = this.segmentsLookup.toArray().at(segment).nativeElement;
		element.textContent = value;
	}
	//#endregion
}
