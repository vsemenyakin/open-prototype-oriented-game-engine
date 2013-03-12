///////////////////////////////////////////////////////////////////////////////
#ifndef PLAPPLICATION_WINDOWS_H_
#define PLAPPLICATION_WINDOWS_H_

///////////////////////////////////////////////////////////////////////////////
#include "../../Interface/IPLApplication.h"

///////////////////////////////////////////////////////////////////////////////
class PLApplication_windows : public IPLApplication
{
public:
	PLApplication_windows();
	virtual ~PLApplication_windows();

	virtual void init();
	virtual PLError *start();
};

#endif /* PLAPPLICATION_WINDOWS_H_ */
