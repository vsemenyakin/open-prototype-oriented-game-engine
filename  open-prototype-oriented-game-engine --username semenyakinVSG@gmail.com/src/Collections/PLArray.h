

#ifndef PLARRAY_H_
#define PLARRAY_H_

#include "../Base/PLScalarTypes.h"
#include "../Base/PLObject/PLObject.h"

class PLArray : public PLObject {

private:
	PLObject **buffer;
	PLIndex bufferSize;

public:

	// *** Memory management ***
	// constructors
	PLArray(PLIndex inCapasity);
	void virtual destroy();

	// *** Content management ***
	PLObject *objectAtIndex(PLIndex inIndex);
	void setObjectAtIndex(PLObject *inObject, PLIndex inIndex);
};

#endif /* PLARRAY_H_ */
