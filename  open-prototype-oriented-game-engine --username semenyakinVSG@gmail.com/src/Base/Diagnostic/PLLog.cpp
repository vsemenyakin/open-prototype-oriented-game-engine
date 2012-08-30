 #include "PLLog.h"

	//PLLog methods
////////////////////////////////////////////////////////


void PLLog::init(const char* filename, PLLogFormatter* formatter)
{
	acceptsAllLoglevels=true;
	acceptsAllChannels=true;
	acceptableLoglevels = new set<const char*>();
	acceptableChannels = new set<const char*>();
	isFile=(*filename !='\0');
	if (!formatter)
	{
		_formatter = new PLLogFormatter();
		formatter_responsibility=true;

	}
	else
		{
			_formatter = formatter;
			formatter_responsibility=false;
		}
	if (!isFile)
	{
		stream_out=&cout;
		stream_responsibility=false;
	}
	else
	{
		stream_responsibility=true;
		ofstream* fstream_out = new ofstream(filename, ios_base::app);
		stream_out = (std::ostream*) fstream_out; //ptr to a new ofstream converted into ptr to ostream;
		if ((stream_out == 0) || stream_out->bad() || !(fstream_out->is_open()) )
		{
			delete stream_out;
			isFile=false;
			stream_out=&cout;
			std::string errmsg("[PLLOG] Cannot initialize ");
			errmsg.append(filename);
			print(errmsg.c_str(), ERROR, "PLLog");

		}
	}
}

void PLLog::init(ostream* stream, PLLogFormatter* formatter)
{
	acceptsAllLoglevels=true;
	acceptsAllChannels=true;
	acceptableLoglevels = new set<const char*>();
	acceptableChannels = new set<const char*>();
	stream_responsibility=false;
	isFile=false;
	if (!formatter)
	{
		_formatter = new PLLogFormatter();
		formatter_responsibility=true;

	}
	else
	{
		_formatter = formatter;
		formatter_responsibility=false;
	}
	if (stream != 0) stream_out=stream;
	else stream_out=&cout;
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

////////////////////////////////////////////////////////////
void PLLog::print(const char *inMessage, const char* errorlevel, const char* channel=GENERAL)
{
	if (stream_out->bad())
	{
		throw new ios_base::failure("[PLLOG] Error: bad stream");
	}
	else if (stream_out->fail() || stream_out->eof()) stream_out->clear();

	*stream_out << _formatter->format(inMessage, errorlevel, channel);
	*stream_out << std::endl;

}


void PLLog::print(const PLString *inMessage, const char* errorlevel, const char* channel=GENERAL)
{
	print(inMessage->getCString(), errorlevel, channel);
}

void PLLog::print(const PLString inMessage, const char* errorlevel, const char* channel=GENERAL)
{
	print(inMessage.getCString(), errorlevel, channel);
}

bool PLLog::acceptsLoglevel(const char* errorlevel)
{
	if (acceptsAllLoglevels) return true;
	else return (acceptableLoglevels->count(errorlevel)>0);
}

bool PLLog::acceptsChannel(const char* channel)
{
	if (acceptsAllChannels) return true;
	else return (acceptableChannels->count(channel)>0);
}



bool PLLog::accepts(const char* errorlevel, const char* channel)
{
	return acceptsLoglevel(errorlevel) && acceptsChannel (channel);
}

void PLLog::addLoglevel(const char* errorlevel)
{
	if (acceptsAllLoglevels==true || ! (acceptsLoglevel(errorlevel)))
	{
		acceptsAllLoglevels=false;
		acceptableLoglevels->insert(errorlevel);
	}
}



bool PLLog::deleteLoglevel(const char* errorlevel)
{
	return (acceptableLoglevels->erase(errorlevel) > 0) ;
}

void PLLog::addChannel(const char* channel)
{
	if (acceptsAllChannels==true || ! (acceptsChannel(channel)))
	{
		acceptsAllChannels=false;
		acceptableChannels->insert(channel);
	}
}


bool PLLog::deleteChannel(const char* channel)
{
	return (acceptableChannels->erase(channel) > 0) ;
}

void PLLog::wipeLogLevels()
{
	acceptableLoglevels->clear();
	acceptsAllLoglevels=true;
}

void PLLog::wipeChannels()
{
	acceptableChannels->clear();
	acceptsAllChannels=true;
}
