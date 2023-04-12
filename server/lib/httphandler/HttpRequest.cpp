#include "../../include/HttpRequest.hpp"

extern bool verbose;

HttpRequest::HttpRequest(std::string &&request) {
  parseRequestType(request);
  parseBody(request);
  parseHeaders(request);

  if (verbose) {
    std::cout << "TYPE:\n";
    std::cout << _requestType << '\n';

    std::cout << "HEADERS:\n";
    for (const auto &mapPair : _headers) {
      std::cout << mapPair.first << ':' << mapPair.second << '\n';
    }

    if (!_body.empty()) {
      std::cout << "BODY:\n";
      std::cout << _body << '\n';
    }
  }
}

int HttpRequest::parseHeaders(std::string &request) {
  size_t pos = 0;
  std::vector<std::string> parts;

  while ((pos = request.find(_newLine)) != std::string::npos) {
    parts.push_back(request.substr(0, pos));
    request.erase(0, pos + _newLine.length());
  }

  for (auto &part : parts) {
    pos = part.find(_colon);
    _headers[part.substr(0, pos)] =
        part.substr(pos + _colon.length(), part.length() - pos);
  }

  return 0;
}

int HttpRequest::parseBody(std::string &request) {
  size_t pos = 0;

  if ((pos = request.find('{')) != std::string::npos) {
    _body = request.substr(pos,
                           request.find('}') - pos + std::string("}").length());
    request.erase(pos - _newLine.length(), pos + _body.length());
    return 0;
  }
  return 1;
}

int HttpRequest::parseRequestType(std::string &request) {
  size_t pos = 0;

  if ((pos = request.find(_newLine)) != std::string::npos) {
    _requestType = request.substr(0, pos - _newLine.length());
    request.erase(0, _requestType.length() + _newLine.length() * 2);
    return 0;
  }
  return 1;
}

const std::string &HttpRequest::operator[](const std::string &key) const {
  // TODO: Add error handling for missing values for a key
  return _headers.at(key);
}