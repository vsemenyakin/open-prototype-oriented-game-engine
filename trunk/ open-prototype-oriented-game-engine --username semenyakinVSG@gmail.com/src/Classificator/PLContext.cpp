#include "PLContext.h"

PLContext::PLContext() :
			subcontexts(NULL),
			objects(NULL)
{
}

void PLContext::destroy()
{
	subcontexts->release();
	objects->release();

	PLObject::destroy();
}

///////////////////////////////////////////////////////////////////////////////
// *** Subcontexts management ***
///////////////////////////////////////////////////////////////////////////////
void PLContext::addSubcontext(PLContext *inContext)
{
	if (NULL == objects)
	{
		subcontexts = new PLList();
	}

	subcontexts->addObject(inContext);
}

///////////////////////////////////////////////////////////////////////////////
// *** Content objects management ***
///////////////////////////////////////////////////////////////////////////////
PLBOOL PLContext::addObject(PLObject *inObject)
{
	if (NULL == objects)
	{
		objects = new PLList();
	}

	objects->addObject(inObject);
}
