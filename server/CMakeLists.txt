﻿#Compilation settings
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 20)

if(UNIX)
	add_compile_options(-Wall -Werror -Wextra -Wno-error=deprecated-copy)
endif()

project ("UltimateTicTacToeServer")
set(INCLUDE "${PROJECT_SOURCE_DIR}/include")
set(LIB "${PROJECT_SOURCE_DIR}/lib")
set(SRC "${PROJECT_SOURCE_DIR}/src")
add_subdirectory(lib)

if(UNIX)
	add_subdirectory(test)
endif()

add_executable (UltimateTicTacToeServer "${PROJECT_SOURCE_DIR}/src/main.cpp")

if(WIN32)
	target_link_libraries(UltimateTicTacToeServer wsock32 ws2_32)
endif()
target_link_libraries(UltimateTicTacToeServer ServerSocket Http GameHandler)

