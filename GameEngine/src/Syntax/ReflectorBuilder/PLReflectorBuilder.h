/*
 * PLReflectorBuilder.h
 *
 *  Created on: 03.10.2012
 *      Author: Сергей
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef PLREFLECTORBUILDER_H_
#define PLREFLECTORBUILDER_H_

///////////////////////////////////////////////////////////////////////////////
#include "../../Base/PLCore.h"

///////////////////////////////////////////////////////////////////////////////
class PLCharacterStreamReflector;

///////////////////////////////////////////////////////////////////////////////
class PLReflectorBuilder : public PLObject
{
public:
	PLReflectorBuilder();
	virtual ~PLReflectorBuilder();

	PLCharacterStreamReflector *identefierReflector();
	PLCharacterStreamReflector *characterReflector();
	PLCharacterStreamReflector *characterRangeReflector();

	virtual PLReflectionDictionary *reflections();
};

#endif /* PLREFLECTORBUILDER_H_ */
