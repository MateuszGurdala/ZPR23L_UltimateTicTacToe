set(SERVERSOCKETSRC "${INCLUDE}/ServerSocket.hpp" "ServerSocket.cpp")
set(WIN32SRC "${INCLUDE}/WIN32ServerSocket.hpp" "win32/WIN32ServerSocket.cpp")
set(LINUXSRC "${INCLUDE}/LinuxServerSocket.hpp" "linux/LinuxServerSocket.cpp")

add_subdirectory(http)

if(WIN32)
    add_library(WIN32ServerSocket ${SERVERSOCKETSRC} ${WIN32SRC})
ELSEIF(UNIX)
    add_library(LinuxServerSocket ${SERVERSOCKETSRC} ${LINUXSRC})
endif()
