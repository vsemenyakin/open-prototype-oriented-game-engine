/*
 * PLScopeBasedLog.cpp
 *
 *  Created on: Dec 12, 2012
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#include "PLScopeBasedLog.h"
#include <string>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
PLScopeBasedLog::PLScopeBasedLog()
	: _file("output_file.txt")
{
	__isEmptyLine = false;
}

PLScopeBasedLog::~PLScopeBasedLog()
{
}

///////////////////////////////////////////////////////////////////////////////
void PLScopeBasedLog::print(PLCharacter inCharacter)
{
	this->beginLine();
	std::cout << inCharacter;
	_file << inCharacter;
}

void PLScopeBasedLog::print(char inChar)
{
	this->beginLine();
	std::cout << inChar;
	_file << inChar;
}

void PLScopeBasedLog::print(PLCharacter *inString)
{
	this->beginLine();
	std::cout << inString;
	_file << inString;
}

void PLScopeBasedLog::print(const char *inString)
{
	this->beginLine();
	std::cout << inString;
	_file << inString;
}

void PLScopeBasedLog::print(int inInteger)
{
	this->beginLine();
	std::cout << inInteger;
	_file << inInteger;
}

void PLScopeBasedLog::print(const void *inPointer)
{
	this->beginLine();
	std::cout << inPointer;
	_file << inPointer;
}

///////////////////////////////////////////////////////////////////////////////
void PLScopeBasedLog::beingScope()
{
	this->endLine();
	this->print("{");
	__scopeDelta.append("\t");
	this->endLine();
}

void PLScopeBasedLog::endScope()
{
	if (__scopeDelta.size() != 0)
	{
		__scopeDelta.erase(__scopeDelta.size() - 1, 1);
		this->endLine();
		this->print("}");
		this->endLine();
	}
}

///////////////////////////////////////////////////////////////////////////////
PLScopeBasedLog *PLScopeBasedLog::sharedLog()
{
	static PLScopeBasedLog *sSharedLog = NULL;

	if (NULL == sSharedLog)
	{
		sSharedLog = new PLScopeBasedLog();
	}

	return sSharedLog;
}

///////////////////////////////////////////////////////////////////////////////
void PLScopeBasedLog::beginLine()
{
	if (__isEmptyLine == true)
	{
		std::cout << std::endl << __scopeDelta;
		_file << std::endl << __scopeDelta;

		__isEmptyLine = false;
	}
}

void PLScopeBasedLog::endLine()
{
	__isEmptyLine = true;
}
