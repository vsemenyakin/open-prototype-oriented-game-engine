/*
 * PLCollider.h
 *
 *  Created on: 01.01.2002
 *      Author: 422
 */

#ifndef PLCOLLIDER_H_
#define PLCOLLIDER_H_

#include "../../Base/PLAutoPointer.h"
#include "../ConvexPolygon2d/PLConvexPolygon2d.h"
#include "../PLVector2d.h"
#include "../../Collections/PLRoundList.h"

#include <list>

////////////////////////////////////////////////////////////////
class PLSegment2dWrapper;

struct PLVertex2dWrapper
{
	PLVector2d *point;
	PLSegment2dWrapper* segmentA;
	PLSegment2dWrapper* segmentB;
};

////////////////////////////////////////////////////////////////
class PLSegment2dWrapper
{
	ref< PLVertex2dWrapper > pointA;
	ref< PLVertex2dWrapper > pointB;

	PLVector2dRef delta;
	PLVector2dRef currentPoint;

	ref< PLConvexPolygon2d > polygon;

	float parameter;

	/////////////////////////////////////////////////
	PLSegment2dWrapper(PLVertex2dWrapper *inVectorWrapperA, PLVertex2dWrapper *inVectorWrapperB,
			PLConvexPolygon2d *inPolygon)
	{
		/*
		pointA.setRawPointer(inVectorWrapperA);
		pointB.setRawPointer(inVectorWrapperB);
		polygon.setRawPointer(inPolygon);
		delta.setRawPointer(Vector2d::subtractionOfVectors(pointB->point, pointA->point));
		 */

		parameter = 0;
	}

	/////////////////////////////////////////////////
	void setParamaeter(const float inParameter)
	{
		parameter = inParameter;
	}
};

////////////////////////////////////////////////////////////////
class PLPolygon2dWrapper
{
private:

public:
	PLPolygon2dWrapper(PLConvexPolygon2d *inPolygon)
	{
		PLRoundList< PLVector2dRef >::Iterator theVertex = inPolygon->vertexes()->begin();
		for (; theVertex.loopCount() != 0; ++theVertex)
		{
		}
	}
};

////////////////////////////////////////////////////////////////
CLASS_WITH_REF(PLCollider) {

private:


public:
	PLCollider();
	virtual ~PLCollider();

	void pushPolygon(PLConvexPolygon2d *inPolygon);
};

#endif /* PLCOLLIDER_H_ */
