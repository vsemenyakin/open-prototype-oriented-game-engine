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
#include <map>
#include <vector>

#include <core/PLFunctor.h>

///////////////////////////////////////////////////////////////////////////////
class IPLCompositeEventSource;

///////////////////////////////////////////////////////////////////////////////
typedef int PLEventKey;
static const PLEventKey kPLNullEventKey = 0xFFFFFFFF;

#define DECLARE_EVENT_KEY(EVENT_NAME) extern PLEventKey EVENT_NAME;
#define EVENT_KEY(EVENT_NAME) PLEventKey EVENT_NAME = kPLNullEventKey;

///////////////////////////////////////////////////////////////////////////////
class PLEventCenter
{
private:


	// **************************************************************
	// *					Private _ Types							*
	// **************************************************************

	// Target to callback functor map
	typedef std::map<void *, PLFunctor>
			PLTargetToFunctor;

	// **************************************************************
	// *					Private _ Field							*
	// **************************************************************

	// Event name to targets to functors map assigning
	std::vector<PLTargetToFunctor > _eventNameAssigning;

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
			void *inTarget, PLFunctor inFunctor);

	// Composite event source invocation
	// (object that needs environment initialization)
	void addInvocationByEventWithNameFromTarget(PLEventKey *inoutEventKey,
			IPLCompositeEventSource *inTarget, PLFunctor inFunctor);

	// ----------------
	// *** Handle event

	// Final event invocation
	void invokeEventWithInformation(PLEventKey *inoutEventKey, void *inTarget,
			void *inEventInformation);

	// ==================
	// *** Static methods
	static PLEventCenter *defaultCenter();
};

///////////////////////////////////////////////////////////////////////////////
#endif /* PLEVENTCENTER_H_ */
