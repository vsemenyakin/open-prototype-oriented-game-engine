/*
 * IPLLogReceiver.h
 *
 *  Created on: 30 ρεπο. 2012
 *      Author: ShareDVI
 */

#ifndef IPLLOGRECEIVER_H_
#define IPLLOGRECEIVER_H_

#include "../PLString.h"
class IPLLogReceiver {
public:
		virtual ~IPLLogReceiver() {};
		virtual void print(const char *inMessage, const char* errorlevel, const char* channel) = 0;
		virtual void print(const PLString *inMessage, const char* errorlevel, const char* channel) = 0;
		virtual bool accepts(const char* errorlevel, const char* channel) = 0;
};
#endif /* IPLLOGRECEIVER_H_ */

