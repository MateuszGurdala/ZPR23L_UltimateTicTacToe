#include "../../include/HttpHandler.hpp"

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
    return HttpResponse(R"({"result":" true"})");
    break;
  }
}

HttpResponse HttpHandler::handleGETRequest(
    const std::shared_ptr<HttpRequest> request) const {
  auto x = request;
  return HttpResponse::GETResponse(R"({"result":" true"})");
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