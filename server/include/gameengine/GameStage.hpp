#ifndef ULTIMATETICTACTOESERVER_GAMESTAGE_H
#define ULTIMATETICTACTOESERVER_GAMESTAGE_H

#include <string>

enum GameStatus {
    Ready,
    WaitingForOpponent,
    Ongoing,
    Finished
};

class GameStage {
private:
    GameStatus gameStatus;
public:
    GameStatus GetGameStatus();
    GameStatus SetGameStatus(GameStatus newGameStatus);
    std::string GameStatusAsJson(bool isNested);
};

#endif //ULTIMATETICTACTOESERVER_GAMESTAGE_H
