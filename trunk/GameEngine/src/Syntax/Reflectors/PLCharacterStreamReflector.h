///////////////////////////////////////////////////////////////////////////////
#ifndef PLCHARSTREAMREFLECTOR_H_
#define PLCHARSTREAMREFLECTOR_H_

///////////////////////////////////////////////////////////////////////////////
#include "../../Base/PLCore.h"

#include <list>
#include <map>
#include <set>

#include "../../CoreCollections/PL_core_graph.h"
#include "../../CoreCollections/PL_core_pool.h"
#include "../../CoreCollections/PL_core_list.h"

#include "IPLCharacterReflector.h"

///////////////////////////////////////////////////////////////////////////////
class PLReflection;
class PLCharacterSet;
class PLCharacterClassifier;
class PLCharacterStreamReflectorMark;

////////////////////////////////////////////`//////////////////////////////////
class PLCharacterStreamReflector : public IPLCharacterReflector
{
private:


	// **************************************************************
	// *					Private _ Types							*
	// **************************************************************

	// ---------------------------
	// *** State graph description
	enum
	{
		PLStateGraphNodeMarkerDefault,
		PLStateGraphNodeMarkerInitial,
		PLStateGraphNodeMarkerFailed,
		PLStateGraphNodeMarkerFinal
	} typedef PLStateGraphNodeMarker;

	typedef PL_core_graph<PLStateGraphNodeMarker, IPLCharacterReflector *>
			PLStateGraph;

	// -------------------
	// *** Result building

	// * Types building one branch of reflections
	typedef PL_core_list<PLStateGraph::edge_iterator>
			PLReflectorConnectionGroup;

	struct
	{
		PLReflectorConnectionGroup *connections;
		PLStateGraph::edge_iterator defaultConnection;

		PLReflectionTree::node_iterator *defferedReflection;

		PLReflectionTree::node_iterator *rootReflection;
	} typedef PLGrowPoint;

	typedef PL_core_list<PLGrowPoint *> PLBuildingFront;

	struct
	{
		PLReflectorUpdateStatus updateStatus;
		PLBuildingFront *branches;
	} typedef PLGrowPointUpdatingResults;

	// * Types for updating tree
	//
	// root1         _
	//   \_______     |_ PLReflectionGraphBuildersGroup .
	//    \_______   _|
	//
	// root2         _
	//   \_______     |_ PLReflectionGraphBuildersGroup .
	//    \_______   _|
	struct
	{
		PLReflectionTree::node_iterator *root;
		PLBuildingFront *buildingFront;
	} typedef PLReflectionTreeBuilder;

	// * Types all updating trees
	typedef map<PLReflectionTree::node_iterator *, PLReflectionTreeBuilder *>
			PLReflectionTreeBuilders;


	// **************************************************************
	// *					Private _ Variables						*
	// **************************************************************

	// ---------------
	// *** State graph
	PLStateGraph::node_iterator *_stateGraphRoot;

	// ----------------
	// *** Result graph
	PLReflectionTreeBuilders _resultBuilders;

	// ---------
	// *** Marks
	PLCharacterStreamReflectorMark *_initialStateMark;

	// **************************************************************
	// *					Private _ Methods						*
	// **************************************************************

	// ---------------------
	// *** Conditional graph
	PLGrowPoint *createGrowPoint(PLReflectionTree::node_iterator *inIterator,
			PLStateGraph::node_iterator *inStaticNode);
	PLGrowPointUpdatingResults *updateGrowPoint(PLGrowPoint *inGrowPoint,
			char inSymbol);

	// ---------------------
	// *** Conditional graph
	void connectStateWithMarks(PLCharacterStreamReflectorMark *inBeginMark,
			PLCharacterStreamReflectorMark **inoutFinishedMark,
			IPLCharacterReflector *inCondition);

	// -------------------------------------
	// *** Result building utility functions
	PLReflectionTreeBuilder *builderForRootIterator(
			PLReflectionTree::node_iterator *inIterator);

	// -----------------
	// *** Final testing
	PLStateGraph::node_iterator *__finalStateIterator;
	PLStateGraph::node_iterator *__failedStateIterator;

	PLStateGraph::node_iterator *finalStateGraphIterator();
	PLStateGraph::node_iterator *failedStateGraphIterator();

	bool isNodeFinal(PLStateGraph::node_iterator *inNode);

	/*
	bool isGrowPointFailed(PLGrowPoint *inGrowPoint);
	bool isGrowPointFinished(PLGrowPoint *inGrowPoint);
	bool isGrowPointFinal(PLGrowPoint *inGrowPoint);
	*/

public:


	// **************************************************************
	// *					Public _ Methods						*
	// **************************************************************

	// ---------------------
	// *** Memory management
	PLCharacterStreamReflector();
	virtual ~PLCharacterStreamReflector();

	// ------------------
	// *** Graph building
	void makeEmptyBranch(PLCharacterStreamReflectorMark *inBeginMark,
			PLCharacterStreamReflectorMark **inoutFinishedMark);

	void makeBranchWithSet(
			PLCharacterStreamReflectorMark *inBeginMark,
			PLCharacterStreamReflectorMark **inoutFinishedMark,
			PLCharacterSet *inSet, PLReflection *inReflection);

	void makeBranchWithString(PLCharacterStreamReflectorMark *inBeginMark,
			PLCharacterStreamReflectorMark **inoutFinishedMark,
			PLString *inString);

	void makeBranchWithSubreflection(
			PLCharacterStreamReflectorMark *inBeginMark,
			PLCharacterStreamReflectorMark **inoutFinishedMark,
			PLCharacterStreamReflector *subreflection,
			PLReflection *inReflection);

	// ------------------
	// *** Markers getters
	PLCharacterStreamReflectorMark *initialStateMark();

	// ----------------------------------------------------
	// *** Updating [IMPLEMENTATION: IPLCharacterReflector]
	virtual PLCharacterReflectorUpdatingResult *updateForRootIteratorWithSymbol(
			PLReflectionTree::node_iterator *inIterator,
					PLCharacter inCharacter);

	virtual PLCharacterReflectorUpdatingResult *updateWithSymbol(
			PLCharacter inCharacter);

	// ---------------------------------------
	// *** Updating [IMPLEMENTATION: PLObject]
	virtual PLString *description();


	// **************************************************************
	// *					Public _ Friends						*
	// **************************************************************

	friend class PLCharacterStreamReflectorMark;
};

///////////////////////////////////////////////////////////////////////////////
class PLCharacterStreamReflectorMark
{
private:
	PLCharacterStreamReflector::PLStateGraph::node_iterator *_iterator;

	PLCharacterStreamReflectorMark(
			PLCharacterStreamReflector::PLStateGraph::node_iterator
					*inIterator)
	{
		_iterator = inIterator;
	}

	PLCharacterStreamReflector::PLStateGraph::node_iterator *&operator *(void)
	{
		return _iterator;
	}

	// Friends
	friend class PLCharacterStreamReflector;

public:
	PLCharacterStreamReflectorMark()
	{
		_iterator = NULL;
	}
};

///////////////////////////////////////////////////////////////////////////////
#endif /* PLCHARSTREAMREFLECTOR_H_ */
