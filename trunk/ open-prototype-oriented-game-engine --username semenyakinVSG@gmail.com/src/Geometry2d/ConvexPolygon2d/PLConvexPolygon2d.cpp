#include "PLConvexPolygon2d.h"

#include "PLVertex2d.h"
#include "PLSegment2d.h"

////////////////////////////////////////////////////////////////////////
PLConvexPolygon2d::PLConvexPolygon2d()
{
}

PLConvexPolygon2d::PLConvexPolygon2d(ref<PLVector2d> *inVertexes, int inCount)
{
	_vertexes = ref< PLRoundList< ref<PLVertex2d> > >::create();
	for (int i = 0; i < inCount; ++i)
	{
		_vertexes->push_back(ref<PLVertex2d>::create(*inVertexes[i]));
	}

	PLRoundList< ref<PLVertex2d> >::Iterator theIterator = _vertexes->begin();

	ref<PLVertex2d> theCurrentVertex;
	ref<PLVertex2d> thePreviosVertex;
	ref<PLVertex2d> theNextVertex;

	for(; theIterator.loopCount() == 0; ++theIterator)
	{
		ref<PLVertex2d> thePreviosVertex = ref<PLVertex2d>::create(**theIterator.prev());
		ref<PLVertex2d> theCurrentVertex = ref<PLVertex2d>::create(**theIterator);
		ref<PLVertex2d> theNextVertex = ref<PLVertex2d>::create(**theIterator.next());

		theCurrentVertex->setPreviousSegment(new PLSegment2d(thePreviosVertex, theCurrentVertex));
		theCurrentVertex->setNextSegment(new PLSegment2d(thePreviosVertex, theCurrentVertex));

		thePreviosVertex->setNextSegment(theCurrentVertex->previousSegment());
		theNextVertex->setPreviousSegment(theCurrentVertex->nextSegment());
	}
}

////////////////////////////////////////////////////////////////////////
PLConvexPolygon2d::~PLConvexPolygon2d()
{
}

////////////////////////////////////////////////////////////////////////
ref< PLRoundList< ref<PLVertex2d> > > PLConvexPolygon2d::vertexes()
{
	return _vertexes;
}

////////////////////////////////////////////////////////////////////////
void PLConvexPolygon2d::Print()
{
}
