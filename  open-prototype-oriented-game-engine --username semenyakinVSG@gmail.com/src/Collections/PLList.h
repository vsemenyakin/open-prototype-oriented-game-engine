#ifndef PLLIST_H_
#define PLLIST_H_

#include <list>
#include "../Base/PLAutoPointer.h"
#include "../Base/PLObject.h"

////////////////////////////////////////////////////////////////////////////////
template <typename ItemType> class PLList;


template <typename ItemType>
class PLList< ref<ItemType> >  : public PLObject
{

private:

	std::list< ref<ItemType> > list;


public:
	// *** Defines ***


	// *** Memory management ***
	// constructors

	PLList()
	{
		list.clear();
	};

	// destructors

	virtual ~PLList()
	{
	};

	// *** Accessors ***
	//getters

	bool isEmpty()
	{
		return list.empty();
	};

	void push_front( ref<ItemType>  inElement)
	{
		list.push_front(inElement);
	};
	void push_back( ref<ItemType>  inElement ){
		list.push_back(inElement);
	};

	//setters

	void clear()
	{
		list.clear();
	};

	void pop_front()
	{
		list.popFront();
	};

	void pop_back()
	{
		list.popBack();
	};

	//methods

	void sort()
	{
		list.sort();
	};

	//To do
	//begin
	//end
	//merge
	void addObject(PLObject *inObject);
	void destroy();
};

#endif /* PLLIST_H_ */
