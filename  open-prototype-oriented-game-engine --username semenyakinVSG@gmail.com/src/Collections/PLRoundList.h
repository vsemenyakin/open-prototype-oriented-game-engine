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
		PLAutoPointer<ItemType> data;

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

public:

	////////////////////////////////////////////////////////////////////////////
	PLIterator(typename PLRoundList<ElementType>::ListElement *inElement)
	{
		typename PLRoundList<ElementType>::ListElement theElement;
		element = inElement;
	}

	virtual ~PLIterator() {	}

	////////////////////////////////////////////////////////////////////////////
	void operator ++(void)
	{
		element = element->next;
	}

	void operator --(void)
	{
		element = element->prev;
	}

	ElementType *operator ->(void)
	{
		ElementType *theElement = element->data.rawPointer();
		return theElement;
	}

	ElementType &operator *(void)
	{
		return element->data;
	}
};



#endif /* PLROUNDLIST_H_ */
