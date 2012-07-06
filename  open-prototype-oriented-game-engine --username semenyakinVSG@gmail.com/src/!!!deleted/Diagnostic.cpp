/*
 * Diagnostic.cpp
 *
 *  Created on: 09.06.2012
 *      Author: SterX
 */

#include "Diagnostic.h"
#include "time.h"

Diagnostic::Diagnostic()
{
}

Diagnostic::~Diagnostic()
{
}

void Diagnostic::void startInterval(PLString *inDescription)
{
	TimeInterval *theInterval;

	theInterval->startTime = clock();
	theInterval->startTime = clock();

	intervals.push(theInterval);
}

void Diagnostic::stopInterval()
{
	stopTime = (long)clock();
}

long Diagnostic::getTime()
{

}

static Diagnostic *sInstance = 0;
static Diagnostic *instance()
{
	if (0 == sInstance)
	{
		sInstance = new Diagnostic();
	}

	return sInstance;
}
