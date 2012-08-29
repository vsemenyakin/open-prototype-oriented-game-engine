#include "PLLog.h"


//get_datetime - not a class member.
const char* get_datetime()
{
	time_t rawtime;
	struct tm* timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	return asctime(timeinfo);
}


////////////////////////////////////////////////////////
PLLog::PLLog()
{
	stream_out = new ostream(cout);

}


PLLog::PLLog(const char* filename)
{
	ofstream* fstream_out = new ofstream(filename, ios_base::app);
	stream_out = (std::ostream*) fstream_out; //ptr to a new ofstream converted into ptr to ostream;
	if ((stream_out == 0) || fstream_out->is_open() || stream_out->bad())
	{
		delete stream_out;

		std::string errmsg("[PLLOG] Cannot initialize ");
		errmsg.append(filename);
		throw new ios_base::failure(errmsg);
	}

}

PLLog::~PLLog()
{
	delete stream_out;
}

//////////////////////////////////////////////////////
void PLLog::print(const char *inMessage, const char* errorlevel)
{
	if (stream_out->bad())
	{
		throw new ios_base::failure("[PLLOG] Error: bad stream");
	}
	else if (stream_out->fail() || stream_out->eof()) stream_out->clear();

	*stream_out << LEFT_LOGLEVEL_BRACKET << errorlevel << RIGHT_LOGLEVEL_BRACKET;  // e.g. "[Debug] "
	*stream_out	<< LEFT_DATE_BRACKET << get_datetime() << RIGHT_DATE_BRACKET; //e.g. "[29.08.2012 16:15] "
	*stream_out << inMessage << std::endl;

}


void PLLog::print(const PLString *inMessage, const char* errorlevel)
{
	print(inMessage->getCString(), errorlevel);
}

void PLLog::print(const PLString inMessage, const char* errorlevel)
{
	print(inMessage.getCString(), errorlevel);
}
