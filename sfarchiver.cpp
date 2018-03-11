/**
* sfarchiver.cpp
*
* Description: Main executable for the program. This is expected to parse all of
*              the arguments in here (at least for now). This should be filled
*              out to be able to parse all of the commands that are described
*              on the README.md file.
*              Note: If exceptions are found, they should be dealt with HERE.
*                    Make sure that sensible errors are thrown.
*                    i.e. ENOSPC -> 28 return value [no space on the drive]
*                    Give messages for these errors as well.
**/

#include <string>
#include <iostream>
#include <exception>
#include "SFArchive.hpp"

auto main(int argc, char* argv[]) -> int {
  SFArchive testCtor("testarchive");
  testCtor.listFiles();
  testCtor.extractFile("emittingtest.txt");
  return 0;
}
