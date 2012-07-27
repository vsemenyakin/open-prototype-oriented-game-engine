///////////////////////////////////////////////////////////////////////////////
#ifndef STRING_H_
#define STRING_H_

///////////////////////////////////////////////////////////////////////////////
#include "PLObject.h"
#include <string>

///////////////////////////////////////////////////////////////////////////////
class PLString : public PLObject {
private:
	std::string *theString;

public:
	PLString();
	PLString(char *inCString);
	virtual ~PLString();

	const char *CString();
	void removeLastSymbles(int inSymblesCount);
	void append(const char *inCString);
};

#endif /* STRING_H_ */
