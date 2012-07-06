#include "PLAutoPointer.h"
#include <iostream.h>

static int debugCounter = 0;
///////////////////////////////////////////////////////////////////////////////
// *** Memory management ***
///////////////////////////////////////////////////////////////////////////////
template<typename ItemType>
PLAutoPointer<ItemType>::PLAutoPointer()
{
	sprintf(name, "pointer %i", debugCounter);
	++debugCounter;

	std::cout << "Constructor of " << name << std::endl;
	pointerWrapper = NULL;
}

///////////////////////////////////////////////////////////////////////////////
template<typename ItemType>
PLAutoPointer<ItemType>::PLAutoPointer(ItemType *inItem)
{
	sprintf(name, "pointer %i", debugCounter);
	++debugCounter;

	std::cout << "Constructor with item of " << name << std::endl;

	pointerWrapper = NULL;
	release();
	pointerWrapper = new PointerWrapper<ItemType>();
	pointerWrapper->pointer = inItem;
	retain();
}

template<typename ItemType>
PLAutoPointer<ItemType>::~PLAutoPointer()
{
	std::cout << "Destructor of " << name << std::endl;

	release();
}

///////////////////////////////////////////////////////////////////////////////
// *** Retain / Release ***
///////////////////////////////////////////////////////////////////////////////
template<typename ItemType>
void PLAutoPointer<ItemType>::release()
{
	if (NULL != pointerWrapper)
	{
		--pointerWrapper->referenceCount;
		if (0 == pointerWrapper->referenceCount)
		{
			delete pointerWrapper->pointer;
			delete pointerWrapper;
			pointerWrapper = NULL;
		}
	}

	std::cout << "Release of " << name << ". Reference count: " <<
				((NULL == pointerWrapper) ? 0 : pointerWrapper->referenceCount)
				<< std::endl;
}

template<typename ItemType>
void PLAutoPointer<ItemType>::retain()
{
	if (NULL != pointerWrapper)
	{
		++pointerWrapper->referenceCount;
	}

	std::cout << "Reatain of " << name << ". Reference count: " <<
				((NULL == pointerWrapper) ? 0 : pointerWrapper->referenceCount)
				<< std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// *** Operators ***
///////////////////////////////////////////////////////////////////////////////
template<typename ItemType>
void PLAutoPointer<ItemType>::operator = (
			PLAutoPointer<ItemType> &inAutoPointer)
{
	release();
	pointerWrapper = inAutoPointer.pointerWrapper;
	retain();
}

template<typename ItemType>
void PLAutoPointer<ItemType>::operator = (ItemType *inItem)
{
	release();
	pointerWrapper = new PointerWrapper<ItemType>();
	pointerWrapper->pointer = inItem;
	retain();
}

template<typename ItemType>
ItemType *PLAutoPointer<ItemType>::operator -> (void)
{
	return pointerWrapper->pointer;
}
