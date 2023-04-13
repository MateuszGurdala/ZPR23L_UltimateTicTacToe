#include "../../include/HttpResponse.hpp"

constexpr auto VERSION = "HTTP/1.1";
constexpr auto STATUS_OK = "200";
constexpr auto STATUS_MESSAGE = "OK";

constexpr auto CONTENT_TYPE() { return "application/json"; };
constexpr auto SERVER_NAME() { return "UltimateTicTacToeServer"; };
constexpr auto CONNECTION() { return "close"; };
constexpr auto ALLOW_ORIGIN() { return "*"; };
constexpr auto ALLOW_METHODS() { return "GET,POST"; };
constexpr auto ALLOW_HEADERS() { return "Content-Type"; };

typedef std::unique_ptr<std::string> PString;

HttpResponse::HttpResponse(std::string &body) { _body = body; }
HttpResponse::HttpResponse(std::string &&body) { _body = std::move(body); }

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
  pushBackHeader("Server", SERVER_NAME());
  pushBackHeader("Content-Type", CONTENT_TYPE());
  pushBackHeader("Connection", CONNECTION());
  pushBackHeader("Content-Length", std::to_string(_body.length()));
  pushBackHeader("Access-Control-Allow-Origin", ALLOW_ORIGIN());
  pushBackHeader("Access-Control-Allow-Methods", ALLOW_METHODS());
  pushBackHeader("Access-Control-Allow-Headers", ALLOW_HEADERS());
  pushBackHeader("Date", getDate()); // Must be last
}

std::string HttpResponse::getResponse() {
  std::stringstream stringStream = getResponseTop();
  addHeaders();

  for (auto header = _headers.begin(); header != _headers.end(); ++header) {
    stringStream << (**header) << '\n';
  }

  stringStream << _body;

  return stringStream.str();
}
