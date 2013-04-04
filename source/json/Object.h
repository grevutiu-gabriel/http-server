/*
 * Object.h
 *
 *  Created on: Apr 4, 2013
 *      Author: omn
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <string>
#include <vector>

typedef std::pair<std::string, std::string> ObjectParam;

class Object {
public:
	Object(void);
	~Object(void);

	std::string& operator[] (std::string key) {
		bool found = false;
		for (int i = 0; i < _count; i++)
			if (_params[i].first == key) {
				return _params[i].second;
				found = true;
				break;
			}

		if (!found) {
			_params.push_back(std::pair<std::string, std::string>(key, std::string("")));
			_count++;
			return _params[_count - 1].second;
		}
	}

private:
	int 						_count;
	std::vector<ObjectParam> 	_params;
};


#endif /* OBJECT_H_ */
