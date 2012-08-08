#include "PLVector2d.h"

#include <math.h>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// *** Memory management ***
///////////////////////////////////////////////////////////////////////////////
// Designated constructor
PLVector2d::PLVector2d(float inX, float inY)
{
	this->setXY(inX, inY);
}

PLVector2d::PLVector2d(const PLVector2d &inVector)
{
	this->setXY(inVector.X(), inVector.Y());
}

PLVector2d::PLVector2d()
{
	this->setXY(0.0, 0.0);
}

///////////////////////////////////////////////////////////////////////////////
// Destructor
void PLVector2d::destroy()
{
	std::cout << "PLPLVector2d destroyed" << std::endl;

	PLObject::destroy();
}

///////////////////////////////////////////////////////////////////////////////
// *** Accessors ***
///////////////////////////////////////////////////////////////////////////////
// --- Atomic ---
float PLVector2d::X() const
{
	return vector.x;
}

float PLVector2d::Y() const
{
	return vector.y;
}

void PLVector2d::setX(float inX)
{
	if (inX != vector.x)
	{
		__length_update_need = true;
		__angle_update_need = true;
	}

	vector.x = inX;
}

void PLVector2d::setY(float inY)
{
	if (inY != vector.y)
	{
		__length_update_need = true;
		__angle_update_need = true;
	}

	vector.y = inY;
}

void PLVector2d::setXY(float inX, float inY)
{
	if (inX != vector.x || inY != vector.y)
	{
		__length_update_need = true;
		__angle_update_need = true;
	}

	vector.x = inX;
	vector.y = inY;
}

///////////////////////////////////////////////////////////////////////////////
// --- Complex ---
float PLVector2d::length() const
{
	if (__length_update_need)
	{
		__length = sqrtf(vector.x * vector.x + vector.y * vector.y);
		__length_update_need = false;
	}

	return __length;
}

float PLVector2d::angle() const
{
	if (__angle_update_need)
	{
		__angle = atan2f(vector.y, vector.x);
		__angle_update_need = false;
	}

	return __angle;
}

void PLVector2d::setLength(float inLength)
{
}

void PLVector2d::setAngle(float inAngle)
{
	__angle = inAngle;

	float theLength = this->length();
	vector.x = theLength * cosf(__angle);
	vector.y = theLength * sinf(__angle);
}

///////////////////////////////////////////////////////////////////////////////
// *** Equivalents ***
///////////////////////////////////////////////////////////////////////////////
float PLVector2d::length2() const
{
	return __length2;
}

float PLVector2d::ACV() const
{
//how to explain all these magic constants 2, 4, 6, 8...
	if (vector.x > vector.y) {
		if (vector.x > -vector.y) {
			return 2 - vector.x / vector.y; //ok, so i called this function with x=1 y=0 and LOL!!!
		} else {
			return 4 + vector.y / vector.x;
		}
	} else {
		if (vector.x > -vector.y) {
			if (vector.y >= 0) {
				return vector.y / vector.x;
			} else {
				return 8 + vector.y / vector.x;
				/*
					Look, at this point x<=y, x>-y, y<0. {(x>-y); (y<0)} =) (x>0), but {(x<=y); (y<0)} =) (x<0), maybe I am wrong, but i think this line will never be executed... 
				*/
			}
		} else {
			return 6 - vector.x / vector.y;
		}
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// *** Vector math ***
///////////////////////////////////////////////////////////////////////////////
// --- Vector ---

void PLVector2d::sum(PLVector2d *inVector)
{
	vector.x += inVector->vector.x;
	vector.y += inVector->vector.y;
}

void PLVector2d::subtract(PLVector2d *inVector)
{
	vector.x -= inVector->vector.x;
	vector.y -= inVector->vector.y;
}

///////////////////////////////////////////////////////////////////////////////
float PLVector2d::scolarMultiply(const PLVector2d *inVector) const
{
	return vector.x * inVector->vector.x + vector.y * inVector->vector.y;
}

float PLVector2d::vectorMultiplyLength(const PLVector2d *inVector) const
{
	return vector.x * inVector->vector.y - vector.y * inVector->vector.x;
}

///////////////////////////////////////////////////////////////////////////////
void PLVector2d::proectToVector(PLVector2d *inVector)
{
	float theDelta = scolarMultiply(inVector) / inVector->length2();

	float theX = inVector->X() * theDelta;
	float theY = inVector->Y() * theDelta;

	setXY(theX, theY);
}

float PLVector2d::lengthOfProectionToVector(PLVector2d *inVector)
{
	return scolarMultiply(inVector) / inVector->length();
}

///////////////////////////////////////////////////////////////////////////////
// --- Static ---
PLVector2d *PLVector2d::sumOfVectors(PLVector2d *inVectorA, PLVector2d *inVectorB)
{
	float theX = inVectorA->X() + inVectorB->X();
	float theY = inVectorA->Y() + inVectorB->Y();

	return new PLVector2d(theX, theY);
}

PLVector2d *PLVector2d::subtractionOfVectors(PLVector2d *inVectorA, PLVector2d *inVectorB)
{
	float theX = inVectorA->X() - inVectorB->X();
	float theY = inVectorA->Y() - inVectorB->Y();

	return new PLVector2d(theX, theY);
}

///////////////////////////////////////////////////////////////////////////////
float PLVector2d::scolarMultiply(PLVector2d *inVectorA, PLVector2d *inVectorB)
{
	return inVectorA->X() * inVectorB->X() + inVectorA->Y() * inVectorB->Y();
}

float PLVector2d::vectorMultiplyLength(PLVector2d *inVectorA, PLVector2d *inVectorB)
{
	return inVectorA->X() * inVectorB->Y() - inVectorA->Y() * inVectorB->X(); //not sure about sign of result
}

///////////////////////////////////////////////////////////////////////////////
PLVector2d *PLVector2d::proectionOfVectorToVector(PLVector2d *inVectorA, PLVector2d *inVectorB)
{
	float theDelta = PLVector2d::scolarMultiply(inVectorA, inVectorB) / inVectorA->length2();

	float theX = inVectorB->X() * theDelta;
	float theY = inVectorB->Y() * theDelta;

	return new PLVector2d(theX, theY);
}

float PLVector2d::lengthOfProectionOfVectorToVector(PLVector2d *inVectorA, PLVector2d *inVectorB)
{
	return PLVector2d::scolarMultiply(inVectorA, inVectorB) / inVectorA->length();
}
