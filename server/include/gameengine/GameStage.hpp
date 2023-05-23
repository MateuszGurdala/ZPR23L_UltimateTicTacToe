#ifndef ULTIMATETICTACTOESERVER_GAMESTAGE_H
#define ULTIMATETICTACTOESERVER_GAMESTAGE_H

#include <string>
#include <array>

enum GameStatus {

};

class GameStage {
private:
    std::array<std::string, 5> availableStatuses = {
                                                    "Ready",
                                                    "WaitingForOpponent",
                                                    "ChoosingSegment",
                                                    "OngoingMove",
                                                    "Finished"
                                                    };
    std::string currentGameStatus = availableStatuses[0];
public:
    std::string GetGameStatus();
    void SetGameStatus(const std::string& newGameStatus);
    std::string GameStatusAsJson(bool isNested);
};

#endif //ULTIMATETICTACTOESERVER_GAMESTAGE_H
