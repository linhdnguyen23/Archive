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
#include <iostream>
#include <string>


#define BLOCK_SIZE 4000
#define HEADER_SIZE 500
#define BLOCK_SIZE_WITH_HEADER 4500

/*
SFArchive::SFArchive(const std::string& aFile, const bool aCompFlag = false) throw() {
	
	
}*/

/**
* fileDoesExist
* Description: Check if file exists in the archive
* Arguments: aFile - the file to look for in the archive
* Returns: true - if the file exists; false - otherwise
*/
bool SFArchive::fileDoesExist(const std::string& aFile) {
	
	if (firstBlocks.find(aFile) == firstBlocks.end()){
		return false;
	}

	   return true;
}

/** addFile  Linh
* Description: Adds a named file to the archive. If the file does not exist,
*              then report a failure through the return. Note that compression
*              will clearly play a role here.
*
* Arguments: tFile - the file to be placed into the archive
*
* Returns: true - if the file add succeeded; false - otherwise
**/
bool SFArchive::addFile(const std::string& aFile) throw(){

	// Calculate the file size;
	std::streampos begin, end;
	std::ifstream myfile(aFile, std::ios::binary | std::ios::in);
	begin = myfile.tellg();
	myfile.seekg(0, std::ios::end);
	end = myfile.tellg();
	int fileSize = end - begin;
	myfile.close();


	// Set the isText depending on file extensions
	bool isText = false;
	std::string extension = aFile.substr(aFile.find_last_of(".") + 1);
	if (extension == "txt") {
		isText = true;
	}

	time_t rawTime;
	time(&rawTime);
	std::string date = asctime(localtime(&rawTime));

	// 4000 or 4096? (Linh) Also define these numbers as constants
	int numOfBlocks = (fileSize / BLOCK_SIZE);
	int spaceLeft = BLOCK_SIZE - fileSize % BLOCK_SIZE;

	int count = 0;
	SFBlock headBlock(aFile, date, archivePos, count, isText);
	// I got a redeclaration of myfile error, so I'm commenting it out (Linh)
	//std::ifstream myfile(aFile, std::ios::binary | std::ios::in);

	std::fstream outputfile;
	// The new file is append to the archive.dat file, added std::ios::ate (Linh)
	outputfile.open("archive.dat", std::ios::binary |  std::ios::app);

	//Writing the starting block to the Dat file.
	char buffer[BLOCK_SIZE];

	myfile.read(buffer, BLOCK_SIZE);
	char headerBuf[HEADER_SIZE];
	strcpy(headerBuf, aFile.c_str());
	strcat(headerBuf, std::string(";").c_str());
	strcat(headerBuf, date.c_str());
	strcat(headerBuf, std::string(";").c_str());
	strcat(headerBuf, std::to_string(archivePos).c_str());
	strcat(headerBuf, std::string(";").c_str());
	strcat(headerBuf, std::to_string(count++).c_str());
	strcat(headerBuf, std::string(";").c_str());
	strcat(headerBuf, std::to_string(isText).c_str());
	strcat(headerBuf, std::string(";").c_str());



	if (!myfile) {
		outputfile.write(headerBuf, HEADER_SIZE);
		outputfile.write(buffer, BLOCK_SIZE);
	}

	// we don't need this if we're just going to divide archivePos by (BLOCK_SIZE + HEADER_SIZE)
	// a few lines later. Instead use line below (Linh)
	// archivePos++;

	// update map and vector
	firstBlocks[aFile] = archivePos++;
	// Instead of this, use  (Linh)
	//firstBlocks[aFile] = archivePos;

	archiveBlocks.push_back(headBlock);

	SFBlock *tail = &headBlock;


	//for (int i = 1; i < fileSize; i++){
	// We're iterating over the num of blocks not fileSize (Linh) change to
	for (int i = 1; i < numOfBlocks; i++) {
		  SFBlock newBlock(aFile, date, archivePos,count++ , isText);
		  SFBlock* blockPtr = &newBlock;
		  *tail->getNextPiece()= *blockPtr;
		// *(tail)->getNextPiece() = &newBlock;
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

			headerBuf[HEADER_SIZE];
			strcpy(headerBuf, aFile.c_str());
			strcat(headerBuf, std::string(";").c_str());
			strcat(headerBuf, date.c_str());
			strcat(headerBuf, std::string(";").c_str());
			strcat(headerBuf, std::to_string(archivePos).c_str());
			strcat(headerBuf, std::string(";").c_str());
			strcat(headerBuf, std::to_string(count++).c_str());
			strcat(headerBuf, std::string(";").c_str());
			strcat(headerBuf, std::to_string(isText).c_str());
			strcat(headerBuf, std::string(";").c_str());


			outputfile.write(buffer, BLOCK_SIZE);
		}
	}

	myfile.close();
	outputfile.close();
	return true;
}

bool SFArchive::deleteFile(const std::string& aFile) throw(){

	int index = firstBlocks[aFile];
	firstBlocks.erase(aFile);
	

	SFBlock headBlock = archiveBlocks.at(index);

	while (headBlock.getNextPiece() != nullptr){

		
	}
	//Not Finished Yet





}

bool SFArchive::extractFile(const::std::string& tString) const
{
    std::fstream extractedfile("extractedfile.txt", std::ios::in | std::ios::binary);
    std::fstream archivefile("archive.txt", std::ios::in | std::ios::binary);
    int location = firstBlocks[tString];
    SFBlock* head = archiveBlocks[location];
    while (head!=nullptr)
    {
        int pos = head->blockPos;
        archivefile.seekg(pos * 4100);
        char buffer[4000];
        if(head->getNextPiece()->nullptr)
        {
            archivefile.read(buffer,head-> fileSize % BLOCK_SIZE);
            extractedfile.write(buffer,head-> fileSize % BLOCK_SIZE);
            head = head -> getNextPiece();
        }
        else
        {
            archivefile.read(buffer,3900);
            extractedfile.write(buffer,3900);
            head = head -> getNextPiece();
        }
    }
    extractedfile.close();
    archivefile.close();
    return true;
}
void printVersionInfo(void) const
{
    std::cout<<"Version Number:"<<VERSION_NUM<<std::endl<<"Information:"<<info<<std::endl;
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

void SFArchive::listFiles() const{
	
	std::cout <<"filename         size          date-added" << std::endl;
	for (auto it : firstBlocks){
		size_t index = it.second;
		SFBlock tempSFblock = archiveBlocks.at(index);
		std::cout << it.first<<"       "<<tempSFblock.getFileSize<<"        "<<tempSFblock.getDate <<std::endl;
	}
};

/** listFiles
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
			std::cout << it.first << "       " << tempSFblock.getFileSize << "        " << tempSFblock.getDate << std::endl;
		}
	}
	
};

/** find
* Description: Shows the properties of any textfile that contains the given
*              input string.
*
* Arguments: tString - the string to look for within text files
*
* Returns: None.
*
* Effects: Prints out statements using the overloaded << operator (although
*          likely not the one in this class!)
**/
void SFArchive::find(const std::string& aString) const {
	for(const auto& file : archiveBlocks) {
		// If file is text, try to find the string, otherwise, skip
		if(file.isText) {
			extractFile(file.fileName);
	    std::fstream textToSearch("extracted.txt", std::ios::in | std::ios::binary);

	    //Search for text line by line
	    std::string line;
	    while(textToSearch) {
	    	getline(textToSearch, line);

	    	// Found aString in text
	    	if(line.find(aString) != std::string::npos) {
	    		// Print out the properties of the file containing aString
	    		std::cout << listFiles(file.fileName) << std::endl;
	    	}
	    }
	    textToSearch.close();
		}
	}
}
