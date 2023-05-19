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
	X = "X",
	O = "O",
}

export enum GameMode {
	SinglePlayer = "Player vs AI",
	Multiplayer = "Player vs Player",
}

export enum GameStage {
	PlayerTurn = "Your Turn",
	EnemyTurn = "Enemy Turn",
	PlayerChooseSegment = "Pick Next Segment",
	EnemyChooseSegment = "Enemy is Choosing Next Segment",
	Finished = "Game is Finished",
}
