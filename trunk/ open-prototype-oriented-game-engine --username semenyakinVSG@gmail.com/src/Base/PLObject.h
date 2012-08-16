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

	// Serialization
	void saveToFile(ref<PLString> inFileName);
	void readFromFile(ref<PLString> inFileName);

	// Logging
	virtual ref<PLString> logString();
	virtual ref<PLString> logString(int inLogLevel);
};

#endif /* RROBJECT_H_ */
