#include "../include/HttpRequest.hpp"
#include "../include/HttpResponse.hpp"
#include <cstdio>
#include <cstdlib>
#include <memory>

#ifdef _WIN32
#include "../include/WIN32ServerSocket.hpp"
#endif

#if defined(__linux__) || defined(__arm64__)
#include "../include/LinuxServerSocket.hpp"
#endif

#define DEFAULT_PORT 1337
#define DEFAULT_REQUEST_BUFFLEN 1024

typedef std::unique_ptr<HttpRequest> URequest;
typedef std::unique_ptr<HttpResponse> UResponse;

bool verbose = true;

int main() {
#ifdef _WIN32
  WIN32ServerSocket serverSocket(DEFAULT_PORT, DEFAULT_REQUEST_BUFFLEN);
#endif

#if defined(__linux__) || defined(__arm64__)
  LinuxServerSocket serverSocket(DEFAULT_PORT, DEFAULT_REQUEST_BUFFLEN);
#endif

  URequest request;
  UResponse();

  if (serverSocket.Init() != 0) {
    printf("Socket intialization failed.\n");
    return 1;
  }

  do {
    if (serverSocket.Listen() == 0) {
      request = std::make_unique<HttpRequest>(serverSocket.GetRequest());

      // TODO: REMOVE
      HttpResponse response("{\"result\":\"true\"}");
      serverSocket.SendResponse(response);
    }
  } while (true);

  return 0;
}
