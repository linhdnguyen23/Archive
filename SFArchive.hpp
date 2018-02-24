/**
* SFArchive
*
* Description : Performs typical archival tasks. A typical usage simply deflates
*             : the archive itself. Compression is assumed to be lossless.
**/

#include <map>
#include <string>
#include <vector>
#include <exception>
#include "SFData.hpp"

class SFArchive {
public:
  /**
  * These methods are deleted because they do not make sense in terms of an
  * archive's typical interface
  **/
  SFArchive() = delete; // prevent empty initialization of class
  SFArchive(const SFArchive&) = delete; // prevent copy construction (want no duplicates)
  SFArchive& operator=(const SFArchive&) = delete; // prevent copy assignment (look above)

  /**
  * Given an input file:
  *   1) Open the file (do not create yet if it doesn't exist)
  *       1.1) If file exists, read the header to containedData member variable.
  *   2) Prepare compression stream if flag has been set. (otherwise store)
  **/
  SFArchive(const std::string& tFile, const bool tCompFlag);

  ~SFArchive() noexcept; // special desctructor not needed (but please do declare this)

  // TODO: FILL OUT ALL CLASS FUNCTIONS

private:
  const bool compressFlag;
  static std::vector<std::string> currArchives; // prevent opening the same archive twice
  std::map<std::string, SFData> containedData;  // personally, I think this should
                                                // be sorted based on insertion order
                                                // but, it's ultimately up to a group vote

  /***************************************************************************
  *                            HELPER FUNCTIONS                              *
  ****************************************************************************
  * Please define any helper functions you need under this header. It makes  *
  * things easier to track :)                                                *
  ***************************************************************************/


  /**
  * This part deals with possible compression features... Ideally, compression
  * will use a stream to simplify the process...
  * These are just placeholders...
  **/
  void* compressData(const void* tData, const size_t tDatLength);
  void* decompressData(const void* tData, const size_t size);
  void* compressedSize(const size_t tData);
};
