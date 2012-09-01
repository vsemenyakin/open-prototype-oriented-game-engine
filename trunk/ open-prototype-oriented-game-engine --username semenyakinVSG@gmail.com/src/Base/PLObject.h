///////////////////////////////////////////////////////////////////////////////
#ifndef RROBJECT_H_
#define RROBJECT_H_

///////////////////////////////////////////////////////////////////////////////
class PLString;

class PLObject {
private:
	int referenceCount;

protected:
	virtual void destroy();

public:

	virtual ~PLObject();
	PLObject();

	// Memory
	PLObject *retain();
	void release();
	void autorelease();
};

#endif /* RROBJECT_H_ */
