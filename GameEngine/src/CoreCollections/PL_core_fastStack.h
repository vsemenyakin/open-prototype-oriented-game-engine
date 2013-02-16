///////////////////////////////////////////////////////////////////////////////
#ifndef PL_CORE_FASTSTACK_H_
#define PL_CORE_FASTSTACK_H_

///////////////////////////////////////////////////////////////////////////////
#include <list>

///////////////////////////////////////////////////////////////////////////////
template <typename ItemType>
class PL_core_fastStack
{
private:
	std::list<ItemType> _list;

///////////////////////////////////////////////////////////////////////////////
public:
	PL_core_fastStack() { }
	virtual ~PL_core_fastStack() { }

	// Content management
	void push(const ItemType &inElement)
	{
		_list.push_back(inElement);
	}

	ItemType pop()
	{
		ItemType theElement = _list.back();
		_list.pop_back();

		return theElement;
	}

	// Getters
	int size()
	{
		return _list.size();
	}
};

#endif /* PL_CORE_FASTSTACK_H_ */
