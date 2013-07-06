/*
 * PLIssuesCenter.cpp
 *
 *  Created on: 14.03.2013
 *      Author: semenyakinVS
 */
///////////////////////////////////////////////////////////////////////////////
#include "PLIssuesCenter.h"

///////////////////////////////////////////////////////////////////////////////
PLIssuesCenter::PLIssuesCenter()
{
	// TODO Auto-generated constructor stub

}

PLIssuesCenter::~PLIssuesCenter()
{
	// TODO Auto-generated destructor stub
}

///////////////////////////////////////////////////////////////////////////////
void PLIssuesCenter::pushError(func_in_ref<PLError> inError)
{
	_stack.push(inError);
}

func_out_ref<PLError> PLIssuesCenter::popError()
{
	return _stack.pop();
}

///////////////////////////////////////////////////////////////////////////////
strong_ref<PLIssuesCenter> sSharedIssuesCenter = NULL_REF(PLIssuesCenter);

func_out_ref<PLIssuesCenter> PLIssuesCenter::sharedIssuesCenter()
{
	if (sSharedIssuesCenter == NULL_REF(PLIssuesCenter))
	{
		sSharedIssuesCenter = new_ref<PLIssuesCenter>();
	}

	return sSharedIssuesCenter;
}
