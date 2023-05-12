import { Component, ElementRef, ViewChild } from "@angular/core";
import { GameMasterService } from "../../services/game-master.service";
import { Router } from "@angular/router";
import { Enemy, GameState, Sign } from "../../structs";
import { ToastrService } from "ngx-toastr";
@Component({
	selector: "startup-page",
	templateUrl: "./startup-page.component.html",
	styleUrls: ["./startup-page.component.css"],
})
export class StartupPageComponent {
	@ViewChild("serverInput") serverURLInput: ElementRef;

	displayWelcome: boolean = true;
	preferredSign: Sign = Sign.X;
	xIsChosen: boolean = true;
	boardSize: number = 3;
	serverURL: string = "localhost:1337";
	enemy: Enemy = Enemy.AI;
	isProcessing: boolean = false;

	constructor(private master: GameMasterService, private router: Router, private toastr: ToastrService) {}

	returnClick(): void {
		this.displayWelcome = true;
	}

	optionsClick(): void {
		this.displayWelcome = false;
	}

	selectSign(arg: PointerEvent | MouseEvent): void {
		let sign = (arg.target as HTMLElement).innerHTML as "X" | "O";
		this.preferredSign = sign === "X" ? Sign.X : Sign.O;

		this.xIsChosen = this.preferredSign == Sign.X;
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

	async checkServer(): Promise<boolean> {
		let serverStatus = await this.master.checkServerIsAlive(this.serverURL);

		if (!serverStatus) {
			this.toastr.error(
				"Server is not working or provided url is invalid.",
				"Could not connect to game server."
			);
		}

		return serverStatus;
	}

	async tryStartGame(): Promise<void> {
		this.isProcessing = true;

		if (!(await this.checkServer())) {
			return;
		}

		switch (await this.master.getGameState()) {
			case GameState.Ready:
				//TODO: Start game based on an chosen enemy
				this.master.setBoardSize(this.boardSize);
				this.master.setPlayerSign(this.preferredSign);
				this.master.startNewSoloGame();
				this.router.navigate(["/Game"]);
				break;
			case GameState.Ongoing:
				this.toastr.error("The game is already ongoing.");
				break;
			case GameState.Waiting:
				this.toastr.error("Someone has already created a new game.");
				this.toastr.info("Maybe you should join him?");
				break;
			default:
				this.router.navigate(["/Game"]);
				break;
		}

		this.isProcessing = false;
	}

	async tryJoinGame(): Promise<void> {
		this.isProcessing = true;

		if (!(await this.checkServer())) {
			return;
		}

		if ((await this.master.getGameState()) !== GameState.Waiting) {
			this.toastr.error("No one is currently waiting for a second player to join.");
		} else {
			//TODO: Add logic for joining another player's game
			this.router.navigate(["/Game"]);
		}
		this.isProcessing = false;
		return;
	}
}
