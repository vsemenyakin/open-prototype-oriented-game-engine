/*
 * PLCharStreamReflector.cpp
 *
 *  Created on: 04.09.2012
 *      Author: Сергей
 */
///////////////////////////////////////////////////////////////////////////////
#include "PLCharacterStreamReflector.h"

// Atomic reflections
#include "PLEmptyReflector.h"
#include "PLCharacterReflector.h"
#include "PLStringReflector.h"

#include <iostream>

#include "../../Base/Diagnostic/PLScopeBasedLog.h"

///////////////////////////////////////////////////////////////////////////////
PLCharacterStreamReflector::PLCharacterStreamReflector()
{
	_initialStateMark = NULL;

	__failedStateIterator = NULL;
	__finalStateIterator = NULL;
}

///////////////////////////////////////////////////////////////////////////////
PLCharacterStreamReflector::~PLCharacterStreamReflector()
{
}

///////////////////////////////////////////////////////////////////////////////
void PLCharacterStreamReflector::makeEmptyBranch(
		PLCharacterStreamReflectorMark *inBeginMark,
		PLCharacterStreamReflectorMark **inoutFinishedMark)
{
	connectStateWithMarks(inBeginMark, inoutFinishedMark,
			new PLEmptyReflector());
}

void PLCharacterStreamReflector::makeBranchWithSet(
		PLCharacterStreamReflectorMark *inBeginMark,
		PLCharacterStreamReflectorMark **inoutFinishedMark,
		PLCharacterSet *inSet, PLReflection *inReflection)
{
	connectStateWithMarks(inBeginMark, inoutFinishedMark,
			new PLCharacterReflector(inSet, inReflection));
}

void PLCharacterStreamReflector::makeBranchWithString(
		PLCharacterStreamReflectorMark *inBeginMark,
		PLCharacterStreamReflectorMark **inoutFinishedMark, PLString *inString)
{
	connectStateWithMarks(inBeginMark, inoutFinishedMark,
			new PLStringReflector(inString));
}

void PLCharacterStreamReflector::makeBranchWithSubreflection(
		PLCharacterStreamReflectorMark *inBeginMark,
		PLCharacterStreamReflectorMark **inoutFinishedMark,
		PLCharacterStreamReflector *subreflection, PLReflection *inReflection)
{
	connectStateWithMarks(inBeginMark, inoutFinishedMark, subreflection);
}

///////////////////////////////////////////////////////////////////////////////
void PLCharacterStreamReflector::connectStateWithMarks(
		PLCharacterStreamReflectorMark *inBeginMark,
		PLCharacterStreamReflectorMark **inoutFinishedMark,
		IPLCharacterReflector *inCondition)
{
	// . ~~~~
	PLScopeBasedLog::sharedLog()->print("Create connection");
	PLScopeBasedLog::sharedLog()->endLine();
	PLScopeBasedLog::sharedLog()->beingScope();
	// . ~~~~

	if (NULL == inCondition || NULL == inBeginMark)
	{
		return;
	}

	// Create item and add to current

	// . ~~~~
	PLScopeBasedLog::sharedLog()->print(inBeginMark);
	PLScopeBasedLog::sharedLog()->print("	");
	PLScopeBasedLog::sharedLog()->print(*inoutFinishedMark);
	PLScopeBasedLog::sharedLog()->endLine();
	// . ~~~~

	// Branch creation mode
	if (NULL == *inoutFinishedMark)
	{
		// Remove previous node from final nodes and add new node to it
		PLStateGraph::edge_iterator theIterator = (**inBeginMark)->findEdgeTo(
				this->finalStateGraphIterator());
		if (theIterator != (**inBeginMark)->edgesOut()->end())
		{
			(**inBeginMark)->removeEdgeOut(theIterator);
		}

		(**inBeginMark)->connectToNode(this->failedStateGraphIterator(), NULL);


		// . ~~~~
		PLScopeBasedLog::sharedLog()->print("Branch creation mode");
		PLScopeBasedLog::sharedLog()->endLine();
		// . ~~~~

		*inoutFinishedMark = new PLCharacterStreamReflectorMark(
				PLStateGraph::sharedGraph()->createNodeWithValue(
						PLStateGraphNodeMarkerDefault));

		(**inBeginMark)->connectToNode(***inoutFinishedMark, inCondition);
		(***inoutFinishedMark)->connectToNode(this->finalStateGraphIterator(),
				NULL);
	}
	// Branch connection mode
	else
	{
		// . ~~~~
		PLScopeBasedLog::sharedLog()->print("Branch connection mode");
		PLScopeBasedLog::sharedLog()->endLine();
		// . ~~~~

		inBeginMark->_iterator->connectToNode((*inoutFinishedMark)->_iterator,
				inCondition);
	}

	// . ~~~~
	PLScopeBasedLog::sharedLog()->print("Condition: ");
	PLScopeBasedLog::sharedLog()->print((char *)inCondition->description()->
			getCString());
	PLScopeBasedLog::sharedLog()->print(" connect ");
	PLScopeBasedLog::sharedLog()->print(**inBeginMark);
	PLScopeBasedLog::sharedLog()->print(" to ");
	PLScopeBasedLog::sharedLog()->print(**(*inoutFinishedMark));
	PLScopeBasedLog::sharedLog()->endLine();
	PLScopeBasedLog::sharedLog()->endScope();
	// . ~~~~
}

///////////////////////////////////////////////////////////////////////////////
PLCharacterStreamReflector::PLReflectionTreeBuilder
		*PLCharacterStreamReflector::builderForRootIterator(
				PLReflectionTree::node_iterator *inIterator)
{
	// . ~~~~
	PLScopeBasedLog::sharedLog()->print("Get builder for root iterator:");
	PLScopeBasedLog::sharedLog()->endLine();
	PLScopeBasedLog::sharedLog()->beingScope();
	// . ~~~~

	PLReflectionTreeBuilder *theBuilder = NULL;

	if (_resultBuilders.end() == _resultBuilders.find(inIterator))
	{
		// . ~~~~
		PLScopeBasedLog::sharedLog()->print(
				"No builder for selected root iterator. Begin it's creation:");
		PLScopeBasedLog::sharedLog()->endLine();

		PLScopeBasedLog::sharedLog()->beingScope();
		// . ~~~~

		// Create new builder
		theBuilder = new PLReflectionTreeBuilder();

		theBuilder->root = PLReflectionTree::sharedGraph()->
				createNodeWithValue(PLReflection::dummyReflection());

		theBuilder->buildingFront = new PLBuildingFront();
		theBuilder->buildingFront->push_back(createGrowPoint(theBuilder->root,
				**initialStateMark()));

		// . ~~~~
		PLScopeBasedLog::sharedLog()->endScope();
		// . ~~~~

		_resultBuilders[inIterator] = theBuilder;
	}
	else
	{
		// . ~~~~
		PLScopeBasedLog::sharedLog()->print("Root exists");
		PLScopeBasedLog::sharedLog()->endLine();
		// . ~~~~

		theBuilder = _resultBuilders[inIterator];
	}

	// . ~~~~
	PLScopeBasedLog::sharedLog()->endScope();
	// . ~~~~

	return theBuilder;
}


PLCharacterReflectorUpdatingResult *PLCharacterStreamReflector::
		updateForRootIteratorWithSymbol(
				PLReflectionTree::node_iterator *inIterator,
						PLCharacter inCharacter)
{
	// . ~~~~
	PLScopeBasedLog::sharedLog()->print("CSR update for character \'");
	PLScopeBasedLog::sharedLog()->print(inCharacter);
	PLScopeBasedLog::sharedLog()->print("\':");
	PLScopeBasedLog::sharedLog()->endLine();
	PLScopeBasedLog::sharedLog()->beingScope();
	// . ~~~~

	PLReflectionTreeBuilder *theBuilder = builderForRootIterator(inIterator);

	// . ~~~~
	PLScopeBasedLog::sharedLog()->print("Builder found");
	PLScopeBasedLog::sharedLog()->endLine();
	// . ~~~~

	// Create standard updating result
	PLCharacterReflectorUpdatingResult *theUpdatingResult =
			new PLCharacterReflectorUpdatingResult();

	theUpdatingResult->branches = NULL;
	theUpdatingResult->root = theBuilder->root;

	theUpdatingResult->updateStatus = PLCharacterReflectorFinished;

	// . ~~~~
	PLScopeBasedLog::sharedLog()->print("Created updating result");
	PLScopeBasedLog::sharedLog()->endLine();
	// . ~~~~

	// Iterating through all buds
	PLBuildingFront *theUpdatingFront = new PLBuildingFront(
			theBuilder->buildingFront);
	PLBuildingFront *theExtraFront = new PLBuildingFront();

	theBuilder->buildingFront->clear();

	// . ~~~~
	PLScopeBasedLog::sharedLog()->print("Begin updating the building front");
	PLScopeBasedLog::sharedLog()->endLine();

	PLScopeBasedLog::sharedLog()->beingScope();
	// . ~~~~

	do
	{
		// . ~~~~
		PLScopeBasedLog::sharedLog()->print("The iteration began for ");
		PLScopeBasedLog::sharedLog()->print(theUpdatingFront->size());
		PLScopeBasedLog::sharedLog()->print(" grow points");
		PLScopeBasedLog::sharedLog()->endLine();

		PLScopeBasedLog::sharedLog()->beingScope();
		// . ~~~~

		theExtraFront->clear();

		// Get all finished points by updating
		// points from current updating front
 		for (PLBuildingFront::iterator theGrowPointIterator =
				theUpdatingFront->begin();
						theGrowPointIterator != theUpdatingFront->end();
								++theGrowPointIterator)
		{
 			// . ~~~~
 			PLScopeBasedLog::sharedLog()->print("Update next grow point");
 			PLScopeBasedLog::sharedLog()->endLine();

 			PLScopeBasedLog::sharedLog()->beingScope();
 			// . ~~~~

 			PLGrowPointUpdatingResults *theResult = updateGrowPoint(
 					*theGrowPointIterator, inCharacter);

 			theExtraFront->push_back(theResult->branches);

 			// . ~~~~
 			PLScopeBasedLog::sharedLog()->print(
 					"Grow point just updated. Generated ");
 			PLScopeBasedLog::sharedLog()->print(theExtraFront->size());
 			PLScopeBasedLog::sharedLog()->print(" grow points");
 			PLScopeBasedLog::sharedLog()->endLine();
 			// . ~~~~

 			// Test if the grow point finished
 			if (theResult->updateStatus == PLCharacterReflectorFailed)
 			{
 				 // . ~~~~
 				 PLScopeBasedLog::sharedLog()->print("Grow point failed");
 				 PLScopeBasedLog::sharedLog()->endLine();
 				 // . ~~~~

 				 // If grow point failed - remove it's branch
 				 (*theGrowPointIterator)->defferedReflection->
 						 removeCurrentBranch();

 				 // Put the node to removing list
 				 theUpdatingFront->deferredRemove(theGrowPointIterator);
 			}
 			else if (theResult->updateStatus == PLCharacterReflectorFinal)
 			{
 				 // . ~~~~
 				 PLScopeBasedLog::sharedLog()->print("Grow point is final");
 				 PLScopeBasedLog::sharedLog()->endLine();
 				 // . ~~~~

 				 // If grow point is final - put it's root to returning results
 				 if (NULL == theUpdatingResult->branches)
 				 {
 				 		theUpdatingResult->branches =
 				 				new PLReflectionTreeIterationFront();
 				 }

 				 theUpdatingResult->branches->push_back(
 				 		(*theGrowPointIterator)->defferedReflection);

 				 // Put the node to removing list
 				 theUpdatingFront->deferredRemove(theGrowPointIterator);
 			}
 			else if (theResult->updateStatus == PLCharacterReflectorFinished)
			{
 				// Connect all branches
 				PLGrowPoint *theGrowPoint = *theGrowPointIterator;

 				PLReflectionTree::edge_iterator theIterator =
 						theGrowPoint->rootReflection->edgesOut()->begin();
 				for (; theIterator !=
 						theGrowPoint->rootReflection->edgesOut()->end();
 								++theIterator)
 				{
 					theGrowPoint->defferedReflection->connectToNode(
 							(*theIterator)->iteratorOut(), NULL);
 				}
 				theGrowPoint->rootReflection->_graph->excludeNodeFromGraph(
 						theGrowPoint->rootReflection);

				// . ~~~~
				PLScopeBasedLog::sharedLog()->print(
						"Grow point finished after update");
				// . ~~~~

				// Just remove the node
				theUpdatingFront->deferredRemove(theGrowPointIterator);
			}

			// . ~~~~
			PLScopeBasedLog::sharedLog()->endScope();
			// . ~~~~
		}

 		// Add updated updating front to all update results
 		theUpdatingFront->update();
 		theBuilder->buildingFront->push_back(theUpdatingFront);

 		// Set new updating front from last iteration generated grow points and
 		// clear the list of generated grow points
 		theUpdatingFront->set(theExtraFront);

 		// . ~~~~
 		PLScopeBasedLog::sharedLog()->endScope();
 		// . ~~~~

		// iterating stops if there was not finished buds in grow point
	} while (theUpdatingFront->size() != 0);

	// If there is no grow points in builder - set some other update status
	theUpdatingResult->updateStatus = PLCharacterReflectorUpdating;
	if (theBuilder->buildingFront->size() == 0)
	{
		if (theBuilder->root->edgesOut()->size() == 0)
		{
			theUpdatingResult->updateStatus = PLCharacterReflectorFailed;
//			theUpdatingResult->updateStatus = PLCharacterReflectorFailed;
//			for (PLStateGraph::edge_iterator theEdgeIterator =
//					_stateGraphRoot->edgesOut()->begin();
//					theEdgeIterator != _stateGraphRoot->edgesOut()->end() &&
//				(theUpdatingResult->updateStatus == PLCharacterReflectorFailed);
//					++theEdgeIterator)
//			{
//				if ((*theEdgeIterator)->value == NULL)
//				{
//					theUpdatingResult->updateStatus =
//							PLCharacterReflectorFinished;
//				}
//			}
		}
		else
		{
			theUpdatingResult->updateStatus = PLCharacterReflectorFinished;
		}
	}

	// . ~~~~
	PLScopeBasedLog::sharedLog()->endScope();
	// . ~~~~

	// . ~~~~
	PLScopeBasedLog::sharedLog()->print(
			"Machine returned with update status: ");
	PLScopeBasedLog::sharedLog()->print(theUpdatingResult->updateStatus);
	PLScopeBasedLog::sharedLog()->endLine();
	// . ~~~~

	PLScopeBasedLog::sharedLog()->endScope();

	// Return processing status
	return theUpdatingResult;
}

///////////////////////////////////////////////////////////////////////////////
PLCharacterStreamReflector::PLGrowPoint *PLCharacterStreamReflector::
		createGrowPoint(PLReflectionTree::node_iterator *inIterator,
				PLStateGraph::node_iterator *inNode)
{
	// . ~~~~
	PLScopeBasedLog::sharedLog()->print("Grow point creation:");
	PLScopeBasedLog::sharedLog()->endLine();

	PLScopeBasedLog::sharedLog()->beingScope();
	// . ~~~~

	PLGrowPoint *thePoint = new PLGrowPoint();

	// . ~~~~
	PLScopeBasedLog::sharedLog()->print("Grow point address: ");
	PLScopeBasedLog::sharedLog()->print(thePoint);

	PLScopeBasedLog::sharedLog()->endLine();
	// . ~~~~

	thePoint->defferedReflection = inIterator;

	thePoint->rootReflection = PLReflectionTree::sharedGraph()->
			createNodeWithValue(PLReflection::dummyReflection());
	thePoint->connections = new PLReflectorConnectionGroup();

	PLStateGraph::edge_iterator theIterator = inNode->edgesOut()->begin();
	for (; theIterator != inNode->edgesOut()->end(); ++(theIterator))
	{
		if ((*theIterator)->value != NULL)
		{
			thePoint->connections->push_back(theIterator);

			// . ~~~~
			PLScopeBasedLog::sharedLog()->print("Created connection");
			PLScopeBasedLog::sharedLog()->endLine();
			// . ~~~~
		}
		else
		{
			thePoint->defaultConnection = theIterator;

			// . ~~~~
			PLScopeBasedLog::sharedLog()->print(
					"Created default connection");
			PLScopeBasedLog::sharedLog()->endLine();
			// . ~~~~
		}
	}

	PLScopeBasedLog::sharedLog()->endScope();

	return thePoint;
}

PLCharacterStreamReflector::PLGrowPointUpdatingResults
		*PLCharacterStreamReflector::
				updateGrowPoint(PLGrowPoint *inGrowPoint, char inSymbol)
{
	// . ~~~~
	PLScopeBasedLog::sharedLog()->print("Updating grow point:");
	PLScopeBasedLog::sharedLog()->endLine();

	PLScopeBasedLog::sharedLog()->beingScope();
	// . ~~~~

	// Create result
	PLGrowPointUpdatingResults *theGrowPointResult =
			new PLGrowPointUpdatingResults();
	theGrowPointResult->branches = new PLBuildingFront();
	theGrowPointResult->updateStatus = PLCharacterReflectorUpdating;

	//
	PLReflectorConnectionGroup *theConnections = inGrowPoint->connections;

	// . ~~~~
	PLScopeBasedLog::sharedLog()->print("Update grow point's ");
	PLScopeBasedLog::sharedLog()->print(inGrowPoint);
	PLScopeBasedLog::sharedLog()->print(" connections ");
	PLScopeBasedLog::sharedLog()->print("[ ");
	PLScopeBasedLog::sharedLog()->print(inGrowPoint->connections->size());
	PLScopeBasedLog::sharedLog()->print(" ]:");
	PLScopeBasedLog::sharedLog()->endLine();

	PLScopeBasedLog::sharedLog()->beingScope();
	// . ~~~~

	for (PLReflectorConnectionGroup::iterator theIterator =
			theConnections->begin(); theIterator != theConnections->end();
					++theIterator)
	{
		// . ~~~~
		PLScopeBasedLog::sharedLog()->print(
				"Updating connection with condition ");
		PLScopeBasedLog::sharedLog()->print((char *)(**theIterator)->value->
				description()->getCString());
		PLScopeBasedLog::sharedLog()->endLine();

		PLScopeBasedLog::sharedLog()->beingScope();
		// . ~~~~


		// *********************
		// Update the connection
		// *********************
		PLCharacterReflectorUpdatingResult *theResult =
				(**theIterator)->value->updateForRootIteratorWithSymbol(
						inGrowPoint->rootReflection, inSymbol);

		// *******************************
		// Decide what to do with branches
		// *******************************
		if (theResult->branches != NULL)
		{
			// . ~~~~
			PLScopeBasedLog::sharedLog()->print(
					"Condition returned with some results");
			PLScopeBasedLog::sharedLog()->endLine();

			PLScopeBasedLog::sharedLog()->beingScope();
			// . ~~~~

			PLReflectionTreeIterationFront::iterator theBranchesIterator =
					theResult->branches->begin();
			for (; theBranchesIterator != theResult->branches->end();
					++theBranchesIterator)
			{
				// Create new grow points by finished connection branches
				PLGrowPoint *theGrowPoint = createGrowPoint(
						*theBranchesIterator, (**theIterator)->iteratorOut());

				theGrowPointResult->branches->push_back(theGrowPoint);
			}

			// . ~~~~
			PLScopeBasedLog::sharedLog()->endScope();
			// . ~~~~

			//inGrowPoint->defaultConnection = PLStateGraph::nullEdge();
		}


		// *************************
		// Process the update status
		// *************************
		if (theResult->updateStatus == PLCharacterReflectorFinished)
		{
			// . ~~~~
			PLScopeBasedLog::sharedLog()->print("Connection finished");
			// . ~~~~

			// If this was empty update - do nothing
			if (theResult->root->edgesOut()->size() != 0)
			{
				// . ~~~~
				PLScopeBasedLog::sharedLog()->print(
						" and contains some branches. ");
				PLScopeBasedLog::sharedLog()->print(
						"Begin connecting root of grow point with branches");
				PLScopeBasedLog::sharedLog()->endLine();

				PLScopeBasedLog::sharedLog()->beingScope();
				// . ~~~~

				// If there was some branches of current connection root -
				// connect grow point's root with finished connection
				// root branches.
				PLReflectionTree::edge_iterator theEdgeIterator =
						theResult->root->edgesOut()->begin();

				for (; theEdgeIterator != theResult->root->edgesOut()->end();
						++theEdgeIterator)
				{
					inGrowPoint->rootReflection->connectToNode(
							(*theEdgeIterator)->iteratorOut(), NULL);

					// . ~~~~
					PLScopeBasedLog::sharedLog()->print("Connected root ");
					PLScopeBasedLog::sharedLog()->print(
							**inGrowPoint->rootReflection);
					PLScopeBasedLog::sharedLog()->print(" to brunch ");
					PLScopeBasedLog::sharedLog()->print(
							(*theEdgeIterator)->iteratorOut());

					PLScopeBasedLog::sharedLog()->endLine();
					// . ~~~~
				}
				theResult->root->_graph->excludeNodeFromGraph(theResult->root);

				// . ~~~~
				PLScopeBasedLog::sharedLog()->endScope();
				// . ~~~~
			}
//			else
//			{
//				// . ~~~~
//				PLScopeBasedLog::sharedLog()->print(
//						" and it was empty. Simply create next grow point");
//				PLScopeBasedLog::sharedLog()->endLine();
//				// . ~~~~
//
//				// Condition for empty connection
//				PLGrowPoint *theGrowPoint = createGrowPoint(
//						inGrowPoint->defferedReflection,
//								(**theIterator)->iteratorOut());
//
//				theGrowPointResult->branches->push_back(theGrowPoint);
//				inGrowPoint->defaultConnection = PLStateGraph::nullEdge();
//			}

			theConnections->deferredRemove(theIterator);
		}
		else if (theResult->updateStatus == PLCharacterReflectorFailed)
		{
			// . ~~~~
			PLScopeBasedLog::sharedLog()->print("Branch failed");
			PLScopeBasedLog::sharedLog()->endLine();
			// . ~~~~

			theConnections->deferredRemove(theIterator);
		}

		// . ~~~~
		PLScopeBasedLog::sharedLog()->endScope();
		// . ~~~~
	}

	// . ~~~~
	PLScopeBasedLog::sharedLog()->endScope();
	// . ~~~~

	// Remove finished connection

	theConnections->update();

	// . ~~~~
	PLScopeBasedLog::sharedLog()->print("Updated connections list");
	PLScopeBasedLog::sharedLog()->endLine();
	// . ~~~~

	if (theConnections->size() == 0)
	{
		if (inGrowPoint->rootReflection->edgesOut()->size() == 0)
		{
			if (*(*inGrowPoint->defaultConnection)->iteratorOut() ==
					*this->finalStateGraphIterator())
			{
				theGrowPointResult->updateStatus = PLCharacterReflectorFinal;
			}
			else
			{
				theGrowPointResult->updateStatus = PLCharacterReflectorFailed;
			}
		}
		else
		{
			theGrowPointResult->updateStatus = PLCharacterReflectorFinished;
		}

//		if (inGrowPoint->defaultConnection != NULL)
//		{
//			// . ~~~~
//			PLScopeBasedLog::sharedLog()->print("Grow point wasn't activated");
//			// . ~~~~
//
//			if (*(*inGrowPoint->defaultConnection)->iteratorOut() ==
//					*this->failedStateGraphIterator())
//			{
//				PLScopeBasedLog::sharedLog()->print(" and it was failed");
//				theGrowPointResult->updateStatus = PLCharacterReflectorFailed;
//			}
//			else if (*(*inGrowPoint->defaultConnection)->iteratorOut() ==
//					*this->finalStateGraphIterator())
//			{
//				PLScopeBasedLog::sharedLog()->print(" and it is final");
//				theGrowPointResult->updateStatus =
//						PLCharacterReflectorFinal;
//
//			}
//
//			// . ~~~~
//			PLScopeBasedLog::sharedLog()->endLine();
//			// . ~~~~
//		}
//		else
//		{
//			theGrowPointResult->updateStatus = PLCharacterReflectorFinished;
//		}
	}

	// . ~~~~
	PLScopeBasedLog::sharedLog()->endScope();
	// . ~~~~

	// Return the finished nodes
	return theGrowPointResult;
}

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
PLCharacterReflectorUpdatingResult *PLCharacterStreamReflector::
		updateWithSymbol(PLCharacter inCharacter)
{
	return updateForRootIteratorWithSymbol(NULL, inCharacter);
}

///////////////////////////////////////////////////////////////////////////////
PLCharacterStreamReflectorMark *PLCharacterStreamReflector::initialStateMark()
{
	if (NULL == _initialStateMark)
	{
		// Create mark and set it's value. Connect as default with final node
		_stateGraphRoot = PLStateGraph::sharedGraph()->
				createNodeWithValue(PLStateGraphNodeMarkerInitial);

		_stateGraphRoot->connectToNode(this->finalStateGraphIterator(), NULL);

		// Create the mark
		_initialStateMark =
				new PLCharacterStreamReflectorMark(_stateGraphRoot);

		//std::cout << "!!!!! BEGIN: " << _graph.begin()->_node << std::endl;
	}

	return _initialStateMark;
}

///////////////////////////////////////////////////////////////////////////////
PLCharacterStreamReflector::PLStateGraph::node_iterator
		*PLCharacterStreamReflector::failedStateGraphIterator()
{
	// TODO: CORRECT THIS CREATERIAS!!! THE FAILED CREATERIA MAY BE
	// "THERE IS NO BRANCHES BEFORE FINISH"
	if (NULL == __failedStateIterator)
	{
		__failedStateIterator = PLStateGraph::sharedGraph()->
				createNodeWithValue(PLStateGraphNodeMarkerFailed);

		//std::cout << "!!!!! FAILED: " << __failedStateIterator->_node <<
		//				std::endl;
	}

	return __failedStateIterator;
}

PLCharacterStreamReflector::PLStateGraph::node_iterator
		*PLCharacterStreamReflector::finalStateGraphIterator()
{
	if (NULL == __finalStateIterator)
	{
		__finalStateIterator =  PLStateGraph::sharedGraph()->
				createNodeWithValue(PLStateGraphNodeMarkerFinal);

		//std::cout << "!!!!! FINAL: " << __finalStateIterator->_node <<
		//		std::endl;
	}

	return __finalStateIterator;
}

///////////////////////////////////////////////////////////////////////////////
/*
bool PLCharacterStreamReflector::isGrowPointFailed(PLGrowPoint *inGrowPoint)
{
	return (inGrowPoint->connections->size() == 0) &&
			(inGrowPoint->defaultConnection != PLStateGraph::nullEdge()) &&
			(*(*inGrowPoint->defaultConnection)->iteratorOut() ==
					*this->failedStateGraphIterator());
}

bool PLCharacterStreamReflector::isGrowPointFinal(PLGrowPoint *inGrowPoint)
{
	return (inGrowPoint->connections->size() == 0) &&
			(inGrowPoint->defaultConnection != PLStateGraph::nullEdge()) &&
			(*(*inGrowPoint->defaultConnection)->iteratorOut() ==
					*this->finalStateGraphIterator());
}

bool PLCharacterStreamReflector::isGrowPointFinished(PLGrowPoint *inGrowPoint)
{
	return (inGrowPoint->connections->size() == 0) &&
			(inGrowPoint->defaultConnection == PLStateGraph::nullEdge());
}
*/
///////////////////////////////////////////////////////////////////////////////
PLString *PLCharacterStreamReflector::description()
{
	return new PLString("PLCharacterStreamReflector");
}
