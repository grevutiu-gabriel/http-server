/*
 * HTTPServer.h
 * Main features defined here
 */

#ifndef HTTPSERVER_H_
#define HTTPSERVER_H_

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>

#include "Logger.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

typedef int (*Callback)(HttpRequest*, HttpResponse*);
typedef std::pair<std::string, Callback> RoutePair;

class HTTPServer {
friend class HttpResponse;
public:
	HTTPServer(void);
	HTTPServer(int port);
	~HTTPServer(void);

	int setPort(int port);
	int getPort(void) const;

	int run(void);
	int run(int port);
	void stop(void);

	void addRoute(std::string route, Callback cb);
	void addRoute(const char* route, Callback cb);

private:
	int 						_port;			// listening port
	int 						_fd;			// socked file descriptor
	struct sockaddr_in 			_thisAddr;
	struct sockaddr_in 			_remoteAddr;
	std::vector<RoutePair>		_routes;
	bool						_listening;
	Logger 						_logger;

	void startListening(void);
};

#endif /* HTTPSERVER_H_ */
