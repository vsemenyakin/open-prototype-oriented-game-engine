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

///////////////////////////////////////////////////////////////////////////////
template <typename ItemType, typename EdgeItemType>
		class PL_core_graph_iterator;

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// >>> GRAPH
///////////////////////////////////////////////////////////////////////////////
template <typename ItemType, typename EdgeItemType>
class PL_core_graph
{

public:


	// **************************************************************
	// *					 Public _ Types							*
	// **************************************************************

	// ------------
	// *** Iterator
	typedef PL_core_graph_iterator<ItemType, EdgeItemType> node_iterator;

private:


	// **************************************************************
	// *					 Private _ Types						*
	// **************************************************************


	// -------------------
	// *** Structure

	// Edge
	struct _node;

	struct edge
	{
		PL_core_graph <ItemType, EdgeItemType> *graph;
		EdgeItemType value;

		_node *nodeIn;
		_node *nodeOut;

		typename PL_core_graph<ItemType, EdgeItemType>::node_iterator
				*iteratorIn()
		{
			return new typename PL_core_graph<ItemType, EdgeItemType>::
					node_iterator(graph, nodeIn);
		}

		typename PL_core_graph<ItemType, EdgeItemType>::node_iterator
				*iteratorOut()
		{
			return new typename PL_core_graph<ItemType, EdgeItemType>::
					node_iterator(graph, nodeOut);
		}
	};
	typedef std::list<edge *> edges;

	// Node
	struct _node
	{
		ItemType value;

		edges edgesOut;
		edges edgesIn;
	} typedef node;

	// **************************************************************
	// *					 Private _ Variables					*
	// **************************************************************

	// --------------
	// *** Graph root
	node_iterator *_root;

	std::list<node *> _nodes;

public:

	// **************************************************************
	// *					Public _ Types							*
	// **************************************************************
	typedef typename edges::iterator edge_iterator;


	// **************************************************************
	// *					Public _ Methods						*
	// **************************************************************

	// ---------------------
	// *** Memory management
	PL_core_graph()
		: _root(NULL)
	{
	}

	PL_core_graph(ItemType &inValue)
		: _root(NULL)
	{
		//begin()->setValue(inValue);
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

	// ------------
	// *** Creation
	node_iterator *createNodeWithValue(ItemType inValue)
	{
		node *theNode = new node();
		theNode->value = inValue;

		_nodes.push_back(theNode);

		std::cout << theNode << std::endl;

		return new node_iterator(this, theNode);
	}

	edge_iterator &connectNodes(node_iterator *inNodeIteratorBegin,
			node_iterator *inNodeIteratorEnd, EdgeItemType inEdgeItem)
	{
		// Create edge
		edge *theEdge = new edge();

		theEdge->value = inEdgeItem;

		theEdge->nodeIn = inNodeIteratorBegin->_node;
		theEdge->nodeOut = inNodeIteratorEnd->_node;

		theEdge->graph = this;

		// Create node
		inNodeIteratorBegin->_node->edgesOut.push_back(theEdge);
		inNodeIteratorEnd->_node->edgesIn.push_back(theEdge);

		return --inNodeIteratorBegin->_node->edgesOut.end();
	}

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

	void excludeNodeFromGraph(node_iterator *inNodeIterator)
	{
		size_t theEdgesCount = 0;

		// Remove edges in
		for (theEdgesCount = inNodeIterator->edgesIn()->size();
				theEdgesCount > 0; --theEdgesCount)
		{
			edge_iterator theIterator = inNodeIterator->edgesIn()->begin();
			inNodeIterator->removeEdgeIn(theIterator);
		}

		// Remove edges out
		for (theEdgesCount = inNodeIterator->edgesOut()->size();
				theEdgesCount > 0; --theEdgesCount)
		{
			inNodeIterator->removeEdgeOut(inNodeIterator->edgesOut()->begin());
		}

		// Make iterator null
		_nodes.remove(inNodeIterator->_node);
		inNodeIterator->_node = NULL;
		inNodeIterator->_graph = NULL;
	}


	void writeToFile(char *inFileName)
	{
		std::ofstream theStream(inFileName);

		std::map<node *, int> adressToNumberMap;

		node *theGlobalNode = NULL;
		node *theLocalNode = NULL;

		typename edges::iterator theEdgeIterator;

		// Create nodes addresses to indexes map
		theStream << _nodes.size() << std::endl;

		int theIndex = 0;
		for (typename std::list<node *>::iterator theIterator = _nodes.begin();
				theIterator != _nodes.end(); ++theIterator)
		{
			adressToNumberMap[*theIterator] = theIndex;
			++theIndex;
		}

		// Create edges explain
		for (typename std::list<node *>::iterator theIterator = _nodes.begin();
				theIterator != _nodes.end(); ++theIterator)
		{
			theGlobalNode = *theIterator;

			// Print edges in
			theStream << "IN:";

			for (theEdgeIterator = theGlobalNode->edgesIn.begin();
					theEdgeIterator != theGlobalNode->edgesIn.end();
					++theEdgeIterator)
			{
				theLocalNode = (*theEdgeIterator)->nodeIn;
				theStream << adressToNumberMap[theLocalNode] << " ";
			}

			theStream << std::endl;

			// Print edges out
			theStream << "OUT:";

			for (theEdgeIterator = theGlobalNode->edgesOut.begin();
					theEdgeIterator != theGlobalNode->edgesOut.end();
					++theEdgeIterator)
			{
				theLocalNode = (*theEdgeIterator)->nodeOut;
				theStream << adressToNumberMap[theLocalNode] << " ";
			}

			theStream << std::endl;
		}

		theStream.close();
	}

	// **************************************************************
	// *					Static methods							*
	// **************************************************************
	static PL_core_graph<ItemType, EdgeItemType> *sharedGraph()
	{
		static PL_core_graph<ItemType, EdgeItemType> *sGraph = NULL;
		if (NULL == sGraph)
		{
			sGraph = new PL_core_graph<ItemType, EdgeItemType>();
		}

		return sGraph;
	}

	// **************************************************************
	// *					Public _ Friends						*
	// **************************************************************
	template<typename _ItemType, typename _EdgeItemType> friend class
			PL_core_graph_iterator;

};

///////////////////////////////////////////////////////////////////////////////
template <typename ItemType, typename EdgeItemType>
class PL_core_graph_iterator
{
public:
	PL_core_graph<ItemType, EdgeItemType> *_graph;
	typename PL_core_graph<ItemType, EdgeItemType>::node *_node;

public:

	// **************************************************************
	// *					Public _ Methods						*
	// **************************************************************

	// ---------------------
	// *** Memory management
	PL_core_graph_iterator(PL_core_graph<ItemType, EdgeItemType> *inGraph,
			typename PL_core_graph<ItemType, EdgeItemType>::node *inNode)
	{
		_graph = inGraph;
		_node = inNode;
	}

	PL_core_graph_iterator(typename PL_core_graph<ItemType, EdgeItemType>::
			node_iterator *inIterator)
	{
		_graph = inIterator->_graph;
		_node = inIterator->_node;
	}

	virtual ~PL_core_graph_iterator()
	{
	}

	///////////////////////////////////////////////////////////////////////////
	typename PL_core_graph<ItemType, EdgeItemType>::edges *edgesIn()
	{
		return &_node->edgesIn;
	}

	typename PL_core_graph<ItemType, EdgeItemType>::edge_iterator
			findEdgeFrom(typename PL_core_graph<ItemType, EdgeItemType>::
					node_iterator *inNodeIterator)
	{
		typename PL_core_graph<ItemType, EdgeItemType>::edge_iterator
				theIterator = _node->edgesIn.begin();
		for (; theIterator != _node->edgesIn.end(); ++theIterator)
		{
			if ((*theIterator)->nodeIn == inNodeIterator->_node)
			{
				break;
			}
		}

		return theIterator;
	}

	void moveToPreviousNode(
			const typename PL_core_graph<ItemType, EdgeItemType>::edge_iterator
					&inIterator)
	{
		_node = (*inIterator)->nodeIn;
	}

	void removeEdgeIn(
			typename PL_core_graph<ItemType, EdgeItemType>::edge_iterator
					&inIterator)
	{
		typename PL_core_graph<ItemType, EdgeItemType>::edge *theEdge =
				*inIterator;

		(*inIterator)->nodeIn->edgesOut.remove(*inIterator);
		_node->edgesIn.erase(inIterator);

		delete theEdge;
	}

	///////////////////////////////////////////////////////////////////////////
	typename PL_core_graph<ItemType, EdgeItemType>::edges *edgesOut()
	{
		return &_node->edgesOut;
	}

	typename PL_core_graph<ItemType, EdgeItemType>::edge_iterator findEdgeTo(
			typename PL_core_graph<ItemType, EdgeItemType>::
					node_iterator *inNodeIterator)
	{
		typename PL_core_graph<ItemType, EdgeItemType>::edge_iterator
				theIterator = _node->edgesOut.begin();
		for (; theIterator != _node->edgesOut.end(); ++theIterator)
		{
			if ((*theIterator)->nodeOut == inNodeIterator->_node)
			{
				break;
			}
		}

		return theIterator;
	}

	void moveToNextNode(
			const typename PL_core_graph<ItemType, EdgeItemType>::edge_iterator
					&inIterator)
	{
		_node = (*inIterator)->nodeOut;
	}

	void removeEdgeOut(
			typename PL_core_graph<ItemType, EdgeItemType>::edge_iterator
					inIterator)
	{
		typename PL_core_graph<ItemType, EdgeItemType>::edge *theEdge =
				*inIterator;

		(*inIterator)->nodeOut->edgesIn.remove(*inIterator);
		_node->edgesOut.erase(inIterator);

		delete theEdge;
	}

	///////////////////////////////////////////////////////////////////////////
	typename PL_core_graph<ItemType, EdgeItemType>::node_iterator
			*createNextNodeWithValue(ItemType inValue, EdgeItemType inEdgeItem)
	{
		typename PL_core_graph<ItemType, EdgeItemType>::node_iterator
				*theIterator =
						_graph->createNodeWithValue(inValue);

		_graph->connectNodes(this, theIterator, inEdgeItem);

		return theIterator;
	}

	typename PL_core_graph<ItemType, EdgeItemType>::edge_iterator
			&connectToNode(typename PL_core_graph<ItemType, EdgeItemType>::
					node_iterator *inIterator, EdgeItemType inEdgeItem)
	{
		return _graph->connectNodes(this, inIterator, inEdgeItem);
	}

	///////////////////////////////////////////////////////////////////////////
	void removeCurrentBranch()
	{
		_graph->removeBranch(this);
	}

	///////////////////////////////////////////////////////////////////////////
	ItemType &operator *()
	{
		return _node->value;
	}

	ItemType *operator ->()
	{
		return &_node->value;
	}

	bool operator ==(
			const typename PL_core_graph<ItemType, EdgeItemType>::
					node_iterator &inIterator)
	{
		return _node == inIterator._node;
	}

	// **************************************************************
	// *					Public _ Friends						*
	// **************************************************************
	template<typename _ItemType, typename _EdgeItemType> friend class
			PL_core_graph;
};

#endif /* PLREFLECTIONTREE_H_ */
