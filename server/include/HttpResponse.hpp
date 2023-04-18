#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include <chrono>
#include <ctime>
#include <memory>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>

class HttpResponse {
private:
  std::vector<std::unique_ptr<std::string>> _headers;
  std::string _body;

  std::stringstream getResponseTop();
  std::string getDate();
  void pushBackHeader(std::string &&name, std::string &&value);
  void addHeaders();

public:
  explicit HttpResponse(std::string &body);
  explicit HttpResponse(std::string &&body);
  ~HttpResponse();

  std::string getResponse();
};

#endif