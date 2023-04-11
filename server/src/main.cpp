﻿#include <cstdio>
#include <cstdlib>
#include <memory>
#include "../include/HttpResponse.hpp"

#ifdef _WIN32
#include "../include/WIN32ServerSocket.hpp"
#endif

#if linux || defined(__arm64__)
#include "../include/LinuxServerSocket.hpp"
#endif

#define DEFAULT_PORT 1337
#define DEFAULT_REQUEST_BUFFLEN 1024

typedef std::unique_ptr<HttpRequest> URequest;
typedef std::unique_ptr<HttpResponse> UResponse;

bool verbose = true;

int main(int argc, char const *argv[])
{
#ifdef _WIN32
	WIN32ServerSocket serverSocket(DEFAULT_PORT, DEFAULT_REQUEST_BUFFLEN);
#endif

#if linux || defined(__arm64__)
    LinuxServerSocket serverSocket(DEFAULT_PORT, DEFAULT_REQUEST_BUFFLEN);
#endif

	URequest request;
    UResponse();
	std::string tempbody = "<body><div>Dzialaaaa!!!!<div></body>";

	if (serverSocket.Init() != 0)
	{
		printf("Socket intialization failed.\n");
		return 1;
	}

	do
	{
		printf("Waiting for request.\n");

		if (serverSocket.Listen() == 0)
		{
			printf("Got new request.\n");
			request = std::make_unique<HttpRequest>(serverSocket.GetRequest());

			// TODO: REMOVE
			HttpResponse response(tempbody);
			serverSocket.SendResponse(response);
			printf("Sent response.\n");
		}
		//else
		//{
		//	printf("Something went wrong.\n");
		//	return 1;
		//}
	} while (true);

	return 0;
}