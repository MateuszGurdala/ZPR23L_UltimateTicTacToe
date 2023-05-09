import { Component, ElementRef, Input } from "@angular/core";
import { GameMasterService } from "../../services/game-master.service";
@Component({
	selector: "startup-page",
	templateUrl: "./startup-page.component.html",
	styleUrls: ["./startup-page.component.css"],
})
export class StartupPageComponent {
	displayWelcome: boolean = false;
	displayOptions: boolean = true;
	preferredSign: "X" | "O" = "X";
	xIsChosen: boolean = true;

	constructor(private master: GameMasterService) {}

	returnClick(): void {
		this.displayWelcome = true;
		this.displayOptions = false;
	}

	optionsClick(): void {
		this.displayWelcome = false;
		this.displayOptions = true;
	}

	selectSign(arg: PointerEvent | MouseEvent): void {
		this.preferredSign = (arg.target as HTMLElement).innerHTML as "X" | "O";

		this.xIsChosen = this.preferredSign == "X";
	}
}
