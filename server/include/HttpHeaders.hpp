#ifndef HTTP_HEADERS_HPP
#define HTTP_HEADERS_HPP

#include "../src/config.hpp"
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

const std::map<const std::string, const std::string> globalHeaders = {
    {"Server", config::serverName},
    {"Content-Type", config::contentType},
    {"Access-Control-Allow-Origin", config::allowOrigin},
    {"Access-Control-Allow-Methods", config::allowMethods},
    {"Access-Control-Allow-Headers", config::allowHeaders}};

class HttpHeaders {
private:
  const std::string _newLine = "\n";
  const std::string _colon = ":";

  std::map<std::string, std::string> _headers;

public:
  HttpHeaders();
  explicit HttpHeaders(std::string &headers);
  void verbose() const;
  std::string toString() const;
  int addHeader(std::string &key, std::string &value);
  const std::string &operator[](const std::string &key) const;
};

#endif