#ifndef LINUX_SERVER_SOCKET_HPP
#define LINUX_SERVER_SOCKET_HPP

#include "ServerSocket.hpp"

#if defined(__linux__) || defined(__arm64__)
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class LinuxServerSocket : public ServerSocket {
private:
  // SocketData
  struct sockaddr_in _address;
  int _addrlen = sizeof(_address);
  int _opt = 1;
  int _server_fd, _new_socket;

public:
  LinuxServerSocket(int port, int reqbufflent);
  ~LinuxServerSocket();
  virtual int Init();
  virtual int Listen();
  virtual int SendResponse(HttpResponse &response) const;
};
#endif

#endif // !LINUX_SERVER_SOCKET_HPP
