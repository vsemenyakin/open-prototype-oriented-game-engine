#ifndef PLCALLBACKDICTIONARY_H_
#define PLCALLBACKDICTIONARY_H_

///////////////////////////////////////////////////////////////////////////////
#include "../../Base/PLCore.h"
#include "PLReflection.h"
#include <map>

///////////////////////////////////////////////////////////////////////////////
class PLReflectionDictionary
{
private:
	std::map<PLString, PLReflection *> reflections;

public:
	PLReflectionDictionary();
	virtual ~PLReflectionDictionary();

	void setReflectionForName(PLReflection *inReflection, PLString *inName);
	PLReflection *reflectionForName(PLString *inName);
};

#endif /* PLCALLBACKDICTIONARY_H_ */
