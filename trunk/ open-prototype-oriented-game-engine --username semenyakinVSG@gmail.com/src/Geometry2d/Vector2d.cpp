#include "Vector2d.h"

#include <math.h>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// *** Memory management ***
///////////////////////////////////////////////////////////////////////////////
// Designated constructor
Vector2d::Vector2d(float inX, float inY)
{
	this->setXY(inX, inY);
}

Vector2d::Vector2d(Vector2d &inVector)
{
	this->setXY(inVector.X(), inVector.Y());
}

Vector2d::Vector2d()
{
	this->setXY(0.0, 0.0);
}

///////////////////////////////////////////////////////////////////////////////
// Destructor
void Vector2d::destroy()
{
	std::cout << "PLVector2d destroyed" << std::endl;

	PLObject::destroy();
}

///////////////////////////////////////////////////////////////////////////////
// *** Accessors ***
///////////////////////////////////////////////////////////////////////////////
// --- Atomic ---
float Vector2d::X()
{
	return x;
}

float Vector2d::Y()
{
	return y;
}

void Vector2d::setX(float inX)
{
	if (inX != x)
	{
		__length_update_need = true;
		__angle_update_need = true;
	}

	x = inX;
}

void Vector2d::setY(float inY)
{
	if (inY != y)
	{
		__length_update_need = true;
		__angle_update_need = true;
	}

	y = inY;
}

void Vector2d::setXY(float inX, float inY)
{
	if (inX != x || inY != y)
	{
		__length_update_need = true;
		__angle_update_need = true;
	}

	x = inX;
	y = inY;
}

///////////////////////////////////////////////////////////////////////////////
// --- Complex ---
float Vector2d::length()
{
	if (__length_update_need)
	{
		__length = sqrtf(x * x + y * y);
		__length_update_need = false;
	}

	return __length;
}

float Vector2d::angle()
{
	if (__angle_update_need)
	{
		__angle = atan2f(y, x);
		__angle_update_need = false;
	}

	return __angle;
}

void Vector2d::setLength(float inLength)
{
	if (__length_update_need)
	{
		__length = inLength;
		x = __length * cosf(__angle);
		y = __length * sinf(__angle);

		__length_update_need = false;
	}
	else
	{
		float theDelta = inLength / __length;
		x *= theDelta;
		y *= theDelta;
	}
}

void Vector2d::setAngle(float inAngle)
{
	__angle = inAngle;

	float theLength = length();
	x = theLength * cosf(__angle);
	y = theLength * sinf(__angle);
}

///////////////////////////////////////////////////////////////////////////////
// *** Equivalents ***
///////////////////////////////////////////////////////////////////////////////
float Vector2d::length2()
{
	float theLength2 = 0;

	if (__length_update_need)
	{
		theLength2 = x * x + y *y;
		__length = sqrtf(theLength2);
		__length_update_need = false;
	}
	else
	{
		theLength2 = __length * __length;
	}

	return theLength2;
}

float Vector2d::ACV() const
{
	if (x > y) {
		if (x > -y) {
			return 2 - x/y;
		} else {
			return 4 + y/x;
		}
	} else {
		if (x > -y) {
			if (y >= 0) {
				return y/x;
			} else {
				return 8 + y/x;
			}
		} else {
			return 6 - x/y;
		}
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// *** Vector math ***
///////////////////////////////////////////////////////////////////////////////
// --- Vector ---
void Vector2d::sum(Vector2d *inVector)
{
	x += inVector->x;
	y += inVector->y;
}

void Vector2d::subtract(Vector2d *inVector)
{
	x -= inVector->x;
	y -= inVector->y;
}

///////////////////////////////////////////////////////////////////////////////
float Vector2d::scolarMultiply(Vector2d *inVector)
{
	return x * inVector->x + y * inVector->y;
}

float Vector2d::vectorMultiplyLength(Vector2d *inVector)
{
	return x * inVector->y - y * inVector->x;
}

///////////////////////////////////////////////////////////////////////////////
void Vector2d::proectToVector(Vector2d *inVector)
{
	float theDelta = scolarMultiply(inVector) / inVector->length2();

	float theX = inVector->X() * theDelta;
	float theY = inVector->Y() * theDelta;

	setXY(theX, theY);
}

float Vector2d::lengthOfProectionToVector(Vector2d *inVector)
{
	return scolarMultiply(inVector) / inVector->length();
}

///////////////////////////////////////////////////////////////////////////////
// --- Static ---
Vector2d *Vector2d::sumOfVectors(Vector2d *inVectorA, Vector2d *inVectorB)
{
	float theX = inVectorA->X() + inVectorB->X();
	float theY = inVectorA->Y() + inVectorB->Y();

	return new Vector2d(theX, theY);
}

Vector2d *Vector2d::subtractionOfVectors(Vector2d *inVectorA, Vector2d *inVectorB)
{
	float theX = inVectorA->X() - inVectorB->X();
	float theY = inVectorA->Y() - inVectorB->Y();

	return new Vector2d(theX, theY);
}

///////////////////////////////////////////////////////////////////////////////
float Vector2d::scolarMultiply(Vector2d *inVectorA, Vector2d *inVectorB)
{
	return inVectorA->X() * inVectorB->X() + inVectorA->Y() * inVectorB->Y();
}

float Vector2d::vectorMultiplyLength(Vector2d *inVectorA, Vector2d *inVectorB)
{
	return inVectorA->X() * inVectorB->Y() - inVectorA->Y() * inVectorB->X();
}

///////////////////////////////////////////////////////////////////////////////
Vector2d *Vector2d::proectionOfVectorToVector(Vector2d *inVectorA, Vector2d *inVectorB)
{
	float theDelta = Vector2d::scolarMultiply(inVectorA, inVectorB) / inVectorA->length2();

	float theX = inVectorB->X() * theDelta;
	float theY = inVectorB->Y() * theDelta;

	return new Vector2d(theX, theY);
}

float Vector2d::lengthOfProectionOfVectorToVector(Vector2d *inVectorA, Vector2d *inVectorB)
{
	return Vector2d::scolarMultiply(inVectorA, inVectorB) / inVectorA->length();
}
