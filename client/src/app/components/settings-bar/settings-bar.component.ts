import { Component } from "@angular/core";
import { GameMasterService } from "src/app/services/game-master.service";

@Component({
	selector: "settings-bar",
	templateUrl: "./settings-bar.component.html",
	styleUrls: ["./settings-bar.component.css"],
})
export class SettingsBarComponent {
	isExtended: boolean = false;
	boardSize: string = "3";
	serverUrl: string = "localhost:4200";

	constructor(private game: GameMasterService) {}

	extend() {
		this.isExtended = !this.isExtended;
	}

	test() {
		this.game.updateBoard();
	}
}
