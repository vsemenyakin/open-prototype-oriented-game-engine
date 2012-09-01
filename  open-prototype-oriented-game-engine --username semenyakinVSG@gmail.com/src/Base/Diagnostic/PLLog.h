#ifndef PLLOG_H_
#define PLLOG_H_

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <set>
#include "IPLLogReceiver.h"
#include "PLLogFormatter.h"

///////////////////////////////////////////////////////////////////////////////
//LOG LEVELS
#define DEBUG "Debug"
#define INFO "Info"
#define WARNING "Warning"
#define ERROR "Error"

//channels
#define GENERAL "General"

///////////////////////////////////////////////////////////////////////////////
// !!!!!!!!!!!!!!!!!!!!!! *******
// Look - there is something with formater
// TODO singletone class for logging (sharedLogger)/ You can googling about it,
// or just look at class on Base/Memory/PLCacheMeneger.h
// !!!!!!!!!!!!!!!!!!!!!! *******
using namespace std;

///////////////////////////////////////////////////////////////////////////////
class PLLog : public IPLLogReceiver
{
private:
	std::ostream* stream_out;
	PLLogFormatter* _formatter;
	bool stream_responsibility;
	bool formatter_responsibility;
	bool isFile;
	bool acceptsAllLoglevels;
	bool acceptsAllChannels;
	set<const char*>* acceptableLoglevels;
	set<const char*>* acceptableChannels;
	void init(const char* filename, PLLogFormatter* formatter);
	void init(ostream* filename, PLLogFormatter* formatter);
	bool acceptsLoglevel(const char* errorlevel);
	bool acceptsChannel(const char* channel);
public:

	//constructor logic moved to init()
	PLLog(const char* filename = "", PLLogFormatter* formatter = 0)
	{
		init(filename, formatter);
	}

	PLLog(PLString* filename, PLLogFormatter* formatter=0)
	{
		init(filename->getCString(), formatter);
	}

	PLLog(ostream* stream, PLLogFormatter* formatter = 0)
	{
		init(stream, formatter);
	}

	virtual ~PLLog();
	virtual void print(const char *inMessage, const char* errorlevel, const char* channel);
	virtual void print(const PLString *inMessage, const char* errorlevel, const char* channel);
	virtual void print(const PLString inMessage, const char* errorlevel, const char* channel);
	bool accepts(const char* errorlevel, const char* channel);
	void addLoglevel(const char* errorlevel);
	bool deleteLoglevel(const char* errorlevel);
	void addChannel(const char* channel);
	bool deleteChannel(const char* channel);
	void wipeLogLevels();
	void wipeChannels();

};

#endif /* PLLOG_H_ */
