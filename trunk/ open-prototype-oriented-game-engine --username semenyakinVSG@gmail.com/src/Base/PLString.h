///////////////////////////////////////////////////////////////////////////////
#ifndef STRING_H_
#define STRING_H_

///////////////////////////////////////////////////////////////////////////////
#include "PLObject.h"
#include <string>

///////////////////////////////////////////////////////////////////////////////
class PLString : public PLObject {
private:

	std::string theString;

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
		return theString.c_str();
	}

	const int length() const
	{
		return theString.length();
	}

	//setters
	//adding
	void append(const char *inCString);
	void append(const PLString *inString);
	void append(const PLString *inString, int firstCharacter, int charactersCount);
	void pushBack(char inCharacter);

	//removing
	void assign(const char *inCString);
	void assign(const PLString *inString);
	void assign(const PLString *inString, int firstCharacter, int charactersCount);
	void erase(int position, int charactersCount);
	void clear();

	//swapping
	// Done without links exchanging, but with reassigning
	// I can`t get access to 'theString' in the swappingString but the encapsulation
	void swap(PLString *swappingString);

	//compare
	bool PLString::operator < (const PLString &inStringA) const;
};


#endif /* STRING_H_ */
