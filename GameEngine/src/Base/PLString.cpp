#include "PLString.h"

//////////////////////////////////////////////////////////////
PLString *PLStringCreate(const char *inCString)
{
	return new PLString(inCString);
}

//////////////////////////////////////////////////////////////
// *** Memory management ***
// constructors
PLString::PLString()
{
}

PLString::PLString(const char *inCString)
{
	_string.append(inCString);
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
void PLString::append(char inCharacter)
{
	_string.append(&inCharacter);
}

void PLString::append(const char *inCString)
{
	_string.append(inCString);
}

void PLString::append(const PLString *inString)
{
	_string.append(inString->getCString());
}

void PLString::append(const PLString *inString, int firstCharacter,
		int charactersCount)
{
	_string.append(inString->getCString(), firstCharacter, charactersCount);
}

void PLString::pushBack(char inCharacter)
{
	_string.push_back(inCharacter);
}

//removing
void PLString::assign(const char *inCString)
{
	_string.assign(inCString);
}

void PLString::assign(const PLString *inString)
{
	_string.assign(inString->getCString());
}

void PLString::assign(const PLString *inString, int firstCharacter,
		int charactersCount)
{
	_string.assign(inString->getCString(), firstCharacter, charactersCount);
}

void PLString::erase(int position, int charactersCount)
{
	_string.erase(position, charactersCount);
}

void PLString::clear()
{
	_string.clear();
}

//swapping
void PLString::swap(PLString *swappingString)
{
	const char *tmp;

	tmp = getCString();
	_string.assign(swappingString->getCString());
	swappingString->assign(tmp);
}

// Characters access
char &PLString::operator [] (size_t inIndex)
{
	return _string[inIndex];
}

//
void PLString::operator = (const PLString &inString)
{
	_string = inString._string;
}

// Concating
PLString &PLString::operator += (const char &inChar)
{
	_string += inChar;

	return *this;
}

PLString &PLString::operator += (const PLCharacter &inCharacter)
{
	_string += inCharacter;

	return *this;
}

PLString &PLString::operator += (const PLString &inString)
{
	_string += inString._string;

	return *this;
}

// Functions concating
PLString &operator + (const PLString &inString, const char &inChar)
{
	PLString *theString = new PLString(inString);
	(*theString) += inChar;

	return *theString;
}

PLString &operator + (const PLString &inString, const PLCharacter &inCharacter)
{
	PLString *theString = new PLString(inString);
	(*theString) += inCharacter;

	return *theString;
}

PLString &operator + (const PLString &inStringA, const PLString &inStringB)
{
	PLString *theString = new PLString(inStringA);
	(*theString) += inStringB;

	return *theString;
}

// Comparing
bool PLString::operator < (const PLString &inString) const
{
	return this->_string < inString._string;
}

bool PLString::operator == (const PLString &inString) const
{
	return this->_string == inString._string;
}
