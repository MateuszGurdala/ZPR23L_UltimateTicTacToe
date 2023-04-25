#include "main.hpp"
#include "config.hpp"

int main() {
  using URequest = std::shared_ptr<HttpRequest>;
  using UResponse = std::shared_ptr<HttpResponse>;

#ifdef _WIN32
  WIN32ServerSocket serverSocket(config::port, config::requestBuffer);
#endif

#if defined(__linux__) || defined(__arm64__)
  LinuxServerSocket serverSocket(config::port, config::requestBuffer);
#endif

  const HttpHandler handler;
  URequest request;
  UResponse response(nullptr);

  if (serverSocket.Init() != 0) {
    std::cout << "Socket intialization failed.\n";
    return 1;
  }

  do {
    if (serverSocket.Listen() == 0) {
      request = std::make_shared<HttpRequest>(serverSocket.GetRequest());
      response = std::make_shared<HttpResponse>(handler.handle(request));
      serverSocket.SendResponse(response);
    }
  } while (true);

  return 0;
}
