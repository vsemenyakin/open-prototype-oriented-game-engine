#include "PLLog.h"

#include <iostream>

#define SEPORATOR "	"

//////////////////////////////////////////////////////
PLLog::PLLog()
{
}

PLLog::~PLLog()
{
}

//////////////////////////////////////////////////////
void PLLog::beginGroup()
{
	theString->append(SEPORATOR);
}

void PLLog::endGroup()
{

}
