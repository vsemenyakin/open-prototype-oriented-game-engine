/*
 * PLAutoreleasePool.cpp
 *
 *  Created on: 17.06.2012
 *      Author: SterX
 */

#include "PLAutoreleasePool.h"

static std::list<PLAutoreleasePool *> *sAutoreleasePools = NULL;

PLAutoreleasePool::PLAutoreleasePool()
{
	if (NULL == sAutoreleasePools)
	{
		sAutoreleasePools = new std::list<PLAutoreleasePool *>();
	}

	sAutoreleasePools->push_back(this);
}

PLAutoreleasePool::~PLAutoreleasePool()
{

}

void PLAutoreleasePool::destroy()
{
	std::list<PLObject *>::iterator theIterator = list.begin();
	for (; theIterator != list.end(); ++theIterator)
	{
		(*theIterator)->release();
	}

	std::cout << "PList destroyed" << std::endl;

	//PLObject::destroy();
}
