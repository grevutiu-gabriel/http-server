/*
 * Logger.h
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>

enum LogMessageType {
	INFO,
	ERROR,
	WARNING
};

class Logger {
public:
	Logger(void);
	~Logger(void);

	void bindStream(LogMessageType type, std::ostream &stream);
	void logMessage(LogMessageType type, const char *message);
	void logMessage(std::ostream &stream, LogMessageType type, const char * message);
private:
	std::ostream * _stream[3];
};


#endif /* LOGGER_H_ */
