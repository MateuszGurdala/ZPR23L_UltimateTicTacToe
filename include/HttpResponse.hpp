#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <ctime>
#include <time.h>

class HttpResponse
{
private:
	std::vector<std::string> _headers;

	std::stringstream getResponseTop();
	std::string getDateHeader();
	void addServerHeader();
	void addContentTypeHeader();
	void addContentLengthHeader(std::string &body);
	void addConnectionHeader();
	void addBaseHeaders();
	std::string endHeaders();

public:
	HttpResponse();
	~HttpResponse();

	std::string getResponse(std::string &body);
};

#endif