import { NgModule } from "@angular/core";
import { RouterModule, Routes } from "@angular/router";

//Components
import { StartupPageComponent } from "./components/startup-page/startup-page.component";
import { GamePageComponent } from "./components/game-page/game-page.component";
import { RouteGuard } from "./services/route-guard";

const routes: Routes = [
	{ path: "Start", component: StartupPageComponent },
	{ path: "Game", component: GamePageComponent, canActivate: [RouteGuard] },
	{ path: "**", redirectTo: "/Start" },
];

@NgModule({
	imports: [RouterModule.forRoot(routes)],
	exports: [RouterModule],
})
export class AppRoutingModule {}
