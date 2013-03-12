///////////////////////////////////////////////////////////////////////////////
#ifndef STRING_H_
#define STRING_H_

///////////////////////////////////////////////////////////////////////////////
#include "PLAutoPointer.h"
#include "../PLTypes.h"

#include <string>

///////////////////////////////////////////////////////////////////////////////
class PLString
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

	PLString(const PLCharacter *inString);
	PLString(func_in_ref<PLString> inString);

	// destructors
	virtual ~PLString();

	// -------------
	// *** Accessors
	const PLCharacter *getCString() const;
	const PLIndex length() const;


	// *********************
	//   Extending methods
	// *********************

	// ---------------------------
	// *** Character methods group

	void assign(PLCharacter inCharacter);
	void append(PLCharacter inCharacter);


	// -------------------------
	// *** CString methods group
	void append(const PLCharacter *inCString);

	// --------------------------
	// *** PLString methods group

	void append(func_in_ref<PLString> inString);
	void append(func_in_ref<PLString> inString, PLRange inRange);


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
	PLCharacter &operator [] (size_t inIndex);

	// -------------
	// *** Extending
	PLString &operator += (const PLCharacter &inChar);
	PLString &operator += (const PLString &inString);

	//
	friend PLString &operator + (const PLString &inString,
			const PLCharacter inCharacter);
	friend PLString &operator + (const PLString &inStringA,
			const PLString &inStringB);
};

PLString &operator + (const PLString &inString, const PLCharacter inCharacter);
PLString &operator + (const PLString &inStringA, const PLString &inStringB);

bool PLCStringEquals(const PLCharacter *inCStringA, size_t inCStringALength,
		const PLCharacter *inCStringB, size_t inCStringBLength);

///////////////////////////////////////////////////////////////////////////////
strong_ref<PLString> PLStringCreate(const PLCharacter *inCString);

#define PL_STR(C_STRING) PLStringCreate(C_STRING)

///////////////////////////////////////////////////////////////////////////////
#endif /* STRING_H_ */
