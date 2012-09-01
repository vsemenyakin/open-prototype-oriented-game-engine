///////////////////////////////////////////////////////////////////////////////
#ifndef PLCACHEMANAGER_H_
#define PLCACHEMANAGER_H_

#include "../../CoreCollections/PL_core_fastStack.h"

//////////////////////////////////////////////////////////////////////////////
class PLCacheManager {
private:
	// Private constructor for singletone. Do nothing while creation.
	PLCacheManager() { };

	typedef struct
	{
		void *object;
	} PLCacheWrapper;

	PL_core_fastStack<PLCacheWrapper *> cachesWrappers;

public:
	virtual ~PLCacheManager();

	PLCacheWrapper *newCacheWrapper();

	static PLCacheManager *sharedManager()
	{
		static PLCacheManager *sharedManagerPointer = NULL;
		if (NULL == sharedManagerPointer)
		{
			sharedManagerPointer = new PLCacheManager();
		}
		return sharedManagerPointer;
	}
};

#endif /* PLCACHEMANAGER_H_ */
