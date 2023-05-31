#include "../../include/http/HttpResponse.hpp"
#include "../../src/config.hpp"

HttpResponse::HttpResponse() {}
HttpResponse::HttpResponse(std::string &body) { _body = body; }
HttpResponse::HttpResponse(std::string &&body) { _body = std::move(body); }

HttpResponse::HttpResponse(HttpResponse &&obj) {
  _body = obj._body;
  _statusLine = obj._statusLine;
  _headers = obj._headers;
}

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
  response._headers.addContentLengthHeader(0);
  response._headers.addCORSHeaders();

  return response;
}

HttpResponse HttpResponse::GETResponse(std::string &&body) {
  HttpResponse response;

  response._statusLine = "HTTP/1.1 200 OK";

  response._headers.addDateHeader();
  response._headers.addAllowHeader();
  response._headers.addCORSHeaders();
  response._headers.closeConnection();
  response._headers.addContentLengthHeader(body.length());

  response._body = body;

  return response;
}

HttpResponse HttpResponse::GETResponse(std::string &body) {
  return GETResponse(std::move(body));
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

HttpResponse HttpResponse::ERRORResponse(std::string &&errorCode,
                                         std::string &&errorMessage) {
  HttpResponse response;
  std::stringstream stream;

  stream << "HTTP/1.1 ";
  stream << errorCode;
  stream << " ";
  stream << errorMessage;

  // response._statusLine = "HTTP/1.1 400 BAD REQUEST";
  response._statusLine = stream.str();

  response._headers.addDateHeader();
  response._headers.closeConnection();
  response._headers.addContentLengthHeader(0);

  return response;
}

int HttpResponse::setCookie(std::string &&cookie, std::string &&value) {
  std::stringstream keyValueStream;
  keyValueStream << cookie;
  keyValueStream << "=";
  keyValueStream << value;

  return _headers.setCookie(keyValueStream.str());
}
