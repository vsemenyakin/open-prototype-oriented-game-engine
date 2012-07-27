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

class PLSegment2d;

////////////////////////////////////////////////
CLASS_WITH_REF(PLVertex2d) : public PLVector2d {

private:
	PLSegment2d* _previousSegment;
	PLSegment2d* _nextSegment;

public:

	PLVertex2d();
	PLVertex2d(const PLVertex2d &inVertex);
	PLVertex2d(const PLVector2d &inVector);
	PLVertex2d(ref<PLVector2d> inVector);

	void setPreviousSegment(PLSegment2d* inSegmentB);
	PLSegment2d* previousSegment();

	void setNextSegment(PLSegment2d* inSegmentA);
	PLSegment2d* nextSegment();
};

#endif /* PLVERTEX2D_H_ */
