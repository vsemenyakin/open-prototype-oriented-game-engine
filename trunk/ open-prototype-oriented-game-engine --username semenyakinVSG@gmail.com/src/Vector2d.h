///////////////////////////////////////////////////////////////////////////////

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include "Base/PLObject/PLObject.h"

///////////////////////////////////////////////////////////////////////////////
class Vector2d : public PLObject {

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
	Vector2d();
	Vector2d(float inX, float inY);
	Vector2d(Vector2d &inVector);

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
	void sum(Vector2d *inVector);
	void subtract(Vector2d *inVector);

	float scolarMultiply(Vector2d *inVector);
	float vectorMultiplyLength(Vector2d *inVector);

	void proectToVector(Vector2d *inVector);
	float lengthOfProectionToVector(Vector2d *inVector);

	// --- Static ---
	static Vector2d *sumOfVectors(Vector2d *inVectorA, Vector2d *inVectorB);
	static Vector2d *subtractionOfVectors(Vector2d *inVectorA, Vector2d *inVectorB);

	static float scolarMultiply(Vector2d *inVectorA, Vector2d *inVectorB);
	static float vectorMultiplyLength(Vector2d *inVectorA, Vector2d *inVectorB);

	static Vector2d *proectionOfVectorToVector(Vector2d *inVectorA, Vector2d *inVectorB);
	static float lengthOfProectionOfVectorToVector(Vector2d *inVectorA, Vector2d *inVectorB);
};

#endif /* VECTOR2D_H_ */
