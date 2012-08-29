///////////////////////////////////////////////////////////////////////////////
#include "PLObject.h"
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
PLObject::PLObject() {
	referenceCount = 1;
}

PLObject::~PLObject()
{
}

///////////////////////////////////////////////////////////////////////////////
PLObject *PLObject::retain()
{
	++referenceCount;

	return this;
}

void PLObject::release()
{
	--referenceCount;
	if (0 == referenceCount)
	{
		this->destroy();
	}
}

void PLObject::destroy()
{
	std::cout << "PLObject destroyed" << std::endl;

	delete this;
}

///////////////////////////////////////////////////////////////////////////////
/*ref<PLString> PLObject::logString()
{
	//
	//ToDo: what's this for? Update this with new PLLOG

}

ref<PLString> PLObject::logString(int inLogLevel)
{	////ToDo: what's this for? Update this with new PLLOG

}
*/
