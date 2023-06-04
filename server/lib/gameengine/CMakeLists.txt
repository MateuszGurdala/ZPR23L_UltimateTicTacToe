set(ENGINESRC "${INCLUDE}/gameengine/GameEngine.hpp" "GameEngine.cpp")
set(HANDLERSRC "${INCLUDE}/gameengine/GameHandler.hpp" "GameHandler.cpp")
set(STAGESRC "${INCLUDE}/gameengine/GameStage.hpp" "GameStage.cpp")


add_library(GameEngine ${ENGINESRC})
add_library(GameHandler ${HANDLERSRC})
add_library(GameStage ${STAGESRC})

#Link libraries
target_link_libraries(GameHandler Player GameEngine HumanPlayer ComputerPlayer GameStage MoveSimulator)
target_link_libraries(GameEngine MainBoard MoveSimulator)