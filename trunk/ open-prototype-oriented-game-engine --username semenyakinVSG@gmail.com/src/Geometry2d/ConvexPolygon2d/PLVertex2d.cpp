/*
 * PLVertex2d.cpp
 *
 *  Created on: 01.01.2002
 *      Author: 422
 */

#include "PLVertex2d.h"

PLVertex2d::PLVertex2d() : PLVector2d() { }
PLVertex2d::PLVertex2d(const PLVertex2d &inVector) : PLVector2d(inVector) { }
////////////////////////////////////////////////////////
void PLVertex2d::setSegmentA(PLSegment2dWrapper* inSegmentA)
{
	_segmentA = inSegmentA;
}

PLSegment2dWrapper* PLVertex2d::segmentA()
{
	return _segmentA;
}

void PLVertex2d:: setSegmentB(PLSegment2dWrapper* inSegmentB)
{
	_segmentB = inSegmentB;
}

PLSegment2dWrapper* PLVertex2d::segmentB()
{
	return _segmentB;
}
