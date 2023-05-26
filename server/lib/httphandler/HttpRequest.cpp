#include "../../include/http/HttpRequest.hpp"
#include "../../src/config.hpp"

HttpRequest::HttpRequest(std::string&& request) {
	parseRequestType(request);
	parseBody(request);

	headers = std::make_unique<HttpHeaders>(HttpHeaders(request));

	if (config::verbose) {
		verboseRequest();
	}
}

std::string HttpRequest::getEndpoint() const { return _endpoint; }
method HttpRequest::getMethod() const { return _method; }

void HttpRequest::verboseRequest() const {
	std::cout << "REQUEST:\n";
	std::cout << "METHOD: " << _method << '\n';
	std::cout << "ENDPOINT: " << _endpoint << '\n';

	headers->verbose();

	if (!queryParams.empty())
	{
		std::cout << "QUERY PARAMS:\n";

		for (auto queryParam : queryParams)
		{
			std::cout << queryParam.first;
			std::cout << " : ";
			std::cout << queryParam.second;
			std::cout << "\n";
		}
	}

	if (!_body.empty()) {
		std::cout << "BODY:\n";
		std::cout << _body << '\n';
	}
	std::cout << "END REQUEST\n\n";
}

int HttpRequest::parseBody(std::string& request) {
	size_t pos = 0;

	if ((pos = request.find('{')) != std::string::npos) {
		_body = request.substr(pos,
			request.find('}') - pos + std::string("}").length());
		request.erase(pos - _newLine.length(), pos + _body.length());
		return 0;
	}
	return 1;
}

int HttpRequest::parseRequestType(std::string& request) {
	size_t pos = 0;
	std::string requestType;

	if ((pos = request.find(_newLine)) != std::string::npos) {
		requestType = request.substr(0, pos - _newLine.length());
		request.erase(0, requestType.length() + _newLine.length() * 2);
		parseRequestMethod(requestType);
		return 0;
	}
	return 1;
}

int HttpRequest::parseRequestMethod(std::string& requestType) {
	size_t pos;
	std::string method;
	if ((pos = requestType.find(_space)) != std::string::npos) {

		method = requestType.substr(0, pos);

		if (method == "GET") {
			_method = method::GET;
		}
		else if (method == "POST") {
			_method = method::POST;
		}
		else if (method == "OPTIONS") {
			_method = method::OPTIONS;
		}
		else {
			_method = method::INVALID;
		}

		requestType.erase(0, pos + _space.length());
	}

	if ((pos = requestType.find(_space)) != std::string::npos) {
		_endpoint = requestType.substr(0, pos);
	}

	extractQueryParameters();

	return 0;
}

void HttpRequest::extractQueryParameters() {
	size_t pos;
	std::string queryString, key, value;
	std::vector<std::string> params;

	if ((pos = _endpoint.find(_questionmark)) != std::string::npos)
	{
		queryString = _endpoint.substr(pos + _questionmark.size(), _endpoint.size());
		_endpoint.erase(pos, _endpoint.size());

		while ((pos = queryString.find(_ampersand)) != std::string::npos)
		{
			params.push_back(queryString.substr(0, pos));
			queryString.erase(0, pos + _ampersand.size());
		}
		params.push_back(queryString.substr(0, pos));

		for (auto param : params)
		{
			if ((pos = param.find(_equals)) != std::string::npos)
			{
				queryParams[param.substr(0, pos)] = param.substr(pos + _equals.size(), param.size());
			}
		}
	}

	return;
}