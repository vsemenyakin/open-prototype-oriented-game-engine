//============================================================================
// Name        : Collider.cpp
// Author      : semenyakinVS
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "Vector2d.h"
#include "Collider/PLConvexPolygon2d.h"

using namespace std;

int main(int argc, char** argv)
{
	Vector2d **theVectors = new Vector2d*[4];
	theVectors[0] = new Vector2d(100.0, 100.0);
	theVectors[1] = new Vector2d(100.0, 200.0);
	theVectors[2] = new Vector2d(200.0, 200.0);
	theVectors[3] = new Vector2d(200.0, 100.0);

	PLConvexPolygon2d *thePolygon = new PLConvexPolygon2d(theVectors, 4);
	thePolygon->print();
}
