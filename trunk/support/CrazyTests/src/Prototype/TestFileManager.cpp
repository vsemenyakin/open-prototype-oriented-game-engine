/*
 * TestFileManager.cpp
 *
 *  Created on: 17.03.2013
 *      Author: BRONY
 */
#include "TestFileManager.h"
#include "FileManager.h"
#include <iostream>

namespace Prototype {

void FileManagerTest(){
	FileManager fm;
	std::cout<<"					FileManager (Directory) test for Windows"<< std::endl;
	std::cout<< std::endl;
	std::cout<<"Function"<<" | "
			 <<"path"<<" | "
			 <<"isDirectory flags"<<" | "
			 <<"should return"<<" | "
			 <<"Function Return"<<" | "
			 << std::endl;
	std::cout<<"------------------------------------------------------------------------"<< std::endl;
	std::cout<<"fileExistsAtPath"<<" | "
			 <<"C:\\Windows "<<" | "
			 <<""<<" | "
			 <<"True(1)"<<" | "
			 <<fm.fileExistsAtPath("C:\\Windows")<<" | "
			 <<std::endl;
	std::cout<<"------------------------------------------------------------------------"<< std::endl;
	std::cout<<"fileExistsAtPathisDirectory"<<" | "
			 <<"C:\\Windows"<<" | "
			 <<"true"<<" | "
			 <<"True(1)"<<" | "
			 <<fm.fileExistsAtPathisDirectory("C:\\Windows",true)<<" | "
			 <<std::endl;
	std::cout<<"------------------------------------------------------------------------"<< std::endl;
	std::cout<<"fileExistsAtPathisDirectory"<<" | "
			 <<"C:\\Windows"<<" | "
			 <<"false"<<" | "
			 <<"False(0)"<<" | "
			 <<fm.fileExistsAtPathisDirectory("C:\\Windows",false)<<" | "
			 <<std::endl;
	std::cout<<"------------------------------------------------------------------------"<< std::endl;
	std::cout<<"fileExistsAtPath"<<" | "
			 <<"C:\\qawsedrftg"<<" | "
			 <<""<<" | "
			 <<"False(0)"<<" | "
			 <<fm.fileExistsAtPath("C:\\qawsedrftg")<<" | "
			 <<std::endl;
	std::cout<<"------------------------------------------------------------------------"<< std::endl;
	std::cout<<"fileExistsAtPathisDirectory"<<" | "
			 <<"C:\\qawsedrftg"<<" | "
			 <<"true"<<" | "
			 <<"False(0)"<<" | "
			 <<fm.fileExistsAtPathisDirectory("C:\\qawsedrftg",true)<<" | "
			 <<std::endl;
	std::cout<<"------------------------------------------------------------------------"<< std::endl;
	std::cout<<"fileExistsAtPathisDirectory"<<" | "
			 <<"C:\\qawsedrftg"<<" | "
			 <<"false"<<" | "
			 <<"False(0)"<<" | "
			 <<fm.fileExistsAtPathisDirectory("C:\\qawsedrftg",false)<<" | "
			 <<std::endl;
	std::cout<<"------------------------------------------------------------------------"<< std::endl;
	std::cout<< std::endl;
	std::cout<<"					FileManager (Files) test for Windows"<< std::endl;
		std::cout<< std::endl;
		std::cout<<"Function"<<" | "
				 <<"path"<<" | "
				 <<"isDirectory flags"<<" | "
				 <<"should return"<<" | "
				 <<"Function Return"<<" | "
				 << std::endl;
		std::cout<<"------------------------------------------------------------------------"<< std::endl;
		std::cout<<"fileExistsAtPath"<<" | "
				 <<"C:\\Windows\\System32\\drivers\\etc\\hosts"<<" | "
				 <<""<<" | "
				 <<"True(1)"<<" | "
				 <<fm.fileExistsAtPath("C:\\Windows\\System32\\drivers\\etc\\hosts")<<" | "
				 <<std::endl;
		std::cout<<"------------------------------------------------------------------------"<< std::endl;
		std::cout<<"fileExistsAtPathisDirectory"<<" | "
				 <<"C:\\Windows\\System32\\drivers\\etc\\hosts"<<" | "
				 <<"true"<<" | "
				 <<"false(0)"<<" | "
				 <<fm.fileExistsAtPathisDirectory("C:\\Windows\\System32\\drivers\\etc\\hosts",true)<<" | "
				 <<std::endl;
		std::cout<<"------------------------------------------------------------------------"<< std::endl;
		std::cout<<"fileExistsAtPathisDirectory"<<" | "
				 <<"C:\\Windows\\System32\\drivers\\etc\\hosts"<<" | "
				 <<"false"<<" | "
				 <<"True(1)"<<" | "
				 <<fm.fileExistsAtPathisDirectory("C:\\Windows\\System32\\drivers\\etc\\hosts",false)<<" | "
				 <<std::endl;
		std::cout<<"------------------------------------------------------------------------"<< std::endl;
		std::cout<<"fileExistsAtPath"<<" | "
				 <<"C:\\Windows\\System32\\drivers\\etc\\hosts1"<<" | "
				 <<""<<" | "
				 <<"False(0)"<<" | "
				 <<fm.fileExistsAtPath("C:\\Windows\\System32\\drivers\\etc\\hosts1")<<" | "
				 <<std::endl;
		std::cout<<"------------------------------------------------------------------------"<< std::endl;
		std::cout<<"fileExistsAtPathisDirectory"<<" | "
				 <<"C:\\Windows\\System32\\drivers\\etc\\hosts1"<<" | "
				 <<"true"<<" | "
				 <<"False(0)"<<" | "
				 <<fm.fileExistsAtPathisDirectory("C:\\Windows\\System32\\drivers\\etc\\hosts1",true)<<" | "
				 <<std::endl;
		std::cout<<"------------------------------------------------------------------------"<< std::endl;
		std::cout<<"fileExistsAtPathisDirectory"<<" | "
				 <<"C:\\Windows\\System32\\drivers\\etc\\hosts1"<<" | "
				 <<"false"<<" | "
				 <<"False(0)"<<" | "
				 <<fm.fileExistsAtPathisDirectory("C:\\Windows\\System32\\drivers\\etc\\hosts1",false)<<" | "
				 <<std::endl;
		std::cout<<"------------------------------------------------------------------------"<< std::endl;
}
}
