#include "../../include/http/HttpHeaders.hpp"

extern std::string allowOrigin;

HttpHeaders::HttpHeaders() {}

HttpHeaders::HttpHeaders(std::string &headers) {
  size_t pos = 0;
  std::string key;
  std::string value;
  std::vector<std::string> parts;

  while ((pos = headers.find(_newLine)) != std::string::npos) {
    parts.push_back(headers.substr(0, pos));
    headers.erase(0, pos + _newLine.length());
  }

  for (auto &part : parts) {
    pos = part.find(_colonSpace);
    if (pos != std::string::npos) {
      key = part.substr(0, pos);
      value = part.substr(pos + _colonSpace.length(), part.length() - pos);
      if (!key.empty() && !value.empty()) {

        _headers[key] = value;
      }
    }
  }
}

void HttpHeaders::verbose() const { std::cout << toString(); }

std::string HttpHeaders::toString() const {
  std::stringstream stream;

  for (const auto &mapPair : _headers) {
    stream << mapPair.first << _colonSpace << mapPair.second << _newLine;
  }

  return stream.str();
}

int HttpHeaders::addHeader(std::string &key, const std::string &value) {
  if (_headers[key].empty()) {
    _headers[key] = value;
    return 0;
  }
  return 1;
}

int HttpHeaders::addHeader(std::string &&key, const std::string &value) {
  if (_headers[key].empty()) {
    _headers[key] = value;
    return 0;
  }
  return 1;
}

int HttpHeaders::addHeader(std::string &&key, std::string &&value) {
  if (_headers[key].empty()) {
    _headers[key] = value;
    return 0;
  }
  return 1;
}

int HttpHeaders::addDateHeader() {
  auto now = std::chrono::system_clock::now();
  auto time = std::chrono::system_clock::to_time_t(now);
  auto timeStr = std::string(ctime(&time));
  auto value = timeStr.substr(0, timeStr.length() - _newLine.length());
  return addHeader("Date", value);
}

int HttpHeaders::addAllowHeader() {
  return addHeader("Allow", globalHeaders.at("Allow"));
}

int HttpHeaders::closeConnection() { return addHeader("Connection", "closed"); }

int HttpHeaders::addContentLengthHeader(int length) {
  return addHeader("Content-Length", std::to_string(length));
}

int HttpHeaders::addCORSHeaders() {
  std::string origin = "Access-Control-Allow-Origin";
  std::string methods = "Access-Control-Allow-Methods";
  std::string headers = "Access-Control-Allow-Headers";
  std::string credentails = "Access-Control-Allow-Credentials";

  addHeader(origin, allowOrigin);
  addHeader(methods, globalHeaders.at(methods));
  addHeader(headers, globalHeaders.at(headers));
  addHeader(credentails, globalHeaders.at(credentails));
  return 0;
}

const std::string &HttpHeaders::operator[](const std::string &key) const {
  if (_headers.count(key)) {
    return _headers.at(key);
  }
  return _nullstring;
}

const std::string &HttpHeaders::operator[](const std::string &&key) const {
  if (_headers.count(key)) {
    return _headers.at(key);
  }
  return _nullstring;
}

HttpHeaders &HttpHeaders::operator=(const HttpHeaders &obj) {
  for (const auto &mapPair : obj._headers) {
    _headers[mapPair.first] = mapPair.second;
  }
  return *this;
}

int HttpHeaders::setCookie(const std::string &keyValueCookie) {
  return addHeader("Set-Cookie", keyValueCookie);
}
