cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 11)

project ("UltimateTicTacToeServer")

set(INCLUDE "${PROJECT_SOURCE_DIR}/include")
add_subdirectory(lib)

add_executable (UltimateTicTacToeServer "${PROJECT_SOURCE_DIR}/src/main.cpp")
target_link_libraries(UltimateTicTacToeServer HTTP)

IF(WIN32)
    target_link_libraries(UltimateTicTacToeServer WIN32ServerSocket)
ELSEIF(UNIX)
    target_link_libraries(UltimateTicTacToeServer LinuxServerSocket)
ENDIF()