#include "../include/socket/ServerSocket.hpp"

ServerSocket::ServerSocket(int port, int reqbufflen) {
  _port = port;
  _recvbufflen = reqbufflen;
  _recvbuff = new char[_recvbufflen];
}

ServerSocket::~ServerSocket() { delete[] _recvbuff; }

HttpRequest ServerSocket::GetRequest() {
  return HttpRequest(std::string(_recvbuff));
}
