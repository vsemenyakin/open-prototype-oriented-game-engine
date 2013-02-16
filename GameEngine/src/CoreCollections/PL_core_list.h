///////////////////////////////////////////////////////////////////////////////
#ifndef PL_CORE_LIST_H_
#define PL_CORE_LIST_H_

///////////////////////////////////////////////////////////////////////////////
#include <list>

#include <cstdlib>

////////////////////////////////////////////////////////////////////////////////
template <typename ItemType> class PL_core_list_iterator;

///////////////////////////////////////////////////////////////////////////////
template <typename ItemType>
class PL_core_list
{
private:
	std::list<ItemType> _list;

	std::list<PL_core_list_iterator<ItemType> *> *_removingElements;
	std::list<ItemType> *_addingElements;

public:


	// **************************************************************
	// *					 Public _ Types							*
	// **************************************************************

	// ------------
	// *** Iterator
	typedef PL_core_list_iterator<ItemType> iterator;


	// **************************************************************
	// *					Public _ Methods						*
	// **************************************************************

	// ---------------------
	// *** Memory management
	PL_core_list()
	{
		_removingElements = NULL;
		_addingElements = NULL;
	}

	PL_core_list(PL_core_list *inList)
	{
		_removingElements = NULL;
		_addingElements = NULL;

		this->set(inList);
	}

	virtual ~PL_core_list()
	{
	}

	// ---------------------
	// ***
	iterator begin()
	{
		return iterator(_list.begin());
	}

	iterator end()
	{
		return iterator(_list.end());
	}

	// Content management
	void push_back(const ItemType &inElement)
	{
		_list.push_back(inElement);
	}

	void push_back(PL_core_list<ItemType> *inList)
	{
		if (inList->size() != 0)
		{
			for (PL_core_list_iterator<ItemType> theIterator = inList->begin();
					theIterator != inList->end(); ++theIterator)
			{
				_list.push_back(*theIterator);
			}
		}
	}

	void clear()
	{
		_list.clear();

		if (NULL != _removingElements)
		{
			_removingElements->clear();
		}
	}

	void set(PL_core_list *inCoreList)
	{
		if (inCoreList != NULL)
		{
			this->clear();
			this->push_back(inCoreList);
		}
	}


	void remove(iterator *inIterator)
	{
		_list.erase(inIterator->_iterator);
	}

	// Getters
	int size()
	{
		return _list.size();
	}

	// Deferred operations
	void deferredPushBack(ItemType inElement)
	{
		if (NULL == _addingElements)
		{
			_addingElements = new std::list<ItemType>();
		}

		_addingElements->push_back(inElement);
	}

	void deferredPushBack(PL_core_list<ItemType> *inList)
	{
		if (NULL == _addingElements)
		{
			_addingElements = new std::list<ItemType>();
		}

		for (PL_core_list_iterator<ItemType> theIterator = inList->begin();
				theIterator != inList->end(); ++theIterator)
		{
			_addingElements->push_back(*theIterator);
		}
	}

	void deferredRemove(iterator inIterator)
	{
		if (NULL == _removingElements)
		{
			_removingElements = new std::list<iterator *>();
		}

		_removingElements->push_back(new iterator(inIterator));
	}

	void update()
	{
		// Remove elements
		if (NULL != _removingElements)
		{
			typename std::list<PL_core_list_iterator<ItemType> *>::iterator
					theIterator = _removingElements->begin();
			for (; theIterator != _removingElements->end(); ++theIterator)
			{
				this->remove(*theIterator);
			}

			_removingElements->clear();
		}

		// Add elements
		if (NULL != _addingElements)
		{
			typename std::list<ItemType>::iterator theIterator =
					_addingElements->begin();
			for (; theIterator != _addingElements->end(); ++theIterator)
			{
				this->push_back(*theIterator);
			}

			_addingElements->clear();
		}
	}

	PL_core_list<ItemType> *copy()
	{
		PL_core_list<ItemType> *theList = new PL_core_list();
		theList->_list = _list;

		return theList;
	}
};

///////////////////////////////////////////////////////////////////////////////
// >>> ITERATOR
///////////////////////////////////////////////////////////////////////////////
template <typename ItemType>
class PL_core_list_iterator
{
private:
	typename std::list<ItemType>::iterator _iterator;

public:

	// ---------------------
	// *** Memory management
	PL_core_list_iterator(typename std::list<ItemType>::iterator inIterator)
	{
		_iterator = inIterator;
	}

	// **************************************************************
	// *					Public _ Methods						*
	// **************************************************************

	// ---------------------
	// *** Memory management
	void operator ++()
	{
		++_iterator;
	}

	ItemType &operator *(void)
	{
		return *(this->_iterator);
	}

	ItemType *operator ->(void)
	{
		return &(*(this->_iterator));
	}

	bool operator ==(const PL_core_list_iterator<ItemType> &inIterator) const
	{
		return this->_iterator == inIterator._iterator;
	}

	bool operator !=(const PL_core_list_iterator<ItemType> &inIterator) const
	{
		// return _iterator != inIterator;
		return !(*this == inIterator);
	}

	// **************************************************************
	// *					Public _ Friends						*
	// **************************************************************
	template<typename _ItemType> friend class PL_core_list;
};

#endif /* PL_CORE_LIST_H_ */
