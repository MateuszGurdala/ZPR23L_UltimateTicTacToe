#include "../../include/http/HttpHandler.hpp"
#include "../../include/helpers/BoardIndexConverter.hpp"
#include "../../include/helpers/MoveSimulator.hpp"

std::string allowOrigin;

HttpResponse HttpHandler::handle(const std::shared_ptr<HttpRequest> &request) {

  allowOrigin = (*request->headers)["Origin"];

  switch (request->getMethod()) {
  case OPTIONS:
    return handleOPTIONSRequest();
  case GET:
    return handleGETRequest(request);
  default:
    return HttpResponse::ERRORResponse("400", "INVALID REQUEST");
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
        "Player X Turn, choose segment",
        "Player O Turn, choose segment",
        "Unknown",
    */
    if (gameHandler) {
      return HttpResponse::GETResponse(gameHandler->GetGameStage());
    }
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
      auto response = HttpResponse::GETResponse(R"(true)");

      gameHandler.reset();

      if (player.compare("playerX")) {
        response.removeCookie("player", "playerX");
      } else if (player.compare("playerO")) {
        response.removeCookie("player", "playerO");
      }

      return response;
    } else {
      return HttpResponse::ERRORResponse("401", "UNAUTHORIZED");
    }
  }
  /* Make Move */
  else if (endpoint == "/MakeMove") {
    if (verifyPlayer(request) && gameHandler) {
      std::string player = extractCookieValue(request);
      std::string boardId = (request->queryParams)["boardId"];
      std::string segmentId = (request->queryParams)["segmentId"];

      unsigned int boardIdIndex = std::stoul(boardId);
      unsigned int segmentIdIndex = std::stoul(segmentId);

      Point outerCoordinates =
          BoardIndexConverter::IndexToPoint(boardIdIndex, boardSize);
      Point innerCoordinates =
          BoardIndexConverter::IndexToPoint(segmentIdIndex, boardSize);
      std::array<Point, 2> move = {outerCoordinates, innerCoordinates};

      bool isValid = gameHandler->PerformMoveValidation(outerCoordinates,
                                                        innerCoordinates);
      if (isValid) {
        gameHandler->PerformTurn(outerCoordinates, innerCoordinates);
      }
      return HttpResponse::GETResponse(
          gameHandler->MoveAsJson(false, move, isValid));
    } else {
      return HttpResponse::ERRORResponse("401", "UNAUTHORIZED");
    }
  }
  /* Create Game */
  else if (endpoint == "/CreateGame") {
    if (verifyPlayer(request)) {
      return HttpResponse::GETResponse(R"(false)");
    } else {
      std::string playerType;
      std::string gameMode = (request->queryParams)["gameMode"];
      std::string playerSign = (request->queryParams)["playerSign"];
      std::string boardSizeQuery = (request->queryParams)["boardSize"];
      char playerSignAsChar = playerSign.c_str()[0];

      if (playerSignAsChar != 'X' && playerSignAsChar != 'O') {
        return HttpResponse::ERRORResponse("400",
                                           "Invalid player "
                                           "figure while creating game.");
      }

      isPlayerVsComputer = gameMode == "Player_vs_AI" ? true : false;

      boardSize = std::stoi(boardSizeQuery);
      gameHandler = std::make_unique<GameHandler>(
          std::stoi(boardSizeQuery), playerSignAsChar, isPlayerVsComputer);

      // Assume game has been successfully created
      auto response = HttpResponse::GETResponse(R"(true)");

      if (playerSign == "X") {
        hostSign = 'X';
        guestSign = 'O';
        if (!isPlayerVsComputer) {
          response.setCookie("player", "playerX");
        }
      } else {
        hostSign = 'O';
        guestSign = 'X';
        if (!isPlayerVsComputer) {
          response.setCookie("player", "playerO");
        }
      }

      if (isPlayerVsComputer) {
        response.setCookie("player", "playerSolo");
      }

      return response;
    }
  }
  /* Join Game */
  else if (endpoint == "/JoinGame") {
    auto falseResponse = HttpResponse::GETResponse(R"(false)");
    if (verifyPlayer(request) || gameHandler.get() == NULL) {
    } else if (gameHandler.get() != NULL && isPlayerVsComputer) {
    } else if (gameHandler.get() != NULL && !isPlayerVsComputer) {
      if (isGuestConnected) {
      } else {
        isGuestConnected = true;
        if (guestSign == 'X') {
          auto response = HttpResponse::GETResponse(R"("X")");
          response.setCookie("player", "playerX");
          return response;
        } else {
          auto response = HttpResponse::GETResponse(R"("O")");
          response.setCookie("player", "playerO");
          return response;
        }
      }
    }
    return falseResponse;
  }
  /* Current Segment */
  else if (endpoint == "/CurrentSegment") {
    auto segment = gameHandler->GetSegmentIndex();
    return HttpResponse::GETResponse(std::to_string(segment));
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
  bool cond;

  rawCookie = (*request->headers)["Cookie"];

  if (!rawCookie.empty() && (p = rawCookie.find('=')) != std::string::npos) {
    cookie = rawCookie.substr(0, p);
    value = rawCookie.substr(p + 1, rawCookie.size());
  } else {
    throw std::exception();
  }

  // Somehow this really doesn't want to work
  // cond = std::find(std::begin(config::playerCookies),
  //                  std::end(config::playerCookies),
  //                  value) != std::end(config::playerCookies);

  for (auto i = config::playerCookies->begin();
       i != config::playerCookies->end(); ++i) {
    if ((cond = ((*i) == *value.c_str()))) {
      break;
    }
  }

  if (cookie == "player" && cond) {
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
  bool isGameOngoing = gameHandler.get() != NULL;
  bool isPlayer = verifyPlayer(request);

  if (isGameOngoing && isPlayer) {

    if (isPlayerVsComputer) {
      stateStr = "3";
    } else {

      playerCookie = extractCookieValue(request);

      if (playerCookie.at(6) == 'X') {
        stateStr = "4";
      } else if (playerCookie.at(6) == 'O') {
        stateStr = "5";
      }
    }
  } else {
    if (isGameOngoing && isPlayerVsComputer) {
      stateStr = "2";
    } else if (isGameOngoing && !isPlayerVsComputer) {
      stateStr = "1";
    } else if (!isGameOngoing) {
      stateStr = "0";
    }
  }

  return HttpResponse::GETResponse(stateStr);
}