#ifndef PLROUNDLIST_H_
#define PLROUNDLIST_H_

#include "../Base/PLAutoPointer.h"
template<typename ElementType> class PLIterator;

////////////////////////////////////////////////////////////////////////////////
template <typename ItemType>
class PLRoundList {
private:
public:
	struct ListElement
	{
		ref<ItemType> data;

		ListElement *next;
		ListElement *prev;
	};

	ListElement *first;
public:
	PLRoundList()
	{
		first = NULL;
	}

	virtual ~PLRoundList()
	{
	}

	///////////////////////////////////////////////////////////////////////////////
	// *** Propeties ***
	///////////////////////////////////////////////////////////////////////////////
	PLIterator<ItemType> begin()
	{
		PLIterator<ItemType> theIterator(first);
		return theIterator;
	}

	///////////////////////////////////////////////////////////////////////////////
	// *** Content management ***
	///////////////////////////////////////////////////////////////////////////////
	void push_back(ItemType inElement)
	{
		ListElement *theElement = new ListElement();

		if (NULL == first)
		{
			first = theElement;
			first->next = first;
			first->prev = first;
		}
		else
		{
			// Set pointers of new element
			theElement->next = first;
			theElement->prev = first->prev;

			// Link new element with list
			first->prev->next = theElement;
			first->prev = theElement;
		}

		//theElement->data.setRawPointer(inElement);
	}

	void push_front(ItemType inElement)
	{
		push_back(inElement);
		first = first->prev;
	}

	// friends
	template<typename ElementType> friend class PLIterator;

	// types
	typedef PLIterator<ItemType> Iterator;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <typename ElementType>
class PLIterator
{
private:
	typename PLRoundList<ElementType>::ListElement *element;

	typename PLRoundList<ElementType>::ListElement *loopBeginElement;
	int _loopCount;

public:

	////////////////////////////////////////////////////////////////////////////
	PLIterator(typename PLRoundList<ElementType>::ListElement *inElement)
	{
		element = inElement;
		_loopCount = 0;
	}

	virtual ~PLIterator() {	}

	////////////////////////////////////////////////////////////////////////////
	int loopCount()
	{
		return _loopCount;
	}

	ElementType *next()
	{
		return ~element->next->data;
	}

	ElementType *prev()
	{
		return ~element->prev->data;
	}

	void operator ++(void)
	{
		element = element->next;
		if (element == loopBeginElement)
		{
			++_loopCount;
		}
	}

	void operator --(void)
	{
		element = element->prev;
		if (element == loopBeginElement)
		{
			--_loopCount;
		}
	}

	ElementType *operator ->(void)
	{
		return element->data.rawPointer();
	}

	ElementType &operator *(void)
	{
		return *element->data.rawPointer();
	}
};



#endif /* PLROUNDLIST_H_ */
