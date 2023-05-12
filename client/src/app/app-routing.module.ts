import { NgModule } from "@angular/core";
import { RouterModule, Routes } from "@angular/router";

//Components
import { StartupPageComponent } from "./components/startup-page/startup-page.component";
import { GamePageComponent } from "./components/game-page/game-page.component";
import { StartRouteGuard } from "./services/start-route-guard";
import { GameRouteGuard } from "./services/game-route-guard";

const routes: Routes = [
	{ path: "Start", component: StartupPageComponent, canActivate: [GameRouteGuard] },
	{ path: "Game", component: GamePageComponent, canActivate: [StartRouteGuard] },
	{ path: "**", redirectTo: "/Start" },
];

@NgModule({
	imports: [RouterModule.forRoot(routes)],
	exports: [RouterModule],
})
export class AppRoutingModule {}
