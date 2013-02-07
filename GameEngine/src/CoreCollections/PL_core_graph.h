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
#include <list>
#include <map>
#include <iostream>
#include <fstream>

#include "../Base/Memory/PLAutoPointer.h"

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


private:


	// **************************************************************
	// *					 Private _ Types						*
	// **************************************************************


	// -------------------
	// *** Structure

	// Edge
	struct _node;

	struct _edge
	{
		typename PL_core_graph<NodeItemType, EdgeItemType>::node_iterator
				_nodeIn;
		typename PL_core_graph<NodeItemType, EdgeItemType>::node_iterator
				_nodeOut;

		EdgeItemType _value;
		PL_core_graph<NodeItemType, EdgeItemType> *_graph;

		// *** Memory management
		_edge(const typename PL_core_graph<NodeItemType, EdgeItemType>::
						node_iterator &inNodeIn,
				const typename PL_core_graph<NodeItemType, EdgeItemType>::
						node_iterator &inNodeOut, const EdgeItemType &inValue,
				PL_core_graph<NodeItemType, EdgeItemType> *inGraph)
		{
			_nodeIn = inNodeIn;
			_nodeOut = inNodeOut;

			_value = inValue;
			_graph = inGraph;
		}
	} typedef edge;
	typedef std::list<edge *> edgesList;
	typedef typename edgesList::iterator inner_edge_iterator;

	// Node
	struct _node
	{
		NodeItemType _value;

		edgesList _edgesOut;
		edgesList _edgesIn;

		_node(const NodeItemType &inValue)
		{
			_value = inValue;
		}
	} typedef node;
	typedef std::list<node> nodesList;
	typedef typename nodesList::iterator inner_node_iterator;

	// **************************************************************
	// *					 Private _ Variables					*
	// **************************************************************

	// ---------------
	// *** Graph nodes
	nodesList _nodes;

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
		_nodes.push_back(node(inValue));

		return node_iterator(this, --_nodes.end());
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
		edge *theEdge = new edge(inNodeIteratorIn, inNodeIteratorOut,
				inEdgeItem, this);

		inNodeIteratorIn._nodeIterator->_edgesOut.push_back(theEdge);
		inNodeIteratorOut._nodeIterator->_edgesIn.push_back(theEdge);

		return edge_iterator(this,
				--inNodeIteratorIn._nodeIterator->_edgesOut.end());
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
				this->excludeNodeFromGraph(theTemporaryIterator);

				std::cout << theIterator->edgesIn()->size() << " : "
						<< theIterator->edgesOut()->size() << std::endl;
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
		theStream << _nodes.size() << std::endl;

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
			PL_core_graph<NodeItemType, EdgeItemType> *inGraph,
			const typename PL_core_graph<NodeItemType, EdgeItemType>::
					inner_edge_iterator &inEdgeIterator)
	{
		_graph = inGraph;
		_edgeIterator = inEdgeIterator;
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
	PL_core_graph<NodeItemType, EdgeItemType> *_graph;
	typename PL_core_graph<NodeItemType, EdgeItemType>::inner_node_iterator
			_nodeIterator;

public:


	// **************************************************************
	// *					Public _ Methods						*
	// **************************************************************

	// ---------------------
	// *** Memory management
	PL_core_graph_node_iterator(
			PL_core_graph<NodeItemType, EdgeItemType> *inGraph,
			const typename PL_core_graph<NodeItemType, EdgeItemType>::
					inner_node_iterator &inNodeIterator)
	{
		_graph = inGraph;
		_nodeIterator = inNodeIterator;
	}

	PL_core_graph_node_iterator(
			const PL_core_graph_node_iterator<NodeItemType, EdgeItemType>
					&inNodeIterator)
	{
		_graph = inNodeIterator._graph;
		_nodeIterator = inNodeIterator._nodeIterator;
	}

	PL_core_graph_node_iterator()
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
				edge_iterator(_graph, _nodeIterator->_edgesOut.begin());
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
				edge_iterator(_graph, _nodeIterator->_edgesOut.end());
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
			createNextNodeWithValue(const NodeItemType &inValue,
					const EdgeItemType &inEdgeItem)
	{
		typename PL_core_graph<NodeItemType, EdgeItemType>::node_iterator
				theIterator = _graph->createNodeWithValue(inValue);
		connectToNode(theIterator, inEdgeItem);

		return theIterator;
	}

	typename PL_core_graph<NodeItemType, EdgeItemType>::edge_iterator
			connectToNode(typename PL_core_graph<NodeItemType, EdgeItemType>::
					node_iterator &inIterator, const EdgeItemType &inEdgeItem)
	{
		return _graph->createEdge(*this, inIterator, inEdgeItem);
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
