import { Component } from "@angular/core";
import { GameMasterService } from "src/app/services/game-master.service";
import { GlobalVariablesService } from "src/app/services/global-variables.service";
import { GameMode } from "../../structs";

@Component({
	selector: "settings-bar",
	templateUrl: "./settings-bar.component.html",
	styleUrls: ["./settings-bar.component.css"],
})
export class SettingsBarComponent {
	isExtended: boolean = false;

	constructor(private master: GameMasterService, readonly gVars: GlobalVariablesService) {}

	extend() {
		this.isExtended = !this.isExtended;
	}

	endGame(): void {
		this.master.endGame();
	}
}
