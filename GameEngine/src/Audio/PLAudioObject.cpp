/*
 * PLAudioObject.cpp
 *
 *  Created on: 23.01.2013
 *      Author: нргл
 */

#include "PLAudioObject.h"

using namespace std;
///////////////////////////////////////////////////////////////////////////////
PLAudioObject::PLAudioObject() {
	// TODO Auto-generated constructor stub
}

PLAudioObject::~PLAudioObject() {
	// TODO Auto-generated destructor stub
}
///////////////////////////////////////////////////////////////////////////////
void PLAudioObject::checkError()
{
	ALenum theError = alGetError();
	if(theError!=AL_NONE)
	{
		cout<<"Audio error occurred: "<<theError<<endl;
	}
}

void PLAudioObject::clearErrors()
{
	alGetError();
}
