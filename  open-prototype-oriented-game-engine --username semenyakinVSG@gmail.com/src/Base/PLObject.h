///////////////////////////////////////////////////////////////////////////////
#ifndef RROBJECT_H_
#define RROBJECT_H_

///////////////////////////////////////////////////////////////////////////////
class PLString;
#include "PLAutoPointer.h"
const int kMaxLogLevel = 0xFFFFFFFF;

class PLObject {
private:

	int referenceCount;


protected:
	virtual void destroy();

public:

	virtual ~PLObject();
	PLObject();

	PLObject *retain();
	void release();
	void autorelease();
};

#endif /* RROBJECT_H_ */
