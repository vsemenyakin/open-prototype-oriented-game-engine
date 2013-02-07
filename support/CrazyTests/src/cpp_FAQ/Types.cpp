/*
 * Types.cpp
 *
 *  Created on: Jan 29, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#include "Types.h"

///////////////////////////////////////////////////////////////////////////////
//
// *** Helpers
//
///////////////////////////////////////////////////////////////////////////////
void Helpers::__printFAQBlock_BEGIN(const char *inName)
{
	size_t theSize = strlen(inName);

	// NB: "memset" function sets count of N=[3] first values
	// to value=[2] for buffer with begin pointer=[1].
	char *theStars = new char[theSize + 1];
	theStars[theSize] = '\0';
	memset(theStars, '*', theSize);

	std::cout << theStars << std::endl;
	std::cout << inName << std::endl;
	std::cout << theStars << std::endl << std::endl;
}

void Helpers::__printFAQBlock_END()
{
	std::cout << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
//
// *** GLOBAL NOTA BENE SECTION
//
///////////////////////////////////////////////////////////////////////////////

// NB: Remember, that all memory-depended values (such as variables size or
//  memory layout) are OS and compiler dependent. One of the task of this crib
//  is to give the possibility to check the standard variables size and memory
//  layout. If you'll see

///////////////////////////////////////////////////////////////////////////////
//
// *** CPPTypes
//
///////////////////////////////////////////////////////////////////////////////
void CPPTypes::printTypesSizes()
{
	Helpers::__printFAQBlock_BEGIN("SIZE OF STANDART TYPES");

	// ------------------.
	// #Byte-size values
	std::cout << "#Byte-size values:" << std::endl;

	std::cout << "<bool>: " << sizeof(bool) << std::endl;
	std::cout << "<char>: " << sizeof(char) << std::endl;

	// ----------------.
	// #Integer values
	std::cout << std::endl << "#Integer values:" << std::endl;

	// NB: Modifier can be used without "int" - they are "int" by default.
	std::cout << "<short>: " << sizeof(short) << std::endl;
	std::cout << "<short int>: " << sizeof(short int) << std::endl;

	std::cout << "<int>: " << sizeof(int) << std::endl;

	// NB: "int" and "long int" have same sizes.
	std::cout << "<long>: " << sizeof(long) << std::endl;
	std::cout << "<long int>: " << sizeof(long int) << std::endl;
	std::cout << "<long long>: " << sizeof(long long int) << std::endl;
	std::cout << "<long long int>: " << sizeof(long long int) << std::endl;

	// ---------.
	// #Pointer
	std::cout << std::endl << "#Pointer:" << std::endl;

	std::cout << "<void *>: " << sizeof(void *) << std::endl;

	// NB: Use "size_t" type in each place, that
	//  determines indexes, sizes and ranges.
	std::cout << "<size_t>: " << sizeof(size_t) << std::endl;

	// -----------------------.
	// #Floating point values
	std::cout << std::endl << "#Floating point values:" << std::endl;

	std::cout << "<float>: " << sizeof(float) << std::endl;

	// NB: Double may have only "long" modifier.
	std::cout << "<double>: " << sizeof(double) << std::endl;
	std::cout << "<long double>: " << sizeof(long double) << std::endl;

	Helpers::__printFAQBlock_END();

	// REFERENCES:
	// 1. To get information about constant values for several types you may
	//  see the CPPTypes::printStandartConstants() function.
}

void CPPTypes::printStandartConstants()
{
	Helpers::__printFAQBlock_BEGIN("STANDART CONSTANTS");

	// -------------------------.
	// #Boolean value constants
	std::cout << "#Boolean value constants:" << std::endl;

	// NB: Despite each nonzero boolean value interpreted as "true" constant,
	//  use constants "true" and "false".
	std::cout << "<false>: " << false << std::endl;
	std::cout << "<true>: " << true << std::endl;

	// -------------------.
	// #Pointer constants

	// NB: Despite 0 (mathematical zero) is interpreted as "NULL" constant,
	//  use constant NULL.
	std::cout << "<NULL>: " << (void *)NULL << std::endl;

	Helpers::__printFAQBlock_END();
}

void CPPTypes::constantsTest()
{
	Helpers::__printFAQBlock_BEGIN("CONSTATS TEST");

	// ----------------------.
	// #Constant stack value
	const int theInteger = 1;

	// NB: The constant before scalar value says that this value cannot be
	//  changes. So the next code will return compile error
	//   <error: assignment of read-only variable `theInteger'>:
	// theInteger = 2;

	// ------------------------------------.
	// #Pointers to constant (fixed value)
	const int *thePointerToConstantInteger = new int(1);

	// NB: The constant before pointer type says that the value the pointer
	//  pointing to cannot be changed. So the next code will return compile
	//  error
	//   <error: assignment of read-only location>:
	// *thePointerToConstantInteger = 2;

	// NB: But the pointer value may be changed, so after next two code lines
	//  the pointer will be pointing to new range of heap memory:
	delete(thePointerToConstantInteger);
	thePointerToConstantInteger = new int(2);

	// -----------------------------------.
	// #Constant pointers (fixed address)
	int *const theConstantPointerToInteger = new int(1);

	// NB: The constant after pointer type says that the pointer value
	//  (address, value of pointer variable) is constant. So the next code will
	//  return compile error
	//   <error: assignment of read-only variable
	//      `theConstantPointerToInteger'>:
	// theConstantPointerToInteger = new int(2);

	// NB: But the value of memory where the pointer pointed is changeable and
	//  the memory must be freed when it's not commonly needed with"delete"
	//  function call:
	*theConstantPointerToInteger = 2;
	delete(theConstantPointerToInteger);

	// ----------------------------------------------------------.
	// #Constant pointers to constants (fixed address and value)
	const int *const theConstantPointerToConstantInteger = new int(1);

	// NB: The constant pointer to constant is read-only value with fixed
	//  location on memory. So you cannot change it's value (address) and value
	//  where it's pointed. Next code will return the error (error messages can
	//  be found above):
	//*theConstantPointerToConstantInteger = 2;
	//theConstantPointerToConstantInteger = new int(2);

	// NB: But you must free the constant pointer's to constant value when it's
	//  not needed:
	delete(theConstantPointerToConstantInteger);

	Helpers::__printFAQBlock_END();

	// REFERENCES:
	// 1. To get information about layout of variables with constant modifiers
	//  you may see the CPPMemory::memoryAllocationTest() function, the
	//  #Stack_memory section.
}

///////////////////////////////////////////////////////////////////////////////
//
// *** CPPMemory
//
///////////////////////////////////////////////////////////////////////////////
void CPPMemory::memoryAllocationTest()
{
	Helpers::__printFAQBlock_BEGIN("MEMORY ALLOCATION TEST");

	// --------------.
	// #Stack memory
	int theStackFirstInteger = 1;
	char theStackChar = 1;
	double *theStackDoublePointer = NULL;
	const int theStackSecondInteger = 2;

	// NB: Four variables declared above are situated on memory one by one
	//  beginning from "theStackFirstInteger" and decreasing the address
	//  (!OS depended. I tested for Windows, on other OS or other C++ compiler
	//  implementation it may be different!). Code below prints the table with
	//  address and value of each declared variable. Code illustrates how the
	//  size of variables influence to address of next variable on stack.
	// NB: Unary operator "&" returns the address of variable.
	std::cout << "Name\t\t\t\tAddress\t\tValue" << std::endl;
	std::cout << "<theStackFirstInteger>\t\t" << &theStackFirstInteger << "\t"
			<< theStackFirstInteger << std::endl;
	std::cout << "<theStackChar>\t\t\t" << (void *)&theStackChar << "\t" <<
			(int)theStackChar << std::endl;
	std::cout << "<theStackDoublePointer>\t\t" << &theStackDoublePointer <<
			"\t" << theStackDoublePointer << std::endl;
	std::cout << "<theStackSecondInteger>\t\t" << &theStackSecondInteger <<
			"\t" << theStackSecondInteger << std::endl;
	// NB: The "const" modifier don't influence to address of variable. It have
	//  a sense only on code compiling.

	// -------------.
	// #Heap memory
	theStackDoublePointer = new double(1.1);
	double *theAnotherStackDoublePointer = new double(2.2);

	// NB: On first of two lines above we set the value of
	//  "theStackDoublePointer" with address on heap that returned by "new"
	//  operator. Operator allocates (and reserve) memory size for double
	//  variable on heap memory and set it's value (1.1) and returns the
	//  address of first byte of this block. On second line of two lines above
	//  we declare new pointer "theAnotherStackDoublePointer" and set it's
	//  value with same way (as explained in last sentence) but with value 2.2.
	//  Code below prints table with columns that explain for each variable:
	//  name of variable with pointer type, address of this variable, address
	//  that saved to it and value that saved on this address on heap. Give
	//  your attention on capslocked end of words on third and fourth columns
	//  names.
	// NB: Unary operator "*" used for some variable A returns the value, saved
	//  on address, numeric value of which is saved on variable A.
	std::cout << std::endl;
	std::cout << "Name\t\t\t\tAddress\t\tPointER value\tPointED value" <<
			std::endl;
	std::cout << "<theStackChar>\t\t\t" << (void *)&theStackDoublePointer <<
			"\t" << theStackDoublePointer << "\t" << *theStackDoublePointer <<
					std::endl;
	std::cout << "<theStackChar>\t\t\t" <<
			(void *)&theAnotherStackDoublePointer << "\t" <<
					theAnotherStackDoublePointer << "\t" <<
							*theAnotherStackDoublePointer << std::endl;

	// -----------.
	// #Reference
	int &theIntegerReference = theStackFirstInteger;
	double &theDoubleReference = *theStackDoublePointer;

	// NB: Reference is something like automatically dereferencing pointer or
	//  alias of object. It's size on windows OS and WinGW compiler is same as
	//  pointer, and (on my mind) it's exactly a pointer, that just
	//  automatically dereferenced on use. Getting address of reference return
	//  address of variable, that is pointed by reference.
	std::cout << std::endl;
	std::cout << "Name\t\t\t\tAddress\t\tValue" << std::endl;
	std::cout << "<theIntegerReference>\t\t" << &theIntegerReference << "\t"
				<< theIntegerReference << std::endl;
	std::cout << "<theDoubleReference>\t\t" << &theDoubleReference << "\t"
				<< theDoubleReference << std::endl;

	// NB: Next two code lines needed to get size of reference. We get it by
	//  decreasing the address of "theVariableForGettingReferenceSize" from
	//  address of "theAnotherStackDoublePointer" and dividing it on a half. On
	//  decreasing we get the size of two references (they are stack variables,
	//  that lie between "theAnotherStackDoublePointer" and
	//  "theVariableForGettingReferenceSize"). On dividing we get the size of
	//  reference variable
	char theVariableForGettingReferenceSize;
	std::cout << std::endl <<  "Size of reference: " <<
			((size_t)&theAnotherStackDoublePointer -
					(size_t)&theVariableForGettingReferenceSize) / 2 <<
							std::endl;

	Helpers::__printFAQBlock_END();
}
