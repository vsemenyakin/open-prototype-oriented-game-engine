/*
 * PLLogFormatter.h
 *
 *  Created on: 30 ρεπο. 2012
 *      Author: ShareDVI
 */

#ifndef PLLOGFORMATTER_H_
#define PLLOGFORMATTER_H_


#include <time.h>
#include "../PLString.h"

using namespace std;

class PLLogFormatter
{

private:

	// **************************************************************
	// *					Private _ Variables						*
	// **************************************************************

	//fields
	const bool _showLogLevel;
	const bool _showDatetime;
	const bool _showChannel;
	const char* _datetime_format;

	const char* _left_loglevel_bracket;
	const char* _right_loglevel_bracket;
	const char* _left_date_bracket;
	const char* _right_date_bracket;
	const char* _left_channel_bracket;
	const char* _right_channel_bracket;

	const char* _begin_group_bracket;
	const char* _end_group_bracket;
	const char* _scope_indentation;

protected:
	const char* get_datetime(const char* format) const;

public:
	// the HORRIBLE CONSTRUCTOR NEEDS TO be rewritten  using templates
	PLLogFormatter(
		const bool showLogLevel = true,
		const bool showDatetime = true,
		const bool showChannel = true,
		const char* datetime_format = "%x %X",
		const char* left_loglevel_bracket = "[",
		const char* right_loglevel_bracket = "] ",
		const char* left_date_bracket = "[",
		const char* right_date_bracket = "] ",
		const char* left_channel_bracket = "[",
		const char* right_channel_bracket = "] ",
		const char* begin_group_bracket = "{",
		const char* end_group_bracket = "}",
		const char* scope_indentation = "	"
		) : _showLogLevel(showLogLevel), _showDatetime(showDatetime),
			_showChannel(showChannel), _datetime_format(datetime_format),
			_left_loglevel_bracket(left_loglevel_bracket),
			_right_loglevel_bracket(right_loglevel_bracket),
			_left_date_bracket(left_date_bracket),
			_right_date_bracket(right_date_bracket),
			_left_channel_bracket(left_channel_bracket),
			_right_channel_bracket(right_channel_bracket),
			_begin_group_bracket(begin_group_bracket),
			_end_group_bracket(end_group_bracket),
			_scope_indentation(scope_indentation)
	{
	}

	~PLLogFormatter()
	{
	}

	const char* format(const char *inMessage, const char* errorlevel,
			const char* channel) const;
};

#endif /* PLLOGFORMATTER_H_ */
