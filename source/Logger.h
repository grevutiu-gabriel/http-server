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
	Logger(std::ostream &initialStream);
	~Logger(void);

	void setStream(std::ostream &stream);
	void logMessage(LogMessageType type, const char *message);
	void logMessage(std::ostream &stream, LogMessageType type, const char * message);
private:
	std::ostream * _stream;
};


#endif /* LOGGER_H_ */
