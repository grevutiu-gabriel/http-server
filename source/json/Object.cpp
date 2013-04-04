/*
 * Object.cpp
 */

#include "Object.h"

Object::Object(void)
{
	_count = 0;
}

Object::~Object(void)
{}

std::string& Object::operator [](std::string key)
{
	bool found = false;
	for (int i = 0; i < _count; i++)
		if (_params[i].first == key) {
			return _params[i].second;
			found = true;
			break;
		}

	if (!found) {
		_params.push_back(std::pair<std::string, std::string>(key, std::string("undefined")));
		_count++;
		return _params[_count - 1].second;
	}
}




