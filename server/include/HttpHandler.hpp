#ifndef HTTP_HANDLER_HPP
#define HTTP_HANDLER_HPP

#include <memory.h>

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

class HttpHandler {
private:
  HttpResponse
  handleGETRequest(const std::shared_ptr<HttpRequest> request) const;
  HttpResponse
  handlePOSTRequest(const std::shared_ptr<HttpRequest> request) const;
  HttpResponse
  handleOPTIONSRequest(const std::shared_ptr<HttpRequest> request) const;

public:
  HttpResponse handle(const std::shared_ptr<HttpRequest> request) const;
};

#endif