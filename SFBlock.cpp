#include <iomanip>
#include "SFBlock.hpp"
#include  <iostream>

//TODO:
SFBlock::SFBlock(const std::string& tFilename, const std::string& tDateString,
                 uint32_t tBlockPosition, uint32_t tFileBlockNumber, uint32_t tFilesize,
                 uint32_t tNextBlock, bool tTextFlag) : fileName(tFilename),
                 date(tDateString), blockPos(tBlockPosition), fileBlockNum(tFileBlockNumber),
                 fileSize(tFilesize), nextIntPiece(tNextBlock), nextPiece(nullptr),
                 isText(tTextFlag), isDeleted(false)
{
  // nothing to do here
}

SFBlock::~SFBlock() noexcept {}  // default dtor only needed

std::string SFBlock::getFilename(void) const {
  return fileName;
}

std::string SFBlock::getDate(void) const {
  return fileName;
}

uint32_t SFBlock::getGlockPos(void) const {
  return blockPos;
}

uint32_t SFBlock::getFileBlockNum(void) const {
  return fileBlockNum;
}

uint32_t SFBlock::getSpaceLeft(void) const {
  // calculate and return space left
  return fileSize%(BLOCK_SIZE-HEADER_SIZE);
}

uint32_t SFBlock::getFileSize(void) const {
  return fileSize;
}

SFBlock* SFBlock::getNextPiece(void) const {
  return nextPiece;
}

bool SFBlock::isTextFile(void) const {
  return isText;
}

void SFBlock::setBlockPos(const int tNewBlockPos) {
  blockPos = tNewBlockPos;
}

void SFBlock::deleteBlockPos(const int tDelBlockPos) {
  isDeleted = true;
}

void SFBlock::setNextBlock(SFBlock* tPoint) {
  nextPiece = tPoint;
}

std::ostream& operator<<(std::ostream& tStream, const SFBlock& tBlock) {
  // print information as size(---) date-added(MM DD HH:MM)
  // space in between is 1
  // size has a width of 12 (11 for digits + 1 for spacing)
  // date has a width of 12 (11 for date string + 1 for spacing)
  std::cout.width(12);
  std::cout << tBlock.getFileSize() << tBlock.getDate();

  return tStream;
}
