/*
 * HttpResponse.cpp
 */

#include "HttpResponse.h"

HttpResponse::HttpResponse(int conn_fd)
{
	_contentLength = 0;
	_statusCode = -1;
	_conn_fd = conn_fd;
}

HttpResponse::~HttpResponse(void)
{}

void HttpResponse::render(const char* filename)
{
	_file = std::string(filename);
}

int HttpResponse::sendResponse()
{
	int page_fd = open(_file.c_str(), O_RDONLY);
	FILE *page = fopen(_file.c_str(), "rt");
	_statusCode = 200;

	if (page == NULL) {
		_statusCode = 404;
	}

	fseek(page, 0L, SEEK_END);
	_contentLength = ftell(page);
	fseek(page, 0L, SEEK_SET);

	char tmp[512];
	sprintf(tmp,
			"HTTP/1.1 %d sample-text\r\nServer: test\r\nContent-Length: %d\r\n\r\n",
			_statusCode,
			_contentLength);

	_responseString = std::string(tmp);

	write(_conn_fd, _responseString.c_str(), _responseString.length());

	char buffer[1024];
	int size;
	do {
		size = read(page_fd, buffer, 1024);
		write(_conn_fd, buffer, size);
	} while (size > 0);

	fclose(page);
	close(page_fd);

	return 0;
}

int HttpResponse::sendResponse(int statusCode)
{
	_statusCode = statusCode;
	_contentLength = 0;

	char tmp[512];
	sprintf(tmp,
			"HTTP/1.1 %d sample-text\r\nServer: test\r\nContent-Length: %d\r\n\r\n",
			_statusCode,
			_contentLength);

	_responseString = std::string(tmp);

	write(_conn_fd, _responseString.c_str(), _responseString.length());
	return 0;
}
