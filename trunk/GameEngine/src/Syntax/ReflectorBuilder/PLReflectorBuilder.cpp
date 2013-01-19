/*
 * PLReflectorBuilder.cpp
 *
 *  Created on: 03.10.2012
 *      Author: Сергей
 */
///////////////////////////////////////////////////////////////////////////////
#include "PLReflectorBuilder.h"

#include <iostream.h>
#include "../Reflectors/PLCharacterStreamReflector.h"
#include "../PLCharacterSet.h"

#include "../../Behavior/Reflection/PLReflectionDictionary.h"

///////////////////////////////////////////////////////////////////////////////
// Identefier reflections
PLString *const kPLCreateIdentefierReflectionKey =
		PL_STR("createIdentefierReflectionKey");
void PLCreateIdentefierReflection(void *inTarget, void *inArguments)
{
}

PLString *const kPLPushSymbolToIdentefierReflectionKey =
		PL_STR("pushSymbolToIdentefierReflectionKey");
void PLPushSymbolToIdentefierReflection(void *inTarget, void *inArguments)
{
}

///////////////////////////////////////////////////////////////////////////////
// Character reflections
PLString *const kPLCreateCharacterReflectionKey =
		PL_STR("createCharacterReflectionKey");
void PLCreateCharacterReflection(void *inTarget, void *inArguments)
{
}

///////////////////////////////////////////////////////////////////////////////
// Character range reflections
PLString *const kPLSetFirstRangeSymbolReflectionKey =
		PL_STR("SetFirstRangeSymbolReflectionKey");
void PLSetFirstRangeSymbolReflection(void *inTarget, void *inArguments)
{
}

PLString *const kPLSetSecondRangeSymbolReflectionKey =
		PL_STR("SetSecondRangeSymbolReflectionKey");
void PLSetSecondRangeSymbolReflection(void *inTarget, void *inArguments)
{
}

///////////////////////////////////////////////////////////////////////////////
PLReflectorBuilder::PLReflectorBuilder()
{
	std::cout << "PLReflectionBuilder started..." << std::endl;
}

PLReflectorBuilder::~PLReflectorBuilder()
{
}

///////////////////////////////////////////////////////////////////////////////
PLCharacterStreamReflector *PLReflectorBuilder::identefierReflector()
{
/*
	// Declare sets
	PLCharacterSet *theCharactersSet = new PLCharacterSet();
	theCharactersSet->addSet(PLCharacterSet::lettersSet());
	theCharactersSet->addSet(PLCharacterSet::digitsSet());

	// Build identifier subreflector
	PLCharacterStreamReflector *theIdentifierReflector =
				new PLCharacterStreamReflector();

	PLString *theSymbolsStateKey = PL_STR("body");
	theIdentifierReflector->declareStateWithName(theSymbolsStateKey);

	// Build callbacks
	theIdentifierReflector->connectStates(kStateBegin, theSymbolsStateKey,
			PLCharacterSet::lettersSet(), reflections()->reflectionForName(
					kPLCreateIdentefierReflectionKey));
	theIdentifierReflector->createLoopConnection(theSymbolsStateKey,
			theCharactersSet, reflections()->reflectionForName(
					kPLPushSymbolToIdentefierReflectionKey));

	// TODO: Put finalizing edges (for finishing the machine)
*/
}

///////////////////////////////////////////////////////////////////////////////
PLCharacterStreamReflector *PLReflectorBuilder::characterReflector()
{
/*
	// Declare sets
	PLCharacterSet *theCharactersSet = new PLCharacterSet();
	theCharactersSet->addSet(PLCharacterSet::lettersSet());
	theCharactersSet->addSet(PLCharacterSet::digitsSet());

	PLCharacterSet *theQuoteSet = new PLCharacterSet();
	theQuoteSet->addRange(PLChatacterRangeCreate('\'', '\''));

	// Build identifier subreflector
	PLCharacterStreamReflector *theIdentifierReflector =
			new PLCharacterStreamReflector();

	PLString *theFoundFirstQuoteKey = PL_STR("foundFirstQuote");
	theIdentifierReflector->declareStateWithName(theFoundFirstQuoteKey);

	PLString *theFoundCharacterKey = PL_STR("foundCharacter");
	theIdentifierReflector->declareStateWithName(theFoundCharacterKey);

	// Build callbacks
	theIdentifierReflector->connectStates(kStateBegin, theFoundFirstQuoteKey,
			theQuoteSet, NULL);
	theIdentifierReflector->connectStates(theFoundFirstQuoteKey,
			theFoundCharacterKey, theCharactersSet,
					reflections()->reflectionForName(
							kPLCreateCharacterReflectionKey));

	// TODO: Put finalizing edges (for finishing the machine)
*/
}

///////////////////////////////////////////////////////////////////////////////
PLCharacterStreamReflector *PLReflectorBuilder::characterRangeReflector()
{
/*
	// Declare sets
	PLCharacterSet *theDotSet = new PLCharacterSet();
	theDotSet->addRange(PLChatacterRangeCreate('.', '.'));

	// Build identifier subreflector
	PLCharacterStreamReflector *theIdentifierReflector =
			new PLCharacterStreamReflector();

	PLString *theFoundFirstCharacterKey = PL_STR("foundFirstCharacter");
	theIdentifierReflector->declareStateWithName(theFoundFirstCharacterKey);

	PLString *theFoundFirstSeporationDotsKey =
			PL_STR("foundFirstSeporationDots");
	theIdentifierReflector->declareStateWithName(
			theFoundFirstSeporationDotsKey);

	PLString *theFoundSecondSeporationDotsKey =
			PL_STR("foundSecondSeporationDots");
	theIdentifierReflector->declareStateWithName(
			theFoundSecondSeporationDotsKey);

	PLString *theFoundSecondCharacterKey = PL_STR("foundSecondCharacter");
	theIdentifierReflector->declareStateWithName(theFoundSecondCharacterKey);

	// Build callbacks
	theIdentifierReflector->connectStates(kStateBegin,
			theFoundFirstCharacterKey, characterReflector(),
					reflections()->reflectionForName(
							kPLSetFirstRangeSymbolReflectionKey));

	theIdentifierReflector->connectStates(theFoundFirstCharacterKey,
			theFoundFirstSeporationDotsKey, theDotSet, NULL);

	theIdentifierReflector->connectStates(theFoundFirstSeporationDotsKey,
			theFoundSecondSeporationDotsKey, theDotSet, NULL);

	theIdentifierReflector->connectStates(theFoundSecondSeporationDotsKey,
			theFoundSecondCharacterKey, characterReflector(),
					reflections()->reflectionForName(
							kPLSetSecondRangeSymbolReflectionKey));

	// TODO: Put finalizing edges (for finishing the machine)
*/
}

///////////////////////////////////////////////////////////////////////////////
PLReflectionDictionary *PLReflectorBuilder::reflections()
{
	// ----------------------
	// Identefier reflections
	PLObject::reflections()->setReflectionForName(new PLReflection(this,
			PLCreateIdentefierReflection), kPLCreateIdentefierReflectionKey);

	PLObject::reflections()->setReflectionForName(new PLReflection(this,
			PLPushSymbolToIdentefierReflection),
				kPLPushSymbolToIdentefierReflectionKey);

	// ---------------------
	// Character reflections
	PLObject::reflections()->setReflectionForName(new PLReflection(this,
			PLCreateCharacterReflection), kPLCreateCharacterReflectionKey);

	// ---------------------------
	// Character range reflections
	PLObject::reflections()->setReflectionForName(new PLReflection(this,
			PLSetFirstRangeSymbolReflection),
					kPLSetFirstRangeSymbolReflectionKey);

	PLObject::reflections()->setReflectionForName(new PLReflection(this,
			PLSetSecondRangeSymbolReflection),
					kPLSetSecondRangeSymbolReflectionKey);

	return PLObject::reflections();
}
