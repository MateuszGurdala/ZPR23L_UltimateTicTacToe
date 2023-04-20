#ifndef HTTP_HEADERS_HPP
#define HTTP_HEADERS_HPP

#include "../src/config.hpp"
#include <chrono>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

const std::map<std::string, std::string> globalHeaders = {
    {"Server", config::serverName},
    {"Content-Type", config::contentType},
    {"Access-Control-Allow-Origin", config::allowOrigin},
    {"Access-Control-Allow-Methods", config::allowMethods},
    {"Allow", config::allowMethods},
    {"Access-Control-Allow-Headers", config::allowHeaders}};

class HttpHeaders {
private:
  const std::string _newLine = "\n";
  const std::string _colon = ":";

  std::map<std::string, std::string> _headers;

public:
  HttpHeaders();
  explicit HttpHeaders(std::string &headers);

  int addHeader(std::string &key, const std::string &value);
  int addHeader(std::string &&key, const std::string &value);
  int addHeader(std::string &&key, std::string &&value);
  int addDateHeader();
  int addAllowHeader();
  int addContentLengthHeader(int length);
  int closeConnection();
  int addCORSHeaders();
  std::string toString() const;

  void verbose() const;
  const std::string &operator[](const std::string &key) const;
};

#endif