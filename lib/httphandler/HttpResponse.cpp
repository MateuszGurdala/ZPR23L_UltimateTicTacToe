#include "../../include/HttpResponse.hpp"

#define VERSION "HTTP/1.1"
#define STATUS_OK "200"
#define STATUS_MESSAGE "OK"

#define CONTENT_TYPE "text/html; charset=utf-8"
#define SERVER_NAME "UltimateTicTacToeServer"
#define CONNECTION "close"

using namespace std;

HttpResponse::HttpResponse() {}

HttpResponse::~HttpResponse()
{
	_headers.clear();
	vector<string>().swap(_headers); // Deallocate memory
}

stringstream HttpResponse::getResponseTop()
{
	stringstream ss;
	ss << VERSION << " ";
	ss << STATUS_OK << " ";
	ss << STATUS_MESSAGE << endl;

	return ss;
}

string HttpResponse::getDateHeader()
{
	string header = "Date: ";

	auto now = chrono::system_clock::now();
	auto time = chrono::system_clock::to_time_t(now);

	header += ctime(&time);
	return header;
}

void HttpResponse::addServerHeader()
{
	string header = "Server: ";
	header += SERVER_NAME;
	_headers.push_back(header);
}

void HttpResponse::addContentTypeHeader()
{
	string header = "Content-Type: ";
	header += CONTENT_TYPE;
	_headers.push_back(header);
}

void HttpResponse::addConnectionHeader()
{
	string header = "Connection: ";
	header += CONNECTION;
	_headers.push_back(header);
}

void HttpResponse::addContentLengthHeader(string &body)
{
	string header = "Content-Length: ";
	header += to_string(body.length());
	_headers.push_back(header);
}

void HttpResponse::addBaseHeaders()
{
	addServerHeader();
	addContentTypeHeader();
	addConnectionHeader();
}

string HttpResponse::endHeaders()
{
	return "\n";
}

string HttpResponse::getResponse(string &body)
{
	stringstream ss = getResponseTop();

	ss << getDateHeader();
	addBaseHeaders();
	addContentLengthHeader(body);

	for (auto i = _headers.begin(); i != _headers.end(); i++)
	{
		ss << *i << endl;
	}

	ss << endHeaders();
	ss << body;

	return ss.str();
}