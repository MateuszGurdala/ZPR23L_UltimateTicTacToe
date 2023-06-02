#ifndef ULTIMATETICTACTOESERVER_GAMESTAGE_H
#define ULTIMATETICTACTOESERVER_GAMESTAGE_H

#include <string>
#include <array>

class GameStage {
private:
    std::array<std::string, 6> validStages = {
                                              "Unknown"
                                              "Player X Turn",
                                              "Player O Turn",
                                              "Player X Turn, choose segment",
                                              "Player O Turn, choose segment",
                                              "Game is Finished",
                                              };
    std::string currentGameStatus = validStages[0];
public:
    void SetGameStatus(const std::string& newGameStatus);
    std::string GameStatusAsJson(bool isNested);
};

#endif //ULTIMATETICTACTOESERVER_GAMESTAGE_H
