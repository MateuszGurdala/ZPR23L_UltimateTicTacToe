import { AfterContentInit, Component, Inject, Input } from "@angular/core";

@Component({
	selector: "",
	template: "",
})
export class SegmentLogic implements AfterContentInit {
	@Input("id") setId: number;

	id: number | undefined = undefined;
	isActive: boolean | undefined = undefined;
	ownerSign: "X" | "O" | undefined = undefined;

	ngAfterContentInit(): void {
		this.id = this.setId;
	}
}
