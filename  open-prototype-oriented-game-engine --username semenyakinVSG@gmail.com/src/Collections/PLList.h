/*
 * PLList.h
 *
 *  Created on: 16.06.2012
 *      Author: SterX
 */

#ifndef PLLIST_H_
#define PLLIST_H_

#include "list.h"
#include "../Base/PLObject/PLObject.h"

class PLList : public PLObject {

private:

	std::list<PLObject *> list;

public:
	PLList();
	virtual void destroy();

	void addObject(PLObject *inObject);

};

#endif /* PLLIST_H_ */
