set(PLAYERSRC "${INCLUDE}/entities/Player.h" "Player.cpp")
set(MAINBOARDSRC "${INCLUDE}/entities/MainBoard.h" "MainBoard.cpp")
set(HUMANPLAYERSRC "${INCLUDE}/entities/HumanPlayer.h" "HumanPlayer.cpp")
set(COMPUTERPLAYERSRC "${INCLUDE}/entities/ComputerPlayer.h" "ComputerPlayer.cpp")
set(INNERBOARDSRC "${INCLUDE}/entities/InnerBoard.h" "InnerBoard.cpp")


add_library(HumanPlayer ${HUMANPLAYERSRC})
add_library(ComputerPlayer ${COMPUTERPLAYERSRC})
add_library(Player ${PLAYERSRC})

add_library(MainBoard ${MAINBOARDSRC})
add_library(InnerBoard ${INNERBOARDSRC})
