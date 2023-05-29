#ifndef HTTP_HANDLER_HPP
#define HTTP_HANDLER_HPP

#include <memory.h>

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "../gameengine/GameHandler.hpp"

/*  Class: HttpHandler
    A singleton class that receives and processes HttpRequest objects.
    Runs GameHandler methods based on request method and endpoint.
    Creates HttpResponse objects and passes them back to the socket.

*/
class HttpHandler {
private:

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
  //   /*  Function: handlePOSTRequest

  //     Processes requests with POST method.

  //     Parameters:

  //       request - HttpRequest object for processing.

  //     Returns:

  //       HttpResponse object with status code 200 or 400, based on if
  //       GameHandler method ended with success.

  //     See Also:

  //       <HttpRequest>
  // */
  //   HttpResponse
  //   handlePOSTRequest(const std::shared_ptr<HttpRequest>& request) const;
  /*  Function: handleOPTIONSRequest

    Processes requests with OPTIONS method.

    Returns:

      HttpResponse object with Accept Headers.

    See Also:

      <HttpRequest>
*/
  HttpResponse handleOPTIONSRequest() const;

  // TODO: Documentation
  unsigned int boardSize;
  bool isPlayerVsComputer;
  bool verifyPlayer(const std::shared_ptr<HttpRequest>& request) const;
  std::string extractCookieValue(const std::shared_ptr<HttpRequest>& request) const;
  std::unique_ptr<GameHandler> gameHandler;

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