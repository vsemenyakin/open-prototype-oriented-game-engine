/*
 * PLCollider.h
 *
 *  Created on: 01.01.2002
 *      Author: 422
 */

#ifndef PLCOLLIDER_H_
#define PLCOLLIDER_H_

#include "../../Base/Memory/PLAutoPointer.h"
#include "../ConvexPolygon2d/PLConvexPolygon2d.h"
#include "../PLVector2d.h"

#include <list>

////////////////////////////////////////////////////////////////
CLASS_WITH_REF(PLCollider) {

private:

public:
	PLCollider();
	virtual ~PLCollider();

	void pushPolygon(PLConvexPolygon2d *inPolygon);
};

#endif /* PLCOLLIDER_H_ */
