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

struct PLVector2Wrapper
{
	PLVector2d *point;
	PLSegment2dWrapper* segmentA;
	PLSegment2dWrapper* segmentB;
};

////////////////////////////////////////////////////////////////
class PLSegment2dWrapper
{
	PLAutoPointer<PLVector2Wrapper> pointA;
	PLAutoPointer<PLVector2Wrapper> pointB;

	PLVector2dRef delta;
	PLVector2dRef currentPoint;


	PLAutoPointer<PLConvexPolygon2d> polygon;

	float parameter;

	/////////////////////////////////////////////////
	PLSegment2dWrapper(PLVector2Wrapper *inVectorWrapperA, PLVector2Wrapper *inVectorWrapperB,
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
	PLPolygon2dWrapper(PLConvexPolygon2d *inPolygon)
	{
		//PLRoundList<Vector2d> *theList = inPolygon->vertexes;
		//PLRoundList<Vector2d>::Iterator theIterator = theList->begin();
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
