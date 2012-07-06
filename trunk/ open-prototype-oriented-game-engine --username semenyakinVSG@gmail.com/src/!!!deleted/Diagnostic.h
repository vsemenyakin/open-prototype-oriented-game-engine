///////////////////////////////////////////////////////////////////////////////
#ifndef DIAGNOSTIC_H_
#define DIAGNOSTIC_H_

#include "Collections/ScalarStackPull.h"

#include "../Base/String.h";

///////////////////////////////////////////////////////////////////////////////
class Diagnostic {
private:

	ScalarStackPull<TimeInterval> intervals;

	Diagnostic();

public:
	static Diagnostic instance();

	void startInterval(PLString *inDescription);
	void stopInterval();
	long getTime();

	virtual ~Diagnostic();
};

#endif /* DIAGNOSTIC_H_ */
