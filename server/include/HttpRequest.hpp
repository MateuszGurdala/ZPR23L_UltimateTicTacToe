#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include "HttpHeaders.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

enum method { GET, POST, OPTIONS };

class HttpRequest {
  using UHeaders = std::unique_ptr<HttpHeaders>;

private:
  const std::string _newLine = "\n";
  const std::string _colon = ":";
  const std::string _space = " ";

  std::string _body, _endpoint;
  method _method;

  int parseBody(std::string &request);
  int parseRequestType(std::string &request);
  int parseRequestMethod(std::string &requestType);
  void verboseRequest() const;

public:
  UHeaders headers;
  std::string getEndpoint() const;
  method getMethod() const;
  explicit HttpRequest(std::string &&request);
};

#endif