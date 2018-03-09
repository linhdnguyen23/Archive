/*
 * SFArchive.cpp
 *
 *  Created on: Mar 1, 2018
 *      Author: linh-nguyen
 */

 /**
  * Given an input file:
  *   1) Open the file (do not create yet if it doesn't exist)
  *       1.1) If file exists, read the header to containedData member variable.
  *       1.2) If file is already open, return an error saying that file cannot
  *            be opened.
  *   2) Prepare compression stream if flag has been set. (otherwise store)
  *   Linh
  **/
#include <fstream>
#include "SFArchive.hpp"
#include "Compression.hpp"
#include <stdexcept>
#include <algorithm>
#include <ctime>

#define BLOCK_SIZE 4096
#define HEADER_SIZE 500
/*

SFArchive::SFArchive(const std::string& aFile, const bool tCompFlag = false) {
	SFBlock tempBlock = firstBlocks[aFile];

}
*/


/*Huang Lin's version of add file 

  Not 100% finished yet

*/

bool SFArchive::addFile(const std::string& aFile) throw(){

	// Calculate the file size;
	std::streampos begin, end;
	std::ifstream myfile(aFile, std::ios::binary | std::ios::in);
	begin = myfile.tellg();
	myfile.seekg(0, std::ios::end);
	end = myfile.tellg();
	int fileSize = end - begin;
	int fileSizeWHeader = fileSize + HEADER_SIZE;
	myfile.close();


	// Set the isText depending on file extensions
	bool isText = false;
	std::string extension = aFile.substr(aFile.find_last_of(".") + 1);
	if(extension == "txt" || extension == "odt" || extension == "doc"
			|| extension == "docx" || extension == "pdf" || extension == "rtf"
					|| extension == "tex" || extension == "wks" || extension == "wps"
							|| extension == "wpd") {
		isText = true;
	}

	time_t rawTime;
	time(&rawTime);
	std::string date = asctime(localtime(&rawTime));

	// 4000 or 4096? (Linh) Also define these numbers as constants
	int numOfBlocks = (fileSizeWHeader/ BLOCK_SIZE) + 1;
	int spaceLeft = fileSize % 4000;

	/*
	int spaceLeft = fileSizeWHeader - numOfBlocks * BLOCK_SIZE;
	 */

	int count=0;
	SFBlock headBlock(aFile,date, count++, 1, isText);
	// I got a redeclaration of myfile error, so I'm commenting it out (Linh)
	//std::ifstream myfile(aFile, std::ios::binary | std::ios::in);

	std::ofstream outputfile;
	// The new file is append to the archive.dat file, added std::ios::ate (Linh)
	outputfile.open("archive.dat", std::ios::binary | std::ios::out | std::ios::ate);

	//Writing the starting block to the Dat file.
	char buffer[BLOCK_SIZE];
	myfile.read(buffer, BLOCK_SIZE);
	if (!myfile) {
		outputfile.write(aFile.c_str(),HEADER_SIZE);
		outputfile.write(buffer, BLOCK_SIZE);
	}

	// we don't need this if we're just going to divide archivePos by (BLOCK_SIZE + HEADER_SIZE)
	// a few lines later. Instead use line below (Linh)
	// archivePos++;
	archivePos += 4500;

	// update map and vector
	firstBlocks[aFile] = archivePos / (BLOCK_SIZE + HEADER_SIZE);
	// Instead of this, use  (Linh)
	//firstBlocks[aFile] = archivePos;

	archiveBlocks.push_back(headBlock);

	SFBlock *tail = &headBlock;


	//for (int i = 1; i < fileSize; i++){
	// We're iterating over the num of blocks not fileSize (Linh) change to
	for (int i = 1; i < numOfBlocks; i++) {
		SFBlock newBlock (aFile, date, count++, archivePos, isText);
		//tail->getNextPiece() = &newBlock;
		// we go to current block pointed to by the tail, get next piece (which returns
		// a pointer so dereference it) and set to the
		// new block (Linh)
		newBlock = *(tail->getNextPiece());

		tail = &newBlock;

		archiveBlocks.push_back(newBlock);

		char buffer[BLOCK_SIZE];
		// Is there any partitioned between read and unread so the program will only
		// get the index of the unread part and read from there
		myfile.read(buffer, BLOCK_SIZE);


		if (!myfile) {
			outputfile.write(aFile.c_str(), HEADER_SIZE);
			outputfile.write(buffer, BLOCK_SIZE);
		}
	}

	myfile.close();
	outputfile.close();
	return true;
}



/** listFiles   Huang Lin
* Description: Lists all of the files present in the currently opened archive.
*
* Arguments: None.isText
*
* Returns: None.
*
* Effects: Prints out statements using the overloaded << operator below. The
*          desired formatting can be seen either in that description or in the
*          README.
**/

void SFArchive::listFiles() const {
	
	std::cout <<"filename         size          date-added" << std::endl;
	for (auto it : firstBlocks){
		size_t index = it.second;
		SFBlock tempSFblock = archiveBlocks.at(index);
		//std::cout << it.first<<"       "<<tempSFblock.getFileSize()<<"        "<<tempSFblock.getDate <<std::endl;
	}
};

/** listFiles  Huang Lin
* Description: Lists a subset of the files present in the currently opened
*              archive by a given string.
*
* Arguments: tString - the substring to check for within all filenames
*
* Returns: None.
*
* Effects: Prints out statements using the overloaded << operator below like
*          above.
**/

void SFArchive::listFiles(const std::string& tString) const{
	std::cout << "filename         size          date-added" << std::endl;
	for (auto it : firstBlocks){
		std::string tempString = it.first;
		if (tempString.find(tString) != std::string::npos){
			size_t index = it.second;
			SFBlock tempSFblock = archiveBlocks.at(index);
			//std::cout << it.first << "       " << tempSFblock.getFileSize()<< "        " << tempSFblock.getDate << std::endl;
		}
	}
};

bool SFArchive::fileDoesExist(const std::string& aFile) {
	return std::find(archiveBlocks.begin(), archiveBlocks.end(), aFile) != archiveBlocks.end();
}

