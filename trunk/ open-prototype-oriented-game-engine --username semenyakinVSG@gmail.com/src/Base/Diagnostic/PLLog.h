#ifndef PLLOG_H_
#define PLLOG_H_

#include <iostream>
#include "../PLAutoPointer.h"
class PLString;

class PLLog : std::ostream {
private:
	ref<PLString> indentation;

public:
	PLLog();
	virtual ~PLLog();

	void print(const char *inMessage);
	void printValue();

	void beginGroup(const char *inGroupName);
	void endGroup();
};

#endif /* PLLOG_H_ */
