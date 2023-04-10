#include "../../include/WIN32ServerSocket.hpp"

using namespace std;

WIN32ServerSocket::WIN32ServerSocket(int port, int reqbufflen) : ServerSocket(port, reqbufflen) {}

WIN32ServerSocket::~WIN32ServerSocket()
{
	closesocket(ClientSocket);
	WSACleanup();
}

int WIN32ServerSocket::Init()
{
	string sport = to_string(_port);
	PCSTR port = sport.c_str();
	WSADATA wsaData;
	int result = 0;
	struct addrinfo hints;
	PADDRINFOA addr;

	// Initialize Winsock
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		printf("WSAStartup failed: %d\n", result);
		return 1;
	}

	ZeroMemory(&hints, sizeof(addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the local address and port to be used by the server
	result = getaddrinfo(NULL, port, &hints, &addr);
	if (result != 0)
	{
		printf("getaddrinfo failed: %d\n", result);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for the server to listen for client connections
	ListenSocket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
	if (ListenSocket == INVALID_SOCKET)
	{
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(addr);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	result = bind(ListenSocket, addr->ai_addr, (int)addr->ai_addrlen);
	if (result == SOCKET_ERROR)
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(addr);

	return 0;
}

int WIN32ServerSocket::Listen()
{
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET)
	{
		printf("accept failed: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	delete _recvbuff;
	_recvbuff = new char[_recvbufflen];

	if (recv(ClientSocket, _recvbuff, _recvbufflen, 0) > 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int WIN32ServerSocket::SendResponse(HttpResponse & response) const
{
	string responseString = response.getResponse();
	int result = send(ClientSocket, responseString.c_str(), responseString.length(), 0);
	if (result == SOCKET_ERROR)
	{
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}
	return 0;
}