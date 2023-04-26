#Compilation settings
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 20)

if(UNIX)
	add_compile_options(-Wall -Werror -Wextra)
endif()

project ("UltimateTicTacToeServer")
set(INCLUDE "${PROJECT_SOURCE_DIR}/include")
add_subdirectory(lib)
add_subdirectory(test)

add_executable (UltimateTicTacToeServer "${PROJECT_SOURCE_DIR}/src/main.cpp")

#Link libraries
target_link_libraries(UltimateTicTacToeServer ServerSocket)
target_link_libraries(UltimateTicTacToeServer Http)
