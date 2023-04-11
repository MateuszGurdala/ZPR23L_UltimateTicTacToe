#ifndef I_SERVER_SOCKET_HPP
#define I_SERVER_SOCKET_HPP

#include <memory>
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <algorithm>

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"


class IServerSocket
{
protected:
	int _port;
	int _recvbufflen;
	char* _recvbuff;

public:
	virtual int Init() = 0;
	virtual int Listen() = 0;
	virtual HttpRequest GetRequest() = 0;
	virtual int SendResponse(HttpResponse& response) const = 0;
};

#endif // ! I_SERVER_SOCKET_H