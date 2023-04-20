set(ENGINESRC "${INCLUDE}/gameengine/GameEngine.hpp" "GameEngine.cpp")
set(HANDLERSRC "${INCLUDE}/gameengine/GameHandler.hpp" "GameHandler.cpp")

add_library(GameEngine ${ENGINESRC})
add_library(GameHandler ${HANDLERSRC})

#Link libraries
target_link_libraries(GameHandler Player GameEngine HumanPlayer ComputerPlayer)
target_link_libraries(GameEngine MainBoard)