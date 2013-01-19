/*
 * IPLInstaller.cpp
 *
 *  Created on: Nov 10, 2012
 *      Author: Admin
 */

///////////////////////////////////////////////////////////////////////////////
#include "PLInstaller.h"

///////////////////////////////////////////////////////////////////////////////
PLInstaller::PLInstaller()
{
}

PLInstaller::~PLInstaller()
{
}

///////////////////////////////////////////////////////////////////////////////
void *PLInstaller::pushStep(void *inStepObject)
{
	_steps.push(inStepObject);
}

void PLInstaller::init()
{
	// Do nothing in base implementation
}

///////////////////////////////////////////////////////////////////////////////
void *PLInstaller::nextStep()
{
	return _steps.pop();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
PLInstallerFabric *PLInstallerFabric::sharedInstallerFabric()
{
	static PLInstallerFabric *theFabric = NULL;
	if (NULL == theFabric)
	{
		theFabric = new PLInstallerFabric();
	}

	return theFabric;
}

///////////////////////////////////////////////////////////////////////////////
PLInstallerFabric::PLInstallerFabric()
	: _installer(NULL)
{
}

PLInstallerFabric::~PLInstallerFabric()
{
}

///////////////////////////////////////////////////////////////////////////////
void PLInstallerFabric::beginInstaller()
{
	// TODO: Add mechanism for deleting of the installer in it's currently exist
	// If there wouldn't be used auto pointer - use "if ( _installer != NULL)"
	_installer = new PLInstaller();
}

void *PLInstallerFabric::pushStep(void *inStepObject)
{
	_installer->pushStep(inStepObject);
}

PLInstaller *PLInstallerFabric::finishInstaller()
{
	PLInstaller *theInstaller = _installer;
	_installer = NULL;

	theInstaller->init();
	return theInstaller;
}
