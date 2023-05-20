import { inject } from "@angular/core";
import { ActivatedRouteSnapshot, CanActivateFn, Router, RouterStateSnapshot } from "@angular/router";
import { GlobalVariablesService } from "./global-variables.service";

export const StartRouteGuard: CanActivateFn = async (
	next: ActivatedRouteSnapshot,
	state: RouterStateSnapshot
) => {
	let gVars = inject<GlobalVariablesService>(GlobalVariablesService);
	let router = inject<Router>(Router);

	if (await gVars.canStartGame()) {
		router.navigate(["/Start"]);
		return false;
	} else {
		return true;
	}
};
