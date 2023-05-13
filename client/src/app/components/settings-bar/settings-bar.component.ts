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
	playerSign: Sign = Sign.X;
	gameMode: GameMode = GameMode.SinglePlayer;
	gameStage: GameStage = GameStage.PlayerTurn;
	isProcessing: boolean = false;

	constructor(private master: GameMasterService) {}

	extend() {
		this.isExtended = !this.isExtended;
	}

	endGame(): void {
		this.master.endGame();
	}
}
