import { NgModule } from "@angular/core";
import { BrowserModule } from "@angular/platform-browser";

import { AppRoutingModule } from "./app-routing.module";
import { AppComponent } from "./components/app/app.component";
import { GameBoardComponent } from "./components/game-board/game-board.component";
import { BoardSegmentComponent } from "./components/board-segment/board-segment.component";
import { CreateBoardDirective } from "./directives/create-board.directive";
import { GameHttpClient } from "./services/game-http-client.service";
import { HttpClientModule } from "@angular/common/http";
import { SettingsBarComponent } from "./components/settings-bar/settings-bar.component";
import { GameMasterService } from "./services/game-master.service";
import { StartupPageComponent } from "./components/startup-page/startup-page.component";
import { GamePageComponent } from "./components/game-page/game-page.component";
import { HoverReactDirective } from "./directives/hover-react.directive";
import { FormsModule } from "@angular/forms";

@NgModule({
	declarations: [
		AppComponent,
		GameBoardComponent,
		BoardSegmentComponent,
		CreateBoardDirective,
		SettingsBarComponent,
		StartupPageComponent,
		GamePageComponent,
		HoverReactDirective,
	],
	imports: [BrowserModule, AppRoutingModule, HttpClientModule, FormsModule],
	providers: [GameMasterService, GameHttpClient],
	bootstrap: [AppComponent],
})
export class AppModule {}
