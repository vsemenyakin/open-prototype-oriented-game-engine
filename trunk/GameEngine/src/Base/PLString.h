///////////////////////////////////////////////////////////////////////////////
#ifndef STRING_H_
#define STRING_H_

///////////////////////////////////////////////////////////////////////////////
#include "PLObject.h"
#include "Types/PLScalarTypes.h"

#include <string>

#include "Memory/PLAutoPointer.h"

///////////////////////////////////////////////////////////////////////////////
class PLString : public PLObject
{
private:


	// **************************************************************
	// *					 Private _ Variables					*
	// **************************************************************

	// ----------
	// *** String
	std::string _string;


public:


	// **************************************************************
	// *					 Public _ Methods						*
	// **************************************************************

	// ------------
	// *** Iterator
	PLString();

	PLString(const char *inString);
	PLString(function_ref<PLString> inString);

	// destructors
	virtual ~PLString();

	// -------------
	// *** Accessors
	const char *getCString() const;
	const PLIndex length() const;


	// *********************
	//   Extending methods
	// *********************

	// ---------------------------
	// *** Character methods group

	void assign(char inCharacter);
	void append(char inCharacter);


	// -------------------------
	// *** CString methods group

	void append(const char *inCString);

	// --------------------------
	// *** PLString methods group

	void append(function_ref<PLString> inString);
	void append(function_ref<PLString> inString, PLRange inRange);


	// ********************
	//   Erasing methods
	// ********************

	void erase(PLRange inRange);
	void clear();


	// *************
	//   Operators
	// *************

	// -------------
	// *** Assigning
	void operator = (const PLString &inString);

	// -------------
	// *** Comparing
	bool operator < (const PLString &inString) const;
	bool operator == (const PLString &inString) const;

	// -------------
	// *** Accessing
	char &operator [] (size_t inIndex);

	// -------------
	// *** Extending
	PLString &operator += (const char &inChar);
	PLString &operator += (const PLString &inString);

	//
	friend PLString &operator + (const PLString &inString, const char inChar);
	friend PLString &operator + (const PLString &inString,
			const PLCharacter inCharacter);
	friend PLString &operator + (const PLString &inString,
			const PLString &inString);
};

PLString &operator + (const PLString &inString, const char inChar);
PLString &operator + (const PLString &inString, const PLCharacter inCharacter);
PLString &operator + (const PLString &inStringA, const PLString &inStringB);

bool PLCStringEquals(const char *inCStringA, size_t inCStringALength,
		const char *inCStringB, size_t inCStringBLength);

///////////////////////////////////////////////////////////////////////////////
PLString *PLStringCreate(const char *inCString);

#define PL_STR(C_STRING) PLStringCreate(C_STRING)

///////////////////////////////////////////////////////////////////////////////
#endif /* STRING_H_ */
