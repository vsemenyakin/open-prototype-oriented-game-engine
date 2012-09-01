///////////////////////////////////////////////////////////////////////////////
#ifndef PLEXCEPTION_H_
#define PLEXCEPTION_H_

#include <exception>

///////////////////////////////////////////////////////////////////////////////
class PLException : public std::exception
{
private:
	const char *message;
	int lineNumber;
	const char *fileName;

public:
	PLException(const char *inMessage, int inLineNumber,
			const char *inFileName) throw();
	virtual ~PLException() throw();

	virtual const char *what() const throw();
};

#define PL_EXCEPTION(message) PLException(message, __LINE__, __FILE__)

#endif /* PLEXCEPTION_H_ */
