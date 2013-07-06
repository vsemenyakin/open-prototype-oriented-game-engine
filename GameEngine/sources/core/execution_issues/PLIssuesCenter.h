/*
 * PLIssuesCenter.h
 *
 *  Created on: 14.03.2013
 *      Author: semenyakinVS
 */

///////////////////////////////////////////////////////////////////////////////
#ifndef PLISSUESCENTER_H_
#define PLISSUESCENTER_H_

///////////////////////////////////////////////////////////////////////////////
#include <core/execution_issues/PLError.h>
#include <core/PLAutoPointer.h>

#include <core/collections/PL_core_fastStack.h>

///////////////////////////////////////////////////////////////////////////////
class PLIssuesCenter
{
private:
	PL_core_fastStack<strong_ref<PLError> > _stack;

public:
	PLIssuesCenter();
	virtual ~PLIssuesCenter();

	void pushError(func_in_ref<PLError> inError);
	func_out_ref<PLError> popError();

	static func_out_ref<PLIssuesCenter> sharedIssuesCenter();
};

///////////////////////////////////////////////////////////////////////////////
#endif /* PLISSUESCENTER_H_ */
