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

class IServerSocket {
protected:
  int _port;
  int _recvbufflen;
  char *_recvbuff;

public:
  virtual int Init() = 0;
  virtual int Listen() = 0;
  virtual HttpRequest GetRequest() = 0;
  virtual int SendResponse(std::shared_ptr<HttpResponse> response) const = 0;
};

#endif // ! I_SERVER_SOCKET_H
