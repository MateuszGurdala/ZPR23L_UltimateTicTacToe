import { Directive, ElementRef, Input, OnInit, Renderer2 } from "@angular/core";

@Directive({
	selector: "[createBoard]",
})
export class CreateBoardDirective implements OnInit {
	@Input("createBoard") size: number;

	constructor(private el: ElementRef, private renderer: Renderer2) {}
	ngOnInit(): void {
		let style: string = "repeat(" + this.size + ", 1fr)";
		this.renderer.setStyle(this.el.nativeElement, "grid-template-columns", style);
		this.renderer.setStyle(this.el.nativeElement, "grid-template-rows", style);
	}
}
