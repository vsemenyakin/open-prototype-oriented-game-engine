/*
 * PLCore.h
 *
 *  Created on: 01.01.2002
 *      Author: 422
 */

#ifndef PLCORE_H_
#define PLCORE_H_

#include "PLAutoPointer.h"
#include "PLObject.h"
#include "PLScalarTypes.h"
#include "PLString.h"

#define CLASS_WITH_REF(name) \
	class name;	\
	typedef PLAutoPointer<name> name##Ref; \
	class name

/*
template<typename ElementType> class PLIterator;
template <typename ItemType>
class PLRoundList
*/

#define TEMPLATE_CLASS_WITH_REF(name, itemTypeName) \
	template<typename ElementType> class name;	\
	typedef PLAutoPointer<name<ElementType> > name##Ref; \
	template <typename itemTypeName> class name


#endif /* PLCORE_H_ */
