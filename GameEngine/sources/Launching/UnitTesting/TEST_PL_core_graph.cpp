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
	: _graphPointer(NULL)
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

	graph::node_iterator theRoot = _graphPointer->createNodeWithValue(1);

	theRoot
		.beginBrunch()
			.createNodeWithValue(2, 2)
				.beginBrunch().createNodeWithValue(3, 3).endBrunch()
				.beginBrunch()
					.createNodeWithValue(4, 4)
						.beginBrunch().createNodeWithValue(5, 5).endBrunch()
						.beginBrunch().createNodeWithValue(6, 6).endBrunch()
				.endBrunch()
		.endBrunch();

	// Removing
	delete _graphPointer;
}
