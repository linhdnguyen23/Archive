#include <map>
#include <functional>

class CommandObject {
public:
  CommandObject(std::function<void(char*)> tExecuteOne);
  CommandObject(std::function<void(char*, char*)> tExecuteTwo);
  void operator()(char* tFirst);
  void operator()(char* tFirst, char* tSec);
  size_t getArgCount(void) const;

  static constexpr size_t UNDEFINED_FUNC = -1;

private:
  size_t argCount;
  std::function<void(char*)> executeOne;
  std::function<void(char*, char*)> executeTwo;
};

class CommandParser {
public:
  bool addCommand(const char* tCommand, std::function<void(char*)> tFunc);
  bool addCommand(const char* tCommand, std::function<void(char*, char*)> tFunc);
  CommandObject parseCommand(const char* tParse);
  void printHelp(void);

private:
  std::map<std::string, CommandObject> functionMap;  // holds all commands
};
