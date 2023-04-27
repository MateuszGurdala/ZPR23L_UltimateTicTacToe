#Compilation settings
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 20)

if(UNIX)
	add_compile_options(-Wall -Werror -Wextra)
endif()

project ("UltimateTicTacToeServer")
set(INCLUDE "${PROJECT_SOURCE_DIR}/include")
add_subdirectory(lib)

if(UNIX)
add_subdirectory(test)
endif()

#add_executable (UltimateTicTacToeServer "${PROJECT_SOURCE_DIR}/src/main.cpp")
add_executable (UltimateTicTacToeServer "${PROJECT_SOURCE_DIR}/src/gameMain.cpp")


#Link libraries
if(WIN32)
	target_link_libraries(UltimateTicTacToeServer wsock32 ws2_32)
endif()
target_link_libraries(UltimateTicTacToeServer ServerSocket Http GameHandler)
