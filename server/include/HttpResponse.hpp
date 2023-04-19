#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include "HttpHeaders.hpp"
#include <sstream>
#include <string>

class HttpResponse {
private:
  HttpHeaders _headers;
  std::string _statusLine, _body;

public:
  HttpResponse();
  explicit HttpResponse(std::string &body);
  explicit HttpResponse(std::string &&body);

  static HttpResponse OPTIONSResponse();
  static HttpResponse ERRORResponse();
  static HttpResponse GETResponse(std::string &&body);
  static HttpResponse POSTResponse(std::string &&body);

  std::string toString() const;
};

#endif