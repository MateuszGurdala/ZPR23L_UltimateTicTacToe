import { NgModule, Renderer2 } from "@angular/core";
import { BrowserModule } from "@angular/platform-browser";

import { AppRoutingModule } from "./app-routing.module";
import { AppComponent } from "./app.component";
import { GameBoardComponent } from "./game-board/game-board.component";
import { BoardSegmentComponent } from "./board-segment/board-segment.component";
import { CreateBoardDirective } from './create-board.directive';

@NgModule({
	declarations: [AppComponent, GameBoardComponent, BoardSegmentComponent, CreateBoardDirective],
	imports: [BrowserModule, AppRoutingModule],
	providers: [],
	bootstrap: [AppComponent],
})
export class AppModule {}
