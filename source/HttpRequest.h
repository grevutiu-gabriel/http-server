/*
 * HttpRequest.h
 * Source: mostly Internet inspiration, all code
 * is my own.
 */

#ifndef HTTPREQUEST_H_
#define HTTPREQUEST_H_

#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>

/* #define NDEBUG */

class HttpRequest {
public:
	HttpRequest(const char* method, const char* url);
	HttpRequest(char* requestString);
	~HttpRequest(void);

	std::string getURL(void);
	std::string getMethod(void);
private:
	std::vector<std::string>		_reqHeaders;
	std::string						_reqString;
	std::string						_url;
	std::string						_method;

protected:
	void addHeader(const char* key, const char* value);
	void addHeader(const char* key, int value);
	void endHeaders(void);
};


#endif /* HTTPREQUEST_H_ */
