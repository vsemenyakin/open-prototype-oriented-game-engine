/*
 * TEST_PL_core_graph.h
 *
 *  Created on: Jan 14, 2013
 *      Author: Admin
 */

#ifndef TEST_PL_CORE_GRAPH_H_
#define TEST_PL_CORE_GRAPH_H_

///////////////////////////////////////////////////////////////////////////////
#include "IPLUnitTest.h"
#include "../../CoreCollections/PL_core_graph.h"

///////////////////////////////////////////////////////////////////////////////
class TEST_PL_core_graph : public IPLUnitTest
{
private:


	// **************************************************************
	// *					 Private _ Types						*
	// **************************************************************

	typedef PL_core_graph<int, int> graph;


	// **************************************************************
	// *					 Private _ Variables					*
	// **************************************************************
	graph *_graphPointer;


	// **************************************************************
	// *					 Private _ Functions					*
	// **************************************************************

	// Test functions
//	void testCreation();
//	void testDistruction();

public:
	TEST_PL_core_graph();
	virtual ~TEST_PL_core_graph();

	// [IMPLEMENTATION: IPLUnitTest]
	void performTest();
};

#endif /* TEST_PL_CORE_GRAPH_H_ */
