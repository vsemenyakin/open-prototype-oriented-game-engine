#ifndef PLAUTORELEASEPOOL_H_
#define PLAUTORELEASEPOOL_H_

#include "list.h"
#include "PLObject.h"

class PLAutoreleasePool {

private:
	std::list<PLObject *> list;

public:
	PLAutoreleasePool();
	void destroy();

	virtual ~PLAutoreleasePool();
};

#endif /* PLAUTORELEASEPOOL_H_ */
