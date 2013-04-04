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

	std::string& operator[] (std::string key);

private:
	int 						_count;
	std::vector<ObjectParam> 	_params;
};


#endif /* OBJECT_H_ */
