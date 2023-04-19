#ifndef HTTP_HEADERS_HPP
#define HTTP_HEADERS_HPP

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

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
  const std::string &operator[](const std::string &key) const;
};

#endif