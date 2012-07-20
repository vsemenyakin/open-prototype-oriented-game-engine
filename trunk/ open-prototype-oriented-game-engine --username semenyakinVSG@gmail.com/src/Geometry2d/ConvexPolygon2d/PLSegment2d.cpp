/*
 * PLSegment2d.cpp
 *
 *  Created on: 01.01.2002
 *      Author: 422
 */

#include "PLSegment2d.h"

/////////////////////////////////////////////////
PLSegment2d::PLSegment2d(ref< PLVertex2d > inVertexA, ref< PLVertex2d > inVertexB)
{
	vertexA = inVertexA;
	vertexB = inVertexB;

	delta = ref< PLVector2d >::create(*PLVector2d::subtractionOfVectors(~inVertexB, ~inVertexA));
	parameter = 0;
}

/////////////////////////////////////////////////
void PLSegment2d::setParameter(const float inParameter)
{
	parameter = inParameter;
}

