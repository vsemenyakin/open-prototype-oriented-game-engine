/*
 * PLCharacterReflector_StressTests.h
 *
 *  Created on: Dec 29, 2012
 *      Author: Admin
 */

///////////////////////////////////////////////////////////////////////////////
#ifndef PLCHARACTERREFLECTOR_STRESSTESTS_H_
#define PLCHARACTERREFLECTOR_STRESSTESTS_H_

///////////////////////////////////////////////////////////////////////////////
#include <map>
#include <string>

#include "../PLCharacterSet.h"

///////////////////////////////////////////////////////////////////////////////
class PLCharacterStreamReflector;

///////////////////////////////////////////////////////////////////////////////
class PLCharacterReflector_StressTests
{
private:

	std::map<PLCharacter, PLCharacterSet *> _sets;
	std::map<std::string, PLCharacterSet *> _rangeSets;

	PLCharacterSet *setForSymbol(PLCharacter inSymbol);
	PLCharacterSet *setForRange(PLCharacter inBeginSymbol,
			PLCharacter inEndSymbol, std::string &inName);

public:
	PLCharacterReflector_StressTests();
	virtual ~PLCharacterReflector_StressTests();

	PLCharacterStreamReflector *reflector();
};

#endif /* PLCHARACTERREFLECTOR_STRESSTESTS_H_ */
