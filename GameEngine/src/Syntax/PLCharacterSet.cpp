#include "PLCharacterSet.h"
#include <string>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
PLCharacterRange *PLChatacterRangeCreate(PLCharacter inBegin, PLCharacter inEnd)
{
	PLCharacterRange *theRange = new PLCharacterRange();
	theRange->begin = inBegin;
	theRange->end = inEnd;

	return theRange;
}

///////////////////////////////////////////////////////////////////////////////
PLCharacterSet::PLCharacterSet()
{
	int theSize = MAX_CHARACTER;
	hashBuffer = new bool[theSize];
	memset((void *)hashBuffer, 0, theSize);
}

PLCharacterSet::~PLCharacterSet()
{
	delete hashBuffer;
}

///////////////////////////////////////////////////////////////////////////////
void PLCharacterSet::addCharacter(PLCharacter inCharacter)
{
	hashBuffer[inCharacter] = true;
}

void PLCharacterSet::addRange(PLCharacterRange *inRange)
{
	for (PLCharacter theSymbolCode = inRange->begin;
			theSymbolCode <= inRange->end; ++theSymbolCode)
	{
		hashBuffer[theSymbolCode] = true;
	}
}

void PLCharacterSet::addSet(PLCharacterSet *inSet)
{
	for (PLCharacter theSymbolCode = 0;
			theSymbolCode < MAX_CHARACTER; ++theSymbolCode)
	{
		hashBuffer[theSymbolCode] |= inSet->containsCharacter(theSymbolCode);
	}
}

///////////////////////////////////////////////////////////////////////////////
bool PLCharacterSet::containsCharacter(PLCharacter inCharacterCode)
{
	return hashBuffer[inCharacterCode];
}

///////////////////////////////////////////////////////////////////////////////
PLString *PLCharacterSet::description()
{
	PLString *theDescription = new PLString();

	bool theRangeBegun = false;
	bool theFirstRange = true;
	PLCharacter theCharacterA, theCharacterB;

	for (PLCharacter theSymbolCode = 0; theSymbolCode < MAX_CHARACTER;
			++theSymbolCode)
	{
		if (true == hashBuffer[theSymbolCode])
		{
			if (false == theRangeBegun)
			{
				theRangeBegun = true;
				theCharacterA = theSymbolCode;
			}
		}
		else
		{
			if (true == theRangeBegun)
			{
				theCharacterB = theSymbolCode - 1;

				if (true == theFirstRange)
				{
					theFirstRange = false;
				}
				else
				{
					theDescription->append(", ");
				}

				if (theCharacterA == theCharacterB)
				{
					char theRangeString[3];
					sprintf(theRangeString, "\'%c\'", theCharacterA);

					theDescription->append(theRangeString);
				}
				else
				{
					char theRangeString[9];
					sprintf(theRangeString, "\'%c\'..\'%c\'", theCharacterA,
							theCharacterB);

					theDescription->append(theRangeString);
				}

				theRangeBegun = false;
			}
		}
	}

	return theDescription;
}

///////////////////////////////////////////////////////////////////////////////
PLCharacterSet *PLCharacterSet::digitsSet()
{
	PLCharacterSet *theDigitsSet = new PLCharacterSet();
	theDigitsSet->addRange(PLChatacterRangeCreate('0', '9'));

	return theDigitsSet;
}

PLCharacterSet *PLCharacterSet::lettersSet()
{
	PLCharacterSet *theLettersSet = new PLCharacterSet();
	theLettersSet->addRange(PLChatacterRangeCreate('a', 'z'));
	theLettersSet->addRange(PLChatacterRangeCreate('A', 'Z'));

	return theLettersSet;
}

PLCharacterSet *PLCharacterSet::anySymbolSet()
{
	PLCharacterSet *theLettersSet = new PLCharacterSet();

	theLettersSet->addRange(PLChatacterRangeCreate(0, MAX_CHARACTER - 1));

	return theLettersSet;
}
