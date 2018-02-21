/*
 * sfarchiver.h
 *
 *  Created on: Feb 16, 2018
 *      Author: linh-nguyen
 */

#ifndef SFARCHIVER_H_
#define SFARCHIVER_H_
#include <iostream>

class sfarchiver {
public:
	sfarchiver();
	virtual ~sfarchiver();
	void add(std::string &anArchive, std::string &aFile);
	void del(std::string &anArchive, std::string &aFile);
	void list(std::string &anArchive);
	void list(std::string &anArchive, std::string &aFile);
	void find(std::string &anArchive, std::string &aFile);
	void extract(std::string &anArchive, std::string &aFile);
	void version();
	int main(int argc, char *argv[]);
};

#endif /* SFARCHIVER_H_ */
