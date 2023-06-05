#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include "HttpHeaders.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

enum method { GET, POST, OPTIONS, INVALID };

/*  Class: HttpRequest
    A class that acts as abstraction between raw http request data and
    HttpHandler.
*/
class HttpRequest {
  using UHeaders = std::unique_ptr<HttpHeaders>;

private:
  const std::string _newLine = "\n";
  const std::string _colon = ":";
  const std::string _space = " ";
  const std::string _questionmark = "?";
  const std::string _ampersand = "&";
  const std::string _equals = "=";

  std::string _body, _endpoint;
  method _method;

  /*  Function: parseBody

        Parses body from json format.

      Parameters:

        request - Request data as std::string.

      Returns:

        0 if parsing ended with success, else 1;
    */
  int parseBody(std::string &request);
  /*  Function: parseRequestType

        Extracts request type from header line.

      Parameters:

        request - Request data as std::string.

      Returns:

        0 if parsing ended with success, else 1;
    */
  int parseRequestType(std::string &request);
  /*  Function: parseRequestMethod

        Extracts request method from header line.

      Parameters:

        request - Request data as std::string.

      Returns:

        0 if parsing ended with success, else 1;
    */
  int parseRequestMethod(std::string &requestType);
  /*  Function: verboseRequest

        Prints parsed request to the standard output.
    */
  void verboseRequest() const;
  /*  Function: extractQueryParameters

        Parses query params and pushes them as param-value pairs into
     queryParams map;
    */
  void extractQueryParameters();

public:
  UHeaders headers;
  std::map<std::string, std::string> queryParams;
  /*  Constructor: HttpRequest

    Parses body from json format.

  Parameters:

    request - Raw request data as std::string.
*/
  explicit HttpRequest(std::string &&request);
  /*  Function: getEndpoint

      Returns:

        Request endpoint;
    */
  std::string getEndpoint() const;
  /*  Function: getEndpoint

      Returns:

        Request method;
    */
  method getMethod() const;
};

#endif