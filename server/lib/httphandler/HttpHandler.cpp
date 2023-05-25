#include "../../include/http/HttpHandler.hpp"
#include "../../include/entities/MainBoard.hpp"

HttpResponse
HttpHandler::handle(const std::shared_ptr<HttpRequest>& request) const {
	switch (request->getMethod()) {
	case OPTIONS:
		return handleOPTIONSRequest();
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

	const std::string endpoint = request->getEndpoint();

	/* Board State */
	if (endpoint == "/BoardState") {
		/* TEMP */
		auto mainBoard = std::make_unique<MainBoard>(3);
		Point outerBoardCoords = Point(1, 1);
		Point innerBoardCoords = Point(1, 1);
		mainBoard->MakeMove(outerBoardCoords, innerBoardCoords, 'X');
		return HttpResponse::GETResponse(mainBoard->ToJson(false));
	}
	/* Game State */
	else if (endpoint == "/GameState")
	{
		return HttpResponse::GETResponse(R"(0)");; //Client parses value into numerical enum
	}
	/* Game Stage */
	else if (endpoint == "/GameStage")
	{
		return HttpResponse::GETResponse(R"("Unknown")"); //State must be inside ""
	}
	/* Server Status */
	else if (endpoint == "/ServerStatus")
	{
		return HttpResponse::GETResponse(R"(true)");
	}
	/* End Gmae */
	// Changed to GET response becouse there is no need for request body
	else if (endpoint == "/EndGame")
	{
		return HttpResponse::GETResponse(R"(true)");
	}
	/* Invalid Endpoint */
	else {
		return HttpResponse::ERRORResponse();
	}
}

HttpResponse HttpHandler::handlePOSTRequest(
	const std::shared_ptr<HttpRequest>& request) const {

	const std::string endpoint = request->getEndpoint();

	/* Make Move */
	if (endpoint == "/MakeMove")
	{
		return HttpResponse::ERRORResponse();
	}
	/* Pick Segment */
	else if (endpoint == "/PickSegment")
	{
		return HttpResponse::ERRORResponse();
	}
	/* Create Game */
	else if (endpoint == "/CreateGame")
	{
		return HttpResponse::POSTResponse(R"(false)");;//Only true/false
	}
	/* Invalid Endpoint */
	else
	{
		return HttpResponse::ERRORResponse();
	}
}

HttpResponse HttpHandler::handleOPTIONSRequest() const {
	return HttpResponse::OPTIONSResponse();
}