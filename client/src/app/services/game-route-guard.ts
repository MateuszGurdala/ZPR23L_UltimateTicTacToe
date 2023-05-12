import { inject } from "@angular/core";
import { ActivatedRouteSnapshot, CanActivateFn, Router, RouterStateSnapshot } from "@angular/router";
import { GameMasterService } from "./game-master.service";

export const GameRouteGuard: CanActivateFn = async (
	next: ActivatedRouteSnapshot,
	state: RouterStateSnapshot
) => {
	let gameMaster = inject<GameMasterService>(GameMasterService);
	let router = inject<Router>(Router);

	if (await gameMaster.isPlayer()) {
		router.navigate(["/Game"]);
		return false;
	} else {
		return true;
	}
};
