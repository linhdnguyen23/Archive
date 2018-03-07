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

SFArchive::SFArchive(const std::string& aFile, const bool aCompFlag = false) throw() {
  if(fileDoesExist(aFile)) {
  	if(openedFile.compare(aFile)) {
			std::ifstream infile;
			infile.open(aFile);
			openedFile = aFile;
			currArchives.push_back(aFile);
			// Assuming readFooter returns a pair <std::string key, std::SFData> or something
			containedData = readFooter(infile);
  	}
  	else {
  		throw std::logic_error("File is already opened.");
  	}
  	/*
		// Compress file if the flag is set to true
		if(aCompFlag) {
			Compression::compressData(infile, 1);
		}*/
  }
}

/**
 * fileDoesExist
 * Description: Check if file exists in the archive
 * Arguments: aFile - the file to look for in the archive
 * Returns: true - if the file exists; false - otherwise
 */
bool SFArchive::fileDoesExist(const std::string& aFile) {
	std::ifstream infile(aFile);
	return infile.good();
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

	if(!fileDoesExist(aFile)) {
		// Find start address to write this new file to
		/**
		 * getFreeSpace will check the size of aFile, and the size of free spaces
		 * in contained member, then return a starting location for a free space
		 * that is bigger than the size of aFile
		 */
		uint64_t fileSize = sizeof(aFile);
		uint64_t writeLoc = getFreeSufficientSpace(fileSize);
		SFData file = new SFData(writeLoc, fileSize);
		// containedData is a map that maintained the file (SFData) as block.
		writeFooter(containedData, file);
		return true;
	}

	return false;
}
