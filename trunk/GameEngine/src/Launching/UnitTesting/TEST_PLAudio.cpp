/*
 * TEST_PLAudio.cpp
 *
 *  Created on: 28.01.2013
 *      Author: нргл
 */
///////////////////////////////////////////////////////////////////////////////
#include "TEST_PLAudio.h"

#include "../../Audio/PLAudioController.h"
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
TEST_PLAudio::TEST_PLAudio()
{
}

TEST_PLAudio::~TEST_PLAudio()
{
}

///////////////////////////////////////////////////////////////////////////////
void TEST_PLAudio::performTest()
{
	std::cout << "////////////////////////////////////" << std::endl;
	std::cout << "Interactive audio testing started" << std::endl;

	PLAudioController* AudioControler = PLAudioController::instance();
	AudioControler->initialiseDevice(NULL);

	AudioControler->_audioLibrary.recordCreateHelloWorld(
			PL_STR("test_record"));

	AudioControler->createContext(PL_STR("context"), NULL);
	AudioControler->setContextCurrent(PL_STR("context"));

	AudioControler->getContext(PL_STR("context"))->
			createSource(PL_STR("source"));
	AudioControler->getContext(PL_STR("context"))->
			getSource(PL_STR("source"))->attachAudio(PL_STR("test_record"));
	AudioControler->getContext(PL_STR("context"))->
			getSource(PL_STR("source"))->play();

	std::cout << "Insert any string to finish:" << std::endl;
	int tmp;
	std::cin >>tmp;
	std::cout << "Interactive audio testing complited" << std::endl;
	std::cout << "////////////////////////////////////" << std::endl;
}
