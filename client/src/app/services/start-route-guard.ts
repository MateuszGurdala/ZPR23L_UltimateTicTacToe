import { inject } from "@angular/core";
import { ActivatedRouteSnapshot, CanActivateFn, Router, RouterStateSnapshot } from "@angular/router";
import { GameMasterService } from "./game-master.service";

export const StartRouteGuard: CanActivateFn = async (
	next: ActivatedRouteSnapshot,
	state: RouterStateSnapshot
) => {
	let gameMaster = inject<GameMasterService>(GameMasterService);
	let router = inject<Router>(Router);

	if (await gameMaster.canStartGame()) {
		router.navigate(["/Start"]);
		return false;
	} else {
		return true;
	}
};
