#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include "HttpHeaders.hpp"
#include <sstream>
#include <string>

/*  Class: HttpResponse
    A class that acts as abstraction between raw http response data and
    HttpHandler.
*/
class HttpResponse {
private:
  HttpHeaders _headers;
  std::string _statusLine, _body;

public:
  /*  Constructor: HttpResponse

        Default constructor.
    */
  HttpResponse();
  /*  Constructor: HttpResponse

        Constructor for responses with body.

      Parameters:

        body - Response body.
    */
  explicit HttpResponse(std::string &body);
  /*  Constructor: HttpResponse

        Constructor for responses with body.

      Parameters:

        body - Response body.
    */
  explicit HttpResponse(std::string &&body);
  /*  Constructor: HttpResponse

        Copy constructor.

      Parameters:

        obj - HttpResponse object to copy.
    */
  HttpResponse(HttpResponse &&obj);
  /*  Constructor: OPTIONSResponse

        Static method that creates default response for request with OPTIONS
        method.

      Returns:

        Default HttpResponse object with Allow headers.
    */
  static HttpResponse OPTIONSResponse();
  /*  Function: ERRORResponse

        Static method that creates response object for invalid requests.

      Returns:

        Default HttpResponse object with status code 400.
    */
  static HttpResponse ERRORResponse();
  /*  Function: GETResponse

        Static method that creates response object with body for GET request.

      Parameters:

        body - Response body.

      Returns:

        Default HttpResponse object with body.
    */
  static HttpResponse GETResponse(std::string &&body);
  /*  Function: GETResponse

        Static method that creates response object with body for GET request.

      Parameters:

        body - response body.

      Returns:

        Default HttpResponse object with body.
    */
  static HttpResponse POSTResponse(std::string &&body);
  /*  Function: toString

      Returns:

        HttpResponse data as raw std::string that can be interpreted by web
        browsers.
    */
  std::string toString() const;
};

#endif