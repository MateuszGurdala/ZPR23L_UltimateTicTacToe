import { Component, ElementRef, ViewChild } from "@angular/core";
import { GameMasterService } from "../../services/game-master.service";
import { Router } from "@angular/router";
import { GameMode, GameState, Sign } from "../../structs";
import { ToastrService } from "ngx-toastr";
import { GlobalVariablesService } from "../../services/global-variables.service";

@Component({
	selector: "startup-page",
	templateUrl: "./startup-page.component.html",
	styleUrls: ["./startup-page.component.css"],
})
export class StartupPageComponent {
	@ViewChild("serverInput") serverURLInput: ElementRef;

	preferredSign: Sign = this.gVars.playerSign;
	boardSize: number = this.gVars.boardSize;
	gameMode: GameMode = this.gVars.gameMode;
	gameModeString: String = "Player_vs_AI";

	isProcessing: boolean = false;
	xIsChosen: boolean = true;
	displayWelcome: boolean = true;

	//#region CoreComponentMethods
	constructor(
		private readonly master: GameMasterService,
		private readonly router: Router,
		private readonly toastr: ToastrService,
		private readonly gVars: GlobalVariablesService
	) {
		this.xIsChosen = this.preferredSign === Sign.X;
	}
	//#endregion

	//#region  Utils
	returnClick(): void {
		this.displayWelcome = true;
	}
	optionsClick(): void {
		this.displayWelcome = false;
	}
	//#endregion

	//#region Setters
	selectSign(arg: PointerEvent | MouseEvent): void {
		let sign = (arg.target as HTMLElement).innerHTML as "X" | "O";
		this.preferredSign = sign === "X" ? Sign.X : Sign.O;

		this.xIsChosen = this.preferredSign == Sign.X;
		this.master.setPlayerSign(this.preferredSign);
	}
	changeGameMode(): void {
		this.gameMode = this.gameModeString == "Player_vs_AI" ? GameMode.SinglePlayer : GameMode.Multiplayer;
		this.master.setGameMode(this.gameMode);
	}
	increaseBoard(): void {
		this.boardSize += 1;
		if (this.boardSize > 5) {
			this.boardSize = 5;
		}
		this.master.setBoardSize(this.boardSize);
	}
	decreaseBoard(): void {
		this.boardSize -= 1;
		if (this.boardSize < 3) {
			this.boardSize = 3;
		}
		this.master.setBoardSize(this.boardSize);
	}
	//#endregion

	//#region GameUtils
	async tryStartGame(): Promise<void> {
		let errorString: any;

		this.isProcessing = true;

		if (typeof (errorString = await this.master.tryStartNewGame()) === "string") {
			this.toastr.error(errorString);
		}

		this.isProcessing = false;
	}
	async tryJoinGame(): Promise<void> {
		this.isProcessing = true;

		if ((await this.gVars.getGameState()) !== GameState.Waiting) {
			this.toastr.error("No one is currently waiting for a second player to join.");
		} else {
			let response = await this.master.tryJoinGame();
			if (response) {
				this.gVars.playerSign = response as Sign;
				this.router.navigate(["/Game"]);
			}
		}
		this.isProcessing = false;
		return;
	}
	//#endregion
}
