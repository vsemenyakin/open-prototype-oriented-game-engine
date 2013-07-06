//============================================================================
// Name        : Functor.cpp
// Author      : Andrew Begunov
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
///////////////////////////////////////////////////////////////////////////////
#ifndef PLFUNCTOR_H_
#define PLFUNCTOR_H_

///////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////
class PLFunctor
{
private:

	///////////////////////////////////////////////////////////////////////////
	// **************              TARGET TYPE                ************** //
	///////////////////////////////////////////////////////////////////////////
	class AbstractTarget
	{
	private:
		static const unsigned kMaxArgsCountAvailable = 100;

	public:
		void *_args[kMaxArgsCountAvailable];

		virtual void call()=0;
		virtual AbstractTarget *clone()=0;

		virtual ~AbstractTarget()
		{
		}
	};

	///////////////////////////////////////////////////////////////////////////
	// Base template implementation
	template <typename T>
	class Target : public AbstractTarget
	{
	};

	///////////////////////////////////////////////////////////////////////////
	// Implementation for function as a target
	template <typename ArgT>
	class Target<void (*)(ArgT)> : public AbstractTarget
	{
		void (*_callback)(ArgT);

	public:
		Target(void (*callback)(ArgT))
			:_callback(callback)
		{
		}

		void call()
		{
			_callback(*(ArgT*)(_args[0]));
		}

		AbstractTarget *clone()
		{
			return new Target<void (*)(ArgT)>(_callback);
		}
	};

	///////////////////////////////////////////////////////////////////////////
	// Implementation for method as target
	template <typename ClassT, typename ArgT>
	class Target<void (ClassT::*)(ArgT)> : public AbstractTarget
	{
		ClassT *_object;
		void (ClassT::*_callback)(ArgT);

	public:
		Target(ClassT *object, void (ClassT::*callback)(ArgT))
			:_object(object), _callback(callback)
		{
		}

		void call()
		{
			(_object->*_callback)(*(ArgT*)(_args[0]));
		}

		AbstractTarget *clone()
		{
			return new Target<void (ClassT::*)(ArgT)>(_object, _callback);
		}
	};

#if __cplusplus > 199711L
	///////////////////////////////////////////////////////////////////////////
	// Implementation for lambda as a target
	template <typename ArgT>
	class Target<int> : public AbstractTarget
	{
		auto _callback;

	public:
		Target(auto inCallback)
			: _callback(inCallback)
		{
		}

		void call()
		{
			_callback(*(ArgT *)(_args[0]));
		}

		AbstractTarget *clone()
		{
			return new Target(_callback);
		}
	};
#endif

	AbstractTarget *_caller;

public:

	PLFunctor()
	{
		_caller = NULL;
	}

	template <typename ArgT>
	PLFunctor(void (*callback)(ArgT))
		:_caller(new Target<void (*)(ArgT)>(callback))
	{
	}

	template <typename ClassT, typename ArgT>
	PLFunctor(ClassT *object, void (ClassT::*callback)(ArgT))
		:_caller(new Target<void (ClassT::*)(ArgT)>(object, callback))
	{
	}

#if __cplusplus > 199711L
	template <typename ArgT>
	PLFunctor(auto inLamda)
		:_caller(new Target<ArgT> >(inLamda))
	{
	}
#endif

	PLFunctor(const PLFunctor &inFunctor)
		:_caller(inFunctor._caller->clone())
	{
	}


	// Deferred call methods
	template <typename T>
	inline void setArguments(T arg)
	{
		_caller->_args[0] = (void *)&arg;
	}

	inline void call()
	{
		_caller->call();
	}

	// Immidiatly call operator
	template <typename T>
	void operator ()(T arg)
	{
		this->setArguments(arg);
		this->call();
	}

	void operator =(const PLFunctor& inFunctor)
	{
		delete _caller;
		_caller = inFunctor._caller->clone();
	}

	~PLFunctor()
	{
		delete _caller;
	}
};

#endif /* PLFUNCTOR_H_ */
