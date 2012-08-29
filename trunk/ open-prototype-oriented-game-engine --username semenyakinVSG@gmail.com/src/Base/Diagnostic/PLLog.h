#ifndef PLLOG_H_
#define PLLOG_H_

#include <iostream>
#include "../PLAutoPointer.h"
#include <fstream>
#include "../PLString.h"
#include <time.h>

//LOG LEVELS
#define DEBUG "Debug"
#define INFO "Info"
#define WARNING "Warning"
#define ERROR "Error"

#define LEFT_LOGLEVEL_BRACKET "["
#define RIGHT_LOGLEVEL_BRACKET "] "

#define LEFT_DATE_BRACKET "["
#define RIGHT_DATE_BRACKET "] "

using namespace std;


class PLLog {
private:
	std::ostream* stream_out;
	bool isFile;
public:
	PLLog();
	PLLog(const char* filename);
	virtual ~PLLog();
	void print(const char *inMessage, const char* errorlevel);
	void print(const PLString *inMessage, const char* errorlevel);
	void print(const PLString inMessage, const char* errorlevel);
};

#endif /* PLLOG_H_ */
