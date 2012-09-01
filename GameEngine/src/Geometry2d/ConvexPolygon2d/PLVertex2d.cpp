/*
 * PLVertex2d.cpp
 *
 *  Created on: 01.01.2002
 *      Author: 422
 */

#include "PLVertex2d.h"

PLVertex2d::PLVertex2d() : PLVector2d() { }
PLVertex2d::PLVertex2d(const PLVertex2d &inVertex) : PLVector2d(inVertex) { }
PLVertex2d::PLVertex2d(const PLVector2d &inVector) : PLVector2d(inVector) { }
PLVertex2d::PLVertex2d(ref<PLVector2d> inVector) : PLVector2d(*inVector) { }

////////////////////////////////////////////////////////
void PLVertex2d:: setPreviousSegment(PLSegment2d* inPreviousSegment)
{
	_previousSegment = inPreviousSegment;
}

PLSegment2d* PLVertex2d::previousSegment()
{
	return _previousSegment;
}

void PLVertex2d::setNextSegment(PLSegment2d *inNextSegment)
{
	_nextSegment = inNextSegment;
}

PLSegment2d* PLVertex2d::nextSegment()
{
	return _nextSegment;
}
