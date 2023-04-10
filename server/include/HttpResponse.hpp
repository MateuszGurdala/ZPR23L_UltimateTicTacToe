#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <ctime>
#include <time.h>
#include <memory>

class HttpResponse
{
private:
	std::vector<std::unique_ptr<std::string>> _headers;
	std::string _body;

	std::stringstream getResponseTop();
	std::string getDate();
	void pushBackHeader(std::string&& name, std::string&& value);
	void addHeaders();

public:
	HttpResponse(std::string& body);
	~HttpResponse();

	std::string getResponse();
};

#endif