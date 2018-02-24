/**
* SFData
*
* Description : Prototype for storing file information. As file information
*               becomes necessary. This can be easily modified to suit the
*               necessary parameters
**/

#include <string>
#include <utility>
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
  SFData(uint64_t tStart, uint64_t tEnd);

  // basic destructor
  ~SFData();

  // getters/modifiers (inline needed?)
  uint64_t getStartLoc(void) const;
  uint64_t getEndLoc(void) const;
  std::pair<uint64_t, uint64_t> getLocTuple(void) const;
  std::string getInsertdate(void) const;  // returned date as a formatted string!

  // shifts location of the file by tShift bytes (Note that this DOES NOT move
  // the file itself. That is the responsibility of the archive...)
  void shiftLoc(int32_t tShift);

private:
  uint64_t startByte; // start loc in archive
  uint64_t endByte; // end loc in archive

  typedef struct tm Date;
  Date currDate;  // allows setting of current date
};

/** overloads the ostream operator for the SFData class. Please use the getters
* for this class to deal with this. Note that the formatting for this should is
* predefined as follows:
*                         size date-added
* Note that size should contain enough spaces to hold any 64bit unsigned int
* (so setw from iomanip may be useful for formatting...)
**/
std::ostream& operator<<(std::ostream& tStream, const SFData& tData);
