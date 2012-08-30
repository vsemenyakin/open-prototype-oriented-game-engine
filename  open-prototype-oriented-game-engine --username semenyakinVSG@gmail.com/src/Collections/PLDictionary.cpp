#include "PLDictionary.h"

///////////////////////////////////////////////////////////////////////////////
PLDictionary::PLDictionary(void)
{
	dictionary = new std::map<PLString, PLObject*>;
}

PLDictionary::~PLDictionary(void)
{
	delete dictionary;
}

///////////////////////////////////////////////////////////////////////////////
void PLDictionary::addKeyAndObject(const PLString* key, PLObject* object)
{
	(*dictionary)[*key]=object;
}

void PLDictionary::removeObjectWithKey(const PLString* key)
{
	if (hasObjectWithKey(key))
	{
		dictionary->erase(*key);
	}
}
PLIndex PLDictionary::count()
{
	return dictionary->size();
}

PLObject* PLDictionary::objectForKey(const PLString* key)
{
	return dictionary->find(*key)->second;
}

PLBOOL PLDictionary::hasObjectWithKey(const PLString* key)
{
	return dictionary->count(*key) != 0;
}

///////////////////////////////////////////////////////////////////////////////
