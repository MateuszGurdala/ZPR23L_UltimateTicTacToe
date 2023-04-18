#ifndef HTTP_HEADERS_HPP
#define HTTP_HEADERS_HPP

#include <iostream>
#include <map>
#include <string>
#include <vector>

class HttpHeaders {
private:
  const std::string _newLine = "\n";
  const std::string _colon = ":";

  std::map<std::string, std::string> _headers;

public:
  HttpHeaders();
  HttpHeaders(std::string &headers);
  void verbose() const;
  const std::string &operator[](const std::string &key) const;
};

#endif