 #include "PLLog.h"

	//PLLog methods
////////////////////////////////////////////////////////
PLLog::PLLog()
{	isFile=false;
	stream_out = &cout;
	_formatter = new PLLogFormatter();
}


PLLog::PLLog(const char* filename)
{	isFile=true;
	_formatter = new PLLogFormatter();
	ofstream* fstream_out = new ofstream(filename, ios_base::app);
	stream_out = (std::ostream*) fstream_out; //ptr to a new ofstream converted into ptr to ostream;
	if ((stream_out == 0) || !(fstream_out->is_open()) || stream_out->bad())
	{
		if (isFile) delete stream_out;

		std::string errmsg("[PLLOG] Cannot initialize ");
		errmsg.append(filename);
		throw new ios_base::failure(errmsg);

	}

}

PLLog::PLLog(PLLogFormatter* formatter)
{
	isFile=false;
	stream_out = &cout;
	_formatter = formatter;
}

PLLog::PLLog(const char* filename, PLLogFormatter* formatter)
{
	isFile=true;
		_formatter = formatter;
		ofstream* fstream_out = new ofstream(filename, ios_base::app);
		stream_out = (std::ostream*) fstream_out; //ptr to a new ofstream converted into ptr to ostream;
		if ((stream_out == 0) || !(fstream_out->is_open()) || stream_out->bad())
		{
			if (isFile) delete stream_out;

			std::string errmsg("[PLLOG] Cannot initialize ");
			errmsg.append(filename);
			throw new ios_base::failure(errmsg);
		}
}

PLLog::~PLLog()
{
	if (isFile)
	{
		((ofstream*) stream_out)->close();
	}
	delete stream_out;
	delete _formatter;
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
