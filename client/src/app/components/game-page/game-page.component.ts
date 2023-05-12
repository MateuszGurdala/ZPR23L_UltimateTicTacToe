import { Component } from "@angular/core";
import { GameMasterService } from "../../services/game-master.service";

@Component({
	selector: "game-page",
	templateUrl: "./game-page.component.html",
	styleUrls: ["./game-page.component.css"],
})
export class GamePageComponent {
	size: number;

	constructor(private master: GameMasterService) {
		this.size = master.boardSize;
	}
}
