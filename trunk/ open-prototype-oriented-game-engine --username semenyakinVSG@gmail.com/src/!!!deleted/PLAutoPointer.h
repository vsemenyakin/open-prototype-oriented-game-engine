/*
 * PLAutoPointer.h
 *
 *  Created on: 20.06.2012
 *      Author: SterX
 */

#ifndef PLAUTOPOINTER_H_
#define PLAUTOPOINTER_H_

#include "map.h"

/*
template <class ItemType>
struct PointerWrapper
{
	int referenceCount;
	ItemType *pointer;
};
*/
///////////////////////////////////////////////////////////////////////////
//template <typename ItemType>
class PLAutoPointer {
private:
	//PointerWrapper<ItemType> *pointerWrapper;
	std::map<char*, int> theMap;

public:
	//PLAutoPointer<ItemType> operator = (PLAutoPointer<ItemType> inPointer);

	PLAutoPointer();
	virtual ~PLAutoPointer();
};

#endif /* PLAUTOPOINTER_H_ */
