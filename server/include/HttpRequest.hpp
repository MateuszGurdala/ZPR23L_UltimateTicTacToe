#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <map>
#include <string>
#include <iostream>
#include <vector>

class HttpRequest
{
private:
	const std::string _newLine = "\n";
	const std::string _colon = ":";

	std::string _requestType, _body;
	std::map<std::string, std::string> _headers;

	int parseBody(std::string& request);
	int parseHeaders(std::string& request);
	int parseRequestType(std::string& request);

public:
	HttpRequest(std::string&& request);
	const std::string& operator[](const std::string& key) const;
};

#endif