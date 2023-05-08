import { inject } from "@angular/core";
import { ActivatedRouteSnapshot, CanActivateFn, Router, RouterStateSnapshot } from "@angular/router";
import { GameMasterService } from "./game-master.service";

export const RouteGuard: CanActivateFn = async (next: ActivatedRouteSnapshot, state: RouterStateSnapshot) => {
	let gameMaster = inject<GameMasterService>(GameMasterService);
	let router = inject<Router>(Router);

	console.log(gameMaster.CanStartGame());

	if (gameMaster.CanStartGame()) {
		router.navigate(["/Start"]);
		return false;
	} else {
		return true;
	}
};
