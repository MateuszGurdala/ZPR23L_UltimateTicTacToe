#ifndef I_SERVER_SOCKET_HPP
#define I_SERVER_SOCKET_HPP

#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "../http/HttpRequest.hpp"
#include "../http/HttpResponse.hpp"

/*  Interface: IServerSocket

      Socket interface.

    See Also:

        <ServerSocket>
        <WIN32ServerSocket>
        <LinuxServerSocket>
*/
class IServerSocket {
protected:
  int _port;
  int _recvbufflen;
  char *_recvbuff;

public:
  /*  Function: Init

        Initializes socket on given port that accepts request that are smaller
        or equal in length that request buffer length.

      Returns:

        0 if initialized successfully.
  */
  virtual int Init() = 0;
  /*  Function: Listen

        Starts listening for incoming http requests.

      Returns:

        0 if received request without body, else request body length.
  */
  virtual int Listen() = 0;
  /*  Function: GetRequest

      Returns:

        Request data as HttpRequest object.
  */
  virtual HttpRequest GetRequest() = 0;
  /*  Function: SendResponse

      Parameters:

        response - HttpResponse object that will be send back.

      Returns:

        0 if response was sent successfully, else 1.
  */
  virtual int SendResponse(std::shared_ptr<HttpResponse> response) const = 0;
};

#endif // ! I_SERVER_SOCKET_H
