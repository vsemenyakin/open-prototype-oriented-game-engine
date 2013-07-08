/*
 * PLEventCenterwindows.h
 *
 *  Created on: 14.03.2013
 *      Author: semenyakinVS
 */

///////////////////////////////////////////////////////////////////////////////
#ifndef PLEVENTCENTER_H_
#define PLEVENTCENTER_H_

///////////////////////////////////////////////////////////////////////////////
#include <list>
#include <map>
#include <vector>

#include <core/PLFunctor.h>

///////////////////////////////////////////////////////////////////////////////
class IPLCompositeEventSource;

///////////////////////////////////////////////////////////////////////////////
typedef int PLEventKey;
static const PLEventKey kPLUnregisteredEventValue = 0xFFFFFFFF;

#define USE_EVENT_KEY(EVENT_NAME) extern PLEventKey EVENT_NAME;
#define DECLARE_EVENT_KEY(EVENT_NAME)\
		PLEventKey EVENT_NAME = kPLUnregisteredEventValue;

///////////////////////////////////////////////////////////////////////////////
class PLEventCenter
{
private:


	// **************************************************************
	// *					Private _ Types							*
	// **************************************************************

	// Target to callback functor map
	typedef std::list<PLFunctor> AFunctorsList;
	typedef std::map<void *, AFunctorsList> AnEventSourceMapping;
	typedef std::vector<AnEventSourceMapping> AEventKeyMapping;

	// **************************************************************
	// *					Private _ Field							*
	// **************************************************************

	// Event name to targets to functors map assigning
	AEventKeyMapping _eventKeyToTargetMappingMap;

public:


	// **************************************************************
	// *					Public _ Methods						*
	// **************************************************************

	// =====================
	// *** Memory management
	PLEventCenter();
	virtual ~PLEventCenter();


	// ====================================
	// *** Event handling

	// --------------------------
	// *** Add event for handling

	// All objects invocation
	void addInvocationByEventWithNameFromTarget(PLEventKey *inoutEventKey,
			void *inEventSource, const PLFunctor &inFunctor);

	// Composite event source invocation
	// (object that needs environment initialization)
	void addInvocationByEventWithNameFromTarget(PLEventKey *inoutEventKey,
			IPLCompositeEventSource *inEventSource, const PLFunctor &inFunctor);

	// ----------------
	// *** Handle event

	// Final event invocation
	void invokeEventWithInformation(PLEventKey *inoutEventKey,
			void *inEventSource, void *inEventInformation);

	// -------------------------
	// *** Remove event handler

	void removeHandler(PLEventKey *inoutEventKey, void *inEventSource,
			const PLFunctor &inFunctor);

	// ==================
	// *** Static methods
	static PLEventCenter *defaultCenter();
};

///////////////////////////////////////////////////////////////////////////////
#endif /* PLEVENTCENTER_H_ */
