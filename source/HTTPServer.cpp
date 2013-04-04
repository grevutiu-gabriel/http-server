/*
 * HTTPServer.cpp
 */

#include "HTTPServer.h"

HTTPServer::HTTPServer(void)
{
	this->_port = 3000;
	this->_fd = 0;
	this->_listening = false;
}

HTTPServer::HTTPServer(int port)
{
	this->_port = (port > 1024) ? port : 3000;
	this->_fd = 0;
	this->_listening = false;
}

HTTPServer::~HTTPServer(void)
{
	if (_fd >= 0)
		close(_fd);
	// Free all the memory
}

int HTTPServer::setPort(int port)
{
	_port = (port > 1024) ? port : _port;
	return (_port == port);
}

int HTTPServer::getPort(void)
{
	return _port;
}

int HTTPServer::run(void)
{
	int err;

	_thisAddr.sin_family = AF_INET;
	_thisAddr.sin_port = htons(_port);
	inet_aton("127.0.0.1", &_thisAddr.sin_addr);

	_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (_fd < 0) {
		_logger.logMessage(ERROR, "Socket could not be created!");
		return -1;
	}

	err = bind(_fd, (struct sockaddr *) &_thisAddr, sizeof(struct sockaddr*));

	if (err < 0) {
		char msg[256];
		sprintf(msg, "Binding on port %d failed!", _port);
		_logger.logMessage(ERROR, msg);
		//std::cerr << "[ERROR] Binding on port " << _port << " failed!\n";
		return -2;
	}

	err = listen(_fd, 10);

	if (err < 0) {
		char msg[256];
		sprintf(msg, "Cannot listen on port %d!", _port);
		_logger.logMessage(ERROR, msg);
		//std::cerr << "[ERROR] Cannot listen on port " << _port << "\n";
		return -3;
	}

	_listening = true;

	char msg[256];
	sprintf(msg, "Server running and listening on port %d...", _port);
	_logger.logMessage(INFO, msg);
	//std::cout << "[INFO] Server running and listening on port " << _port << "\n";

	this->startListening();
	return 0;
}

int HTTPServer::run(int port)
{
	int err;

	this->_port = (port > 1024) ? port : _port;

	memset(&_thisAddr, 0, sizeof(sockaddr_in));

	_thisAddr.sin_family = AF_INET;
	_thisAddr.sin_port = htons(_port);
	_thisAddr.sin_addr.s_addr = INADDR_ANY;

	_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_fd < 0) {
		std::cerr << "[ERROR] Socket could not be created!\n";
		return -1;
	}

	err = bind(_fd, (struct sockaddr *) &_thisAddr, sizeof(struct sockaddr));

	if (err < 0) {
		std::cerr << "[ERROR] Binding on port " << _port << " failed!\n";
		return -2;
	}

	err = listen(_fd, 10);

	if (err < 0) {
		std::cerr << "[ERROR] Cannot listen on port " << _port << "\n";
		return -3;
	}

	std::cout << "[INFO] Server running and listening on port " << _port << "...\n";

	this->startListening();
	return 0;
}

void HTTPServer::stop()
{
	if (_fd > 0)
		close(_fd);
}

void HTTPServer::addRoute(std::string route, Callback cb)
{
	_routes.push_back(RoutePair(route, cb));
}

void HTTPServer::addRoute(const char* route, Callback cb)
{
	_routes.push_back(RoutePair(std::string(route), cb));
}

void HTTPServer::startListening(void)
{
	int conn_fd, size;
	bool found;
	HttpRequest *req;
	HttpResponse *res;
	char buffer[512];
	unsigned int len = sizeof(_remoteAddr);
	while (true) {

		found = false;

		conn_fd = accept(_fd, (sockaddr*) &_remoteAddr, &len);
		if (conn_fd <= 0) {
			_logger.logMessage(ERROR, "Accepting connection failed!");
			//assert(false);
			continue;
		}

		size = read(conn_fd, buffer, 512);
		if (size < 0) {
			_logger.logMessage(ERROR, "Reading from socket failed!");
			assert(false);
		}

		req = new HttpRequest(buffer);
		res = new HttpResponse(conn_fd);

		std::string url = req->getURL();

		for (int i = 0; i < (int) _routes.size(); i++) {
			std::cout << "checking " << _routes[i].first << " and " << url << "\n";
			if (_routes[i].first == url) {
				_routes[i].second(req, res);
				found = true;
				break;
			}
		}

		if (!found) {
			res->sendResponse(404);
			_logger.logMessage(ERROR, std::string("Cannot GET " + url + "!").c_str());
		}

		delete req;
		delete res;

	}
	_logger.logMessage(WARNING, "Server exiting main loop...");
}
