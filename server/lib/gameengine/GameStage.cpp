
#include <sstream>
#include "../../include/gameengine/GameStage.hpp"

std::string GameStage::GetGameStatus() {
    return currentGameStatus;
}

void GameStage::SetGameStatus(const std::string& newGameStatus) {
    if (std::find(availableStatuses.begin(), availableStatuses.end(), newGameStatus) == availableStatuses.end()) {
        throw std::invalid_argument("Invalid game status.");
    }
    currentGameStatus = newGameStatus;
}


std::string GameStage::GameStatusAsJson(bool isNested) {
    std::stringstream ss;
    if(!isNested)
    {
        ss << "{";
    }
    ss << "\"gameStage\":";
    ss << "{";
    ss << "\"currentGameStage\":" <<  currentGameStatus;

    ss << "}";
    {
        ss << "}";
    }
    return ss.str();
}
