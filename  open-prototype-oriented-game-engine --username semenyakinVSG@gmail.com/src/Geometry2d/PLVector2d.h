///////////////////////////////////////////////////////////////////////////////

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include "../Base/PLCore.h"

///////////////////////////////////////////////////////////////////////////////
CLASS_WITH_REF(PLVector2d) : public PLObject {

private:
	float x;
	float y;

	// Caching variables
	float __length;
	float __angle;

	bool __length_update_need;
	bool __angle_update_need;

public:
	// *** Memory management ***
	// constructors
	PLVector2d();
	PLVector2d(float inX, float inY);
	PLVector2d(PLVector2d &inVector);

	// destructors
	virtual void destroy();

	// *** Accessors ***
	// --- Atomic ---
	// getters
	float X();
	float Y();

	// setters
	void setX(float inX);
	void setY(float inY);

	void setXY(float inX, float inY);

	// --- Complex ---
	// getters
	float length();
	float angle();

	// setters
	void setLength(float inLength);
	void setAngle(float inAngle);

	// *** Equivalents ***
	float length2();
	float ACV() const;

	// *** Vector math ***
	// --- Vector ---
	void sum(PLVector2d *inVector);
	void subtract(PLVector2d *inVector);

	float scolarMultiply(PLVector2d *inVector);
	float vectorMultiplyLength(PLVector2d *inVector);

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
