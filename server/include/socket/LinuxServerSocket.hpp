#ifndef LINUX_SERVER_SOCKET_HPP
#define LINUX_SERVER_SOCKET_HPP

#include "ServerSocket.hpp"

#if defined(__linux__) || defined(__arm64__)
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

/*  Class: LinuxServerSocket

      Server socket class for unix systems.

    See Also:

        <IServerSocket>
        <ServerSocket>
        <WIN32ServerSocket>
*/
class LinuxServerSocket : public ServerSocket {
private:
  // SocketData
  struct sockaddr_in _address;
  int _addrlen = sizeof(_address);
  int _opt = 1;
  int _server_fd, _new_socket;

public:
  /*  Constructor: LinuxServerSocket

        Creates LinuxServerSocket instance.

      Parameters:

        port - Port number that socket will listen on.
        reqbufflen - Request buffer length.
  */
  LinuxServerSocket(int port, int reqbufflent);
  /*  Destructor: LinuxServerSocket
   */
  ~LinuxServerSocket();
  /*  Function: Init

        Initializes socket on given port that accepts request that are smaller
        or equal in length that request buffer length.

      Returns:

        0 if initialized successfully.
  */
  virtual int Init();
  /*  Function: Listen

        Starts listening for incoming http requests.

      Returns:

        0 if received request without body, else request body length.
  */
  virtual int Listen();
  /*  Function: SendResponse

      Parameters:

        response - HttpResponse object that will be send back.

      Returns:

        0 if response was sent successfully, else 1.
  */
  virtual int SendResponse(std::shared_ptr<HttpResponse> response) const;
};
#endif

#endif // !LINUX_SERVER_SOCKET_HPP
