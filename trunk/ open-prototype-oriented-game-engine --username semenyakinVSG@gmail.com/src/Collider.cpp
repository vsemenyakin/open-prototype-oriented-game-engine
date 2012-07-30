//============================================================================
// Name        : Collider.cpp
// Author      : semenyakinVS
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
// Mateush Artyom is trying to commit this comment...
// Gusiev Olexandr is trying to commit this comment...
#include <iostream>

#include "Base/PLCore.h"
#include "Geometry2d/PLGeometry2dCore.h"

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
//	PLColliderRef theCollider = PLColliderRef::create();

	ref< PLRoundList< ref<PLVertex2d> > > theList;
	ref<PLVertex2d> theVertex = ref<PLVertex2d>::create(ref<PLVector2d>::create(100.0, 100.0));
	theList->push_back(theVertex);

	PLLog *theLog = new PLLog();

	theLog->beginGroup("Group_1");
	theLog->print("Message 1");
	theLog->print("Message 2");
	theLog->beginGroup("Group_2");
	theLog->print("Message 3");
	theLog->endGroup();
	theLog->endGroup();
	theLog->print("Message 4");

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
