/*
 * SFData.cpp
 *
 *  Created on: Mar 5, 2018
 *      Author: linh-nguyen
 */
#include "SFData.hpp"

SFData::SFData(uint64_t tStart, uint64_t tSize, bool tText = false) {
  	startByte = tStart;
  	fileSize = tSize;
  	isText = tText;
  	time_t rawTime;
  	time(&rawtime);
  	currDate = *localtime(&rawtime);
}

uint64_t SFData::getStartLoc(void) const {
	return startByte;
}

uint64_t SFData::getEndLoc(void) const {
	return startByte + fileSize;
}

uint64_t SFData::getFileSize(void) const {
	return fileSize;
}

std::string SFData::getInsertdate(void) const {
	return currDate;
}

void SFData::shiftLoc(int32_t tShift) {
	startByte += tShift;
}

std::ostream& operator<<(std::ostream& tStream, const SFData& tData) {
	std::ostream of(tStream);
}
