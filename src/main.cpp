#include <stdio.h>
#include <stdlib.h>
#include "../include/HttpResponse.hpp"

#ifdef _WIN32
#include "../include/WIN32ServerSocket.hpp"
#endif

#ifdef linux
#include "../include/LinuxServerSocket.hpp"
#endif

#define DEFAULT_PORT 1337
#define DEFAULT_REQUEST_BUFLEN 1024

int main(int argc, char const *argv[])
{
	char *buffptr = NULL;
	int recvlen;
	std::string respstr;
	std::string respBody = "<body><div>Dzialaaaa!!!!<div></body>"; // temp

#ifdef _WIN32
	WIN32ServerSocket serverSocket = WIN32ServerSocket(DEFAULT_PORT, DEFAULT_REQUEST_BUFLEN);
#endif // _WIN32

#ifdef linux
	LinuxServerSocket serverSocket = LinuxServerSocket(DEFAULT_PORT, DEFAULT_REQUEST_BUFLEN);
#endif

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
			HttpResponse httpResponse;

			// Klient -> request -> HttpHandlera -> Engine -> Gra
			// Ustalanie stanu gry
			// Engine ->(stan gry)HttpHandlera -> (HttpResponse) -> socket -> Klienta

			recvlen = serverSocket.GetRequest(buffptr);
			printf(buffptr);
			printf("\n");

			httpResponse.getResponse(respstr, respBody);

			printf("Sending response:\n");
			printf(respstr.c_str());
			printf("\n");

			serverSocket.SendResponse(respstr.c_str(), respstr.length());
		}
	} while (true);

	return 0;
}
