import { Component } from "@angular/core";

@Component({
	selector: "settings-bar",
	templateUrl: "./settings-bar.component.html",
	styleUrls: ["./settings-bar.component.css"],
})
export class SettingsBarComponent {
	isExtended: boolean = false;

	extend() {
		this.isExtended = !this.isExtended;
	}
}
