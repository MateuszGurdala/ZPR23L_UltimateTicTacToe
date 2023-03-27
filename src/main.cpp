// Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <memory>

// Custom includes
#include "../include/HttpResponse.hpp"

#ifdef _WIN32
#include "../include/WIN32ServerSocket.hpp"
#endif

#ifdef linux
#include "../include/LinuxServerSocket.hpp"
#endif

#define DEFAULT_PORT 1337
#define DEFAULT_REQUEST_BUFFLEN 1024

int main(int argc, char const *argv[])
{
#ifdef _WIN32
	WIN32ServerSocket serverSocket = WIN32ServerSocket(DEFAULT_PORT, DEFAULT_REQUEST_BUFFLEN);
#endif // _WIN32

#ifdef linux
	LinuxServerSocket serverSocket = LinuxServerSocket(DEFAULT_PORT, DEFAULT_REQUEST_BUFFLEN);
#endif

	// std::shared_ptr<HttpResponse> resp_ptr(nullptr);
	std::shared_ptr<HttpResponse> resp_ptr = std::make_shared<HttpResponse>();

	std::string reqstr;
	std::string respstr;

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
		}
	} while (true);

	return 0;
}
