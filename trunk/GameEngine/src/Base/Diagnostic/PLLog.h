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


	// **************************************************************
	// *					Private _ Variables						*
	// **************************************************************

	// ---------------
	// *** Inner state
	bool stream_responsibility;
	bool formatter_responsibility;
	bool isFile;

	// --------------------
	// *** Output variables
	std::ostream* stream_out;
	PLLogFormatter* _formatter;

	// ------------------------------
	// *** Levels and channels accept
	bool acceptsAllLoglevels;
	bool acceptsAllChannels;
	set<const char*>* acceptableLoglevels;
	set<const char*>* acceptableChannels;


	// **************************************************************
	// *					Private _ Methods						*
	// **************************************************************

	// ------------------
	// *** Initialization
	void init(const char* inFilename, PLLogFormatter* inFormatter);
	void init(ostream* inFilename, PLLogFormatter* inFormatter);

	// ------------------------------
	// *** Levels and channels accept
	bool acceptsLoglevel(const char* errorlevel);
	bool acceptsChannel(const char* channel);

public:


	// **************************************************************
	// *					Public _ Constants						*
	// **************************************************************
	//char *const kErrorLevelDefault = "default_error";


	// **************************************************************
	// *					Public _ Methods						*
	// **************************************************************

	// ---------------------
	// *** Memory management
	PLLog(const char* inFilename = "", PLLogFormatter* inFormatter = 0);
	PLLog(PLString* inFilename, PLLogFormatter* inFormatter = 0);
	PLLog(ostream* inStream, PLLogFormatter* inFormatter = 0);

	virtual ~PLLog();

	// ------------
	// *** Printing
	virtual void print(const char *inMessage, const char* errorlevel,
			const char* channel);
	virtual void print(const PLString *inMessage, const char* errorlevel,
			const char* channel);
	virtual void print(const PLString inMessage, const char* errorlevel,
			const char* channel);

	// ------------
	// *** Grouping
	virtual void beginGroup(const char *inErrorLevel, const char *inChannel);
	virtual void endGroup(const char *inErrorLevel, const char *inChannel);

	// -------------------------------------
	// *** Log level and channels management
	bool accepts(const char* errorlevel, const char* channel);

	void addLoglevel(const char* errorlevel);
	bool deleteLoglevel(const char* errorlevel);
	void addChannel(const char* channel);
	bool deleteChannel(const char* channel);
	void wipeLogLevels();
	void wipeChannels();


	// **************************************************************
	// *					Static _ Methods						*
	// **************************************************************
	static PLLog *sharedLog();
};

// ****************************************************************************
// Macros
#define PRINT()


#endif /* PLLOG_H_ */
