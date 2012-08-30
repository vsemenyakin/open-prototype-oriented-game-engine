#include <time.h>
#include "../PLString.h"

using namespace std;

class PLLogFormatter {
public:
PLLogFormatter( // the HORRIBLE CONSTRUCTOR NEEDS TO be rewritten  using templates
		const bool showLogLevel = true,
		const bool showDatetime = true,
		const bool showChannel = true,
		const char* datetime_format = "%x %X",
		const char* left_loglevel_bracket = "[",
		const char* right_loglevel_bracket = "] ",
		const char* left_date_bracket = "[",
		const char* right_date_bracket = "] ",
		const char* left_channel_bracket = "[",
		const char* right_channel_bracket = "] "
		) : _showLogLevel(showLogLevel), _showDatetime(showDatetime), _showChannel(showChannel), _datetime_format(datetime_format),
				_left_loglevel_bracket(left_loglevel_bracket), _right_loglevel_bracket(right_loglevel_bracket),
				_left_date_bracket(left_date_bracket), _right_date_bracket(right_date_bracket),
				_left_channel_bracket(left_channel_bracket), _right_channel_bracket(right_channel_bracket) {}


~PLLogFormatter() {}
const char* format(const char *inMessage, const char* errorlevel, const char* channel);

private:
const char* get_datetime(const char* format);

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

};
