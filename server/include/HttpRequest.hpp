#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include "HttpHeaders.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

class HttpRequest {
  typedef std::unique_ptr<HttpHeaders> UHeaders;

private:
  const std::string _newLine = "\n";
  const std::string _colon = ":";
  const std::string _space = " ";

  std::string _body, _method, _endpoint;

  int parseBody(std::string &request);
  int parseRequestType(std::string &request);
  int parseRequestMethod(std::string &requestType);
  void verboseRequest() const;

public:
  UHeaders headers;
  explicit HttpRequest(std::string &&request);
};

#endif