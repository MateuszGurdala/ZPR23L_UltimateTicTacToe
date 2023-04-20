set(SERVERSOCKETSRC "${INCLUDE}/ServerSocket.hpp" "ServerSocket.cpp")
set(WIN32SRC "${INCLUDE}/WIN32ServerSocket.hpp" "win32/WIN32ServerSocket.cpp")
set(LINUXSRC "${INCLUDE}/LinuxServerSocket.hpp" "linux/LinuxServerSocket.cpp")


add_subdirectory(httphandler)
add_subdirectory(entities)
add_subdirectory(gameengine)

if(WIN32)
    add_library(WIN32ServerSocket ${SERVERSOCKETSRC} ${WIN32SRC})
    target_link_libraries(WIN32ServerSocket HTTP)
ELSEIF(UNIX)
    add_library(LinuxServerSocket ${SERVERSOCKETSRC} ${LINUXSRC})
    target_link_libraries(LinuxServerSocket HTTP)
endif()

