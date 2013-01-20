/*
 * TEST_PL_core_graph.cpp
 *
 *  Created on: Jan 14, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#include "TEST_PL_core_graph.h"

///////////////////////////////////////////////////////////////////////////////
TEST_PL_core_graph::TEST_PL_core_graph()
{
}

TEST_PL_core_graph::~TEST_PL_core_graph()
{
}

///////////////////////////////////////////////////////////////////////////////
void TEST_PL_core_graph::performTest()
{
	// Creation
	_graphPointer = new graph();



	// Removing
	delete _graphPointer;
}
