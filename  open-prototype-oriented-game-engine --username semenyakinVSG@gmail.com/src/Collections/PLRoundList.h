#ifndef PLROUNDLIST_H_
#define PLROUNDLIST_H_

#include "../Base/PLAutoPointer.h"
template<typename ElementType> class PLIterator;

////////////////////////////////////////////////////////////////////////////////
template <typename AnyType> class PLRoundList;

template <typename ItemType>
class PLRoundList< ref<ItemType> > {
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
	PLIterator< ref<ItemType> > begin()
	{
		PLIterator< ref<ItemType> > theIterator(first);
		return theIterator;
	}

	///////////////////////////////////////////////////////////////////////////////
	// *** Content management ***
	///////////////////////////////////////////////////////////////////////////////
	void push_back(ref<ItemType> inElement)
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

		theElement->data = inElement;
	}

	void push_front(ref<ItemType> inElement)
	{
		push_back(inElement);
		first = first->prev;
	}

	// friends
	template<typename ElementType> friend class PLIterator;

	// types
	typedef PLIterator< ref<ItemType> > Iterator;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <typename AnyType> class PLIterator;

template <typename ItemType>
class PLIterator< ref<ItemType> >
{
private:
	typename PLRoundList< ref<ItemType> >::ListElement *element;
	typename PLRoundList< ref<ItemType> >::ListElement *loopBeginElement;
	int _loopCount;

public:

	////////////////////////////////////////////////////////////////////////////
	PLIterator(typename PLRoundList< ref<ItemType> >::ListElement *inElement)
	{
		element = inElement;
		loopBeginElement = inElement;
		_loopCount = 0;
	}

	virtual ~PLIterator() {	}

	////////////////////////////////////////////////////////////////////////////
	int loopCount()
	{
		return _loopCount;
	}

	ref<ItemType> next()
	{
		return element->next->data;
	}

	ref<ItemType> prev()
	{
		return element->prev->data;
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

	ref<ItemType> operator *(void)
	{
		return element->data;
	}

	ref<ItemType> *operator ->(void)
	{
		return element->data.rawPointer();
	}
};



#endif /* PLROUNDLIST_H_ */
