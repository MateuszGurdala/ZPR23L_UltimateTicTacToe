import { Directive, ElementRef, Input, OnInit, Renderer2 } from "@angular/core";

@Directive({
	selector: "[setSize]",
})
export class SetSignSize implements OnInit {
	@Input("setSize") size: number;

	constructor(private el: ElementRef, private renderer: Renderer2) {}
	ngOnInit(): void {
		let style: string = this.size + "vmin";
		this.renderer.setStyle(this.el.nativeElement, "font-size", style);
	}
}
