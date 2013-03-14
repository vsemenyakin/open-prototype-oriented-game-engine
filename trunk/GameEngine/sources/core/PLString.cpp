#include "PLString.h"

//////////////////////////////////////////////////////////////
func_out_ref<PLString> PLStringCreate(const PLCharacter *inCString)
{
	return new_ref<PLString>(inCString);
}

//////////////////////////////////////////////////////////////
// *** Memory management ***

// constructors
PLString::PLString()
{
}

PLString::PLString(const PLCharacter *inCString)
{
	_string.append(inCString);
}

PLString::PLString(func_in_ref<PLString> inString)
{
	_string.append(inString->getCString());
}

// destructors
PLString::~PLString()
{
}

//////////////////////////////////////////////////////////////
// *** Accessors
const PLCharacter* PLString::getCString() const
{
	return _string.c_str();
}

const PLIndex PLString::length() const
{
	return _string.length();
}

//////////////////////////////////////////////////////////////
// *** Character methods group
void PLString::assign(PLCharacter inCharacter)
{
	this->clear();
	this->append(inCharacter);
}

void PLString::append(PLCharacter inCharacter)
{
	_string.push_back(inCharacter);
}

//////////////////////////////////////////////////////////////
// *** CString methods group
void PLString::append(const PLCharacter *inCString)
{
	_string.append(inCString);
}

//////////////////////////////////////////////////////////////
// *** PLString methods group
void PLString::append(func_in_ref<PLString> inString)
{
	_string.append(inString->getCString());
}

void PLString::append(func_in_ref<PLString> inString, PLRange inRange)
{
	_string.append(inString->getCString(), inRange.begin, inRange.count);
}

//////////////////////////////////////////////////////////////
// *** Erasing methods
void PLString::erase(PLRange inRange)
{
	_string.erase(inRange.begin, inRange.count);
}

void PLString::clear()
{
	_string.clear();
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

PLString &PLString::operator += (const PLString &inString)
{
	_string += inString._string;

	return *this;
}

// Functions concating
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

///////////////////////////////////////////////////////////////////////////////
// ***
///////////////////////////////////////////////////////////////////////////////
bool PLCStringEquals(const char *inCStringA, size_t inCStringALength,
		const char *inCStringB, size_t inCStringBLength)
{
	if (inCStringALength != inCStringBLength)
	{
		return false;
	}

	for (size_t theIndex = 0; theIndex < inCStringALength; ++theIndex)
	{
		if (inCStringA[theIndex] != inCStringB[theIndex])
		{
			return false;
		}
	}

	return true;
}

