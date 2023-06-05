#ifndef HTTP_HANDLER_HPP
#define HTTP_HANDLER_HPP

#include <memory.h>

#include "../gameengine/GameHandler.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

/*  Class: HttpHandler
    A singleton class that receives and processes HttpRequest objects.
    Runs GameHandler methods based on request method and endpoint.
    Creates HttpResponse objects and passes them back to the socket.

*/
class HttpHandler {
private:
  unsigned int boardSize;
  bool isPlayerVsComputer = true;
  bool isGuestConnected = false;
  char hostSign;
  char guestSign;
  std::unique_ptr<GameHandler> gameHandler;
  /*  Function: handleGETRequest

    Processes requests with GET method.

    Parameters:

      request - HttpRequest object for processing.

    Returns:

      HttpResponse object with/without body and status code 200 or empty
      response with status code 400, based on if GameHandler method ended with
      success.

    See Also:

      <HttpRequest>
*/
  HttpResponse handleGETRequest(const std::shared_ptr<HttpRequest> &request);
  /*  Function: handleOPTIONSRequest

    Processes requests with OPTIONS method.

    Returns:

      HttpResponse object with Accept Headers.

    See Also:

      <HttpRequest>
*/
  HttpResponse handleOPTIONSRequest() const;
  /*  Function: verifyPlayer

    Authorizes request sender based on cookie value.

    Returns:

      True if player is verified, otherwise false.

    See Also:

      <HttpRequest>
      <extractCookieValue>
*/
  bool verifyPlayer(const std::shared_ptr<HttpRequest> &request) const;
  /*  Function: extractCookieValue

    Extracts player cookie from the request headers and compares its value to
    accepted values. If cookie with the name "player" is absent or contains
    an incorrect value, an error will be thrown.

    Returns:

      Cookie value as std::string.

    See Also:

      <HttpRequest>
      <verifyPlayer>
*/
  std::string
  extractCookieValue(const std::shared_ptr<HttpRequest> &request) const;
  /*  Function: serverState

    Returns:

      Current server state as HttpResponse object.

    See Also:

      <HttpRequest>
      <HttpResponse>
      <serverStateEndpoint>
*/
  HttpResponse serverState(const std::shared_ptr<HttpRequest> &request) const;
  /*  Function: boardStateEndpoint

    If game is initialised, it returns the current state of the board in json
    format.

    Returns:

      HttpResponse object with a GameHandler::BoardStateAsJson() return value;

    See Also:

      <HttpRequest>
      <BoardStateAsJson>
*/
  HttpResponse boardStateEndpoint() const;
  /*  Function: serverStateEndpoint

    Returns:

      HttpResponse object with Accept Headers.

    See Also:

      <HttpRequest>
      <serverState>
*/
  HttpResponse
  serverStateEndpoint(const std::shared_ptr<HttpRequest> &request) const;
  /*  Function: gameStageEndpoint

    Returns:

      Current game stage as HttpResponse object if game is initialized.

    See Also:

      <HttpRequest>
      <HttpResponse>
*/
  HttpResponse gameStageEndpoint() const;
  /*  Function: currentSegmentEndpoint

    Returns:

      Currently active segment number as HttpResponse object. If value is
    unknown, it returns -1;

    See Also:

      <HttpRequest>
      <GameHandler>
      <GetSegmentIndex>
*/
  HttpResponse currentSegmentEndpoint() const;
  /*  Function: endGameEndpoint

    Ends game on behalf on sender. Removes player cookie.

    Returns:

      HttpResponse object with boolean value that indicates if operation ended
    in success.

    See Also:

      <HttpRequest>
*/
  HttpResponse endGameEndpoint(const std::shared_ptr<HttpRequest> &request);
  /*  Function: makeMoveEndpoint

    Makes move based on given board and segment values. If sender is not
    authorized or move is illegal, it returns invalid request HttpResponse
    object.

    Returns:

      GameHandler::MoveAsJson as body of HttpResponse object.

    See Also:

      <HttpRequest>
      <GameHandler>
      <PerformTurn>
      <MoveAsJson>
*/
  HttpResponse makeMoveEndpoint(const std::shared_ptr<HttpRequest> &request);
  /*  Function: createGameEndpoint

    Creates GameHandler object on server with board size, game mode and host
    sign values from request.

    Returns:

      HttpResponse object with player Set-Cookie header.

    See Also:

      <HttpRequest>
      <GameHandler>
*/
  HttpResponse createGameEndpoint(const std::shared_ptr<HttpRequest> &request);
  /*  Function: joinGameEndpoint

    Processes requests with OPTIONS method.

    Returns:

      HttpResponse object with a Boolean value indicating whether the player has
      successfully joined the game. If true, the player's cookie is set in the
      response.

    See Also:

      <HttpRequest>
      <HttpResponse>
*/
  HttpResponse joinGameEndpoint(const std::shared_ptr<HttpRequest> &request);

public:
  /*  Function: handle

  Processes HttpRequest objects.

  Parameters:

    request - HttpRequest object for processing.

  Returns:

    HttpResponse object.

  See Also:

    <HttpRequest>
*/
  HttpResponse handle(const std::shared_ptr<HttpRequest> &request);
};

#endif