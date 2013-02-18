/*
 * TEST_PLWindow.cpp
 *
 *  Created on: Feb 13, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#include "TEST_PLWindow.h"

#include "../../OSDepended/Interface/PLGraphic.h"

///////////////////////////////////////////////////////////////////////////////
TEST_PLWindow::TEST_PLWindow()
{
}

TEST_PLWindow::~TEST_PLWindow()
{

}

///////////////////////////////////////////////////////////////////////////////
void TEST_PLWindow::performTest()
{
	PLWindow *theWindow = new PLWindow("Test window",
			PLCreateRectangle(100.0, 100.0, 300.0, 300.0));

	theWindow->show();
	theWindow->setFocus();
}
