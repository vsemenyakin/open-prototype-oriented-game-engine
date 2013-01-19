#pragma once

///////////////////////////////////////////////////////////////////////////////
#include "../Base/PLCore.h"
#include <map>

///////////////////////////////////////////////////////////////////////////////
class PLDictionary: public PLObject
{
private:
	std::map<PLString, PLObject*> *dictionary;
public:
	PLDictionary(void);
	~PLDictionary(void);

	void setObjectForKey(PLObject* object, PLString* key);
	PLObject* objectForKey(const PLString* key);
	void removeObjectWithKey(const PLString* key);
	PLIndex count(void);
	PLBOOL hasObjectWithKey(const PLString * key);
};

