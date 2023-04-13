import { NgModule } from "@angular/core";
import { BrowserModule } from "@angular/platform-browser";

import { AppRoutingModule } from "./app-routing.module";
import { AppComponent } from "./components/app/app.component";
import { GameBoardComponent } from "./components/game-board/game-board.component";
import { BoardSegmentComponent } from "./components/board-segment/board-segment.component";
import { CreateBoardDirective } from "./directives/create-board.directive";
import { GameHttpClient } from "./services/game-http-client.service";
import { HttpClientModule } from "@angular/common/http";
import { SettingsBarComponent } from './components/settings-bar/settings-bar.component';

@NgModule({
	declarations: [AppComponent, GameBoardComponent, BoardSegmentComponent, CreateBoardDirective, SettingsBarComponent],
	imports: [BrowserModule, AppRoutingModule, HttpClientModule],
	providers: [GameHttpClient],
	bootstrap: [AppComponent],
})
export class AppModule {}
