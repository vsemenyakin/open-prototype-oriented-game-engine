/*
 * PLScopeBasedLog.h
 *
 *  Created on: Dec 12, 2012
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef PLSCOPEBASEDLOG_H_
#define PLSCOPEBASEDLOG_H_

///////////////////////////////////////////////////////////////////////////////
#include <string>
#include <fstream>

#include <core/PLTypes.h>

///////////////////////////////////////////////////////////////////////////////
class PLScopeBasedLog
{
private:
	std::ofstream _file;

	std::string __scopeDelta;
	bool __isEmptyLine;

	void beginLine();

public:

	//
	PLScopeBasedLog();
	virtual ~PLScopeBasedLog();

	//
	void print(PLCharacter inCharacter);
	void print(PLCharacter *inString);
	void print(int inInteger);
	void print(const void *inPointer);

	//
	void endLine();
	void beingScope();
	void endScope();

	// Static methods
	static PLScopeBasedLog *sharedLog();
};

#endif /* PLSCOPEBASEDLOG_H_ */
