/*
 * PLLogger.h
 *
 *  Created on: 30 ρεπο. 2012
 *      Author: ShareDVI
 */

#ifndef PLLOGGER_H_
#define PLLOGGER_H_

#include "PLLog.h"

class PLLogger : IPLLogReceiver {
public:
	PLLogger();
	virtual ~PLLogger();
	virtual bool accepts(const char* errorlevel, const char* channel);
private:
	set<IPLLogReceiver*> logs;
};

#endif /* PLLOGGER_H_ */
