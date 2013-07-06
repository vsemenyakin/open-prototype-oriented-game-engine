/*
 * PLEventCenterwindows.cpp
 *
 *  Created on: 14.03.2013
 *      Author: semenyakinVS
 */

///////////////////////////////////////////////////////////////////////////////
#include "PLEventCenter.h"

#include <core/IPLCompositeEventSource.h>

#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////
PLEventCenter::PLEventCenter()
	: _eventNameAssigning()
{
}

PLEventCenter::~PLEventCenter()
{
}

///////////////////////////////////////////////////////////////////////////////
void PLEventCenter::addInvocationByEventWithNameFromTarget(
		PLEventKey *inoutEventKey, void *inTarget, PLFunctor inFunctor)
{
	if (kPLNullEventKey == *inoutEventKey)
	{
		_eventNameAssigning.push_back(PLTargetToFunctor());
		*inoutEventKey = _eventNameAssigning.size() - 1;
	}

	PLTargetToFunctor &theMap = _eventNameAssigning[*inoutEventKey];
	theMap[inTarget] = inFunctor;
}

void PLEventCenter::addInvocationByEventWithNameFromTarget(
		PLEventKey *inoutEventKey, IPLCompositeEventSource *inTarget,
				PLFunctor inFunctor)
{
	if (kPLNullEventKey == *inoutEventKey)
	{
		inTarget->initializeEnvironmentForEvent(inoutEventKey);
	}

	addInvocationByEventWithNameFromTarget(inoutEventKey, (void *)inTarget,
			inFunctor);
}

///////////////////////////////////////////////////////////////////////////////
void PLEventCenter::invokeEventWithInformation(PLEventKey *inoutEventKey,
		void *inTarget, void *inEventInformation)
{
	if (kPLNullEventKey != *inoutEventKey)
	{
		PLTargetToFunctor theMap = _eventNameAssigning[*inoutEventKey];
		for (PLTargetToFunctor::iterator theIterator = theMap.begin();
				theIterator != theMap.end(); ++theIterator)
		{
			theIterator->second(inEventInformation);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
static PLEventCenter *sDefaultCenter = NULL;

PLEventCenter *PLEventCenter::defaultCenter()
{
	if (NULL == sDefaultCenter)
	{
		sDefaultCenter = new PLEventCenter();
	}

	return sDefaultCenter;
}
