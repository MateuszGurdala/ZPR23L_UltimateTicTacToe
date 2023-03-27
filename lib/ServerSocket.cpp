#include "../include/ServerSocket.hpp"

ServerSocket::ServerSocket(int port, int reqbufflen)
{
    _port = port;
    _recvbufflen = reqbufflen;
    _recvbuff = new char[_recvbufflen];
}

ServerSocket::~ServerSocket()
{
    delete[] _recvbuff;
}

std::string ServerSocket::GetRequest()
{
    return std::string(_recvbuff);
}