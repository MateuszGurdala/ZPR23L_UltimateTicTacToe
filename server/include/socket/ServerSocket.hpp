#ifndef SERVER_SOCKET_HPP
#define SERVER_SOCKET_HPP

#include "IServerSocket.hpp"

/*  Class: ServerSocket

      Parent class for server sockets. Implements IServerSocket interface.

    See Also:

        <IServerSocket>
        <WIN32ServerSocket>
        <LinuxServerSocket>
*/
class ServerSocket : public IServerSocket {
public:
  /*  Constructor: ServerSocket

        Creates ServerSocket instance.

      Parameters:

        port - Port number that socket will listen on.
        reqbufflen - Request buffer length.
  */
  ServerSocket(int port, int reqbufflen);
  /*  Destructor: ServerSocket
   */
  ~ServerSocket();
  /*  Function: GetRequest

      Returns:

        Request data parsed and stored in HttpRequest object.

      See Also:

      <HttpRequest>
   */
  HttpRequest GetRequest() override;
};

#endif