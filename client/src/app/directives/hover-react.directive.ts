import { Directive, ElementRef } from "@angular/core";

@Directive({
	selector: "[colorReact]",
})
export class HoverReactDirective {
	constructor(private element: ElementRef) {
		this.element.nativeElement.classList.add("color-react");
	}
}
