/*
 * PLConvexPolygon2d.h
 *
 *  Created on: 01.01.2002
 *      Author: 422
 */

#ifndef PLCONVEXPOLYGON2D_H_
#define PLCONVEXPOLYGON2D_H_

#include <list>
#include "../../Base/PLCore.h"
#include "../../Collections/PLRoundList.h"
#include "../PLVector2d.h"

CLASS_WITH_REF(PLConvexPolygon2d) {

private:


	PLAutoPointer<PLRoundList<PLVector2dRef> > vertexes;

public:
	PLConvexPolygon2d();
	PLConvexPolygon2d(PLVector2dRef *inVertexes, int inCount);
	virtual ~PLConvexPolygon2d();

	PLAutoPointer<PLRoundList<PLVector2dRef> > Vertexes();

	void Print();
};

#endif /* PLCONVEXPOLYGON2D_H_ */
