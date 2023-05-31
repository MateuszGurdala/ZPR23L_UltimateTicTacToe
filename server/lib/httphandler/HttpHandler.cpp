#include "../../include/http/HttpHandler.hpp"
#include "../../include/helpers/BoardIndexConverter.hpp"
#include "../../include/helpers/MoveSimulator.hpp"

HttpResponse HttpHandler::handle(const std::shared_ptr<HttpRequest> &request) {
  switch (request->getMethod()) {
  case OPTIONS:
    return handleOPTIONSRequest();
    break;
  case GET:
    return handleGETRequest(request);
    break;
  default:
    return HttpResponse::ERRORResponse("400", "INVALID REQUEST");
    break;
  }
}

HttpResponse
HttpHandler::handleGETRequest(const std::shared_ptr<HttpRequest> &request) {

  const std::string endpoint = request->getEndpoint();

  /* Board State */
  if (endpoint == "/BoardState") {
    if (gameHandler) {
      return HttpResponse::GETResponse(gameHandler->BoardStateAsJson());
    }
    return HttpResponse::ERRORResponse("400", "Game not yet created");
  }
  /* Game State */
  else if (endpoint == "/ServerState") {
    return serverState(request);
  }
  /* Game Stage */
  else if (endpoint == "/GameStage") {
    /*
        "Player X Turn",
        "Player O Turn",
        "Game is Finished",
        "Unknown",
    */
    //    if (gameHandler) {
    //      return HttpResponse::GETResponse(gameHandler->GameStateAsJson());
    //    }
    // TODO: Krystian
    // return HttpResponse::GETResponse(R"("Unknown")"); // State must be inside
    return HttpResponse::ERRORResponse("501", "NOT IMPLEMENTED");
  }
  /* Server Status */
  else if (endpoint == "/ServerStatus") {
    return HttpResponse::GETResponse(R"(true)");
  }
  /* End Game */
  else if (endpoint == "/EndGame") {
    if (verifyPlayer(request)) {
      std::string player = extractCookieValue(request);
      // TODO: Krystian
      // return HttpResponse::GETResponse(R"(true)");
      return HttpResponse::ERRORResponse("501", "NOT IMPLEMENTED");
    } else {
      return HttpResponse::ERRORResponse("401", "UNAUTHORIZED");
    }
  } else if (endpoint == "/MakeMove") {
    if (verifyPlayer(request) && gameHandler) {
      std::string player = extractCookieValue(request);
      std::string boardId = (request->queryParams)["boardId"];
      std::string segmentId = (request->queryParams)["segmentId"];
      unsigned int boardIdIndex = std::stoul(boardId);
      unsigned int segmentIdIndex = std::stoul(segmentId);
      Point outerCoordinates =
          BoardIndexConverter::IndexToPoint(segmentIdIndex, boardSize);
      Point innerCoordinates =
          BoardIndexConverter::IndexToPoint(boardIdIndex, boardSize);
      std::array<Point, 2> move = {outerCoordinates, innerCoordinates};
      bool isValid = gameHandler->PerformMoveValidation(outerCoordinates,
                                                        innerCoordinates);
      return HttpResponse::GETResponse(
          gameHandler->MoveAsJson(false, move, isValid));
    } else {
      return HttpResponse::ERRORResponse("401", "UNAUTHORIZED");
    }
  }
  /* Pick Segment */
  else if (endpoint == "/PickSegment") {
    if (verifyPlayer(request)) {
      std::string player = extractCookieValue(request);
      std::string segmentNumber = (request->queryParams)["segmentNumber"];
      // TODO: Krystian
      // return HttpResponse::GETResponse(R"(true)");
      return HttpResponse::ERRORResponse("501", "NOT IMPLEMENTED");
    } else {
      return HttpResponse::ERRORResponse("401", "UNAUTHORIZED");
    }
  }
  /* Create Game */
  else if (endpoint == "/CreateGame") {
    if (verifyPlayer(request)) {
      return HttpResponse::GETResponse(gameHandler->CreateGameAsJson(false));
    } else {
      std::string gameMode = (request->queryParams)["gameMode"];
      std::string playerSign = (request->queryParams)["playerSign"];
      std::string boardSizeQuery = (request->queryParams)["boardSize"];
      char playerSignAsChar = playerSign.c_str()[0];
      if (playerSignAsChar != 'X' && playerSignAsChar != 'O') {
        return HttpResponse::ERRORResponse("400",
                                           "Invalid player "
                                           "figure while creating game.");
      }
      if (gameMode == "Player") {
        isPlayerVsComputer = true;
      }
      boardSize = std::stoi(boardSizeQuery);
      gameHandler = std::make_unique<GameHandler>(
          std::stoi(boardSizeQuery), playerSignAsChar, isPlayerVsComputer);
      // return HttpResponse::GETResponse(gameHandler->CreateGameAsJson(true));
      return HttpResponse::GETResponse(R"(true)");
    }
  }
  /* Invalid Endpoint */
  else {
    return HttpResponse::ERRORResponse("400", "BAD REQUEST");
  }
}

HttpResponse HttpHandler::handleOPTIONSRequest() const {
  return HttpResponse::OPTIONSResponse();
}

bool HttpHandler::verifyPlayer(
    const std::shared_ptr<HttpRequest> &request) const {
  try {
    extractCookieValue(request);
    return true;
  } catch (const std::exception &) {
    return false;
  }
}

std::string HttpHandler::extractCookieValue(
    const std::shared_ptr<HttpRequest> &request) const {
  size_t p;
  std::string rawCookie;
  std::string cookie;
  std::string value;

  rawCookie = (*request->headers)["Cookie"];
  std::cout << rawCookie << "\n";

  if (!rawCookie.empty() && (p = rawCookie.find('=')) != std::string::npos) {
    cookie = rawCookie.substr(0, p);
    value = rawCookie.substr(p + 1, rawCookie.size());
  } else {
    throw std::exception();
  }

  if (cookie == "player" && std::find(std::begin(config::playerCookies),
                                      std::end(config::playerCookies), value) !=
                                std::end(config::playerCookies)) {
    return value;
  } else {
    throw std::exception();
  }
}

HttpResponse
HttpHandler::serverState(const std::shared_ptr<HttpRequest> &request) const {
  /*
    0 - Ready
    1 - Waiting
    2 - Ongoing
    3 - PlayerSolo
    4 - PlayerX
    5 - PlayerO
    6 - Unknown
*/
  std::string stateStr = "6";
  std::string playerCookie;
  bool isGameOngoing = gameHandler.get() != nullptr;
  bool isPlayer = verifyPlayer(request);

  if (isGameOngoing && isPlayer) {

    if (isPlayerVsComputer) {
      stateStr = "3";
    } else {

      playerCookie = extractCookieValue(request);

      if (playerCookie == "playerX") {
        stateStr = "4";
      } else if (playerCookie == "playerO") {
        stateStr = "5";
      }
    }
  } else if (isGameOngoing && isPlayerVsComputer) {
    stateStr = "2";
  } else if (isGameOngoing && !isPlayerVsComputer) {
    stateStr = "1";
  } else if (!isGameOngoing) {
    stateStr = "0";
  }

  return HttpResponse::GETResponse(stateStr);
}