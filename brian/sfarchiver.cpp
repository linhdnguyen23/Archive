#include <iostream>
#include "CommandParser.hpp"

class WasteOfSpace{
public:
  void printThisThing(char* input) {
    std::cout << input << std::endl;
  }
};

int main(int argc, char **argv) {
  WasteOfSpace waster;
  CommandParser tester;

  using std::placeholders::_1;
  std::function<void(char*)> test = std::bind(&WasteOfSpace::printThisThing, waster, _1);
  tester.addCommand("-e", test);
  tester.addCommand("echo", test);

  // now this should be skipped
  std::function<void(char*)> test2;
  tester.addCommand("testnull", test2);

  // if no inputs say so
  if(argc == 1) {
    std::cout << "No arguments supplied. Help would probably go here!" << std::endl;
    return 0;
  }

  // now parse inputs
  auto toProcess = tester.parseCommand(argv[1]);
  if(!toProcess.isInvalid())
    if(toProcess.getArgCount() == 1)
      toProcess(argv[2]);
}
