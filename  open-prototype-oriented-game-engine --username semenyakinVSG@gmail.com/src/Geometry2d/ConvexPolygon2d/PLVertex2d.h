/*
 * PLVertex2d.h
 *
 *  Created on: 01.01.2002
 *      Author: 422
 */

#ifndef PLVERTEX2D_H_
#define PLVERTEX2D_H_

////////////////////////////////////////////////
#include "../PLVector2d.h"
#include "../../Base/PLCore.h"

class PLSegment2dWrapper;

////////////////////////////////////////////////
CLASS_WITH_REF(PLVertex2d) : public PLVector2d {

private:
	PLSegment2dWrapper* _segmentA;
	PLSegment2dWrapper* _segmentB;

public:

	PLVertex2d();
	PLVertex2d(const PLVertex2d &inVector);
	void setSegmentA(PLSegment2dWrapper* inSegmentA);
	PLSegment2dWrapper* segmentA();

	void setSegmentB(PLSegment2dWrapper* inSegmentB);
	PLSegment2dWrapper* segmentB();
};

#endif /* PLVERTEX2D_H_ */
