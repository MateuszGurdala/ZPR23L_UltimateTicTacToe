find_package(Catch2 3 REQUIRED)

# HTTP
set(HTTPHANDLERSRC "${INCLUDE}/http/HttpHandler.hpp" "${LIB}/httphandler/HttpHandler.cpp")
set(HTTPHEADERS "${INCLUDE}/http/HttpHeaders.hpp" "${LIB}/httphandler/HttpHeaders.cpp")
set(HTTPREQUEST "${INCLUDE}/http/HttpRequest.hpp" "${LIB}/httphandler/HttpRequest.cpp")
set(HTTPRESPONSE "${INCLUDE}/http/HttpResponse.hpp" "${LIB}/httphandler/HttpResponse.cpp")
set(CONFIG "${SRC}/config.hpp")

# GAMEENGINE
set(GAMEENGINE "${INCLUDE}/gameengine/GameEngine.hpp" "${LIB}/gameengine/GameEngine.cpp")
set(GAMEHANDLER "${INCLUDE}/gameengine/GameHandler.hpp" "${LIB}/gameengine/GameHandler.cpp")
set(GAMESTAGE "${INCLUDE}/gameengine/GameStage.hpp" "${LIB}/gameengine/GameStage.cpp")

# ENTITIES
set(BOARDBASE "${INCLUDE}/entities/BoardBase.hpp" "${LIB}/entities/BoardBase.cpp")
set(INNERBOARD "${INCLUDE}/entities/InnerBoard.hpp" "${LIB}/entities/InnerBoard.cpp")
set(MAINBOARD "${INCLUDE}/entities/MainBoard.hpp" "${LIB}/entities/MainBoard.cpp")
set(PLAYER "${INCLUDE}/entities/Player.hpp" "${LIB}/entities/Player.cpp")
set(HUMANPLAYER "${INCLUDE}/entities/HumanPlayer.hpp" "${LIB}/entities/HumanPlayer.cpp")
set(COMPUTERPLAYER "${INCLUDE}/entities/ComputerPlayer.hpp" "${LIB}/entities/ComputerPlayer.cpp")

# HELPERS
set(BOARDINDEXCONVERTER "${INCLUDE}/helpers/BoardIndexConverter.hpp" "${LIB}/helpers/BoardIndexConverter.cpp"
        "${INCLUDE}/helpers/MoveSimulator.hpp" "${LIB}/helpers/MoveSimulator.cpp")


# TESTS
set(HTTPHEADERSTESTS "http/HttpHeadersTest.cpp" ${HTTPHEADERS})
set(HTTPREQUESTTESTS "http/HttpRequestTest.cpp" ${HTTPREQUEST})
set(HTTPRESPONSETESTS "http/HttpResponseTest.cpp" ${HTTPRESPONSE})
set(ENGINETESTS "engine/GameEngineTests.cpp" ${GAMEENGINE})
set(HANDLERTESTS "engine/GameHandlerTests.cpp" ${GAMEHANDLER})
set(GAMESTAGETESTS "engine/GameStageTests.cpp" ${GAMESTAGE})

set(INNERBOARDTESTS "entities/InnerBoardTests.cpp" ${INNERBOARD} ${BOARDBASE})
set(OUTERBOARDTESTS "entities/MainBoardTests.cpp" ${MAINBOARD} ${BOARDBASE})
set(PLAYERTESTS "entities/PlayerTests.cpp" ${PLAYER}  ${HUMANPLAYER} ${COMPUTERPLAYER})
set(HELPERTESTS "helpers/HelperTests.cpp" ${BOARDINDEXCONVERTER})


add_executable(UltimateTicTacToeServerGameTest 
                ${HTTPHEADERSTESTS}
                ${HTTPREQUESTTESTS}
                ${HTTPRESPONSETESTS}
                ${ENGINETESTS}
                ${HANDLERTESTS}
                ${GAMESTAGETESTS}
                ${INNERBOARDTESTS}
                ${OUTERBOARDTESTS}
                ${PLAYERTESTS}
                ${HELPERTESTS}
                )
target_link_libraries(UltimateTicTacToeServerGameTest PRIVATE Catch2::Catch2WithMain)
