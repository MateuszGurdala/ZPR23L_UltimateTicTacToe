#Compilation settings
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 20)

if(UNIX)
	add_compile_options(-Wall -Werror -Wextra -Wno-error=deprecated-copy)
endif()

project ("UltimateTicTacToeServer")
set(INCLUDE "${PROJECT_SOURCE_DIR}/include")
set(LIB "${PROJECT_SOURCE_DIR}/lib")
add_subdirectory(lib)
add_subdirectory(test)

#add_executable (UltimateTicTacToeServer "${PROJECT_SOURCE_DIR}/src/main.cpp")
add_executable (UltimateTicTacToeServer "${PROJECT_SOURCE_DIR}/src/gameMain.cpp")


#Link libraries
target_link_libraries(UltimateTicTacToeServer ServerSocket)
target_link_libraries(UltimateTicTacToeServer Http)
target_link_libraries(UltimateTicTacToeServer GameHandler)

