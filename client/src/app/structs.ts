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
	SinglePlayer = "Player_vs_AI",
	Multiplayer = "Player_vs_Player",
}

export enum GameStage {
	PlayerTurn = "Your Turn",
	EnemyTurn = "Enemy Turn",
	PlayerChooseSegment = "Pick Next Segment",
	EnemyChooseSegment = "Enemy is Choosing Next Segment",
	Finished = "Game is Finished",
	Unknown = "Unknown",
}

/* Responses */
export interface CreateGameResponse {
	isSuccess: boolean;
	hostName: string;
	hostSymbol: Sign;
	guestName: string;
	guestSymbol: Sign;
	boardSize: number;
}

export interface EndGameResponse {
	whoEndedGame: string;
	winner: boolean;
}

export interface GameStateResponse {
	hostPlayer: {
		name: string;
		symbol: Sign;
		points: number;
	};
	guestPlayer: {
		name: string;
		symbol: Sign;
		points: number;
	};
	currentTurn: {
		nowPlaying: Sign;
	};
}

export interface MoveResponse {
	outerBoardIndex: number;
	innerBoardIndex: number;
	isMoveValid: boolean;
}
