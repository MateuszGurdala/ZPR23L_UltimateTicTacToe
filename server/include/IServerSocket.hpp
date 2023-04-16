#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
#ifndef I_SERVER_SOCKET_HPP
#define I_SERVER_SOCKET_HPP

#include <memory>
#include <cstdio>
#include <iostream>
#include <cstdio>
#include <cstdlib>
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

#endif // I_SERVER_SOCKET_HPP

#pragma clang diagnostic pop