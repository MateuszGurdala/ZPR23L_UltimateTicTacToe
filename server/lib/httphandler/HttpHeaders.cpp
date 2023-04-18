#include "../../include/HttpHeaders.hpp"

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
    pos = part.find(_colon);
    key = part.substr(0, pos);
    value = part.substr(pos + _colon.length(), part.length() - pos);
    if (!key.empty() && !value.empty()) {

      _headers[key] = value;
    }
  }
}

void HttpHeaders::verbose() const {
  std::cout << "HEADERS:\n";
  for (const auto &mapPair : _headers) {
    std::cout << mapPair.first << ':' << mapPair.second << '\n';
  }
}

const std::string &HttpHeaders::operator[](const std::string &key) const {
  // TODO: Add error handling for missing values for a key
  return _headers.at(key);
}