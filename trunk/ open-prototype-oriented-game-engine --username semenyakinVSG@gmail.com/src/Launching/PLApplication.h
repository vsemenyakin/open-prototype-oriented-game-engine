///////////////////////////////////////////////////////////////////////////////
#ifndef PLAPPLICATION_H_
#define PLAPPLICATION_H_

///////////////////////////////////////////////////////////////////////////////
class PLError;

///////////////////////////////////////////////////////////////////////////////
class PLApplication {
public:
	PLApplication();

	virtual PLError *start();

	virtual ~PLApplication();
};

#endif /* PLAPPLICATION_H_ */