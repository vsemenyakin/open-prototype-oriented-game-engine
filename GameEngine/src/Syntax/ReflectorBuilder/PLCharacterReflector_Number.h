/*
 * PLCharacterReflector_Number.h
 *
 *  Created on: Nov 23, 2012
 *      Author: Admin
 */

///////////////////////////////////////////////////////////////////////////////
#ifndef PLCHARACTERREFLECTOR_NUMBER_H_
#define PLCHARACTERREFLECTOR_NUMBER_H_

///////////////////////////////////////////////////////////////////////////////
class PLCharacterSet;
class PLCharacterStreamReflector;

///////////////////////////////////////////////////////////////////////////////
class PLCharacterReflector_Number
{
private:
	PLCharacterStreamReflector *_reflector;

	PLCharacterSet *_set_0_9;	// '0'..'9'
	PLCharacterSet *_set_0;		// '0'
	PLCharacterSet *_set_1_9;	// '1'..'9'
	PLCharacterSet *_set_DOT;	// '.'

	PLCharacterSet *set_0_9();
	PLCharacterSet *set_0();
	PLCharacterSet *set_1_9();
	PLCharacterSet *set_DOT();


public:
	PLCharacterReflector_Number();
	virtual ~PLCharacterReflector_Number();

	PLCharacterStreamReflector *reflector();
};

#endif /* PLCHARACTERREFLECTOR_NUMBER_H_ */
