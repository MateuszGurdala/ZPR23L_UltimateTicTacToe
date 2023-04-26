set(SERVERSOCKETSRC "${INCLUDE}/ServerSocket.hpp" "ServerSocket.cpp")
set(WIN32SRC "${INCLUDE}/WIN32ServerSocket.hpp" "win32/WIN32ServerSocket.cpp")
set(LINUXSRC "${INCLUDE}/LinuxServerSocket.hpp" "linux/LinuxServerSocket.cpp")
set(INDEXCONVERTERSRC "${INCLUDE}/helpers/BoardIndexConverter.hpp" "helpers/BoardIndexConverter.cpp")

add_subdirectory(httphandler)
add_subdirectory(entities)
add_subdirectory(gameengine)

add_library(BoardIndexConverter ${INDEXCONVERTERSRC})
if(WIN32)
    add_library(ServerSocket ${SERVERSOCKETSRC} ${WIN32SRC})
ELSEIF(UNIX)
    add_library(ServerSocket ${SERVERSOCKETSRC} ${LINUXSRC})
endif()

