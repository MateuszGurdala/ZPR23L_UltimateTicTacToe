import { AfterViewInit, Component, ElementRef, QueryList, ViewChildren } from "@angular/core";
import { GameMasterService } from "src/app/services/game-master.service";
import { GlobalVariablesService } from "src/app/services/global-variables.service";

@Component({
	selector: "settings-bar",
	templateUrl: "./settings-bar.component.html",
	styleUrls: ["./settings-bar.component.css"],
})
export class SettingsBarComponent implements AfterViewInit {
	isExtended: boolean = true;
	private segmentsLookup: Array<ElementRef> = Array<ElementRef>();
	@ViewChildren("s1") segment1: QueryList<any>;
	@ViewChildren("s2") segment2: QueryList<any>;
	@ViewChildren("s3") segment3: QueryList<any>;
	@ViewChildren("s4") segment4: QueryList<any>;
	@ViewChildren("s5") segment5: QueryList<any>;
	@ViewChildren("s6") segment6: QueryList<any>;
	@ViewChildren("s7") segment7: QueryList<any>;
	@ViewChildren("s8") segment8: QueryList<any>;
	@ViewChildren("s9") segment9: QueryList<any>;

	//#region CoreComponentMethods
	constructor(private master: GameMasterService, readonly gVars: GlobalVariablesService) {
		this.master.setSettingsBarComponent(this);
	}
	ngAfterViewInit(): void {
		this.segmentsLookup.push(this.segment1.last);
		this.segmentsLookup.push(this.segment2.last);
		this.segmentsLookup.push(this.segment3.last);
		this.segmentsLookup.push(this.segment4.last);
		this.segmentsLookup.push(this.segment5.last);
		this.segmentsLookup.push(this.segment6.last);
		this.segmentsLookup.push(this.segment7.last);
		this.segmentsLookup.push(this.segment8.last);
		this.segmentsLookup.push(this.segment9.last);
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
		let element = this.segmentsLookup.at(segment)?.nativeElement;
		element.textContent = value;
	}
	//#endregion
}
