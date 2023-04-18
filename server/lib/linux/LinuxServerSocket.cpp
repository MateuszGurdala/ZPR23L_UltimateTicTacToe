#include "../../include/LinuxServerSocket.hpp"

LinuxServerSocket::LinuxServerSocket(int port, int reqbufflen)
    : ServerSocket(port, reqbufflen) {}

LinuxServerSocket::~LinuxServerSocket() {
  // closing the connected socket
  close(_new_socket);
  // closing the listening socket
  shutdown(_server_fd, SHUT_RDWR);
}

int LinuxServerSocket::Init() {

  // Creating socket file descriptor
  if ((_server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket failed");
    return 1;
  }

  // Forcefully attaching socket to the port
  if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &_opt, sizeof(_opt))) {
    perror("setsockopt");
    return 1;
  }
  _address.sin_family = AF_INET;
  _address.sin_addr.s_addr = INADDR_ANY;
  _address.sin_port = htons(_port);

  if (::bind(_server_fd, (struct sockaddr *)&_address, sizeof(_address)) < 0) {
    perror("bind failed");
    return 1;
  }

  return 0;
}

int LinuxServerSocket::Listen() {
  if (listen(_server_fd, 3) < 0) {
    perror("listen");
    return 1;
  }
  if ((_new_socket = accept(_server_fd, (struct sockaddr *)&_address,
                            (socklen_t *)&_addrlen)) < 0) {
    perror("accept");
    return 1;
  }

  read(_new_socket, _recvbuff, _recvbufflen);
  return 0;
}

int LinuxServerSocket::SendResponse(HttpResponse &response) const {
  std::string responseString = response.getResponse();
  send(_new_socket, responseString.c_str(), responseString.length(), 0);
  return 0;
}