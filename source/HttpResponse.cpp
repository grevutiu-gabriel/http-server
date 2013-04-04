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
	this->sendResponse();
}

void HttpResponse::render(const char* finename, Object params)
{
	_file = std::string(finename);
	int page_fd = open(_file.c_str(), O_RDONLY);
	FILE *page = fopen(_file.c_str(), "rt");
	_statusCode = 200;

	if (page == NULL) {
		_statusCode = 404;
	}

	fseek(page, 0L, SEEK_END);
	_contentLength = ftell(page);
	fseek(page, 0L, SEEK_SET);

	char buffer[_contentLength];
	int size = read(page_fd, buffer, 1024);
	/* processing buffer - replacing variables */

	std::string tmp = std::string(buffer);
	unsigned int start = 0, end;

	do {
		start = tmp.find("#{", start);
		if (start != std::string::npos && start < tmp.length()) {
			end = tmp.find("}", start + 1);
			if (end != std::string::npos && end < tmp.length()) {
				std::string tmp2 = tmp.substr(start + 2, end - start - 2);

				tmp = tmp.replace(start, end - start + 1, params[tmp2.c_str()]);

				size -= end - start + 1;
				size += params[tmp2.c_str()].length();

				start = end + 1;
			}
		}
	} while (start != std::string::npos && start > end && start < tmp.length());
	/* end of processing - writing to socket */

	_contentLength = size;

	char temp[512];
	sprintf(temp,
			"HTTP/1.1 %d sample-text\r\nServer: test\r\nContent-Length: %d\r\n\r\n",
			_statusCode,
			_contentLength);

	_responseString = std::string(temp);

	write(_conn_fd, _responseString.c_str(), _responseString.length());
	write(_conn_fd, tmp.c_str(), size + 1);

	fclose(page);
	close(page_fd);
	close(_conn_fd);
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
	close(_conn_fd);
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
	close(_conn_fd);
	return 0;
}

void HttpResponse::writeBytes(const char* bytes)
{
	_statusCode = 200;
	_contentLength = std::string(bytes).length();

	char tmp[512];
	sprintf(tmp,
			"HTTP/1.1 %d sample-text\r\nServer: test\r\nContent-Length: %d\r\n\r\n",
			_statusCode,
			_contentLength);

	_responseString = std::string(tmp);

	write(_conn_fd, _responseString.c_str(), _responseString.length());
	write(_conn_fd, bytes, _contentLength);
}

void HttpResponse::end(void)
{
	shutdown(_conn_fd, SHUT_RDWR);
}

void HttpResponse::end(const char* bytes)
{
	writeBytes(bytes);
	end();
}
