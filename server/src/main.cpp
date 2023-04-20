#include "main.hpp"
#include "config.hpp"

int main() {
  using URequest = std::shared_ptr<HttpRequest>;

#ifdef _WIN32
  WIN32ServerSocket serverSocket(DEFAULT_PORT, DEFAULT_REQUEST_BUFFLEN);
#endif

#if defined(__linux__) || defined(__arm64__)
  LinuxServerSocket serverSocket(config::port, config::requestBuffer);
#endif

  const HttpHandler handler;
  URequest request;

  if (serverSocket.Init() != 0) {
    std::cout << "Socket intialization failed.\n";
    return 1;
  }

  do {
    if (serverSocket.Listen() == 0) {
      request = std::make_shared<HttpRequest>(serverSocket.GetRequest());

      auto x = handler.handle(request);
      serverSocket.SendResponse(x);
    }
  } while (true);

  return 0;
}
