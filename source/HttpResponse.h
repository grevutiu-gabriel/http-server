/*
 * HttpResponse.h
 * Source: Internet of course (for inspiration);
 * all code is mine!
 */

#ifndef HTTPRESPONSE_H_
#define HTTPRESPONSE_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>


class HttpResponse {
friend class HTTPServer;
public:
	HttpResponse(int conn_fd);
	~HttpResponse(void);

	void render(const char* filename);
protected:
	int sendResponse();
	int sendResponse(int statusCode);
private:
	int _conn_fd;
	std::string _file;
	int _statusCode;
	int _contentLength;

	std::string _responseString;
};

#endif /* HTTPRESPONSE_H_ */
