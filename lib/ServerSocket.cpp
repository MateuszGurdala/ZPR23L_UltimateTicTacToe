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

int ServerSocket::GetRequest(char *&buffptr)
{
    buffptr = new char[_recvbufflen];
    std::copy(_recvbuff, _recvbuff + _recvbufflen, buffptr);

    return _recvbufflen;
}