#include "../include/HttpHandler.hpp"
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
