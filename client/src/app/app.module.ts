import { NgModule } from "@angular/core";
import { BrowserModule } from "@angular/platform-browser";

import { AppRoutingModule } from "./app-routing.module";
import { AppComponent } from "./components/app/app.component";
import { GameBoardComponent } from "./components/game-board/game-board.component";
import { BoardSegmentComponent } from "./components/board-segment/board-segment.component";
import { CreateBoardDirective } from "./directives/create-board.directive";

@NgModule({
	declarations: [AppComponent, GameBoardComponent, BoardSegmentComponent, CreateBoardDirective],
	imports: [BrowserModule, AppRoutingModule],
	providers: [],
	bootstrap: [AppComponent],
})
export class AppModule {}
