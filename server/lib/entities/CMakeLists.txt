set(PLAYERSRC "${INCLUDE}/entities/Player.hpp" "Player.cpp")
set(MAINBOARDSRC "${INCLUDE}/entities/MainBoard.hpp" "MainBoard.cpp")
set(HUMANPLAYERSRC "${INCLUDE}/entities/HumanPlayer.hpp" "HumanPlayer.cpp")
set(COMPUTERPLAYERSRC "${INCLUDE}/entities/ComputerPlayer.hpp" "ComputerPlayer.cpp")
set(INNERBOARDSRC "${INCLUDE}/entities/InnerBoard.hpp" "InnerBoard.cpp")
set(BOARDBASESRC "${INCLUDE}/entities/BoardBase.hpp" "BoardBase.cpp")


add_library(HumanPlayer ${HUMANPLAYERSRC})
add_library(ComputerPlayer ${COMPUTERPLAYERSRC})
add_library(Player ${PLAYERSRC})

add_library(BoardBase ${BOARDBASESRC})
add_library(MainBoard ${MAINBOARDSRC})
add_library(InnerBoard ${INNERBOARDSRC})

target_link_libraries(MainBoard InnerBoard BoardBase)
target_link_libraries(InnerBoard BoardBase)
