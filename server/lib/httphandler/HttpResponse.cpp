#include "../../include/HttpResponse.hpp"

#define VERSION "HTTP/1.1"
#define STATUS_OK "200"
#define STATUS_MESSAGE "OK"

#define CONTENT_TYPE "text/html; charset=utf-8"
#define SERVER_NAME "UltimateTicTacToeServer"
#define CONNECTION "close"

typedef std::unique_ptr<std::string> PString;

HttpResponse::HttpResponse(std::string &body) { _body = body; }

HttpResponse::~HttpResponse() {
  _headers.clear();
  std::vector<PString>().swap(_headers); // Deallocate memory
}

std::stringstream HttpResponse::getResponseTop() {
  std::stringstream ss;
  ss << VERSION << " ";
  ss << STATUS_OK << " ";
  ss << STATUS_MESSAGE << '\n';

  return ss;
}

std::string HttpResponse::getDate() {
  auto now = std::chrono::system_clock::now();
  auto time = std::chrono::system_clock::to_time_t(now);

  return std::string(ctime(&time));
}

void HttpResponse::pushBackHeader(std::string &&name, std::string &&value) {
  PString header = std::make_unique<std::string>(name);
  (*header) += ": ";
  (*header) += value;
  _headers.push_back(std::move(header));
}

void HttpResponse::addHeaders() {
  pushBackHeader("Server", SERVER_NAME);
  pushBackHeader("Content-Type", CONTENT_TYPE);
  pushBackHeader("Connection", CONNECTION);
  pushBackHeader("Content-Length", std::to_string(_body.length()));
  pushBackHeader("Date", getDate());
}

std::string HttpResponse::getResponse() {
  std::stringstream ss = getResponseTop();
  addHeaders();

  for (auto header = _headers.begin(); header != _headers.end(); ++header) {
    ss << (**header) << '\n';
  }

  ss << _body;

  return ss.str();
}