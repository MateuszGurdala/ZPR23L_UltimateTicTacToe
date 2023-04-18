#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <iostream>
#include <map>
#include <string>
#include <vector>

class HttpRequest {
private:
  const std::string _newLine = "\n";
  const std::string _colon = ":";
  const std::string _space = " ";

  std::string _body, _method, _endpoint;
  std::map<std::string, std::string> _headers;

  int parseBody(std::string &request);
  int parseHeaders(std::string &request);
  int parseRequestType(std::string &request);
  int parseRequestMethod(std::string &requestType);

public:
  HttpRequest(std::string &&request);
  const std::string &operator[](const std::string &key) const;
};

#endif