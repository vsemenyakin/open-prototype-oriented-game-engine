#ifndef PLLOG_H_
#define PLLOG_H_

#include <iostream>
#include "../Base/PLCore.h"

class PLString;

class PLLog : std::ostream {
private:
	ref<PLString> theString;

public:
	PLLog();
	virtual ~PLLog();

	void beginGroup();
	void endGroup();
};

#endif /* PLLOG_H_ */
