/*
 * Logger.cpp
 */
#include "Logger.h"

Logger::Logger()
{
	_stream[0] = _stream[1] = &(std::cout);
	_stream[2] = &(std::cerr);
}

Logger::~Logger(void)
{
	delete [] _stream;
	//delete _stream;
	// free all the memory
}

void Logger::bindStream(LogMessageType type, std::ostream &stream)
{
	_stream[type] = &stream;
}

void Logger::logMessage(std::ostream &stream, LogMessageType type, const char *message)
{
	stream << "[" << type << "] " << message << "\n";
}

void Logger::logMessage(LogMessageType type, const char *message)
{
	*_stream[type] << "[" << type << "] " << message << "\n";
}

