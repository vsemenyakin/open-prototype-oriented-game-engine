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
	: _eventKeyToTargetMappingMap()
{
}

PLEventCenter::~PLEventCenter()
{
}

///////////////////////////////////////////////////////////////////////////////
void PLEventCenter::addInvocationByEventWithNameFromTarget(
		PLEventKey *inoutEventKey, void *inTarget, const PLFunctor &inFunctor)
{
	// Register event
	if (kPLUnregisteredEventValue == *inoutEventKey)
	{
		*inoutEventKey = _eventKeyToTargetMappingMap.size();
		_eventKeyToTargetMappingMap.push_back(AnEventSourceMapping());
	}

	AnEventSourceMapping &theMap = _eventKeyToTargetMappingMap[*inoutEventKey];
	theMap[inTarget].push_back(inFunctor);
}

void PLEventCenter::addInvocationByEventWithNameFromTarget(
		PLEventKey *inoutEventKey, IPLCompositeEventSource *inEventSource,
				const PLFunctor &inFunctor)
{
	if (kPLUnregisteredEventValue == *inoutEventKey)
	{
		inEventSource->initializeEnvironmentForEvent(inoutEventKey);
	}

	addInvocationByEventWithNameFromTarget(inoutEventKey, (void *)inEventSource,
			inFunctor);
}

///////////////////////////////////////////////////////////////////////////////
void PLEventCenter::removeHandler(PLEventKey *inoutEventKey,
		void *inEventSource, const PLFunctor &inFunctor)
{
	if (*inoutEventKey != kPLUnregisteredEventValue)
	{
		AnEventSourceMapping &theEventSourceMapping =
				_eventKeyToTargetMappingMap[*inoutEventKey];

		const AnEventSourceMapping::iterator &theIterator =
				theEventSourceMapping.find(inEventSource);

		if (theIterator != theEventSourceMapping.end())
		{
			theIterator->second.remove(inFunctor);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
void PLEventCenter::invokeEventWithInformation(PLEventKey *inoutEventKey,
		void *inEventSource, void *inEventInformation)
{
	if (kPLUnregisteredEventValue != *inoutEventKey)
	{
		AnEventSourceMapping &theEventSourceMapping =
				_eventKeyToTargetMappingMap[*inoutEventKey];

		if (NULL != inEventSource)
		{
			const AnEventSourceMapping::iterator &theIterator =
					theEventSourceMapping.find(inEventSource);

			if (theIterator != theEventSourceMapping.end())
			{
				AFunctorsList &theFunctorsList = theIterator->second;

				AFunctorsList::iterator theFunctorsIterator =
						theFunctorsList.begin();
				for (; theFunctorsIterator != theFunctorsList.end();
						++theFunctorsIterator)
				{
					theFunctorsIterator->call();
				}
			}
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
