///////////////////////////////////////////////////////////////////////////////
#ifndef STRING_H_
#define STRING_H_

///////////////////////////////////////////////////////////////////////////////
#include "PLObject.h"
#include <string>

#include "PLScalarTypes.h"

///////////////////////////////////////////////////////////////////////////////
class PLString : public PLObject
{
private:
	std::string _string;

public:

	//////////////////////////////////////////////////////////////
	// *** Memory management ***
	// constructors

	PLString();

	PLString(const char *inCString);
	PLString(PLString *inString);

	// destructors
	virtual ~PLString();

	//////////////////////////////////////////////////////////////
	// *** Accessors ***

	//getters

	const char* getCString() const
	{
		return _string.c_str();
	}

	const size_t length() const
	{
		return _string.length();
	}

	//setters
	//adding
	void append(char inCharacter);
	void append(const char *inCString);
	void append(const PLString *inString);
	void append(const PLString *inString, int firstCharacter,
			int charactersCount);
	void pushBack(char inCharacter);

	//removing
	void assign(const char *inCString);
	void assign(const PLString *inString);
	void assign(const PLString *inString, int firstCharacter,
			int charactersCount);
	void erase(int position, int charactersCount);
	void clear();

	//swapping
	// Done without links exchanging, but with reassigning
	// I can`t get access to 'theString' in the swappingString but the encapsulation
	void swap(PLString *swappingString);

	//compare
	char &operator [] (size_t inIndex);

	PLString &operator += (const char &inChar);
	PLString &operator += (const PLCharacter &inCharacter);
	PLString &operator += (const PLString &inString);

	void operator = (const PLString &inString);
	bool operator < (const PLString &inString) const;
	bool operator == (const PLString &inString) const;

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

///////////////////////////////////////////////////////////////////////////////
PLString *PLStringCreate(const char *inCString);

#define PL_STR(C_STRING) PLStringCreate(C_STRING)

///////////////////////////////////////////////////////////////////////////////
#endif /* STRING_H_ */
