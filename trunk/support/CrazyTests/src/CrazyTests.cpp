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

///////////////////////////////////////////////////////////////////////////////
template<typename ItemType> class A;
template<typename ItemType> class B;

///////////////////////////////////////////////////////////////////////////////
template <typename ItemType>
class A
{
private:
	ItemType anArgument;

public:
	template<typename ItemType_1> void operator = (A<ItemType_1> &inArgument)
	{
		anArgument = static_cast<ItemType_1>(inArgument.getVariable());
	}


	virtual void setVariable(const ItemType &inType)
	{
		anArgument = inType;
	}

	virtual ItemType &getVariable()
	{
		return anArgument;
	}
};

///////////////////////////////////////////////////////////////////////////////
template <typename ItemType>
class B : public A<ItemType>
{
};

///////////////////////////////////////////////////////////////////////////////
int main()
{
	CPPTypes::printTypesSizes();
	//CPPTypes::printStandartConstants();

	CPPMemory::memoryAllocationTest();

	/*
	A<int> first;
	A<double> second;

	second.setVariable(-0.1);

	first = second;
	*/

	/*
	void *first = new B<int>();
	void *second1;

	clock_t theClockTime = clock();

	int size = 40000;
	int i, j;

	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			//second1 = (A<int> *)first;
			second1 = first;
		}
	}

	std::cout << "Time: " << clock() - theClockTime << std::endl;
*/
	return 0;
}
