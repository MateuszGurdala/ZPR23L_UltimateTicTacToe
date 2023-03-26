#ifndef SERVER_SOCKET_HPP
#define SERVER_SOCKET_HPP

#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <algorithm>

#include "IServerSocket.hpp"

class ServerSocket : public IServerSocket
{
public:
    ServerSocket(int port, int reqbufflen);
    ~ServerSocket();
    int GetRequest(char *&buffptr);
};

#endif