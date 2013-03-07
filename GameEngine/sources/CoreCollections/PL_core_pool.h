/*
 * PL_core_pool.h
 *
 *  Created on: Nov 5, 2012
 *      Author: Admin
 */

///////////////////////////////////////////////////////////////////////////////
#ifndef PL_CORE_POOL_H_
#define PL_CORE_POOL_H_

///////////////////////////////////////////////////////////////////////////////
#include "../Base/PLCore.h"

#include <vector>
#include "PL_core_fastStack.h"

///////////////////////////////////////////////////////////////////////////////
typedef PLIndex PLPoolKey;

const PLPoolKey PLPoolNullKey = 0xFFFFFFFF; // TODO: Use integer max value here
const PLPoolKey PLPoolDefaultKey = 0;

///////////////////////////////////////////////////////////////////////////////
template <typename Type> class PL_core_pool;
typedef PL_core_pool<int> PLIndexGenerator;

///////////////////////////////////////////////////////////////////////////////
template <typename Type>
class PL_core_pool
{
public:

private:
	static const PLPoolKey PL_core_pool_block_size = 10;

	PLPoolKey lastObjectKey;
	PLPoolKey sizeKey;

	std::vector<Type> _vector;
	PL_core_fastStack<PLPoolKey> _freeKeys;

public:

	PL_core_pool()
		: lastObjectKey(0), sizeKey(PL_core_pool_block_size),
		  _vector(PL_core_pool_block_size), _freeKeys()
	{
	}

	virtual ~PL_core_pool()
	{

	}

	// TODO: Add method for setting initial method for object

	PLPoolKey createObject()
	{
		Type theObject;
		PLPoolKey theKey;

		if (0 == _freeKeys.size())
		{
			// If there are no free objects in pool - use last object
			++lastObjectKey;
			if (lastObjectKey >= sizeKey)
			{
				// If the pool is full - resize it
				for (PLPoolKey theIndex = 0; theKey < PL_core_pool_block_size;
						++theKey)
				{
					Type theResizingObject;
					_vector.push_back(theResizingObject);
				}
			}

			theKey = lastObjectKey;
		}
		else
		{
			theKey = _freeKeys.pop();
		}

		_vector[theKey] = theObject;
		return theKey;
	}

	// Content accessing
	Type objectForKey(PLPoolKey inKey)
	{
		// TODO: Add checking of the correct key
		return _vector[inKey];
	}

	void setObjectForKey(Type inObject, PLPoolKey &inKey)
	{
		_vector[inKey] = inObject;
	}

	//
	void removeObjectForKey(PLPoolKey &inKey)
	{
		_freeKeys.push(inKey);
	}
};

#endif /* PL_CORE_POOL_H_ */
