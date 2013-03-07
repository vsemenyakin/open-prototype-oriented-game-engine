/*
 * PLShader.cpp
 *
 *  Created on: 23.02.2013
 *      Author: semenyakinVS
 */
///////////////////////////////////////////////////////////////////////////////
#include "PLShader.h"

#include <iostream>

///////////////////////////////////////////////////////////////////////////////
static int sShaderTypeMapping[] = { GL_FRAGMENT_SHADER, GL_VERTEX_SHADER };

///////////////////////////////////////////////////////////////////////////////
PLShader::PLShader()
	: _shaderObjectHandles(), _shaderProgramHandle(0)
{
}

PLShader::~PLShader()
{
}

///////////////////////////////////////////////////////////////////////////////
void PLShader::attachShader(shaderType inShaderType, const char *inSourceCode)
{
	// Create shader object
	GLuint theShaderObjectHandle =
			glCreateShader(sShaderTypeMapping[inShaderType]);

	if (0 == theShaderObjectHandle)
	{
		// TODO: Return an error for problems in shader creation
		std::cout << "Error while creating the shader" << std::endl;
	}

	// Copy source code into shader object and compile it
	glShaderSource(theShaderObjectHandle, 1, (const GLchar **)&inSourceCode,
			NULL);

	glCompileShader(theShaderObjectHandle);

	// Verify the compilation status
	GLint theCompilationResultStatus = GL_FALSE;

	glGetShaderiv(theShaderObjectHandle, GL_COMPILE_STATUS,
			&theCompilationResultStatus);

	if (GL_FALSE == theCompilationResultStatus)
	{
		// TODO: There was an error while compiling -
		//  return information about it
		std::cout << "Compiler error..." << std::endl;

		GLint theCompileLogLength = 0;
		glGetShaderiv(theShaderObjectHandle, GL_INFO_LOG_LENGTH,
				&theCompileLogLength);

		if (theCompileLogLength > 0)
		{
			GLchar *theCompileLog = new GLchar[theCompileLogLength];

			GLsizei theWrittenCharactersCount = 0;
			glGetShaderInfoLog(theShaderObjectHandle, theCompileLogLength,
					&theWrittenCharactersCount, theCompileLog);

			// TODO: Create compiling log
			std::cout << theCompileLog << std::endl;

			delete[] theCompileLog;
		}
	}
	else
	{
		// If the shader was compiled successfully
		_shaderObjectHandles.push_back(theShaderObjectHandle);
	}
}

void PLShader::link()
{
	// Create the program
	_shaderProgramHandle = glCreateProgram();
	if (0 == _shaderProgramHandle)
	{
		// TODO: Return error status on creation program
	}

	std::list<GLuint>::iterator theIterator = _shaderObjectHandles.begin();
	for (; theIterator != _shaderObjectHandles.end(); ++theIterator)
	{
		glAttachShader(_shaderProgramHandle, *theIterator);
	}

	// Link program
	glLinkProgram(_shaderProgramHandle);

	// Verify the link status
	GLint theStatus = 0;

	glGetProgramiv(_shaderProgramHandle, GL_LINK_STATUS, &theStatus);
	if (GL_FALSE == theStatus)
	{
		// TODO: There was an error while linking - return information about it
		std::cout << "Linker error" << std::endl;

		GLint theCompileLogLength = 0;

		glGetProgramiv(_shaderProgramHandle, GL_INFO_LOG_LENGTH,
				&theCompileLogLength);

		if (theCompileLogLength > 0)
		{
			char *theLog = (char *)new char[theCompileLogLength];
			GLsizei theWritten = 0;
			glGetProgramInfoLog(_shaderProgramHandle, theCompileLogLength,
					&theWritten, theLog);

			// TODO: Save linking log
			std::cout << theLog << std::endl;

			delete[] theLog;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
GLuint PLShader::handler()
{
	return _shaderProgramHandle;
}
