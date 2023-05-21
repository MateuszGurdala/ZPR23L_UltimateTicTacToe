
#include "../../include/gameengine/GameStage.hpp"

GameStatus GameStage::GetGameStatus() {
    return gameStatus;
}

GameStatus GameStage::SetGameStatus(GameStatus newGameStatus) {
    gameStatus = newGameStatus;
}

std::string GameStage::GameStatusAsJson(bool isNested) {
    return std::string();
}
