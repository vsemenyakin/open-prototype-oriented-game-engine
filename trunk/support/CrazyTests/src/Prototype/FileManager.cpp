/*
 * FileManager.cpp
 *
 *  Created on: 16.03.2013
 *      Author: BRONY
 */
#include "FileManager.h"
#include <fstream>
#include  <io.h>



namespace Prototype {



FileManager::FileManager() {
	// TODO Auto-generated constructor stub
}

FileManager::~FileManager() {
	// TODO Auto-generated destructor stub
}



	bool FileManager::fileExistsAtPath(const char *path){
		if( (access( path, 0 )) != -1 ){
			return true;
		}
		else{
			return false;
		}
	}

	bool FileManager::fileExistsAtPathisDirectory (const char *path, bool isDirectory){

		if(isDirectory==true){
			if( std::ifstream(path) != NULL){
				return false;
			}
			else{
				if( (access( path, 0 )) != -1 ){
					return true;
				}
				else{
					return false;
				}
			}
		}
		else{
			return std::ifstream(path) != NULL;
		}
	}
}
