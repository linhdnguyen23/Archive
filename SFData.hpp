/**
* SFData
*
* Description : Prototype for storing file information. As file information
*               becomes necessary. This can be easily modified to suit the
*               necessary parameters
**/

#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>  // this is somewhat bloated... Maybe we can change it to a
                  // less bloated class??

class SFData {
public:
  // prevent empty class construction (it's bad for you anyways!)
  SFData() = delete;

  // Constructor sets the start byte, end byte, and the time (time is initialized)
  // inside without any arguments needed. The time should be based off the user's
  // computer time.
  SFData(uint64_t tStart, uint64_t tSize, bool tText = false); //Linh

  // basic destructor (please define it as well)
  ~SFData() noexcept;

  /** Getters/Setters
  * These are quite straightforward to understand as follows:
  *     _getStartLoc   -> Return starting byte in archive
  *     _getEndLoc     -> Return ending byte in archive
  *     _getFileSize   -> Return the size of the file
  *     _getInsertDate -> Return the insertion date/time of the file as a string
  *     _isTextFile    -> Return whether or not the file in question is a text file
  **/
  uint64_t getStartLoc(void) const;
  uint64_t getEndLoc(void) const;
  uint64_t getFileSize(void) const;
  std::string getInsertdate(void) const;  // returned date as a formatted string!
  bool isTextFile(void) const;

  /** shiftLoc
  *
  * Description: Marks the shift of the entire file by a specified amount. Note
  *              that the shifting DOES NOT occur in here, but in the archive itself.
  *
  * Arguments: tShift - The amount to mark the shift in the file.
  **/
  void shiftLoc(int32_t tShift);

private:
  uint64_t startByte; // start loc in archive
  uint64_t fileSize; // file size for end loc calculation
  bool isText;       // checks if the file is a text file that can be parsed

  typedef struct tm Date;
  Date currDate;  // allows setting of current date
};

/** operator<<
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
std::ostream& operator<<(std::ostream& tStream, const SFData& tData);
