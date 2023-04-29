#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

namespace config {
const int port = 1337;
const int requestBuffer = 1024;
const bool verbose = true;
const std::string serverName = "UltimateTicTacToeServer";
const std::string contentType = "application/json";
const std::string allowOrigin = "*";
const std::string allowMethods = "GET,POST";
const std::string allowHeaders = "Content-Type";
} // namespace config

#endif