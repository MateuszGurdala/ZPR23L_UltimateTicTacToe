import { Component } from "@angular/core";
import { GameMasterService } from "../../services/game-master.service";
@Component({
	selector: "startup-page",
	templateUrl: "./startup-page.component.html",
	styleUrls: ["./startup-page.component.css"],
})
export class StartupPageComponent {
	displayWelcome: boolean = false;
	displayOptions: boolean = false;

	constructor(private master: GameMasterService) {}

	returnClick(): void {
		this.displayWelcome = true;
	}

	optionsClick(): void {
		this.displayWelcome = false;
	}
}
