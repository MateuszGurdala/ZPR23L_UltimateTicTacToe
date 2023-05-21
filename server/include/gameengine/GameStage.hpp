#ifndef ULTIMATETICTACTOESERVER_GAMESTAGE_H
#define ULTIMATETICTACTOESERVER_GAMESTAGE_H

#include <string>

enum GameStatus {

};

class GameStage {
private:
    std::array<std::string, 5> availableStatuses = {{
                                                    "Ready",
                                                    "WaitingForOpponent",
                                                    "ChoosingSegment",
                                                    "OngoingMove",
                                                    "Finished"
                                                    }};
    std::string currentGameStatus;
public:
    GameStatus GetGameStatus();
    void SetGameStatus(std::string newGameStatus);
    std::string GameStatusAsJson(bool isNested);
};

#endif //ULTIMATETICTACTOESERVER_GAMESTAGE_H
