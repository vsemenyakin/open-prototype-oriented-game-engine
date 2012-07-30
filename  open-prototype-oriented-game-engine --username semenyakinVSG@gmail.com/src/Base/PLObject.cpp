///////////////////////////////////////////////////////////////////////////////
#include "PLObject.h"

#include "iostream.h"

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
ref<PLString> logString()
{
}

ref<PLString> logString(int inLogLevel)
{
}
