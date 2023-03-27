#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <map>
#include <string>

class HttpRequest
{
private:
    std::map<std::string, std::string> _headers;
    std::string _body;

    int parseHeaders();

public:
    HttpRequest(std::string &request);
    ~HttpRequest();
};

#endif