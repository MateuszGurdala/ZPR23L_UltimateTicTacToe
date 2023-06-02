#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

namespace config {
const int port = 1337;
const int requestBuffer = 1024;
const bool verbose = true;
const std::string serverName = "UltimateTicTacToeServer";
const std::string contentType = "application/json";
const std::string allowOrigin = "http://localhost:4200";
const std::string allowMethods = "GET";
const std::string allowHeaders = "Content-Type";
const std::string allowCredentials = "true";
const std::string playerCookies[]{"playerSolo", "playerX", "playerO"};
} // namespace config

#endif