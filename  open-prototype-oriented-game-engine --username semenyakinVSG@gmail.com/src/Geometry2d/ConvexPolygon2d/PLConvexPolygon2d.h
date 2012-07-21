/*
 * PLConvexPolygon2d.h
 *
 *  Created on: 01.01.2002
 *      Author: 422
 */

#ifndef PLCONVEXPOLYGON2D_H_
#define PLCONVEXPOLYGON2D_H_

#include "../../Base/PLCore.h"
#include "../../Collections/PLRoundList.h"

class PLVertex2d;
class PLVector2d;

///////////////////////////////////////////////////////////////
CLASS_WITH_REF(PLConvexPolygon2d) {

private:
	ref< PLRoundList< ref<PLVertex2d> > > _vertexes;

public:
	PLConvexPolygon2d();
	PLConvexPolygon2d(ref<PLVector2d> *inVertexes, int inCount);
	virtual ~PLConvexPolygon2d();

	ref< PLRoundList< ref<PLVertex2d> > > vertexes();

	void Print();
};

#endif /* PLCONVEXPOLYGON2D_H_ */
