#include "../include/http/HttpHandler.hpp"
#include "../include/http/HttpRequest.hpp"
#include "../include/http/HttpResponse.hpp"
#include <cstdio>
#include <cstdlib>
#include <memory>

#ifdef _WIN32
#include "../include/socket/WIN32ServerSocket.hpp"
#endif

#if defined(__linux__) || defined(__arm64__)
#include "../include/socket/LinuxServerSocket.hpp"
#endif
