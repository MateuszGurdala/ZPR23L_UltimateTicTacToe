import { Component, ElementRef, ViewChild } from "@angular/core";
import { GameMasterService } from "../../services/game-master.service";
@Component({
	selector: "startup-page",
	templateUrl: "./startup-page.component.html",
	styleUrls: ["./startup-page.component.css"],
})
export class StartupPageComponent {
	@ViewChild("serverInput") serverURLInput: ElementRef;

	displayWelcome: boolean = true;
	preferredSign: "X" | "O" = "X";
	xIsChosen: boolean = true;
	boardSize: number = 3;
	serverURL: string = "localhost:1337";
	enemy: "AI Enemy" | "Player" = "AI Enemy";

	constructor(private master: GameMasterService) {}

	returnClick(): void {
		this.displayWelcome = true;
	}

	optionsClick(): void {
		this.displayWelcome = false;
	}

	selectSign(arg: PointerEvent | MouseEvent): void {
		this.preferredSign = (arg.target as HTMLElement).innerHTML as "X" | "O";

		this.xIsChosen = this.preferredSign == "X";
	}

	increaseBoard(): void {
		this.boardSize += 1;
		if (this.boardSize > 5) {
			this.boardSize = 5;
		}
	}

	decreaseBoard(): void {
		this.boardSize -= 1;
		if (this.boardSize < 3) {
			this.boardSize = 3;
		}
	}

	onInputChange(): void {
		if (this.serverURL === "") {
			this.serverURL = "localhost:1337";
		}
	}
}
