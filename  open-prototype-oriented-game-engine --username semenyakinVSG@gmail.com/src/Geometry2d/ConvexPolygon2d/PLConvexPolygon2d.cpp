#include "PLConvexPolygon2d.h"

#include <iostream.h>
#include "../PLVector2d.h"

////////////////////////////////////////////////////////////////////////
PLConvexPolygon2d::PLConvexPolygon2d()
{
}

PLConvexPolygon2d::PLConvexPolygon2d(PLVector2dRef *inVertexes, int inCount)
{
	vertexes =
			PLAutoPointer<PLRoundList<PLVector2dRef> >::create();
	for (int i = 0; i < inCount; ++i)
	{
		vertexes->push_back(PLVector2dRef::create(*(inVertexes[i])));
	}
}

////////////////////////////////////////////////////////////////////////
PLConvexPolygon2d::~PLConvexPolygon2d()
{
}

////////////////////////////////////////////////////////////////////////
PLAutoPointer<PLRoundList<PLVector2dRef> > PLConvexPolygon2d::Vertexes()
{
	return vertexes;
}

////////////////////////////////////////////////////////////////////////
void PLConvexPolygon2d::Print()
{
	/*
	for (std::list<PLAutoPointer<Vector2d> >::iterator
			theVertexIterator = vertexes->begin();
			theVertexIterator != vertexes->end(); ++theVertexIterator)
	{
		std::cout << "Vertex (" << (*theVertexIterator)->X() << " : " <<
				(*theVertexIterator)->Y() << ")" << std::endl;
	}
	*/
}
