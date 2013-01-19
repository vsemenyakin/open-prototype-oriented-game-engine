/*
 * PLLogFormatter.cpp
 *
 *  Created on: 30 ρεπο. 2012
 *      Author: ShareDVI
 */


#include "PLLogFormatter.h"

//PLLogFormatter methods.
	const char* PLLogFormatter::get_datetime(const char* format) const
{
	time_t rawtime;
	struct tm* timeinfo;
	static char buffer [100];
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	strftime(buffer, 100, format, timeinfo);
	return buffer;
}

	const char* PLLogFormatter::format(const char *inMessage,
			const char* inErrorLevel, const char* inChannel) const
	{
		static std::string buffer("");
		buffer.clear();
		if (_showLogLevel) {
			buffer.append(_left_loglevel_bracket);
			buffer.append(inErrorLevel);
			buffer.append(_right_loglevel_bracket);
		}

		if (_showDatetime) {
			buffer.append(_left_date_bracket);
			buffer.append(get_datetime(_datetime_format));
			buffer.append(_right_date_bracket);
		}

		if (_showChannel) {
			buffer.append(_left_channel_bracket);
			buffer.append(inChannel);
			buffer.append(_right_channel_bracket);
		}
		buffer.append(inMessage);
		return buffer.c_str();
	}

