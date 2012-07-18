#ifndef PLAUTOPOINTER_H_
#define PLAUTOPOINTER_H_

///////////////////////////////////////////////////////////////////////////////
#define TRACE_EXPRESSION(expr) std::cout << #expr << " = " << expr << std::endl;

#include <iostream>
///////////////////////////////////////////////////////////////////////////////
//static int debugCounter = 0;

///////////////////////////////////////////////////////////////////////////////
template <typename ItemType>
class PLAutoPointer
{
private:

	template <typename WrapperItemType>
	struct PointerWrapper
	{
		int referenceCount;
		WrapperItemType *pointer;
	};

	char name[20];
	PointerWrapper<ItemType> *pointerWrapper;

	ItemType * (PLAutoPointer::*_pointer)();


	// 	Private methods
	void setRawPointer(ItemType *inRawPointer)
	{
		release();
		pointerWrapper = new PointerWrapper<ItemType>();
		pointerWrapper->pointer = inRawPointer;
		retain();
	}

public:
	///////////////////////////////////////////////////////////////////////////////
	// *** Memory management ***
	///////////////////////////////////////////////////////////////////////////////
	PLAutoPointer()
	{
		//sprintf(name, "POINTER %i", debugCounter);
		//std::cout << "Constructor of " << name << std::endl;
		//++debugCounter;

		pointerWrapper = NULL;
		_pointer = &(PLAutoPointer::objectPointerWithCreation);
	}

	///////////////////////////////////////////////////////////////////////////////
	PLAutoPointer(const PLAutoPointer<ItemType> &inAutoPointer)
	{
		//sprintf(name, "POINTER %i", debugCounter);
		//std::cout << "Copying constructor of " << name << std::endl;
		//++debugCounter;

		pointerWrapper = inAutoPointer.pointerWrapper;
		_pointer = &PLAutoPointer::objectPointerWithCreation;
		retain();
	}

	virtual ~PLAutoPointer()
	{
		//std::cout << "Destructor of " << name << std::endl;
		release();
	}

	///////////////////////////////////////////////////////////////////////////////
	// *** Retain / Release ***
	///////////////////////////////////////////////////////////////////////////////
	void release()
	{
		if (NULL != pointerWrapper)
		{
			--pointerWrapper->referenceCount;
			if (0 == pointerWrapper->referenceCount)
			{
				delete pointerWrapper->pointer;
				delete pointerWrapper;
				pointerWrapper = NULL;
			}
		}
		//std::cout << "Release of " << name << ". Reference count: " <<
		//			((NULL == pointerWrapper) ? 0 : pointerWrapper->referenceCount)
		//			<< std::endl;
	}

	///////////////////////////////////////////////////////////////////////////////
	void retain()
	{
		if (NULL != pointerWrapper)
		{
			++pointerWrapper->referenceCount;
		}

		//std::cout << "Reatain of " << name << ". Reference count: " <<
		//			((NULL == pointerWrapper) ? 0 : pointerWrapper->referenceCount)
		//			<< std::endl;
	}

	///////////////////////////////////////////////////////////////////////////////
	// *** Operators ***
	///////////////////////////////////////////////////////////////////////////////
	PLAutoPointer<ItemType> &operator = (const PLAutoPointer<ItemType> &inAutoPointer)
	{
		if (inAutoPointer.pointerWrapper != pointerWrapper)
		{
			release();
			pointerWrapper = inAutoPointer.pointerWrapper;
			retain();
		}

		return *this;
	}

	// ***************************
	// Object pointer from wrapper
	// {
	ItemType *objectPointerWithCreation()
	{
		if (NULL == pointerWrapper)
		{
			this->setRawPointer(new ItemType());
			_pointer = &PLAutoPointer::objectPointer;
		}
		return pointerWrapper->pointer;
	}

	ItemType *objectPointer()
	{
		return pointerWrapper->pointer;
	}
	// }
	// ***************************

	ItemType *operator ~()
	{
		return (this->*_pointer)();
	}

	ItemType &operator *(void)
	{
		return *(this->*_pointer)();
	}

	ItemType *operator ->(void)
	{
		return (this->*_pointer)();
	}

	///////////////////////////////////////////////////////////////////////////////
	// *** Properties ***
	///////////////////////////////////////////////////////////////////////////////
	ItemType *rawPointer()
	{
		return pointerWrapper->pointer;
	}

	///////////////////////////////////////////////////////////////////////////////
	// *** Create ***
	///////////////////////////////////////////////////////////////////////////////
	static PLAutoPointer<ItemType> create()
	{
		PLAutoPointer<ItemType> thePointer;
		thePointer.setRawPointer(new ItemType());
		return thePointer;
	}

	template<typename T1>
	static PLAutoPointer<ItemType> create(T1 arg1)
	{
		PLAutoPointer<ItemType> thePointer;
		thePointer.setRawPointer(new ItemType(arg1));
		return thePointer;
	}

	template<typename T1, typename T2>
	static PLAutoPointer<ItemType> create(T1 arg1, T2 arg2)
	{
		PLAutoPointer<ItemType> thePointer;
		thePointer.setRawPointer(new ItemType(arg1, arg2));
		return thePointer;
	}

	template<typename T1, typename T2, typename T3>
	static PLAutoPointer<ItemType> create(T1 arg1, T2 arg2, T3 arg3)
	{
		PLAutoPointer<ItemType> thePointer;
		thePointer.setRawPointer(new ItemType(arg1, arg2, arg3));
		return thePointer;
	}

	template<typename T1, typename T2, typename T3, typename T4>
	static PLAutoPointer<ItemType> create(T1 arg1, T2 arg2, T3 arg3, T4 arg4)
	{
		PLAutoPointer<ItemType> thePointer;
		thePointer.setRawPointer(new ItemType(arg1, arg2, arg3, arg4));
		return thePointer;
	}

	template<typename T1, typename T2, typename T3, typename T4, typename T5>
	static PLAutoPointer<ItemType> create(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5)
	{
		PLAutoPointer<ItemType> thePointer;
		thePointer.setRawPointer(new ItemType(arg1, arg2, arg3, arg4, arg5));
		return thePointer;
	}
};

#endif /* PLAUTOPOINTER_H_ */
