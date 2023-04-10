#ifndef LINUX_SERVER_SOCKET_HPP
#define LINUX_SERVER_SOCKET_HPP

#include "ServerSocket.hpp"

#ifdef linux
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

class LinuxServerSocket : public ServerSocket
{
private:
	int _port;

	// SocketData
	struct sockaddr_in _address;
	int _addrlen = sizeof(_address);
	int _opt = 1;
	int _server_fd, _new_socket;

public:
	LinuxServerSocket(int port, int reqbufflent);
	~LinuxServerSocket();
	int Init();
	int Listen();
	virtual int SendResponse(HttpResponse& response) const;
};
#endif

#endif // !LINUX_SERVER_SOCKET_HPP
