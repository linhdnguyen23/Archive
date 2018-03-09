/**
* SFArchive
*
* Description : Performs typical archival tasks. A typical usage simply deflates
*             : the archive itself. Compression is assumed to be lossless.
*
* NOTE: Compression is currently not implemented. Please write the logic as though
*       compression was available. See Compression.hpp for further comments.
*
* NOTE: If you are updating this class, CHANGE THE VERSION NUMBER ACCORDINGLY!
*       CHANGE THE DATE RIGHT UNDER IT TOO!
*       +0.1 for only minute changes (i.e. slight declaration changes)
*       floor(VER+1) for substantial file changes (i.e. implementation altered)
*
* REVIEW: Please enter your thoughts using review tags. It makes it easier for me
*         (and others) to locate :)
**/

#include <map>
#include <string>
#include <vector>
#include <unordered_map>
#include <exception>
#include "SFBlock.hpp"
#include "Compression.hpp"

// #define VERBOSE_ON      // used for debugging. uncomment for verbose output

class SFArchive {
public:
  /**
  * These methods are deleted because they do not make sense in terms of an
  * archive's typical interface. Note that we cannot have duplicates due to
  * resources not being properly shared. Consider using a share pointer instead.
  **/
  SFArchive() = delete; // prevent empty initialization of class
  SFArchive(const SFArchive&) = delete; // prevent copy construction (want no duplicates)
  SFArchive& operator=(const SFArchive&) = delete; // prevent copy assignment (look above)

  /**
  * Given an input file:
  *   1) Open the file (do not create yet if it doesn't exist)
  *       1.1) If file exists, read the footer to containedData member variable.
  *       1.2) If file is already open, return an error saying that file cannot
  *            be opened.
  *   2) Prepare compression stream if flag has been set. (otherwise store)
  *   Linh
  **/
  SFArchive(const std::string& tFile, const bool tCompFlag = false);

  ~SFArchive() noexcept; // special destructor not needed (but please do define this)

  /***************************************************************************
  *                            ARCHIVE INTERFACE                             *
  ****************************************************************************
  * These implement basic functionality which is expected from an archiver.  *
  * TODO: WRITE HOW TO USE HERE                                              *
  ***************************************************************************/
  /** addFile  Linh
  * Description: Adds a named file to the archive. If the file does not exist,
  *              then report a failure through the return. Note that compression
  *              will clearly play a role here.
  *
  * Arguments: tFile - the file to be placed into the archive
  *
  * Returns: true - if the file add succeeded; false - otherwise
  **/
  bool addFile(const std::string& tFile);

  /** deleteFile    Huang Lin
  * Description: Removes the file given the input filename. If the file does not
  *              exist, then report a failure through the return. If the file
  *              was compressed, be sure to decompress!
  *
  * Arguments: tFile - the file to be removed from the archive
  *
  * Returns: true - if the file remove succeeded; false - otherwise
  **/
  bool deleteFile(const std::string& tFile);

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
  void listFiles(void) const;

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
  void listFiles(const std::string& tString) const;

  /** findWithinText
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
  void findWithinText(const std::string& tString) const;

  /** extractFile Aravind
  * Description: Emit a copy of the file specified by a query. Like remove, this
  *              function also depends on the compression flag.
  *
  * Arguments: tString - the string representing the file to emit.
  *
  * Returns: None.
  *
  * Effects: Emits a file out to the current working directory.
  *          WARNING: This MAY overwrite a current file that WAS NOT the file in
  *                   the archive! Please prompt for it THEN remove this warning!
  **/
  bool extractFile(const std::string& tString) const;

  /** printVersionInfo Aravind
  * Description: Prints out a copy of the program's name and version.
  *
  * Arguments: None.
  *
  * Returns: None.
  *
  * Effects: Prints out the program name, version number, and update stamp.
  **/
  void printVersionInfo(void) const;

private:
  // NEW VALUES (We'll keep it simple with only two values for now)
  std::vector<SFBlock> archiveBlocks;
  std::unordered_map<std::string, size_t> firstBlocks;

  const bool compressFlag;                        // this probably won't stay
  static constexpr float VERSION_NUM = 1.0;             // version number
  static constexpr const char* info = "March 8, 2018";   // update date


  // OLD VALUES
  // std::string openedFile;                       // currently opened file
  // const bool compressFlag;                      // to compress or not to compress...
  // std::map<std::string, SFData> containedData;  // personally, I think this should
  //                                               // be sorted based on insertion order
  //                                               // but, it's ultimately up to a group vote
  //
  // static std::vector<std::string> currArchives; // prevent opening the same archive twice
  //
  // static constexpr float VERSION_NUM = 0.2;     // version number
  // static constexpr const char* info = "March 7, 2018";  // update date
  // Compression* compressObj;                     // compression object


  /***************************************************************************
  *                            HELPER FUNCTIONS                              *
  ****************************************************************************
  * Please define any helper functions you need under this header. It makes  *
  * things easier to track :)                                                *
  ***************************************************************************/

  //TODO: Need basic functionality here such as::
  //      _readFooter  -> processes header for currArchives member
  //      _writeFooter -> writes the header back to the END OF THE FILE
  //                      (Consider what happens if we add a file!!!)
  //      _nameSort/_ptrSort -> Need a comparator for sorting the map based on
  //                            pointer (for the remove/add commands) and filenames
  //                            (for the list commands)
  //      AND ANY OTHER HELPER METHODS LIKELY NEEDED
  bool fileDoesExist(const std::string& aFile);
};

/** operator<<
*
* Description : Overloads the ostream operator for the SFArchive class. Please use
*               getters for this class to deal with this. Note that the formatting
*               for this is predefined as follows *SUBJECT TO CHANGE*:
*                      filename(----) size(---) date-added(MM DD HH:MM)
*               If the ostream operator was correctly implemented in the SFData
*               class, then this will be much simpler!
*
* Arguments: tStream - The output stream to write to
*            tArchive - The archive to display info about
*
* Returns: A reference to the tStream as typically expected.
**/
std::ostream& operator<<(std::ostream& tStream, const SFArchive& tArchive);
