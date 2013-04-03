/*
 * HTTP Server entry point.
 */

#include <iostream>

#include "source/HTTPServer.h"

int index(HttpRequest *req, HttpResponse *res)
{
	res->render("Public/index.html");
	return 0;
}

int test(HttpRequest *req, HttpResponse *res)
{
	res->render("Public/test.html");
	return 0;
}

int main(int argc, char *argv[]) {

	HTTPServer server;
	server.addRoute("/", index);
	server.addRoute("/test", test);

	server.run(8084);
	return 0;
}




