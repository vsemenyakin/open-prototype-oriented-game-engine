/*
 * StackPull.cpp
 *
 *  Created on: 09.06.2012
 *      Author: SterX
 */

#include "ScalarStackPull.h"


///////////////////////////////////////////////////////////////////////////////
// *** Memory management ***
///////////////////////////////////////////////////////////////////////////////
// Designated constructor
template <class ItemType>
ScalarStackPull::ScalarStackPull(size_t inBlockSize)
{
	blockSize = inBlockSize;
	buffer = NULL;

	lengthOfBuffer = 0;
	freeSpaceLeft = 0;
	lengthOfPull = -1;
}

ScalarStackPull::ScalarStackPull()
{
	ScalarStackPull(DEFAULT_BLOCK_SIZE);
}

ScalarStackPull::~ScalarStackPull()
{
	delete buffer;
}

///////////////////////////////////////////////////////////////////////////////
// *** Content management ***
///////////////////////////////////////////////////////////////////////////////
template <class ItemType>
void ScalarStackPull::push(ItemType inElement)
{
	if (0 == freeSpaceLeft)
	{
		// Copy buffer
		ItemType *theBuffer = new ItemType[lengthOfBuffer + blockSize];

		memcpy(theBuffer, buffer, length);

		delete buffer;
		buffer = theBuffer;

		// Set fields
		lengthOfBuffer += blockSize;
		freeSpaceLeft = blockSize;
	}

	buffer[lengthOfPull] = inElement;

	// Change indexes
	--freeSpaceLeft;
	++lengthOfPull;
}

template <class ItemType>
void ScalarStackPull::pop()
{
	++freeSpaceLeft;
	--lengthOfPull;
}

ItemType *lastItem()
{
	return buffer[lengthOfPull];
}
