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

  /**
  * Given an input file:
  *   1) Open the file (do not create yet if it doesn't exist)
  *       1.1) If file exists, read the footer to containedData member variable.
  *       1.2) If file is already open, return an error saying that file cannot
  *            be opened.
  *   2) Prepare compression stream if flag has been set. (otherwise store)
  *   Linh
  **/
SFArchive::SFArchive(const std::string& aFile, const bool aCompFlag = false) throw() {
	// Check first blocks for file name, if it exists, do
	if(std::find(firstBlocks.begin(), firstBlocks.end(), aFile) != firstBlocks.end()) {
		/*while(!file.eof)
		 * 	read block header();
		 * 		construct map
		 * 		construct vector
		 */


	}
}

