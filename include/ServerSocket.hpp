#ifndef SERVER_SOCKET_HPP
#define SERVER_SOCKET_HPP

#include "IServerSocket.hpp"

class ServerSocket : public IServerSocket
{
public:
    ServerSocket(int port, int reqbufflen);
    ~ServerSocket();
    std::string GetRequest();
};

#endif