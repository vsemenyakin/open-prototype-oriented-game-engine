///////////////////////////////////////////////////////////////////////////////
#ifndef PLAPPLICATION_H_
#define PLAPPLICATION_H_

///////////////////////////////////////////////////////////////////////////////
class PLError;

///////////////////////////////////////////////////////////////////////////////
class PLApplication {
public:
	PLApplication();
	virtual ~PLApplication();

	virtual PLError *start();
};

#endif /* PLAPPLICATION_H_ */
