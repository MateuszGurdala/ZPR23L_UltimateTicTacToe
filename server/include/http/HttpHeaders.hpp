#ifndef HTTP_HEADERS_HPP
#define HTTP_HEADERS_HPP

#include "../../src/config.hpp"
#include <chrono>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

const std::map<std::string, std::string> globalHeaders = {
    {"Server", config::serverName},
    {"Content-Type", config::contentType},
    {"Access-Control-Allow-Origin", config::allowOrigin},
    {"Access-Control-Allow-Methods", config::allowMethods},
    {"Allow", config::allowMethods},
    {"Access-Control-Allow-Headers", config::allowHeaders}};

/*  Class: HttpHeaders
    Helper class used for parsing and accessing http headers, or for building
    headers based on request requirements.
*/
class HttpHeaders {
private:
  const std::string _newLine = "\n";
  const std::string _colon = ":";

  std::map<std::string, std::string> _headers;

public:
  /*  Constructor: HttpHeaders

          Default constructor. Used to add headers to HttpResponse object.

        See Also:

          <HttpResponse>
    */
  HttpHeaders();
  /*  Constructor: HttpHeaders

        Constructor that parses headers from string object. Used when generating
        HttpRequest object.

      Parameters:

        headers - reference to std::string that contains raw headers.

      See Also:

        <HttpRequest>
*/
  explicit HttpHeaders(std::string &headers);
  /*  Function: addHeader

    Adds key-value pair as header data to internal std::map structure.

    Parameters:

      key - Header name.
      value - Header value.

    Returns:

      1 if header with same name was already added. Else 0.
*/
  int addHeader(std::string &key, const std::string &value);
  /*  Function: addHeader

        Adds key-value pair as header data to internal std::map structure.

      Parameters:

        key - Header name.
        value - Header value.

      Returns:

        1 if header with same name was already added. Else 0.
*/
  int addHeader(std::string &&key, const std::string &value);
  /*  Function: addHeader

        Adds key-value pair as header data to internal std::map structure.

      Parameters:

        key - Header name.
        value - Header value.

      Returns:

        1 if header with same name was already added. Else 0.
*/
  int addHeader(std::string &&key, std::string &&value);
  /*  Function: addDateHeader

        Adds a header with the date and time the response was generated.

      Returns:

        1 if header with same name was already added. Else 0.
*/
  int addDateHeader();
  /*  Function: addAllowHeader

        Adds a header with data types that are accepted by the server.

      Returns:

        1 if header with same name was already added. Else 0.
*/
  int addAllowHeader();
  /*  Function: addContentLengthHeader

        Adds a header with content length.

      Parameters:

        length - Length of response body.

      Returns:

        1 if header with same name was already added. Else 0.
*/
  int addContentLengthHeader(int length);
  /*  Function: closeConnection

        Adds a header that indicates that connection should be closed.

      Returns:

      1 if header with same name was already added. Else 0.
*/
  int closeConnection();
  /*  Function: addCORSHeaders

        Adds a header that indicates that connection should be closed.

      Returns:

        1 if header with same name was already added. Else 0.
*/
  int addCORSHeaders();
  /*  Function: toString

      Returns:

        All added headers as std::string formatted to be understood by web
        browsers.
*/
  std::string toString() const;
  /*  Function: verbose

      Returns:

        Headers data as formatted std::string.
*/
  void verbose() const;
  /*  Function: operator[]

        Operator overload used to more easily obtain header data by its name.

      Parameters:

        key - Header name.

      Returns:

        Header data.
*/
  const std::string &operator[](const std::string &key) const;
  /*  Function: operator=

        Copy operator.
*/
  HttpHeaders &operator=(const HttpHeaders &obj);
};

#endif