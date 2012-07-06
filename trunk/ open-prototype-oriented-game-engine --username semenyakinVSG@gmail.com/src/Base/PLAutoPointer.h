#ifndef PLAUTOPOINTER_H_
#define PLAUTOPOINTER_H_

///////////////////////////////////////////////////////////////////////////////
// Wrapper for object points.
template <typename ItemType>
struct PointerWrapper
{
	int referenceCount;
	ItemType *pointer;
};

///////////////////////////////////////////////////////////////////////////////
template <typename ItemType>
class PLAutoPointer {
private:
	char name[20];
	PointerWrapper<ItemType> *pointerWrapper;

public:

	// *** Memory management ***
	PLAutoPointer(ItemType *inItem);
	PLAutoPointer();
	virtual ~PLAutoPointer();

	// *** Retain / Release ***
	void release();
	void retain();

	// *** Operators ***
	void operator = (PLAutoPointer<ItemType> &inAutoPointer);
	void operator = (ItemType *inItem);

	ItemType *operator -> (void);
};

#endif /* PLAUTOPOINTER_H_ */
