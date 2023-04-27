#include "../../include/http/HttpHandler.hpp"

/* TEMP */
#include <fstream>
#include <sstream>

HttpResponse
HttpHandler::handle(const std::shared_ptr<HttpRequest> request) const {
  switch (request->getMethod()) {
  case OPTIONS:
    return handleOPTIONSRequest(request);
    break;
  case GET:
    return handleGETRequest(request);
    break;
  case POST:
    return handlePOSTRequest(request);
    break;
  default:
    return HttpResponse::ERRORResponse();
    break;
  }
}

HttpResponse HttpHandler::handleGETRequest(
    const std::shared_ptr<HttpRequest> request) const {
  if (request->getEndpoint() == "/BoardState") {
    /* TEMP */
    std::ifstream t(
        "../../templates/BoardState.json"); // ../ linux ../../ win32
    std::stringstream buffer;
    buffer << t.rdbuf();
    return HttpResponse::GETResponse(buffer.str());
  } else {
    return HttpResponse::GETResponse(R"({"result":" true"})");
  }
}

HttpResponse HttpHandler::handlePOSTRequest(
    const std::shared_ptr<HttpRequest> request) const {
  auto x = request;
  return HttpResponse::POSTResponse(R"({"result":" true"})");
}

HttpResponse HttpHandler::handleOPTIONSRequest(
    const std::shared_ptr<HttpRequest> request) const {
  auto x = request;
  return HttpResponse::OPTIONSResponse();
}