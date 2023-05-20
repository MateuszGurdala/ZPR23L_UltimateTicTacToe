import { inject } from "@angular/core";
import { ActivatedRouteSnapshot, CanActivateFn, Router, RouterStateSnapshot } from "@angular/router";
import { GlobalVariablesService } from "./global-variables.service";

export const GameRouteGuard: CanActivateFn = async (
	next: ActivatedRouteSnapshot,
	state: RouterStateSnapshot
) => {
	let gVars = inject<GlobalVariablesService>(GlobalVariablesService);
	let router = inject<Router>(Router);

	if (await gVars.isPlayer()) {
		router.navigate(["/Game"]);
		return false;
	} else {
		return true;
	}
};
