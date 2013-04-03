/*
 * HttpRequest.cpp
 *
 */

#include "HttpRequest.h"

HttpRequest::HttpRequest(const char* method, const char* url)
{
	char tmp[512];
	sprintf(tmp, "%s %s HTTP/1.1", method, url);
	_reqHeaders.push_back(tmp);

	addHeader("Host", "127.0.0.1");
	addHeader("Accept-Encoding", "identity");

	_url = std::string(url);
	_method = std::string(method);
}

HttpRequest::HttpRequest(char* requestString)
{
	std::stringstream ss(requestString);

	ss >> _method;
	ss >> _url;
}

HttpRequest::~HttpRequest(void)
{}

void HttpRequest::addHeader(const char* key, const char* value)
{
	_reqHeaders.push_back(std::string(key) + ": " + std::string(value));
}

void HttpRequest::addHeader(const char* key, int value)
{
	char tmp[64];
	sprintf(tmp, "%d", value);
	_reqHeaders.push_back(std::string(key) + ": " + std::string(tmp));
}

void HttpRequest::endHeaders(void)
{
	_reqHeaders.push_back("");
	for (int i = 0; i < (int) _reqHeaders.size(); i++) {
		_reqString += _reqHeaders[i] + "\r\n";
	}
}

std::string HttpRequest::getURL(void)
{
	return _url;
}

std::string HttpRequest::getMethod(void)
{
	return _method;
}
