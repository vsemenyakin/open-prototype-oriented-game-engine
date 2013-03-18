/*
 * FileManager.h
 *
 *  Created on: 16.03.2013
 *      Author: BRONY
 */

#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

#include <string>

namespace Prototype {

class FileManager {
public:
	FileManager();
	virtual ~FileManager();
	bool fileExistsAtPath (const char *path);
	bool fileExistsAtPathisDirectory (const char *path, bool isDirectory);
};

} /* namespace Prototype */
#endif /* FILEMANAGER_H_ */
