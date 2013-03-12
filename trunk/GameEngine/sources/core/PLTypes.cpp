///////////////////////////////////////////////////////////////////////////////
#include "PLTypes.h"

///////////////////////////////////////////////////////////////////////////////
PLPoint PLCreatePoint(double inX, double inY)
{
	PLPoint theSize;
	theSize.x = inX;
	theSize.y = inY;

	return theSize;
}

PLSize PLCreateSize(double inWidth, double inHeight)
{
	PLSize theSize;
	theSize.width = inWidth;
	theSize.height = inHeight;

	return theSize;
}

PLRectange PLCreateRectangle(double inX, double inY, double inWidth,
		double inHeight)
{
	PLRectange theRectangle;
	theRectangle.position = PLCreatePoint(inX, inY);
	theRectangle.size = PLCreateSize(inWidth, inHeight);

	return theRectangle;
}

///////////////////////////////////////////////////////////////////////////////
PLCharacter *charactersFromCharBuffer(const char *inCharBuffer, size_t inSize)
{
	PLCharacter *theCharacters = new PLCharacter(inSize + 1);

	size_t theIndex = 0;
	for (; theIndex < inSize; ++theIndex)
	{
		theCharacters[theIndex] = inCharBuffer[theIndex];
	}
	theCharacters[theIndex] = '\0';

	return theCharacters;
}
