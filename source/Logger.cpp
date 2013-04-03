/*
 * Logger.cpp
 */
#include "Logger.h"

Logger::Logger()
{
	_stream = &(std::cout);
}

Logger::Logger(std::ostream &initialStream)
{
	_stream = &(initialStream);
}

Logger::~Logger(void)
{
	//delete _stream;
	// free all the memory
}

void Logger::setStream(std::ostream &stream)
{
	_stream = &stream;
}

void Logger::logMessage(std::ostream &stream, LogMessageType type, const char *message)
{
	stream << "[" << type << "] " << message << "\n";
}

void Logger::logMessage(LogMessageType type, const char *message)
{
	*_stream << "[" << type << "] " << message << "\n";
}

