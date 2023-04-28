#ifndef WIN32_SERVER_SOCKET_HPP
#define WIN32_SERVER_SOCKET_HPP

#include "ServerSocket.hpp"
#include <stdio.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>

#ifdef _MSC_VER
#pragma comment(lib, "ws2_32.lib")
#endif

/*  Class: WIN32ServerSocket

      Server socket class for windows systems.

    See Also:

        <IServerSocket>
        <ServerSocket>
        <LinuxServerSocket>
*/
class WIN32ServerSocket : public ServerSocket {
private:
  // SocketData
  SOCKET ListenSocket = INVALID_SOCKET;
  SOCKET ClientSocket = INVALID_SOCKET;

public:
  /*  Constructor: WIN32ServerSocket

        Creates WIN32ServerSocket instance.

      Parameters:

        port - Port number that socket will listen on.
        reqbufflen - Request buffer length.
  */
  WIN32ServerSocket(int port, int reqbufflen);
  /*  Destructor: WIN32ServerSocket
   */
  ~WIN32ServerSocket();
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

#endif // !WIN32_SERVER_SOCKET_H
