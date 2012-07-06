/*
 * PLList.cpp
 *
 *  Created on: 16.06.2012
 *      Author: SterX
 */

#include "PLList.h"

///////////////////////////////////////////////////////////////////////////////
PLList::PLList()
{
}

///////////////////////////////////////////////////////////////////////////////
void PLList::destroy()
{
	std::list<PLObject *>::iterator theIterator = list.begin();
	for (; theIterator != list.end(); ++theIterator)
	{
		(*theIterator)->release();
	}

	std::cout << "PList destroyed" << std::endl;

	PLObject::destroy();
}

///////////////////////////////////////////////////////////////////////////////
void PLList::addObject(PLObject *inObject)
{
	list.push_back(inObject);
	inObject->retain();
}
