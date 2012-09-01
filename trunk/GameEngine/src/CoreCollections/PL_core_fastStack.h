///////////////////////////////////////////////////////////////////////////////
#ifndef PL_CORE_FASTSTACK_H_
#define PL_CORE_FASTSTACK_H_

///////////////////////////////////////////////////////////////////////////////
#include <list>

///////////////////////////////////////////////////////////////////////////////
template <typename ItemType>
class PL_core_fastStack {
private:
	std::list<ItemType > list;

///////////////////////////////////////////////////////////////////////////////
public:
	PL_core_fastStack() { }
	virtual ~PL_core_fastStack() { }

	// Content management
	void push(const ItemType &inElement)
	{
		list.push_back(inElement);
	}

	ItemType pop()
	{
		ItemType theElement = *list.end();
		list.pop_back();

		return theElement;
	}

	// Getters
	int size()
	{
		return list.size();
	}
};

#endif /* PL_CORE_FASTSTACK_H_ */
