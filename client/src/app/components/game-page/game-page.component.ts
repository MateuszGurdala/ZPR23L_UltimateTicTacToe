import { Component } from "@angular/core";
import { GameMasterService } from "../../services/game-master.service";
import { GlobalVariablesService } from "../../services/global-variables.service";

@Component({
	selector: "game-page",
	templateUrl: "./game-page.component.html",
	styleUrls: ["./game-page.component.css"],
})
export class GamePageComponent {
	size: number;

	constructor(private readonly gVars: GlobalVariablesService) {
		this.size = this.gVars.boardSize;
	}
}
