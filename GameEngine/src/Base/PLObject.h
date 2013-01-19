///////////////////////////////////////////////////////////////////////////////
#ifndef RROBJECT_H_
#define RROBJECT_H_

///////////////////////////////////////////////////////////////////////////////
class PLString;
class PLReflectionDictionary;

class PLObject
{
private:
	PLReflectionDictionary *_reflections;

public:
	virtual ~PLObject();
	PLObject();

	virtual PLString *description();
	virtual PLReflectionDictionary *reflections();
};

#endif /* RROBJECT_H_ */
