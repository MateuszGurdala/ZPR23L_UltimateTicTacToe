find_package(Catch2 3 REQUIRED)

set(HTTPHEADERSTESTS "http/HttpHeadersTest.cpp" "${INCLUDE}/http/HttpHeaders.hpp" "${LIB}/httphandler/HttpHeaders.cpp")

set(INNERBOARDTESTS "entities/MainBoardTests.cpp" "${INCLUDE}/entities/InnerBoard.hpp" "${LIB}/entities/InnerBoard.cpp")
set(OUTERBOARDTESTS "entities/MainBoardTests.cpp" "${INCLUDE}/entities/MainBoard.hpp" "${LIB}/entities/MainBoard.cpp")
set(PLAYERTESTS "entities/PlayerTests.cpp" "${INCLUDE}/entities/Player.hpp" "${INCLUDE}/entities/HumanPlayer.hpp" "${INCLUDE}/entities/ComputerPlayer.hpp"
        "${LIB}/entities/Player.cpp" "${LIB}/entities/HumanPlayer.cpp" "${LIB}/entities/ComputerPlayer.cpp")

set(ENGINETESTS "engine/GameEngineTests.cpp" "${INCLUDE}/gameengine/GameEngine.hpp" "${LIB}/gameengine/GameEngine.cpp")
set(HANDLERTESTS "engine/GameHandlerTests.cpp" "${INCLUDE}/gameengine/GameHandler.hpp" "${LIB}/gameengine/GameHandler.cpp")

set(HELPERTESTS "helpers/HelperTests.cpp" "${INCLUDE}/helpers/BoardIndexConverter.hpp" "${LIB}/helpers/BoardIndexConverter.cpp")


add_executable(TESTS ${HTTPHEADERSTESTS} ${INNERBOARDTESTS} ${OUTERBOARDTESTS} ${PLAYERTESTS} ${ENGINETESTS} ${HANDLERTESTS} ${HELPERTESTS})
target_link_libraries(TESTS PRIVATE Catch2::Catch2WithMain)