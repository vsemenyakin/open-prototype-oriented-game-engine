/*
 * PLList.cpp
 *
 *  Created on: 16.06.2012
 *      Author: SterX
 */

#include "PLList.h"

///////////////////////////////////////////////////////////////////////////////
//Functions PLList(), addObject(PLObject *inObject) and destroy() moved to PLList.h
//because of scope-specified way of method's implementation (I mean "void class::method()")
//is not working properly with templates now.
//I hope that's a temporary solution.
//PLAutoPointer is only in a header file, I think because of that.
///////////////////////////////////////////////////////////////////////////////

