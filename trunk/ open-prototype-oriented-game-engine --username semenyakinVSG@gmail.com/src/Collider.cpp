//============================================================================
// Name        : Collider.cpp
// Author      : semenyakinVS
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "Geometry2d/PLGeometry2dCore.h"
#include "Base/PLCore.h"

using namespace std;

PLConvexPolygon2dRef PLMakePolygon()
{
	PLVector2dRef *theVertexes = new PLVector2dRef[4];
	theVertexes[0] = PLVector2dRef::create(100.0, 100.0);
	theVertexes[1] = PLVector2dRef::create(100.0, 200.0);
	theVertexes[2] = PLVector2dRef::create(200.0, 200.0);
	theVertexes[3] = PLVector2dRef::create(200.0, 100.0);
	PLConvexPolygon2dRef thePolygon = PLConvexPolygon2dRef::create(theVertexes, 4);
	delete [] theVertexes;

	return thePolygon;
}

int main()
{
	PLColliderRef theCollider = PLColliderRef::create();

/*
	// ROUND LIST UNIT TESTS

	PLAutoPointer<PLRoundList<Vector2d> > theList = PLAutoPointer<PLRoundList<Vector2d> >::create();
	theList->push_back(new Vector2d(100.0, 100.0));
	theList->push_back(new Vector2d(100.0, 200.0));
	theList->push_back(new Vector2d(200.0, 200.0));
	theList->push_back(new Vector2d(200.0, 100.0));

	PLIterator<Vector2d> theIterator = theList->begin();
	for (int i = 0; i < 3 ; ++i)
	{
		cout << theIterator->X() << " : " << theIterator->Y() << endl;
		++theIterator;
	}

	// CONVEX POLYGON UNIT TESTS

	Vector2d **theVertexes = new Vector2d*[4];
	theVertexes[0] = new Vector2d(100.0, 100.0);
	theVertexes[1] = new Vector2d(100.0, 200.0);
	theVertexes[2] = new Vector2d(200.0, 200.0);
	theVertexes[3] = new Vector2d(200.0, 100.0);

	PLAutoPointer<PLConvexPolygon2d> thePolygon = PLAutoPointer<PLConvexPolygon2d>::create(theVertexes, 4);
	thePolygon->Print();
*/
	return 0;
}
