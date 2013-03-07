/*
 * PLReflectionTree.h
 *
 *  Created on: 20.10.2012
 *      Author: Сергей
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef PLREFLECTIONTREE_H_
#define PLREFLECTIONTREE_H_

///////////////////////////////////////////////////////////////////////////////
// Utilities
#include <list>
#include <map>

#include "PL_core_fastStack.h"

// Streams
#include <iostream>
#include <fstream>

// PLCore
#include "../Base/PLString.h"

///////////////////////////////////////////////////////////////////////////////
template <typename NodeItemType, typename EdgeItemType>
		class PL_core_graph_edge_iterator;

template <typename NodeItemType, typename EdgeItemType>
		class PL_core_graph_node_iterator;

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// >>> GRAPH
///////////////////////////////////////////////////////////////////////////////
template <typename NodeItemType, typename EdgeItemType>
class PL_core_graph
{

public:


	// **************************************************************
	// *					 Public _ Types							*
	// **************************************************************
	typedef PL_core_graph_edge_iterator<NodeItemType, EdgeItemType>
			edge_iterator;

	typedef PL_core_graph_node_iterator<NodeItemType, EdgeItemType>
			node_iterator;


public:


	// **************************************************************
	// *					 Private _ Types						*
	// **************************************************************


	// -------------------
	// *** Structure

	struct _edge;

	// Node
	struct _node
	{
		NodeItemType _value;

		std::list<_edge *> _edgesOut;
		std::list<_edge *> _edgesIn;

		_node(const NodeItemType &inValue)
		{
			_value = inValue;
		}
	} typedef node;
	typedef std::list<node> nodesList;
	typedef typename nodesList::iterator inner_node_iterator;

	// Edge
	struct _edge
	{
		node_iterator _nodeIn;
		node_iterator _nodeOut;

		EdgeItemType _value;
		PL_core_graph<NodeItemType, EdgeItemType> *_graph;

		// *** Memory management
		_edge(const typename PL_core_graph<NodeItemType, EdgeItemType>::
						inner_node_iterator &inNodeIn,
				const typename PL_core_graph<NodeItemType, EdgeItemType>::
						inner_node_iterator &inNodeOut,
						const EdgeItemType &inValue,
				PL_core_graph<NodeItemType, EdgeItemType> *inGraph)
			: _nodeIn(inNodeIn, inGraph), _nodeOut(inNodeOut, inGraph),
			  _value(inValue), _graph(inGraph)
		{
		}
	} typedef edge;
	typedef std::list<edge *> edgesList;
	typedef typename edgesList::iterator inner_edge_iterator;

	// **************************************************************
	// *					 Private _ Variables					*
	// **************************************************************

	// ---------------
	// *** Graph nodes
	nodesList _nodes;


	// **************************************************************
	// *					Private _ Methods						*
	// **************************************************************
	inner_node_iterator _createNodeWithValue(const NodeItemType &inValue)
	{
		_nodes.push_back(node(inValue));
		return --_nodes.end();
	}

	inner_edge_iterator _createEdge(
			const inner_node_iterator &inNodeIteratorIn,
			const inner_node_iterator &inNodeIteratorOut,
			const EdgeItemType &inEdgeItem)
	{
		edge *theEdge = new edge(inNodeIteratorIn, inNodeIteratorOut,
				inEdgeItem, this);

		inNodeIteratorIn->_edgesOut.push_back(theEdge);
		inNodeIteratorOut->_edgesIn.push_back(theEdge);

		return --inNodeIteratorIn->_edgesOut.end();
	}

public:


	// **************************************************************
	// *					Public _ Methods						*
	// **************************************************************

	// ---------------------
	// *** Memory management
	PL_core_graph()
		: _nodes()
	{
	}

	virtual ~PL_core_graph()
	{
		// TODO: To do
	}

	// -------------
	// *** Iterators
	static edge_iterator nullEdge()
	{
		return NULL;
	}

	// ------------------
	// *** Node lifecicle
	node_iterator createNodeWithValue(const NodeItemType &inValue)
	{
		return node_iterator(_createNodeWithValue(inValue), this);
	}

	// Returns iterator for beginning node
	void removeNode(node_iterator &inNodeIterator)
	{
		size_t theEdgesCount = inNodeIterator->edgesOut.size();

		// Remove edges in
		for (theEdgesCount = inNodeIterator->edgesIn()->size();
				theEdgesCount > 0; --theEdgesCount)
		{
			edge_iterator theIterator = inNodeIterator->edgesIn()->begin();
			inNodeIterator->removeEdgeIn(theIterator);
		}

		// Make iterator null
		_nodes.erase(inNodeIterator);
		inNodeIterator->_graph = NULL;
	}

	// ------------------
	// *** Edge lifecicle
	edge_iterator createEdge(const node_iterator &inNodeIteratorIn,
			const node_iterator &inNodeIteratorOut,
					const EdgeItemType &inEdgeItem)
	{
		return edge_iterator(this,
				_createEdge(inNodeIteratorIn, inNodeIteratorOut, inEdgeItem));
	}

	void removeEdge(const edge_iterator &inEdgeIterator)
	{
		// Remove edge's input connection
		node_iterator &theTemporaryIterator = (*inEdgeIterator)->iteratorIn();
		theTemporaryIterator->edgesOut().erase(theTemporaryIterator);

		// Remove edge's output connection
		theTemporaryIterator = (*inEdgeIterator)->iteratorOut();
		theTemporaryIterator->edgesIn().erase(theTemporaryIterator);

		// Free edge's memory
		delete (*inEdgeIterator);
	}

	///////////////////////////////////////////////////////////////////////////
	void removeBranch(node_iterator *inNodeIterator)
	{
		node_iterator *theIterator = new node_iterator(inNodeIterator);
		node_iterator *theTemporaryIterator = NULL;

		if ((theIterator->_node->edgesIn.size() == 1) &&
				(theIterator->_node->edgesOut.size() == 0))
		{
			do
			{
				theTemporaryIterator = new node_iterator(theIterator);
				theIterator->moveToPreviousNode(
						theIterator->edgesIn()->begin());
				//this->excludeNodeFromGraph(theTemporaryIterator);
			} while (theIterator->edgesIn()->size() != 0 &&
					theIterator->edgesOut()->size() == 0);
		}
	}

	///////////////////////////////////////////////////////////////////////////
	void writeToFile(char *inFileName)
	{
		std::ofstream theStream(inFileName);

		std::map<node *, int> adressToNumberMap;

		node *theGlobalNode = NULL;
		node *theLocalNode = NULL;

		inner_edge_iterator theEdgeIterator;

		// Create nodes addresses to indexes map
		//theStream << _nodes.size() << std::endl;

		int theIndex = 0;
		for (inner_node_iterator theIterator = _nodes.begin();
				theIterator != _nodes.end(); ++theIterator)
		{
			adressToNumberMap[&(*theIterator)] = theIndex;
			++theIndex;
		}

		// Create edges explain
		for (inner_node_iterator theIterator = _nodes.begin();
				theIterator != _nodes.end(); ++theIterator)
		{
			theGlobalNode = &(*theIterator);

			// Print edges in
			theStream << "IN:";

			for (theEdgeIterator = theGlobalNode->_edgesIn.begin();
					theEdgeIterator != theGlobalNode->_edgesIn.end();
					++theEdgeIterator)
			{
				theLocalNode = &(*(*theEdgeIterator)->_nodeIn._nodeIterator);
				theStream << adressToNumberMap[theLocalNode] << " ";
			}

			theStream << std::endl;

			// Print edges out
			theStream << "OUT:";

			for (theEdgeIterator = theGlobalNode->_edgesOut.begin();
					theEdgeIterator != theGlobalNode->_edgesOut.end();
					++theEdgeIterator)
			{
				theLocalNode = &(*(*theEdgeIterator)->_nodeOut._nodeIterator);
				theStream << adressToNumberMap[theLocalNode] << " ";
			}

			theStream << std::endl;
		}

		theStream.close();
	}

	// **************************************************************
	// *					Static methods							*
	// **************************************************************
	static PL_core_graph<NodeItemType, EdgeItemType> *sharedGraph()
	{
		static PL_core_graph<NodeItemType, EdgeItemType> *sGraph = NULL;
		if (NULL == sGraph)
		{
			sGraph = new PL_core_graph<NodeItemType, EdgeItemType>();
		}

		return sGraph;
	}

	// **************************************************************
	// *					Public _ Friends						*
	// **************************************************************
	template<typename _NodeItemType, typename _EdgeItemType> friend class
			PL_core_graph_edge_iterator;

	template<typename _NodeItemType, typename _EdgeItemType> friend class
			PL_core_graph_node_iterator;

	template<typename _NodeItemType, typename _EdgeItemType> friend class
			PL_core_graph_builder;
};

///////////////////////////////////////////////////////////////////////////////
template <typename NodeItemType, typename EdgeItemType>
class PL_core_graph_edge_iterator
{
private:
	PL_core_graph<NodeItemType, EdgeItemType> *_graph;

	typename PL_core_graph<NodeItemType, EdgeItemType>::inner_edge_iterator
			_edgeIterator;

public:

	// *** Memory management
	PL_core_graph_edge_iterator(
			const typename PL_core_graph<NodeItemType, EdgeItemType>::
					inner_edge_iterator &inEdgeIterator,
			PL_core_graph<NodeItemType, EdgeItemType> *inGraph)
		: _graph(inGraph), _edgeIterator(inEdgeIterator)
	{
	}

	// *** Value getter
	const EdgeItemType &getValue() const
	{
		return (*_edgeIterator)->_value;
	}

	// *** Iteration getters
	typename PL_core_graph<NodeItemType, EdgeItemType>::node_iterator
			&iteratorIn() const
	{
		return (*_edgeIterator)->_nodeIn;
	}

	typename PL_core_graph<NodeItemType, EdgeItemType>::node_iterator
			&iteratorOut() const
	{
		return (*_edgeIterator)->_nodeOut;
	}

	// -------------
	// *** Operators
	EdgeItemType &operator *()
	{
		return (*_edgeIterator)->_value;
	}

	EdgeItemType *operator ->()
	{
		return &(*_edgeIterator)->_value;
	}

	void operator ++()
	{
		++_edgeIterator;
	}

	bool operator ==(const PL_core_graph_edge_iterator &inIterator)
	{
		return _edgeIterator == inIterator._edgeIterator;
	}

	bool operator !=(const PL_core_graph_edge_iterator &inIterator)
	{
		return _edgeIterator != inIterator._edgeIterator;
	}
};

///////////////////////////////////////////////////////////////////////////////
template <typename NodeItemType, typename EdgeItemType>
class PL_core_graph_node_iterator
{

private:

	class buildingState
	{
	private:
		PL_core_graph<NodeItemType, EdgeItemType> *_graph;

		PL_core_fastStack<typename PL_core_graph<NodeItemType, EdgeItemType>::
				inner_node_iterator> _buildingStack;
		std::map<PLString,
				typename PL_core_graph<NodeItemType, EdgeItemType>::
						inner_node_iterator> _savedLables;

	public:

		buildingState(PL_core_graph<NodeItemType, EdgeItemType> *inGraph)
		{
			_graph = inGraph;
		}

		//
		void pushToBuildingStack(
				typename PL_core_graph<NodeItemType, EdgeItemType>::
						inner_node_iterator inIterator)
		{
			_buildingStack.push(inIterator);
		}

		typename PL_core_graph<NodeItemType, EdgeItemType>::inner_node_iterator
				popFromBuildingStack()
		{
			if (0 != _buildingStack.size())
			{
				return _buildingStack.pop();
			}

			// TODO: Throw an exception here. Return null node constant
			return typename PL_core_graph<NodeItemType, EdgeItemType>::
					inner_node_iterator();
		}

		//
		void saveNodeByLable(PLString &inLable,
				typename PL_core_graph<NodeItemType, EdgeItemType>::
						inner_node_iterator inIterator)
		{
			_savedLables[inLable] = inIterator;
		}

		typename PL_core_graph<NodeItemType, EdgeItemType>::
				inner_node_iterator getNodeByLable(PLString &inLable)
		{
			return _savedLables[inLable];
		}

	};

	///////////////////////////////////////////////////////////////////////////
	buildingState _buildingState;
	PL_core_graph<NodeItemType, EdgeItemType> *_graph;

	typename PL_core_graph<NodeItemType, EdgeItemType>::inner_node_iterator
			_nodeIterator;

	///////////////////////////////////////////////////////////////////////////

public:


	// **************************************************************
	// *					Public _ Methods						*
	// **************************************************************

	// ---------------------
	// *** Memory management
	PL_core_graph_node_iterator(
			const typename PL_core_graph<NodeItemType, EdgeItemType>::
					inner_node_iterator &inNodeIterator,
			PL_core_graph<NodeItemType, EdgeItemType> *inGraph)
		: _buildingState(inGraph), _graph(inGraph),
		  _nodeIterator(inNodeIterator)
	{
	}

	PL_core_graph_node_iterator(
			const PL_core_graph_node_iterator<NodeItemType, EdgeItemType>
					&inNodeIterator)
		: _buildingState(inNodeIterator._graph),
		  _graph(inNodeIterator._graph),
		  _nodeIterator(inNodeIterator._nodeIterator)
	{
	}

	PL_core_graph_node_iterator()
		: _buildingState(NULL), _graph(NULL), _nodeIterator(NULL)
	{
		_graph = NULL;
	}

	virtual ~PL_core_graph_node_iterator()
	{
	}

	///////////////////////////////////////////////////////////////////////////
	typename PL_core_graph<NodeItemType, EdgeItemType>::edge_iterator
			beginOutEdge() const
	{
		return typename PL_core_graph<NodeItemType, EdgeItemType>::
				edge_iterator(_nodeIterator->_edgesOut.begin(), _graph);
	}

	void moveThroughOutEdge(
			const typename PL_core_graph<NodeItemType, EdgeItemType>::
					edge_iterator &inEdge)
	{
		_nodeIterator = inEdge.nodeOut;
	}

	void removeOutEdge(
			typename PL_core_graph<NodeItemType, EdgeItemType>::
					edge_iterator &inEdge)
	{
		_graph->removeEdge(inEdge);
	}

	typename PL_core_graph<NodeItemType, EdgeItemType>::edge_iterator
			endOutEdge() const
	{
		return typename PL_core_graph<NodeItemType, EdgeItemType>::
				edge_iterator(_nodeIterator->_edgesOut.end(), _graph);
	}

	///////////////////////////////////////////////////////////////////////////
	typename PL_core_graph<NodeItemType, EdgeItemType>::node_iterator
			&createNodeOut(NodeItemType &inNodeItem,
					EdgeItemType &inEdgeItem)
	{
		typename PL_core_graph<NodeItemType, EdgeItemType>::node_iterator
				theCreatedNodeIterator =
						_graph->createNodeWithValue(inNodeItem);
		_graph->createEdge(*this, theCreatedNodeIterator, inEdgeItem);
		return theCreatedNodeIterator;
	}

	///////////////////////////////////////////////////////////////////////////
	typename PL_core_graph<NodeItemType, EdgeItemType>::node_iterator
			&beginBrunch()
	{
		_buildingState.pushToBuildingStack(_nodeIterator);
		return *this;
	}

	typename PL_core_graph<NodeItemType, EdgeItemType>::node_iterator
			&createNodeWithValue(const NodeItemType &inValue,
					const EdgeItemType &inEdgeItem)
	{
		typename PL_core_graph<NodeItemType, EdgeItemType>::inner_node_iterator
				theIterator = _graph->_createNodeWithValue(inValue);
		_graph->_createEdge(_nodeIterator, theIterator, inEdgeItem);

		_nodeIterator = theIterator;

		return *this;
	}

	typename PL_core_graph<NodeItemType, EdgeItemType>::node_iterator
			&saveNodeByLable(PLString &inString)
	{
		_buildingState.saveNodeByLable(inString, _nodeIterator);
		return *this;
	}

	typename PL_core_graph<NodeItemType, EdgeItemType>::node_iterator
			&connectToNode(PLString &inString, const EdgeItemType &inEdgeItem)
	{
		_graph->_createEdge(_nodeIterator,
				_buildingState.getNodeByLable(inString), inEdgeItem);
		return *this;
	}

	typename PL_core_graph<NodeItemType, EdgeItemType>::node_iterator
			&endBrunch()
	{
		_nodeIterator = _buildingState.popFromBuildingStack();
		return *this;
	}

	///////////////////////////////////////////////////////////////////////////
	void removeCurrentBranch()
	{
		_graph->removeBranch(this);
	}

	///////////////////////////////////////////////////////////////////////////
	NodeItemType &operator *()
	{
		return _nodeIterator->_value;
	}

	NodeItemType *operator ->()
	{
		return &_nodeIterator->_value;
	}

	bool operator ==(
			const typename PL_core_graph<NodeItemType, EdgeItemType>::
					node_iterator &inIterator)
	{
		return _nodeIterator == inIterator._nodeIterator;
	}

	///////////////////////////////////////////////////////////////////////////
	PL_core_graph<NodeItemType, EdgeItemType> *graph()
	{
		return _graph;
	}

	// **************************************************************
	// *					Public _ Friends						*
	// **************************************************************
	template<typename _NodeItemType, typename _EdgeItemType> friend class
			PL_core_graph;
};

#endif /* PLREFLECTIONTREE_H_ */
