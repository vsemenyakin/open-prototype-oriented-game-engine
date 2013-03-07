///////////////////////////////////////////////////////////////////////////////
#ifndef PL_CORE_FASTQUEUE_H_
#define PL_CORE_FASTQUEUE_H_

///////////////////////////////////////////////////////////////////////////////
#include <list>

///////////////////////////////////////////////////////////////////////////////
template <typename ItemType>
class PL_core_fastQueue
{
private:
	std::list<ItemType > list;

///////////////////////////////////////////////////////////////////////////////
public:
	PL_core_fastQueue() { }
	virtual ~PL_core_fastQueue() { }

	// Content management
	void push(const ItemType &inElement)
	{
		list.push_back(inElement);
	}

	ItemType pop()
	{
		ItemType theElement = *list.begin();
		list.pop_front();

		return theElement;
	}

	// Getters
	int size()
	{
		return list.size();
	}
};

#endif /* PL_CORE_FASTQUEUE_H_ */
