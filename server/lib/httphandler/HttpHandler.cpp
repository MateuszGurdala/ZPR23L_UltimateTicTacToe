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
		return HttpResponse::ERRORResponse("400", "INVALID REQUEST");
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
		auto resp = HttpResponse::GETResponse(R"(0)");
		resp.setCookie("player", "PlayerSolo");
		return resp; //Client parses value into numerical enum
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
	/* End Game */
	else if (endpoint == "/EndGame")
	{
		return HttpResponse::GETResponse(R"(true)");
	}
	else if (endpoint == "/MakeMove")
	{
		return HttpResponse::ERRORResponse("400", "NOT IMPLEMENTED");
	}
	/* Pick Segment */
	else if (endpoint == "/PickSegment")
	{
		return HttpResponse::ERRORResponse("400", "NOT IMPLEMENTED");
	}
	/* Create Game */
	else if (endpoint == "/CreateGame")
	{
		if (!verifyPlayer(request))
		{
			return HttpResponse::GETResponse(R"(false)");
		}
		return HttpResponse::GETResponse(R"(true)");;//Only true/false
	}
	/* Invalid Endpoint */
	else {
		return HttpResponse::ERRORResponse("400", "INVALID REQUEST");
	}
}

HttpResponse HttpHandler::handlePOSTRequest(
	const std::shared_ptr<HttpRequest>& request) const {

	const std::string endpoint = request->getEndpoint();

	///* Make Move */
	//if (endpoint == "/MakeMove")
	//{
	//	return HttpResponse::ERRORResponse("400", "NOT IMPLEMENTED");
	//}
	///* Pick Segment */
	//else if (endpoint == "/PickSegment")
	//{
	//	return HttpResponse::ERRORResponse("400", "NOT IMPLEMENTED");
	//}
	///* Create Game */
	//else if (endpoint == "/CreateGame")
	//{
	//	if (!verifyPlayer(request))
	//	{
	//		return HttpResponse::ERRORResponse("469", "UNAUTHORISED");
	//	}
	//	return HttpResponse::POSTResponse(R"(false)");;//Only true/false
	//}
	///* Invalid Endpoint */
	//else
	//{
		return HttpResponse::ERRORResponse("500", "NOT IMPLEMENTED");
	//}
}

HttpResponse HttpHandler::handleOPTIONSRequest() const {
	return HttpResponse::OPTIONSResponse();
}

bool HttpHandler::verifyPlayer(const std::shared_ptr<HttpRequest> request) const
{
	try
	{
		extractCookieValue(request);
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

std::string HttpHandler::extractCookieValue(const std::shared_ptr<HttpRequest> request) const {
	size_t p;
	std::string rawCookie;
	std::string cookie;
	std::string value;

	rawCookie = (*request->headers)["Cookie"];
	std::cout << rawCookie << "\n";

	if (!rawCookie.empty() && (p = rawCookie.find("=")) != std::string::npos)
	{
		cookie = rawCookie.substr(0, p);
		value = rawCookie.substr(p + 1, rawCookie.size());
	}
	else
	{
		throw new std::exception;
	}

	if (cookie == "player" && std::find(std::begin(config::playerCookies),
		std::end(config::playerCookies), value)
		!= std::end(config::playerCookies))
	{
		return value;
	}
	else
	{
		throw new std::exception;
	}
}
