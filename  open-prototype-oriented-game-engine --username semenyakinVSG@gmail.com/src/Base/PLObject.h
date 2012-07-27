///////////////////////////////////////////////////////////////////////////////
#ifndef RROBJECT_H_
#define RROBJECT_H_

///////////////////////////////////////////////////////////////////////////////
class PLString;
#include "PLAutoPointer.h"

class PLObject {
private:

	int referenceCount;

public:
	virtual void destroy();

	virtual ~PLObject();
	PLObject();

	PLObject *retain();
	void release();
	void autorelease();

	void saveToFile(ref<PLString> inFileName);
	void readFromFile(ref<PLString> inFileName);
};

#endif /* RROBJECT_H_ */
