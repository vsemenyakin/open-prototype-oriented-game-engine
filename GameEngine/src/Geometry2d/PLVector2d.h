///////////////////////////////////////////////////////////////////////////////

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include "../Base/PLCore.h"

///////////////////////////////////////////////////////////////////////////////
struct PLPoint2d
{
	float x;
	float y;
};

///////////////////////////////////////////////////////////////////////////////
CLASS_WITH_REF(PLVector2d) : public PLObject {

private:
	PLPoint2d vector;

	// Caching variables
	mutable PLPoint2d __ort;
	mutable float __length;
	mutable float __length2;
	mutable float __angle;

	mutable bool __length_update_need;
	mutable bool __angle_update_need;

public:
	// *** Memory management ***
	// constructors
	PLVector2d();
	PLVector2d(float inX, float inY);
	PLVector2d(const PLVector2d &inVector);

	// destructors
	virtual void destroy();

	// *** Accessors ***
	// --- Atomic ---
	// getters
	float X() const;
	float Y() const;

	// setters
	void setX(float inX);
	void setY(float inY);

	void setXY(float inX, float inY);

	// --- Complex ---
	// getters
	float length() const;
	float angle() const;

	// setters
	void setLength(float inLength);
	void setAngle(float inAngle);

	// *** Equivalents ***
	float length2() const;
	float ACV() const;

	// *** Vector math ***
	// --- Vector ---
	void sum(PLVector2d *inVector);
	void subtract(PLVector2d *inVector);

	float scolarMultiply(const PLVector2d *inVector) const;
	float vectorMultiplyLength(const PLVector2d *inVector) const;

	void proectToVector(PLVector2d *inVector);
	float lengthOfProectionToVector(PLVector2d *inVector);

	// --- Static ---
	static PLVector2d *sumOfVectors(PLVector2d *inVectorA, PLVector2d *inVectorB);
	static PLVector2d *subtractionOfVectors(PLVector2d *inVectorA, PLVector2d *inVectorB);

	static float scolarMultiply(PLVector2d *inVectorA, PLVector2d *inVectorB);
	static float vectorMultiplyLength(PLVector2d *inVectorA, PLVector2d *inVectorB);

	static PLVector2d *proectionOfVectorToVector(PLVector2d *inVectorA, PLVector2d *inVectorB);
	static float lengthOfProectionOfVectorToVector(PLVector2d *inVectorA, PLVector2d *inVectorB);
};

#endif /* VECTOR2D_H_ */
