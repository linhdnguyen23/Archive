/*
 * sfarchiver.cpp
 *
 *  Created on: Feb 16, 2018
 *      Author: linh-nguyen
 */

#include "sfarchiver.h"
#include <iostream>
#include <map>
#include <cstdlib>

sfarchiver::sfarchiver() {
	// TODO Auto-generated constructor stub

}

sfarchiver::~sfarchiver() {
	// TODO Auto-generated destructor stub
}

void sfarchiver::add(std::string &anArchive, std::string &aFile){
	// check if archive exists
	// create
	std::cout << "add" << std::endl;
}

void sfarchiver::del(std::string &anArchive, std::string &aFile) {
	std::cout << "del" << std::endl;

}
void sfarchiver::list(std::string &anArchive) {
	std::cout << "list" << std::endl;

}
void sfarchiver::list(std::string &anArchive, std::string &aFile) {
	std::cout << "list" << std::endl;
}
void sfarchiver::find(std::string &anArchive, std::string &aFile) {
	std::cout << "find" << std::endl;

}
void sfarchiver::extract(std::string &anArchive, std::string &aFile) {
	std::cout << "extract" << std::endl;

}
void sfarchiver::version() {
	std::cout << "version" << std::endl;

}

int main(int argc, char *argv[]) {
	if(argc < 2) {
		std::cout << "You forgot to provide a command." << std::endl;
		std::cout << "Possible commands are add, del, find, extract, and version (or -v)." << std::endl;
		return 1;
	}

	std::string theCmd = argv[1];
	std::string theArchiveName = argv[2];
	std::string theFileName = argv[3];

	sfarchiver archiver;
	if("add" == theCmd) {
		if(4 == argc) {
			archiver.add(theArchiveName, theFileName);
		}
		else {
			std::cout << "You did not provide a valid argument." << std::endl;
		}
	}

	else if("del" == theCmd) {
		if(4 == argc) {
			archiver.del(theArchiveName, theFileName);
		}
		else {
			std::cout << "You did not provide a valid argument." << std::endl;
		}
	}

	else if("list" == theCmd || "l" == theCmd) {
		if(3 == argc) {
			archiver.list(theArchiveName);
		}
		else if(4 == argc) {
			archiver.list(theArchiveName, theFileName);
		}
		else {
			std::cout << "You did not provide a valid argument." << std::endl;
		}
	}

	else if("find" == theCmd) {
		if(4 == argc) {
			archiver.find(theArchiveName, theFileName);
		}
		else {
			std::cout << "You did not provide a valid argument." << std::endl;
		}
	}

	else if("extract" == theCmd) {
		if(4 == argc) {
			archiver.extract(theArchiveName, theFileName);
		}
		else {
			std::cout << "You did not provide a valid argument." << std::endl;
		}
	}

	else if("version" == theCmd || "v" == theCmd) {
		archiver.version();
	}

	else {
		std::cout << "You did not provide a valid command" << std::endl;
		return 1;
	}
	return 0;
}
