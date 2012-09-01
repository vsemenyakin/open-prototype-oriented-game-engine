#include "PLString.h"

//////////////////////////////////////////////////////////////
// *** Memory management ***
// constructors

PLString::PLString()
{
}

PLString::PLString(const char *inCString)
{
	theString.append(inCString);
}

PLString::PLString(PLString *inString)
{
	append(inString);
}

// destructors

PLString::~PLString()
{
}

//////////////////////////////////////////////////////////////
// *** Accessors ***

//getters

//setters

//adding
void PLString::append(const char *inCString)
{
	theString.append(inCString);
}

void PLString::append(const PLString *inString)
{
	theString.append(inString->getCString());
}

void PLString::append(const PLString *inString, int firstCharacter, int charactersCount)
{
	theString.append(inString->getCString(), firstCharacter, charactersCount);
}

void PLString::pushBack(char inCharacter)
{
	theString.push_back(inCharacter);
}

//removing
void PLString::assign(const char *inCString)
{
	theString.assign(inCString);
}

void PLString::assign(const PLString *inString)
{
	theString.assign(inString->getCString());
}

void PLString::assign(const PLString *inString, int firstCharacter, int charactersCount)
{
	theString.assign(inString->getCString(), firstCharacter, charactersCount);
}

void PLString::erase(int position, int charactersCount)
{
	theString.erase(position, charactersCount);
}

void PLString::clear()
{
	theString.clear();
}

//swapping
void PLString::swap(PLString *swappingString)
{
	const char *tmp;

	tmp = getCString();
	theString.assign(swappingString->getCString());
	swappingString->assign(tmp);
}

// Comparing
bool PLString::operator < (const PLString &inStringA) const
{
	return this->theString < inStringA.theString;
}
