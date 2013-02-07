/*
 * OOPExamples.h
 *
 *  Created on: 07.02.2013
 *      Author: нргл
 */

#ifndef OOPEXAMPLES_H_
#define OOPEXAMPLES_H_

#include <iostream.h>

namespace OOPExampleClasses
{
	///////////////////////////////////////////////////////////////////////////
	// Base class
	///////////////////////////////////////////////////////////////////////////
	class BaseClass
	{
	private:
		int _privateField;

		void privateFunction()
		{
			std::cout << "Called private function" << std::endl;
		}

	protected:
		void protectedFunction()
		{
			std::cout << "Called protected function" << std::endl;
		}

	public:
		void publicFunction()
		{
			std::cout << "Called public function" << std::endl;
		}
	};

	///////////////////////////////////////////////////////////////////////////
	// Inherited classes
	///////////////////////////////////////////////////////////////////////////
	class ChildClass_PublicInherited : public BaseClass
	{
	public:
		void callBaseMethods()
		{
			// NB: Private methods of base class is inaccessible on child
			//  class. You can't call it. No way, guys. So next code will throw
			//  an error on two lines - on beginning of method body and on line
			//  where the method called. Text of errors:
			//  1. (On begin of method body) `void OOPExampleClasses::
			//   BaseClass::privateFunction()' is private
			//  2. (On line of method calling) within this context
			//privateFunction();
			//BaseClass::privateFunction();

			protectedFunction();
			BaseClass::protectedFunction();

			publicFunction();
			BaseClass::publicFunction();
		}
	};

	class ChildClass_ProtectedInherited : protected BaseClass
	{
	public:
		void callBaseMethods()
		{
			// NB: To get information about the private methods calling see the
			//  ChildClass_PublicInherited::callBaseMethods() method
			//privateFunction();
			//BaseClass::privateFunction();

			protectedFunction();
			BaseClass::protectedFunction();

			publicFunction();
			BaseClass::publicFunction();

			// REFERENCES:
			// 1. To get information about the private methods calling see the
			//  ChildClass_PublicInherited::callBaseMethods() method.
		}
	};

	// Inheritance is private by default
	class ChildClass_PrivateInherited : private BaseClass
	{
	public:
		void callBaseMethods()
		{
			// NB: To get information about the private methods calling see the
			//  ChildClass_PublicInherited::callBaseMethods() method
			//privateFunction();
			//BaseClass::privateFunction();

			protectedFunction();
			BaseClass::protectedFunction();

			publicFunction();
			BaseClass::publicFunction();

			// REFERENCES:
			// 1. To get information about the private methods calling see the
			//  ChildClass_PublicInherited::callBaseMethods() method.
		}
	};
}

#endif /* OOPEXAMPLES_H_ */
