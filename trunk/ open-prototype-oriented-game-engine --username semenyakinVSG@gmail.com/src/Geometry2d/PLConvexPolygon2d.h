/*
 * PLConvexPolygon2d.h
 *
 *  Created on: 01.01.2002
 *      Author: 422
 */

#ifndef PLCONVEXPOLYGON2D_H_
#define PLCONVEXPOLYGON2D_H_

class Vector2d;
#include <list>
#include "../Base/PLAutoPointer.h"

class PLConvexPolygon2d {

private:
	PLAutoPointer<std::list<PLAutoPointer<Vector2d> > > _vertexes;

public:
	PLConvexPolygon2d(Vector2d **inVertexes, int inCount);
	virtual ~PLConvexPolygon2d();

	void Print();
};

#endif /* PLCONVEXPOLYGON2D_H_ */
