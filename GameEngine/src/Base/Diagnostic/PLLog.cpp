
///////////////////////////////////////////////////////////////////////////////
#include "PLLog.h"

///////////////////////////////////////////////////////////////////////////////
PLLog::PLLog(const char* inFilename, PLLogFormatter* inFormatter)
{
	init(inFilename, inFormatter);
}

PLLog::PLLog(PLString* inFilename, PLLogFormatter* inFormatter)
{
	init(inFilename->getCString(), inFormatter);
}

PLLog::PLLog(ostream* inStream, PLLogFormatter* inFormatter)
{
	init(inStream, inFormatter);
}

///////////////////////////////////////////////////////////////////////////////
void PLLog::init(const char* inFilename, PLLogFormatter* inFormatter)
{
	acceptsAllLoglevels = true;
	acceptsAllChannels = true;
	acceptableLoglevels = new set<const char*>();
	acceptableChannels = new set<const char*>();

	isFile = (*inFilename != '\0');
	if (NULL == inFormatter)
	{
		_formatter = new PLLogFormatter();
		formatter_responsibility = true;
	}
	else
	{
		_formatter = inFormatter;
		formatter_responsibility = false;
	}

	if (!isFile)
	{
		stream_out=&cout;
		stream_responsibility = false;
	}
	else
	{
		stream_responsibility=true;
		ofstream* fstream_out = new ofstream(inFilename, ios_base::app);

		//ptr to a new ofstream converted into ptr to ostream;
		stream_out = (std::ostream*) fstream_out;
		if ((stream_out == 0) || stream_out->bad() ||
				!(fstream_out->is_open()))
		{
			delete stream_out;
			isFile=false;
			stream_out=&cout;
			std::string errmsg("[PLLOG] Cannot initialize ");
			errmsg.append(inFilename);
			print(errmsg.c_str(), ERROR, "PLLog");
		}
	}
}

void PLLog::init(ostream* inStream, PLLogFormatter* inFormatter)
{
	acceptsAllLoglevels = true;
	acceptsAllChannels = true;
	acceptableLoglevels = new set<const char*>();
	acceptableChannels = new set<const char*>();
	stream_responsibility = false;
	isFile = false;

	if (!inFormatter)
	{
		_formatter = new PLLogFormatter();
		formatter_responsibility = true;
	}
	else
	{
		_formatter = inFormatter;
		formatter_responsibility = false;
	}

	stream_out = (inStream != 0) ? inStream : &cout;
}


PLLog::~PLLog()
{
	stream_out->flush();
	if (isFile)
	{
		ofstream* fstream_out = (static_cast<ofstream*>(stream_out));
		fstream_out->close();
	}

	if (stream_responsibility) delete stream_out;
	if (formatter_responsibility) delete _formatter;
	delete acceptableLoglevels;
	delete acceptableChannels;
}

///////////////////////////////////////////////////////////////////////////////
void PLLog::print(const char *inMessage, const char* errorlevel,
		const char* channel = GENERAL)
{
	if (stream_out->bad())
	{
		throw new ios_base::failure("[PLLOG] Error: bad stream");
	}
	else if (stream_out->fail() || stream_out->eof())
	{
		stream_out->clear();
	}

	*stream_out << _formatter->format(inMessage, errorlevel, channel);
	*stream_out << std::endl;
}

void PLLog::print(const PLString *inMessage, const char* errorlevel,
		const char* channel = GENERAL)
{
	print(inMessage->getCString(), errorlevel, channel);
}

void PLLog::print(const PLString inMessage, const char* errorlevel,
		const char* channel = GENERAL)
{
	print(inMessage.getCString(), errorlevel, channel);
}

///////////////////////////////////////////////////////////////////////////////
void PLLog::beginGroup(const char *inErrorLevel, const char *inChannel)
{
}

void PLLog::endGroup(const char *inErrorLevel, const char *inChannel)
{
}

///////////////////////////////////////////////////////////////////////////////
bool PLLog::accepts(const char* errorlevel, const char* channel)
{
	return acceptsLoglevel(errorlevel) && acceptsChannel (channel);
}

///////////////////////////////////////////////////////////////////////////////
bool PLLog::acceptsChannel(const char* channel)
{
	if (acceptsAllChannels) return true;
	else return (acceptableChannels->count(channel)>0);
}

void PLLog::addChannel(const char* channel)
{
	if (acceptsAllChannels == true || ! (acceptsChannel(channel)))
	{
		acceptsAllChannels = false;
		acceptableChannels->insert(channel);
	}
}

bool PLLog::deleteChannel(const char* channel)
{
	return (acceptableChannels->erase(channel) > 0) ;
}

void PLLog::wipeChannels()
{
	acceptableChannels->clear();
	acceptsAllChannels = true;
}

///////////////////////////////////////////////////////////////////////////////
bool PLLog::acceptsLoglevel(const char* errorlevel)
{
	if (acceptsAllLoglevels) return true;
	else return (acceptableLoglevels->count(errorlevel)>0);
}

void PLLog::addLoglevel(const char* errorlevel)
{
	if (acceptsAllLoglevels == true || ! (acceptsLoglevel(errorlevel)))
	{
		acceptsAllLoglevels = false;
		acceptableLoglevels->insert(errorlevel);
	}
}

bool PLLog::deleteLoglevel(const char* errorlevel)
{
	return (acceptableLoglevels->erase(errorlevel) > 0) ;
}

void PLLog::wipeLogLevels()
{
	acceptableLoglevels->clear();
	acceptsAllLoglevels = true;
}

///////////////////////////////////////////////////////////////////////////////
static PLLog *sharedLogPointer = NULL;

static PLLog *PLLogsharedLog()
{
	if (NULL == sharedLogPointer)
	{
		//sharedLogPointer = new PLLog(NULL);
	}

	return sharedLogPointer;
}
