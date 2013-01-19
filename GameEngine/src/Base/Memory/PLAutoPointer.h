#ifndef PLAUTOPOINTER_H_
#define PLAUTOPOINTER_H_

///////////////////////////////////////////////////////////////////////////////
#define TRACE_EXPRESSION(expr) std::cout << #expr << " = " << expr << std::endl;

#include <iostream>
///////////////////////////////////////////////////////////////////////////////
//static int debugCounter = 0;

#define ref PLAutoPointer_owning
#define CLASS_WITH_REF(name) \
	class name;	\
	typedef PLAutoPointer_owning<name> name##Ref; \
	class name

//////////////////////////////////////////////////////////////////////////////
//
//	KNOWS-A POINTER
//
///////////////////////////////////////////////////////////////////////////////
template <typename ItemType>
class PLAutoPointer_knowing
{
protected:


	// **************************************************************
	// *					 Private _ Types						*
	// **************************************************************

	// -----------
	// *** Wrapper
	struct PointerWrapper
	{
		PointerWrapper(ItemType *inPointer)
		{
			pointer = inPointer;
		}

		int referenceCount;
		ItemType *pointer;
	};


	// **************************************************************
	// *					 Private _ Variables					*
	// **************************************************************

	// ---------
	// *** Debug
	char _name[20];

	// -----------
	// *** Wrapper
	PointerWrapper *_pointerToWrapper;


public:


	// **************************************************************
	// *					 Public _ Methods						*
	// **************************************************************
	PLAutoPointer_knowing()
		: _pointerToWrapper(NULL)
	{
	}


	// **************************************************************
	// *					 Public _ Operators						*
	// **************************************************************
	PLAutoPointer_knowing<ItemType> &operator = (
			const PLAutoPointer_knowing<ItemType> &inPointer)
	{
		_pointerToWrapper = inPointer._pointerToWrapper;

		return *this;
	}

	ItemType &operator *(void)
	{
		return this->_pointerToWrapper->pointer;
	}

	ItemType *operator ->(void)
	{
		return this->_pointerToWrapper->pointer;
	}
};


///////////////////////////////////////////////////////////////////////////////
//
//	HAS-A POINTER
//
///////////////////////////////////////////////////////////////////////////////
template <typename ItemType>
class PLAutoPointer_owning : public PLAutoPointer_knowing<ItemType>
{
public:


	// **************************************************************
	// *					 Public _ Method						*
	// **************************************************************

	// ---------------------
	// *** Memory management
	PLAutoPointer_owning()
	{
		//sprintf(name, "POINTER %i", debugCounter);
		//std::cout << "Constructor of " << name << std::endl;
		//++debugCounter;
		this->_pointerToWrapper = NULL;
	}

	PLAutoPointer_owning(const PLAutoPointer_owning<ItemType> &inPointer)
	{
		//sprintf(name, "POINTER %i", debugCounter);
		//std::cout << "Copying constructor of " << name << std::endl;
		//++debugCounter;

		this->_pointerToWrapper = inPointer._pointerToWrapper;
		retain();
	}

	virtual ~PLAutoPointer_owning()
	{
		//std::cout << "Destructor of " << name << std::endl;
		release();
	}

	// -------------------
	// *** Owning behavior
	void release()
	{
		if (NULL != this->_pointerToWrapper)
		{
			--this->_pointerToWrapper->referenceCount;
			if (0 == this->_pointerToWrapper->referenceCount)
			{
				delete this->_pointerToWrapper->pointer;
				delete this->_pointerToWrapper;
				this->_pointerToWrapper = NULL;
			}
		}
		//std::cout << "Release of " << name << ". Reference count: " <<
		//			((NULL == pointerWrapper) ? 0 : pointerWrapper->referenceCount)
		//			<< std::endl;
	}

	void retain()
	{
		if (NULL != this->_pointerToWrapper)
		{
			++this->_pointerToWrapper->referenceCount;
		}

		//std::cout << "Reatain of " << name << ". Reference count: " <<
		//			((NULL == pointerWrapper) ? 0 : pointerWrapper->referenceCount)
		//			<< std::endl;
	}


	// **************************************************************
	// *					 Public _ Operators						*
	// **************************************************************
	PLAutoPointer_owning<ItemType> &operator = (
			const PLAutoPointer_knowing<ItemType> &inPointer)
	{
		if (inPointer.pointerWrapper != this->_pointerToWrapper)
		{
			release();
			this->_pointerToWrapper = inPointer._pointerToWrapper;
			retain();
		}

		return *this;
	}

	ItemType &operator *(void)
	{
		return *this->_pointerToWrapper->pointer;
	}

	ItemType *operator ->(void)
	{
		return this->_pointerToWrapper->pointer;
	}


	///////////////////////////////////////////////////////////////////////////////
	// *** Properties ***
	///////////////////////////////////////////////////////////////////////////////
	ItemType *rawPointer()
	{
		return this->_pointerToWrapper->pointer;
	}

	// **************************************************************
	// *					 Static _ Method						*
	// **************************************************************
	static PLAutoPointer_owning<ItemType> create()
	{
		PLAutoPointer_owning<ItemType> thePointer;
		thePointer._pointerToWrapper = new typename
				PLAutoPointer_knowing<ItemType>::PointerWrapper(NULL);
		return thePointer;
	}

	template<typename T1>
	static PLAutoPointer_owning<ItemType> create(T1 arg1)
	{
		PLAutoPointer_owning<ItemType> thePointer;
		thePointer._pointerToWrapper = new typename
				PLAutoPointer_knowing<ItemType>::PointerWrapper(
						new ItemType(arg1));
		return thePointer;
	}

	template<typename T1, typename T2>
	static PLAutoPointer_owning<ItemType> create(T1 arg1, T2 arg2)
	{
		PLAutoPointer_owning<ItemType> thePointer;
		thePointer._pointerToWrapper = new typename
				PLAutoPointer_knowing<ItemType>::PointerWrapper(
						new ItemType(arg1, arg2));
		return thePointer;
	}

	template<typename T1, typename T2, typename T3>
	static PLAutoPointer_owning<ItemType> create(T1 arg1, T2 arg2, T3 arg3)
	{
		PLAutoPointer_owning<ItemType> thePointer;
		thePointer._pointerToWrapper = new typename
				PLAutoPointer_knowing<ItemType>::PointerWrapper(
						new ItemType(arg1, arg2, arg3));
		return thePointer;
	}

	template<typename T1, typename T2, typename T3, typename T4>
	static PLAutoPointer_owning<ItemType> create(T1 arg1, T2 arg2, T3 arg3,
			T4 arg4)
	{
		PLAutoPointer_owning<ItemType> thePointer;
		thePointer._pointerToWrapper = new typename
				PLAutoPointer_knowing<ItemType>::PointerWrapper(
						new ItemType(arg1, arg2, arg3, arg4));
		return thePointer;
	}

	template<typename T1, typename T2, typename T3, typename T4, typename T5>
	static PLAutoPointer_owning<ItemType> create(T1 arg1, T2 arg2, T3 arg3,
			T4 arg4, T5 arg5)
	{
		PLAutoPointer_owning<ItemType> thePointer;
		thePointer._pointerToWrapper = new typename
				PLAutoPointer_knowing<ItemType>::PointerWrapper(
						new ItemType(arg1, arg2, arg3, arg4, arg5));
		return thePointer;
	}
};

#endif /* PLAUTOPOINTER_H_ */
