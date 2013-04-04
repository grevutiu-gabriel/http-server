/*
 * HTTP Server entry point.
 */

#include <iostream>

#include "source/HTTPServer.h"
#include "source/json/Object.h"

int index(HttpRequest *req, HttpResponse *res)
{
	Object params;
	params["custom"] = "this is a custom message!";

	std::cout << "Rendering index.html...\n";
	res->render("public/index.html", params);
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

	server.run(3040);

//	Object obj;
//
//	obj["id"] = "alex";
//	obj["am mere"] = "jsdfd";
//	std::cout << obj["id"];
//	std::cout << obj["am mere"];

	return 0;
}




