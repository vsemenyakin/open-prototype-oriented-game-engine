#ifndef PLLOG_H_
#define PLLOG_H_

#include <iostream>
#include "../PLAutoPointer.h"
#include <fstream>
#include "../PLString.h"
#include "PLLogFormatter.h"

//LOG LEVELS
#define DEBUG "Debug"
#define INFO "Info"
#define WARNING "Warning"
#define ERROR "Error"

//channels
#define GENERAL "General"


using namespace std;

class PLLog {
private:
	std::ostream* stream_out;
	PLLogFormatter* _formatter;
	bool isFile;
public:
	PLLog();
	PLLog(const char* filename);
	PLLog(PLLogFormatter* formatter);
	PLLog(const char* filename, PLLogFormatter* formatter);
	virtual ~PLLog();
	void print(const char *inMessage, const char* errorlevel, const char* channel);
	void print(const PLString *inMessage, const char* errorlevel, const char* channel);
	void print(const PLString inMessage, const char* errorlevel, const char* channel);
};

#endif /* PLLOG_H_ */
