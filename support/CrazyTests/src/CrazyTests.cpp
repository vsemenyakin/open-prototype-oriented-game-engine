/*
 *		This Code Was Created By Jeff Molofee 2000
 *		A HUGE Thanks To Fredric Echols For Cleaning Up
 *		And Optimizing The Base Code, Making It More Flexible!
 *		If You've Found This Code Useful, Please Let Me Know.
 *		Visit My Site At nehe.gamedev.net
 */
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <time.h>
#include "cpp_FAQ/Types.h"
#include "Prototype/TestFileManager.h"

/*
///////////////////////////////////////////////////////////////////////////////
using namespace std;

#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <vector>

#include <functional>

///////////////////////////////////////////////////////////////////////////////
// *** CALLER
///////////////////////////////////////////////////////////////////////////////
//============================================================================
// Name        : Functor.cpp
// Author      : Andrew Begunov
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;

static const unsigned kMaxArgsCountAvailable = 100;

///////////////////////////////////////////////////////////////////////////////
class AbstractTarget
{
public:
	void *_args[kMaxArgsCountAvailable];

	virtual void call()=0;

	virtual ~AbstractTarget()
	{
	}
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
class Target : public AbstractTarget
{
};

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
};

///////////////////////////////////////////////////////////////////////////////
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
};

///////////////////////////////////////////////////////////////////////////////
template <typename ArgT>
class Target<std::function<void(ArgT)> > : public AbstractTarget
{
	std::function<void(ArgT)> _callback;

public:
	Target(std::function<void(ArgT)> inCallback)
		: _callback(inCallback)
	{
	}

	void call()
	{
		_callback(*(ArgT *)(_args[0]));
	}
};

///////////////////////////////////////////////////////////////////////////////
class Functor
{
private:
	AbstractTarget *_caller;

public:
	template <typename ClassT, typename ArgT>
	Functor(ClassT *object, void (ClassT::*callback)(ArgT))
		:_caller(new Target<void (ClassT::*)(ArgT)>(object, callback))
	{
	}

	template <typename ArgT>
	Functor(void (*callback)(ArgT))
		:_caller(new Target<void (*)(ArgT)>(callback))
	{
	}

	template <typename ArgT>
	Functor(std::function<void(ArgT)> inLamda)
		:_caller(new Target<std::function<void(ArgT)> >(inLamda))
	{
	}

	template <typename T>
	void call(T arg)
	{
		_caller->_args[0] = (void *)&arg;
		_caller->call();
	}

	~Functor()
	{
		delete _caller;
	}
};

///////////////////////////////////////////////////////////////////////////////
typedef int PLEventKey;
static const PLEventKey kPLNullEventKey = 0;
#define DECLARE_EVENT_KEY(EVENT_NAME) PLEventKey EVENT_NAME = kPLNullEventKey;

void addEventListener(PLEventKey *inKey)
{
	if (*inKey == kPLNullEventKey)
	{
		// Set key
	}
}

///////////////////////////////////////////////////////////////////////////////
void f(float arg)
{
	std::cout << arg * arg << std::endl;
}

class Test
{
public:
	void method(float x)
	{
		std::cout << x*x << std::endl;
	}
};

///////////////////////////////////////////////////////////////////////////////
template <typename RetType, typename Arg>
RetType test_func(Arg inArgument)
{
	return (RetType)inArgument;
}
*/

class MyClass
{
public:
	int x;
	int y;
	char name;

	MyClass(const MyClass &inObject)
		: x(inObject.x), y(inObject.y), name(inObject.name)
	{
		std::cout << "Copy constructor called" << std::endl;
	}

	MyClass()
		: x(0), y(0), name('A')
	{
	}

	MyClass &operator = (const MyClass &inObject)
	{
		x = inObject.x;
		y = inObject.y;
		name = inObject.name;

		std::cout << "Assigning object address: " << this << std::endl;

		return *this;
	}
};

///////////////////////////////////////////////////////////////////////////////
class ClassWithExplicityInlineMethod
{
public:
	inline void sum(int &a, int b)
	{
		a = a + b;
	}
};

int sum(int &a, int b)
{
	return a + b;
}

///////////////////////////////////////////////////////////////////////////////
int main()
{
	ClassWithExplicityInlineMethod theClass;

	int theTestTimes = 1000000000;
	int theIndex = 0;

	int theResult = 0;

	time_t theTime = 0;

	// Simple sum
	theTime = clock();
	theResult = 0;
	for (theIndex = 0; theIndex < theTestTimes; ++theIndex)
	{
		theResult = theResult + theIndex;
	}
	theTime = clock() - theTime;
	std::cout << theResult << " " << theTime << std::endl;

	// Function sum
	theTime = clock();
	theResult = 0;
	for (theIndex = 0; theIndex < theTestTimes; ++theIndex)
	{
		theResult = sum(theResult, theIndex);
	}
	theTime = clock() - theTime;
	std::cout << theResult << " " << theTime << std::endl;

	// Inline method sum
	theTime = clock();
	theResult = 0;
	for (theIndex = 0; theIndex < theTestTimes; ++theIndex)
	{
		theClass.sum(theResult, theIndex);
	}
	theTime = clock() - theTime;
	std::cout << theResult << " " << theTime << std::endl;


	/*
	MyClass a, b, c;

	std::cout << "A address: " << &a << std::endl;
	std::cout << "B address: " << &b << std::endl;
	std::cout << "C address: " << &c << std::endl;

	c.x = 1;
	c.y = 2;
	c.name = 'a';

	a = b = c;
	*/

	/*
	Functor theFunctor = std::function<void(float)>([](float inArgument)
	{
		std::cout << "Lambda" << std::endl;
	});

	theFunctor.call(1.6);

	std::cout << "Test finished" << std::endl;
	 */

	return 0;
}
