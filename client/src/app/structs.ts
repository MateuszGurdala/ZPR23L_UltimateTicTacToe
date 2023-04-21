export interface GameBoard {
	segments: DaughterBoard[];
}

export interface DaughterBoard {
	id: number;
	winner: "X" | "O";
	segments: Segment[];
}

export interface Segment {
	id: number;
	winner: "X" | "O";
}
