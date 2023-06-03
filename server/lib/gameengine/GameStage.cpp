
#include "../../include/gameengine/GameStage.hpp"
#include <sstream>

void GameStage::SetGameStage(const std::string &newGameStatus) {
  if (std::find(validStages.begin(), validStages.end(), newGameStatus) ==
      validStages.end()) {
    throw std::invalid_argument("Invalid game status.");
  }
  currentGameStage = newGameStatus;
}
std::string GameStage::GetCurrentGameStage() { return currentGameStage; }