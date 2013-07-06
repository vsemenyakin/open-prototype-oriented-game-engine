#ifndef PLAUTOPOINTER_H_
#define PLAUTOPOINTER_H_

///////////////////////////////////////////////////////////////////////////////
#define TRACE_EXPRESSION(expr) std::cout << #expr << " = " << expr << std::endl;

///////////////////////////////////////////////////////////////////////////////
//#include <iostream>
#include <cstdlib>

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// MACRO: Type mapping
//
///////////////////////////////////////////////////////////////////////////////
#define weak_ref PLAutoPointer_knowing
#define strong_ref PLAutoPointer_owning

#define func_in_ref PLAutoPointer_knowing
#define func_out_ref PLAutoPointer_knowing

#define CLASS_WITH_REF(name) \
	class name;	\
	typedef PLAutoPointer_owning<name> name##Ref; \
	class name

///////////////////////////////////////////////////////////////////////////////
//
// TYPES: Wrapper types declarations
//
///////////////////////////////////////////////////////////////////////////////
// TODO: Encapsulate classes on this file

// -------------------
// *** Reference count
typedef unsigned int reference_count;

// -----------
// *** Wrapper
struct PointerWrapper
{
	PointerWrapper(void *inPointer)
	{
		pointer = inPointer;
		referenceCount = 1;
	}

	reference_count referenceCount;
	void *pointer;
};

template <typename ItemType> class PLAutoPointer_knowing;
template <typename ItemType> class PLAutoPointer_owning;

///////////////////////////////////////////////////////////////////////////////
//
// MACRO: Null reference constant
//
///////////////////////////////////////////////////////////////////////////////
template<typename ItemType>
static inline weak_ref<ItemType> null_ref_function()
{
	return weak_ref<ItemType>((ItemType *)NULL);
}

#define NULL_REF(TYPE) null_ref_function<TYPE>()

///////////////////////////////////////////////////////////////////////////////
//
// MACRO: Creation referenced objects declaration
//
///////////////////////////////////////////////////////////////////////////////
template<typename ItemType>
static weak_ref<ItemType> new_ref()
{
	return weak_ref<ItemType>(new ItemType());
}

template<typename ItemType, typename T1>
static weak_ref<ItemType> new_ref(T1 arg1)
{
	return weak_ref<ItemType>(new ItemType(arg1));
}

template<typename ItemType, typename T1, typename T2>
static weak_ref<ItemType> new_ref(T1 arg1, T2 arg2)
{
	return weak_ref<ItemType>(new ItemType(arg1, arg2));
}

template<typename ItemType, typename T1, typename T2, typename T3>
static weak_ref<ItemType> new_ref(T1 arg1, T2 arg2, T3 arg3)
{
	return weak_ref<ItemType>(new ItemType(arg1, arg2, arg3));
}

template<typename ItemType, typename T1, typename T2, typename T3, typename T4>
static weak_ref<ItemType> new_ref(T1 arg1, T2 arg2, T3 arg3, T4 arg4)
{
	return weak_ref<ItemType>(new ItemType(arg1, arg2, arg3, arg4));
}

template<typename ItemType, typename T1, typename T2, typename T3, typename T4,
		typename T5>
static weak_ref<ItemType> new_ref(T1 arg1, T2 arg2, T3 arg3, T4 arg4,
		T5 arg5)
{
	return weak_ref<ItemType>(new ItemType(arg1, arg2, arg3, arg4, arg5));
}

///////////////////////////////////////////////////////////////////////////////
//
// MACRO: Type casting
//
///////////////////////////////////////////////////////////////////////////////
#define CASTING_DECLARATION(INPUT_REFERENCE_TYPE)\
template<typename _CastType, typename _ItemType> friend\
		weak_ref<_CastType> cast_ref(\
				const INPUT_REFERENCE_TYPE<_ItemType> &inReference);

#define CASTING_IMPLEMENTATION(INPUT_REFERENCE_TYPE)\
template<typename CastType, typename RefType> static weak_ref<CastType>\
		cast_ref(const INPUT_REFERENCE_TYPE<RefType> &inReference)\
{\
	static_cast<CastType *>(inReference._pointerToWrapper->pointer);\
	weak_ref<CastType> theReference(inReference._pointerToWrapper);\
	return theReference;\
}\

///////////////////////////////////////////////////////////////////////////////
//
//	CLASS: Knows-a pointer
//
///////////////////////////////////////////////////////////////////////////////
// Helping macro
#define DECALRE_KNOWING_CREATION_AND_ASSIGNING(ASSIGNING_TYPE)\
PLAutoPointer_knowing(const ASSIGNING_TYPE<ItemType> &inPointer)\
{\
	/*std::cout << "Knowing copy constructor" << std::endl;*/\
	PLAutoPointer_knowing<ItemType>::_pointerToWrapper =\
			inPointer._pointerToWrapper;\
}\
PLAutoPointer_knowing<ItemType> &operator = (\
		const ASSIGNING_TYPE<ItemType> &inPointer)\
{\
/*std::cout << "Knowing assigning" << std::endl;*/\
	if (inPointer._pointerToWrapper != this->_pointerToWrapper)\
	{\
		PLAutoPointer_knowing<ItemType>::_pointerToWrapper =\
				inPointer._pointerToWrapper;\
	}\
	return *this;\
}\
bool operator == (const ASSIGNING_TYPE<ItemType> &inPointer) const\
{\
	return _pointerToWrapper == inPointer._pointerToWrapper;\
}\
bool operator != (const ASSIGNING_TYPE<ItemType> &inPointer) const\
{\
	return _pointerToWrapper != inPointer._pointerToWrapper;\
}\
bool operator > (const ASSIGNING_TYPE<ItemType> &inPointer) const\
{\
	return _pointerToWrapper > inPointer._pointerToWrapper;\
}\
bool operator < (const ASSIGNING_TYPE<ItemType> &inPointer) const\
{\
	return _pointerToWrapper < inPointer._pointerToWrapper;\
}\
\

///////////////////////////////////////////////////////////////////////////////
// Class
template <typename ItemType>
class PLAutoPointer_knowing
{

// TODO: Change to protected later
public:


	// **************************************************************
	// *					 Protected _ Variables					*
	// **************************************************************

	// -----------
	// *** Wrapper
	PointerWrapper *_pointerToWrapper;


	// **************************************************************
	// *					 Protected _ Methods					*
	// **************************************************************
	PLAutoPointer_knowing(void *inRawPointer)
	{
		//std::cout << "Knowing reference constructor for raw pointer" <<
		//		std::endl;
		_pointerToWrapper = new PointerWrapper(inRawPointer);
	}

	PLAutoPointer_knowing(PointerWrapper *inPointerWrapper)
	{
		//std::cout << "Knowing reference constructor for pointer wrapper" <<
		//		std::endl;
		_pointerToWrapper = inPointerWrapper;
	}


public:


	// **************************************************************
	// *					 Public _ Methods						*
	// **************************************************************

	// ----------------------
	// *** Macro declarations

	// Creation and assigning
	DECALRE_KNOWING_CREATION_AND_ASSIGNING(PLAutoPointer_knowing)
	DECALRE_KNOWING_CREATION_AND_ASSIGNING(PLAutoPointer_owning)

	//
	PLAutoPointer_knowing()
	{
		//std::cout << "Default knowing constructor" << std::endl;
		_pointerToWrapper = NULL;
	}

	virtual ~PLAutoPointer_knowing()
	{
		// Do nothing
	}


	// **************************************************************
	// *					 Public _ Operators						*
	// **************************************************************
	ItemType &operator *(void)
	{
		return *static_cast<ItemType *>(this->_pointerToWrapper->pointer);
	}

	ItemType *operator ->(void)
	{
		return static_cast<ItemType *>(this->_pointerToWrapper->pointer);
	}


	// **************************************************************
	// *					 Friend _ Method						*
	// **************************************************************
	CASTING_DECLARATION(PLAutoPointer_knowing)
	CASTING_DECLARATION(PLAutoPointer_owning)
};

CASTING_IMPLEMENTATION(PLAutoPointer_knowing)
CASTING_IMPLEMENTATION(PLAutoPointer_owning)

///////////////////////////////////////////////////////////////////////////////
//
//	CLASS: Has-a pointer
//
///////////////////////////////////////////////////////////////////////////////
// Helping macro
#define DECALRE_OWNING_CREATION_AND_ASSIGNING(ASSIGNING_TYPE)\
PLAutoPointer_owning(const ASSIGNING_TYPE<ItemType> &inPointer)\
{\
	/*std::cout << "Owning copy constructor" << std::endl;*/\
	PLAutoPointer_knowing<ItemType>::_pointerToWrapper =\
			inPointer._pointerToWrapper;\
	retain();\
}\
PLAutoPointer_owning<ItemType> &operator = (\
		const ASSIGNING_TYPE<ItemType> &inPointer)\
{\
	/*std::cout << "Owning assigning" << std::endl;*/\
	if (inPointer._pointerToWrapper != this->_pointerToWrapper)\
	{\
		release();\
		PLAutoPointer_knowing<ItemType>::_pointerToWrapper =\
				inPointer._pointerToWrapper;\
		retain();\
	}\
	return *this;\
}\
bool operator == (const ASSIGNING_TYPE<ItemType> &inPointer) const\
{\
	return _pointerToWrapper == inPointer._pointerToWrapper;\
}\
bool operator != (const ASSIGNING_TYPE<ItemType> &inPointer) const\
{\
	return _pointerToWrapper != inPointer._pointerToWrapper;\
}\
bool operator > (const ASSIGNING_TYPE<ItemType> &inPointer) const\
{\
	return _pointerToWrapper > inPointer._pointerToWrapper;\
}\
bool operator < (const ASSIGNING_TYPE<ItemType> &inPointer) const\
{\
	return _pointerToWrapper < inPointer._pointerToWrapper;\
}\
\

///////////////////////////////////////////////////////////////////////////////
// Class
template <typename ItemType>
class PLAutoPointer_owning : public PLAutoPointer_knowing<ItemType>
{
	using PLAutoPointer_knowing<ItemType>::_pointerToWrapper;


protected:


	// **************************************************************
	// *					 Protected _ Methods					*
	// **************************************************************

	// ---------------------
	// *** Memory management
	PLAutoPointer_owning(ItemType *inRawPointer)
		: PLAutoPointer_knowing<ItemType>(inRawPointer)
	{
	}


public:


	// **************************************************************
	// *					 Public _ Methods						*
	// **************************************************************

	// ----------------------
	// *** Macro declarations

	// Creation and assigning
	DECALRE_OWNING_CREATION_AND_ASSIGNING(PLAutoPointer_knowing)
	DECALRE_OWNING_CREATION_AND_ASSIGNING(PLAutoPointer_owning)

	// ---------------------
	// *** Memory management
	PLAutoPointer_owning()
		: PLAutoPointer_knowing<ItemType>()
	{
		//std::cout << "Owning default constructor" << std::endl;
	}

	virtual ~PLAutoPointer_owning()
	{
		//std::cout << "Removed owning reference" << std::endl;
		release();
	}

	// -------------------
	// *** Owning behavior
	void retain()
	{
		//std::cout << "Retained" << std::endl;
		if (NULL != this->_pointerToWrapper)
		{
			++this->_pointerToWrapper->referenceCount;
		}
	}

	void release()
	{
		//std::cout << "Released" << std::endl;
		if (NULL != this->_pointerToWrapper)
		{
			--this->_pointerToWrapper->referenceCount;
			if (0 == this->_pointerToWrapper->referenceCount)
			{
				delete (ItemType *)this->_pointerToWrapper->pointer;
				delete this->_pointerToWrapper;
				this->_pointerToWrapper = NULL;
			}
		}
	}
};

#endif /* PLAUTOPOINTER_H_ */
