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
#include <algorithm>
#include <sstream>
#include <ctime>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_map>
#include "SFArchive.hpp"

SFArchive::SFArchive(const std::string& aFile, bool aCompFlag) : openedFile(aFile),
																																 compressFlag(false) {
	// opens the file
	std::ifstream inputStream(aFile, std::fstream::binary);

	// read the file headers until none are left
	if(inputStream.good())
		constructValues(inputStream);

	// note that if not good, then clearly no file exists!

	// done with file
	inputStream.close();
}

SFArchive::~SFArchive() {
	// nothing to do in here
}

void SFArchive::constructValues(std::ifstream& tInStream) {
	// read header given SFBLock::HEADER_SIZE
	// seek forward (curr + SF:BLOCK_SIZE - SFBlock::HEADER_SIZE
	// HEADER :: FNAME DATE FSIZE FBLKNUM NEXTBLK IS_TEXT LEFT_OVER

	char* buffer = new char[SFBlock::HEADER_SIZE];
	while(!tInStream.eof()) {
		tInStream.read(buffer, SFBlock::HEADER_SIZE);

		// check for faulty input by read
		if(tInStream.eof() && tInStream.fail())
			break;

		std::istringstream ibuffer(buffer);
		std::string token;
		size_t counter = 0;

		std::string fName, fDate;
		uint32_t fSize, fBlkNum, isText, nextBlock;

		while(getline(ibuffer, token, ';')) { // read entries
			switch (counter) {
				case 0: fName = token; counter++; break;
				case 1: fDate = token; counter++; break;
				case 2: fSize = atoi(token.c_str()); counter++; break;
				case 3: fBlkNum = atoi(token.c_str()); counter++; break;
				case 4: isText = (bool)atoi(token.c_str()); counter++; break;
				case 5: nextBlock = atoi(token.c_str()); counter++; break;
			}
			if(counter>5)
				break;	// leave if done with all variables to read
		}

		// construct entry
		archiveBlocks.emplace_back(fName, fDate, archiveBlocks.size(), fBlkNum, fSize, nextBlock, isText);

#ifdef VERBOSE_ON
		std::cout << "Constructed block for file " << fName << " created on " << fDate
							<< " with filesize " << fSize << ", block number " << fBlkNum
							<< ", and next block number " << nextBlock << " with isText="
							<< isText << std::endl;
#endif

		// if first piece, create a reference within map to location
		if(fBlkNum == 0)
			firstBlocks[fName] = archiveBlocks.size()-1; 	// -1 since it was currently added

		// now seek forward to the beginning of the next block (will be caught if outside stream)
		tInStream.seekg(SFBlock::BLOCK_SIZE - SFBlock::HEADER_SIZE, std::ios_base::cur);
	}

	// now build assemble the links between blocks
	for(SFBlock& block:archiveBlocks) {
		// read each block and link them if necessary
		uint32_t linkedTo = block.getNextIntPiece();
		if(linkedTo!=(uint32_t)-1)
			block.setNextBlock(&(archiveBlocks[linkedTo]));
	}
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
bool SFArchive::addFile(const std::string& aFile) {
	// define constants
	const size_t HEADER_SIZE = SFBlock::HEADER_SIZE;
	const size_t BLOCK_SIZE = SFBlock::BLOCK_SIZE;
	size_t archivePos = archiveBlocks.size();

	// Calculate the file size;
	std::streampos begin, end;
	std::ifstream myfile(aFile, std::ios::in | std::ios::binary);

	begin = myfile.tellg();
	myfile.seekg(0, std::ios::end);
	end = myfile.tellg();
	myfile.seekg(0, std::ios::beg);
	int fileSize = end - begin;

	std::cout << fileSize << std::endl;

	// Set the isText depending on file extensions
	bool isText = false;
	std::string extension = aFile.substr(aFile.find_last_of(".") + 1);
	if (extension == "txt") {
		isText = true;
	}

	time_t rawTime;
	time(&rawTime);
	std::string date = asctime(localtime(&rawTime));

	std::cout << date;

	int numOfBlocks = (fileSize / (BLOCK_SIZE-HEADER_SIZE));
	int spaceLeft = (BLOCK_SIZE - HEADER_SIZE) - fileSize % (BLOCK_SIZE - HEADER_SIZE);

	int count = 0;

	int nextBlockNumber = count+1;

	if (numOfBlocks == 0){
		nextBlockNumber = -1;
	}

	archiveBlocks.emplace_back(aFile, date, archivePos, count, fileSize, nextBlockNumber, isText);

	std::cout << archivePos << "pos" << std::endl;
	std::ofstream outputfile;
	// The new file is append to the archive.dat file, added std::ios::ate (Linh)
	outputfile.open(openedFile, std::ios::app | std::ios::binary);


	//Writing the starting block to the Dat file.
	char buffer[(BLOCK_SIZE - HEADER_SIZE)];
	myfile.read(buffer, (BLOCK_SIZE - HEADER_SIZE));


	char headerBuf[HEADER_SIZE];

	strcpy(headerBuf, aFile.c_str());
	strcat(headerBuf, std::string(";").c_str());
	strcat(headerBuf, date.c_str());
	strcat(headerBuf, std::string(";").c_str());
	strcat(headerBuf, std::to_string(fileSize).c_str());
	strcat(headerBuf, std::string(";").c_str());
	strcat(headerBuf, std::to_string(count++).c_str());
	strcat(headerBuf, std::string(";").c_str());
	strcat(headerBuf, std::to_string(isText).c_str());
	strcat(headerBuf, std::string(";").c_str());
	strcat(headerBuf, std::to_string(nextBlockNumber).c_str());
	strcat(headerBuf, std::string(";").c_str());


	outputfile.write(headerBuf, HEADER_SIZE);

	outputfile.write(buffer, BLOCK_SIZE - HEADER_SIZE);

	int archiveStart = archivePos;
	// update map and vector
	firstBlocks[aFile] = archivePos++;
	// Instead of this, use  (Linh)
	//firstBlocks[aFile] = archivePos;

	// We're iterating over the num of blocks not fileSize (Linh) change to
	for (int i = 0; i < numOfBlocks; i++) {

		int index = archiveBlocks.size();

		if (i == numOfBlocks - 1){
			archiveBlocks.emplace_back(aFile, date, archivePos++, count, fileSize, -1, isText);
		}
		else{
			archiveBlocks.emplace_back(aFile, date, archivePos++, count, fileSize, count + 1, isText);
		}

		//archiveBlocks.at(index - 1).nextPiece = &newBlock;

		char buffer[BLOCK_SIZE - HEADER_SIZE];
		// Is there any partitioned between read and unread so the program will only
		// get the index of the unread part and read from there

		myfile.read(buffer, BLOCK_SIZE - HEADER_SIZE);

		char headerBuf1[HEADER_SIZE];

		strcpy(headerBuf1, aFile.c_str());
		strcat(headerBuf1, std::string(";").c_str());
		strcat(headerBuf1, date.c_str());
		strcat(headerBuf1, std::string(";").c_str());
		strcat(headerBuf1, std::to_string(fileSize).c_str());
		strcat(headerBuf1, std::string(";").c_str());
		strcat(headerBuf1, std::to_string(count++).c_str());
		strcat(headerBuf1, std::string(";").c_str());
		strcat(headerBuf1, std::to_string(isText).c_str());
		strcat(headerBuf1, std::string(";").c_str());

		if (i == numOfBlocks - 1){
			strcat(headerBuf1, std::to_string(-1).c_str());
			strcat(headerBuf1, std::string(";").c_str());
		}
		else{
			strcat(headerBuf1, std::to_string(count).c_str());
			strcat(headerBuf1, std::string(";").c_str());
		}


		outputfile.write(headerBuf1, HEADER_SIZE);

		if (i == numOfBlocks - 1){
			outputfile.write(buffer, fileSize % (BLOCK_SIZE - HEADER_SIZE));

			char space[BLOCK_SIZE - HEADER_SIZE];

			outputfile.write(space, (BLOCK_SIZE - HEADER_SIZE) - fileSize % (BLOCK_SIZE - HEADER_SIZE));

		}
		else{
			outputfile.write(buffer, BLOCK_SIZE - HEADER_SIZE);
		}

		// std::cout << "executed" << std::endl;
	}


	myfile.close();
	outputfile.close();



	for (SFBlock& block : archiveBlocks) {

		uint32_t linkedTo = block.getNextIntPiece();
		if (linkedTo != (uint32_t)-1){
			block.setNextBlock(&(archiveBlocks[linkedTo]));
		///	std::cout << "test0 "<<linkedTo<<"  "<< block.getNextPiece()->blockPos << std::endl;
		}
	}

	

	return true;
}

bool SFArchive::deleteFile(const std::string& aFile) {
	// int index = firstBlocks.at(aFile);
	firstBlocks.erase(aFile);

	int count = 0;

	std::vector<SFBlock> newArchiveBlock;

	std::fstream myFile(openedFile, std::ios::in | std::ios::binary);

	std::fstream outputfile(aFile, std::ios::out | std::ios::binary);

	for (SFBlock n : archiveBlocks){

		std::string targetFile = n.getFilename();

		if (strcmp(targetFile.c_str(), aFile.c_str()) != 0){


			int readPos = n.getBlockPos();
			myFile.seekg(readPos * 4500);
			std::cout << "readPost " << readPos << std::endl;
			char tempBuffer[4500];

		 	myFile.read(tempBuffer, 4500);
	     	outputfile.write(tempBuffer, 4500);


			n.setBlockPos(count);

			std::cout << n.getFilename() << " " << n.getBlockPos() << " " << n.getFileBlockNum()<<std::endl;

			count++;

			newArchiveBlock.push_back(n);
		}

	}

	archiveBlocks.clear();

	archiveBlocks = newArchiveBlock;

	myFile.close();
	outputfile.close();

	std::cout << "delete" << std::endl;
	std::cout << archiveBlocks.size() << std::endl;

	for (SFBlock n : archiveBlocks){
		std::cout << n.getFilename() << " " << n.getBlockPos() << " " << n.getFileBlockNum() << std::endl;
	}



	std::fstream readTemp("temp.txt", std::ios::in | std::ios::binary);

	std::fstream outputTemp(openedFile, std::ios::out | std::ios::binary);


	for (size_t i = 0; i < archiveBlocks.size();i++)
		{
			char tempBuffer[4500];
			readTemp.read(tempBuffer, 4500);
			outputTemp.write(tempBuffer, 4500);
			std::cout << "sss" << std::endl;
		}

		readTemp.close();
		outputTemp.close();

		remove("temp.txt");

	return true;
}

bool SFArchive::extractFile(const std::string& tString) const {
	auto loc = firstBlocks.find(tString);
	if(!(loc == firstBlocks.end())) {
		const SFBlock* curr = &(archiveBlocks[loc->second]);
		std::ifstream archiveSource(openedFile, std::ios::binary);
		std::ofstream outputFile(curr->getFilename(), std::ios::binary|std::ios::trunc);

		// is there extra data that will not need to be written?
		uint32_t leftover = curr->getSpaceLeft();

		// set up buffer for writing
		size_t sizeToAlloc = SFBlock::BLOCK_SIZE - SFBlock::HEADER_SIZE;
		char* buf = new char[sizeToAlloc];

		// now write the entire file out to the current working directory
		while(curr != nullptr) {
			// go to start position
			size_t startPos = curr->getBlockPos()*SFBlock::BLOCK_SIZE+SFBlock::HEADER_SIZE;
			archiveSource.seekg(startPos);

			// now write to the output
			if(curr->getNextPiece() == nullptr) {	// must be last block
				delete[] buf;
				buf = new char[leftover];
				archiveSource.read(buf, leftover);
				outputFile.write(buf, leftover);
				delete[] buf;
			} else {	// not last block
				archiveSource.read(buf, sizeToAlloc);
				outputFile.write(buf, sizeToAlloc);
			}
			curr = curr->getNextPiece();	// move onto next piece
		}
		outputFile.close();
		archiveSource.close();
	} else {
		return false;	// file does not exist within archive
	}
	return true;
}

void SFArchive::printVersionInfo(void) const {
	std::cout << "sfarchiver version " << VERSION_NUM << " " << INFO << std::endl;
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
		std::cout << it.first<<"       "<<tempSFblock.getFileSize()<<"        "<<tempSFblock.getDate()<<std::endl;
	}
}

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
			std::cout << it.first << "       " << tempSFblock.getFileSize() << "        " << tempSFblock.getDate() << std::endl;
		}
	}

}

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
		if(file.isTextFile()) {
			extractFile(file.getFilename());
	    std::fstream textToSearch("extracted.txt", std::ios::in | std::ios::binary);

	    //Search for text line by line
	    std::string line;
	    while(textToSearch) {
	    	getline(textToSearch, line);

	    	// Found aString in text
	    	if(line.find(aString) != std::string::npos) {
	    		// Print out the properties of the file containing aString
	    		listFiles(file.getFilename());	// already prints the props
	    	}
	    }
	    textToSearch.close();
			remove("extracted.txt");
		}
	}
}

// void SFArchive::find(const std::string& aString) const {
// 	for(auto block:archiveBlocks) {
// 		if(block.isTextFile()) {
// 			// if text, follow chain and read all of the blocks to memory
// 			size_t sizeToAlloc = block.getFileSize();
// 			std::string document;
// 			document.reserve(sizeToAlloc+1);
//
// 		}
// 	}
// }
