#include "../../include/http/HttpHandler.hpp"
#include "../../include/entities/MainBoard.hpp"

/* TEMP */
#include <fstream>
#include <sstream>

HttpResponse
HttpHandler::handle(const std::shared_ptr<HttpRequest>& request) const {
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

//TODO expand later (prototype test purpose)
HttpResponse HttpHandler::handleGETRequest(
    const std::shared_ptr<HttpRequest>& request) const {
  if (request->getEndpoint() == "/BoardState") {
    /* TEMP */
    auto mainBoard = std::make_unique<MainBoard>(3);
    Point outerBoardCoords = Point(1,1);
    Point innerBoardCoords = Point(1,1);
    mainBoard->MakeMove(outerBoardCoords,innerBoardCoords, 'X');
    return HttpResponse::GETResponse(mainBoard->ToJson(false));
  } else {
    return HttpResponse::GETResponse(R"({"result":" true"})");
  }
}

HttpResponse HttpHandler::handlePOSTRequest(
    const std::shared_ptr<HttpRequest>& request) const {
  auto x = request;
  return HttpResponse::POSTResponse(R"({"result":" true"})");
}

HttpResponse HttpHandler::handleOPTIONSRequest(
    const std::shared_ptr<HttpRequest>& request) const {
  auto x = request;
  return HttpResponse::OPTIONSResponse();
}