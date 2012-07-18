///////////////////////////////////////////////////////////////////////////////
#ifndef RROBJECT_H_
#define RROBJECT_H_

///////////////////////////////////////////////////////////////////////////////
class PLObject {
private:

	int referenceCount;

public:
	PLObject *retain();
	void release();
	void autorelease();

	virtual void destroy();

	virtual ~PLObject();
	PLObject();
};

#endif /* RROBJECT_H_ */
