#include "PLConvexPolygon2d.h"

#include <iostream.h>
#include "../Vector2d.h"

////////////////////////////////////////////////////////////////////////
PLConvexPolygon2d::PLConvexPolygon2d(Vector2d **inVertexes, int inCount)
{
	_vertexes =
			PLAutoPointer<std::list<PLAutoPointer<Vector2d> > >::create();
	for (int i = 0; i < inCount; ++i)
	{
		_vertexes->push_back(PLAutoPointer<Vector2d>::create(*(inVertexes[i])));
	}
}

////////////////////////////////////////////////////////////////////////
PLConvexPolygon2d::~PLConvexPolygon2d()
{
}

////////////////////////////////////////////////////////////////////////
void PLConvexPolygon2d::Print()
{
	for (std::list<PLAutoPointer<Vector2d> >::iterator
			theVertexIterator = _vertexes->begin();
			theVertexIterator != _vertexes->end(); ++theVertexIterator)
	{
		std::cout << "Vertex (" << (*theVertexIterator)->X() << " : " <<
				(*theVertexIterator)->Y() << ")" << std::endl;
	}
}
