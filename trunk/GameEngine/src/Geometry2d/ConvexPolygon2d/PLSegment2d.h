/*
 * PLSegment2d.h
 *
 *  Created on: 01.01.2002
 *      Author: 422
 */

#ifndef PLSEGMENT2D_H_
#define PLSEGMENT2D_H_

#include "../../Base/PLCore.h"
#include "PLVertex2d.h"

class PLSegment2d {

private:
	ref<PLVertex2d> vertexA;
	ref<PLVertex2d> vertexB;

	ref<PLVector2d> delta;
	ref<PLVector2d> currentPoint;

	float parameter;

public:
	/////////////////////////////////////////////////
	PLSegment2d(ref<PLVertex2d> inVertexA, ref<PLVertex2d> inVertexB);
	void setParameter(const float inParameter);
};

#endif /* PLSEGMENT2D_H_ */
