/**
* SFData
*
* Description : Prototype for storing file information. As file information
*               becomes necessary. This can be easily modified to suit the
*               necessary parameters
**/

#include <string>
#include <iostream>
#include <cinttypes>

class SFBlock {
public:
  // prevent empty class construction (it's bad for you anyways!)
  SFBlock() = delete;

  // Constructor wil set the filename, insertion date, block position, file block
  // number, and filesize by default. If needed, the isText flag and the nextPiece
  // pointers can be set to describe the file.
  // This also sets the isDeleted flag to false by default.
  SFBlock(const std::string& tFilename, const std::string& tDateString,
          uint32_t tBlockPosition, uint32_t tFileBlockNumber, uint32_t tFilesize,
          uint32_t tNextBlock, bool tTextFlag = false);

  // basic destructor (please define it as well)
  ~SFBlock() noexcept;

  /** Getters - These are self explanatory          (Brian)
  * _getFilename       - gets the file name
  * _getDate           - gets the date the file was placed as a string
  * _getBlockPos       - gets the position of the block in the archive
  * _getFileBlockNum   - gets the number of the block in the file
  * _getSpaceLeft      - gets the space left over in the block (usually 0)
  * _getFileSize       - gets the file's filesize
  * _getNextPiece      - gets the next piece of the block
  * _isTextFile        - returns whether the file is boolean or not
  **/
  std::string getFilename(void) const;
  std::string getDate(void) const;
  uint32_t getBlockPos(void) const;
  uint32_t getFileBlockNum(void) const;
  uint32_t getSpaceLeft(void) const;  // calculated from the fileSize
  uint32_t getNextIntPiece(void) const;
  uint32_t getFileSize(void) const;
  SFBlock* getNextPiece(void) const;
  bool isTextFile(void) const;

  /** SetBlockPos     (Brian)
  * Sets the new block position given the vector respresenting the archive. This
  * should be called AFTER the block has already moved positions in the archiver.
  **/
  void setBlockPos(const int tNewBlockPos);

  /** DeleteBlock       (Brian)
  * Sets the block as deleted (and thus allows for error checking with above)
  **/
  void deleteBlockPos(const int tDelBlockPos);

  /** setNextBlock      (Brian)
  * Sets the pointer to the next block
  **/
  void setNextBlock(SFBlock* tPoint);

  static const constexpr uint16_t BLOCK_SIZE = 4000;
  static const constexpr uint16_t HEADER_SIZE = 500;

private:
  std::string fileName;   // holds the filename for block
  std::string date;       // records date added
  uint32_t blockPos;      // records position in the entire archive
  uint32_t fileBlockNum;  // block number of the current block
  uint32_t fileSize;      // filesize
  uint32_t nextIntPiece;  // next piece's position in vector
  SFBlock* nextPiece;     // pointer to the next piece
  bool isText;        // flag to check if a file is a text file

  // NOTE: This will NOT be written to the header. It's a flag to monitor archive
  //       status.
  bool isDeleted;     // flag for file deletion (causes exception if not deleted)
};

/** operator<< (Brian)
*
* Description : Overloads the ostream operator for the SFData class. Please use
*               getters for this class to deal with this. Note that the formatting
*               for this is predefined as follows *SUBJECT TO CHANGE*:
*                           size(---) date-added(MM DD HH:MM)
*               Note that size should contain enough spaces to hold any 64bit unsigned
*               int (so setw from iomanip may be useful for formatting...)
*
* Arguments: tStream - The output stream to write to
*            tData - the SFData object to write to the stream
*
* Returns: A reference to the tStream as typically expected.
**/
std::ostream& operator<<(std::ostream& tStream, const SFBlock& tBlock);
