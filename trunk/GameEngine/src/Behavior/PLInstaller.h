/*
 * IPLInstaller.h
 *
 *  Created on: Nov 10, 2012
 *      Author: Admin
 */

#ifndef IPLINSTALLER_H_
#define IPLINSTALLER_H_

///////////////////////////////////////////////////////////////////////////////
#include "../CoreCollections/PL_core_fastQueue.h"

///////////////////////////////////////////////////////////////////////////////
class PLInstallerFabric;

///////////////////////////////////////////////////////////////////////////////
class PLInstaller
{
private:
	PL_core_fastQueue<void *> _steps;

	// Private creation methods
	virtual void *pushStep(void *inStepObject);
	virtual void init();

public:
	PLInstaller();
	virtual ~PLInstaller();

	virtual void *nextStep();

	// Friends
	friend class PLInstallerFabric;
};

///////////////////////////////////////////////////////////////////////////////
class PLInstallerFabric
{
private:
	// Fields
	PLInstaller *_installer;

	// Hidden memory management for singletone
	PLInstallerFabric();
	virtual ~PLInstallerFabric();

public:
	static PLInstallerFabric *sharedInstallerFabric();

	virtual void beginInstaller();
	virtual void *pushStep(void *inStepObject);
	virtual PLInstaller *finishInstaller();
};

#endif /* IPLINSTALLER_H_ */
