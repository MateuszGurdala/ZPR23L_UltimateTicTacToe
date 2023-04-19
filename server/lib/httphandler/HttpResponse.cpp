#include "../../include/HttpResponse.hpp"
#include "../../src/config.hpp"

HttpResponse::HttpResponse() {}
HttpResponse::HttpResponse(std::string &body) { _body = body; }
HttpResponse::HttpResponse(std::string &&body) { _body = std::move(body); }

std::string HttpResponse::toString() const {
  std::stringstream stream;
  stream << _statusLine << '\n';
  stream << _headers.toString() << '\n';
  if (!_body.empty()) {
    stream << _body << '\n';
  }

  if (config::verbose) {
    std::cout << stream.str() << std::endl;
  }

  return stream.str();
}

HttpResponse HttpResponse::OPTIONSResponse() {
  HttpResponse response;

  response._statusLine = "HTTP/1.1 200 OK";

  response._headers.addDateHeader();
  response._headers.addAllowHeader();
  response._headers.closeConnection();
  response._headers.addCORSHeaders();

  return response;
}

HttpResponse HttpResponse::GETResponse(std::string &&body) {
  HttpResponse response;

  response._statusLine = "HTTP/1.1 200 OK";

  response._headers.addDateHeader();
  response._headers.addAllowHeader();
  response._headers.closeConnection();
  response._headers.addContentLengthHeader(body.length());

  response._body = body;

  return response;
}

HttpResponse HttpResponse::POSTResponse(std::string &&body) {
  HttpResponse response;

  response._statusLine = "HTTP/1.1 200 OK";

  response._headers.addDateHeader();
  response._headers.addAllowHeader();
  response._headers.closeConnection();
  response._headers.addCORSHeaders();
  response._headers.addContentLengthHeader(body.length());

  response._body = body;

  return response;
}

HttpResponse HttpResponse::ERRORResponse() {
  HttpResponse response;

  response._statusLine = "HTTP/1.1 400 BAD REQUEST";

  response._headers.addDateHeader();
  response._headers.closeConnection();

  return response;
}