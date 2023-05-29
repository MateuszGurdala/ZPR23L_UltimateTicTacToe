set(SERVERSOCKETSRC "${INCLUDE}/socket/ServerSocket.hpp" "ServerSocket.cpp")
set(WIN32SRC "${INCLUDE}/socket/WIN32ServerSocket.hpp" "win32/WIN32ServerSocket.cpp")
set(LINUXSRC "${INCLUDE}/socket/LinuxServerSocket.hpp" "linux/LinuxServerSocket.cpp")

add_subdirectory(httphandler)
add_subdirectory(entities)
add_subdirectory(gameengine)
add_subdirectory(helpers)

if(WIN32)
    add_library(ServerSocket ${SERVERSOCKETSRC} ${WIN32SRC})
ELSEIF(UNIX)
    add_library(ServerSocket ${SERVERSOCKETSRC} ${LINUXSRC})
endif()

