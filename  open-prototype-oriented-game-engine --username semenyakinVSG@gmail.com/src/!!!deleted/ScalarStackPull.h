/*
 * StackPull.h
 *
 *  Created on: 09.06.2012
 *      Author: SterX
 */

#ifndef STACKPULL_H_
#define STACKPULL_H_

#define DEFAULT_BLOCK_SIZE 1024

template <class ItemType>
class ScalarStackPull {

private:

	size_t blockSize;

	size_t lengthOfBuffer;
	size_t lengthOfPull;
	size_t freeSpaceLeft;

	ItemType *buffer;

public:
	ScalarStackPull();
	ScalarStackPull(size_t inBlockSize);

	void push(ItemType *inElement);
	void pop();

	ItemType *lastItem();

	virtual ~ScalarStackPull();
};

#endif /* STACKPULL_H_ */
