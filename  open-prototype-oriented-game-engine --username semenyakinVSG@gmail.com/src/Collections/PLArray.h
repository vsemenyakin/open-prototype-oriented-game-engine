

#ifndef PLARRAY_H_
#define PLARRAY_H_

#include "../Base/PLCore.h"

class PLArray : public PLObject {

private:
	PLObject **buffer;
	PLIndex bufferSize;

public:

	// *** Memory management ***
	// constructors
	PLArray(PLIndex inCapasity);

	// *** Content management ***
	PLObject *objectAtIndex(PLIndex inIndex);
	void setObjectAtIndex(PLObject *inObject, PLIndex inIndex);
};

#endif /* PLARRAY_H_ */
