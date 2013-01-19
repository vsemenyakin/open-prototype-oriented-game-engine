/*
 * IPLReflective.h
 *
 *  Created on: 13.10.2012
 *      Author: Сергей
 */

#ifndef IPLREFLECTIVE_H_
#define IPLREFLECTIVE_H_

#include "PLReflectionDictionary.h"

class IPLReflective
{
public:
	virtual PLReflectionDictionary *reflections() = 0;
};

#endif /* IPLREFLECTIVE_H_ */
