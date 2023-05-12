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

export enum GameState {
	Ready,
	Waiting,
	Ongoing,
	PlayerSolo,
	PlayerX,
	PlayerO,
	Unknown,
}

export enum Sign {
	X,
	O,
}

export enum Enemy {
	AI = "AI Enemy",
	Player = "Player",
}
