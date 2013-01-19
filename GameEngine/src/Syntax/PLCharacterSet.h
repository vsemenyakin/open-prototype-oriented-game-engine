#ifndef PLCHARSET_H_
#define PLCHARSET_H_

///////////////////////////////////////////////////////////////////////////////
#include "../Base/PLCore.h"

///////////////////////////////////////////////////////////////////////////////
struct
{
	PLCharacter begin;
	PLCharacter end;
} typedef PLCharacterRange;

///////////////////////////////////////////////////////////////////////////////
PLCharacterRange *PLChatacterRangeCreate(PLCharacter inBegin,
		PLCharacter inEnd);

///////////////////////////////////////////////////////////////////////////////
class PLCharacterSet : public PLObject
{
private:
	bool *hashBuffer;

public:
	PLCharacterSet();
	virtual ~PLCharacterSet();

	void addCharacter(PLCharacter inCharacter);
	void addRange(PLCharacterRange *inRange);
	void addSet(PLCharacterSet *inSet);

	bool containsCharacter(PLCharacter inCharacterCode);

	// ----------------------------------------------------
	// *** Base behavior [IMPLEMENTATION: PLObject]
	virtual PLString *description();

	// Static

	static PLCharacterSet *lettersSet();
	static PLCharacterSet *digitsSet();
	static PLCharacterSet *anySymbolSet();
};

#endif /* PLCHARSET_H_ */
