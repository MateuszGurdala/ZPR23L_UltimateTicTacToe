import { Component } from "@angular/core";
import { GameMasterService } from "src/app/services/game-master.service";
import { GameMode, GameStage, Sign } from "../../structs";

@Component({
	selector: "settings-bar",
	templateUrl: "./settings-bar.component.html",
	styleUrls: ["./settings-bar.component.css"],
})
export class SettingsBarComponent {
	isExtended: boolean = false;
	playerSign: Sign = this.master.playerSign;
	gameMode: GameMode = this.master.gameMode;
	gameStage: GameStage = GameStage.PlayerTurn;
	isProcessing: boolean;

	constructor(private master: GameMasterService) {
		this.isProcessing = this.master.isProcessing;
	}

	extend() {
		this.isExtended = !this.isExtended;
	}

	endGame(): void {
		this.master.endGame();
	}
}
