/*
 * HTTP Server entry point.
 */

#include <iostream>

#include "source/HTTPServer.h"

int index(HttpRequest *req, HttpResponse *res)
{
	std::cout << "Rendering index.html...\n";
	res->render("public/index.html");
	return 0;
}

int test(HttpRequest *req, HttpResponse *res)
{
	res->render("public/test.html");
	return 0;
}

int anotherOne(HttpRequest *req, HttpResponse *res)
{
	res->writeBytes("This is a message!");
	res->end();
	return 0;
}

int main(int argc, char *argv[]) {

	HTTPServer server;
	server.addRoute("/", index);
	server.addRoute("/test", test);
	server.addRoute("/bytes", anotherOne);

	server.run(3006);
	return 0;
}




