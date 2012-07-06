

#ifndef PLCONTEXT_H_
#define PLCONTEXT_H_

#include "../Collections/PLList.h"
#include "../Base/PLObject/PLObject.h"
#include "../Base/PLScalarTypes.h"

class PLContext : public PLObject {

private:

	PLList *subcontexts;
	PLList *objects;



public:
	// *** Memory management ***
	// constructors
	PLContext();
	virtual void destroy();

	// *** Subcontexts management ***
	void addSubcontext(PLContext *inContext);

	// *** Content objects management ***
	PLBOOL addObject(PLObject *inObject);
};

#endif /* PLCONTEXT_H_ */
