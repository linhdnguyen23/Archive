#include <map>
#include <functional>

class CommandObject {
public:
  CommandObject();
  CommandObject(std::function<void()> tExecuteZero);
  CommandObject(std::function<void(char*)> tExecuteOne);
  CommandObject(std::function<void(char*, char*)> tExecuteTwo);
  bool isInvalid() const;
  void operator()() const;
  void operator()(char* tFirst) const;
  void operator()(char* tFirst, char* tSec) const;
  size_t getArgCount(void) const;

private:
  size_t argCount;
  std::function<void()> executeNone;
  std::function<void(char*)> executeOne;
  std::function<void(char*, char*)> executeTwo;
};

class CommandParser {
public:
  CommandParser(std::function<void(const char*)> tDefault = defaultErrorPrint);
  bool addCommand(const char* tCommand, std::function<void()> tFunc);
  bool addCommand(const char* tCommand, std::function<void(char*)> tFunc);
  bool addCommand(const char* tCommand, std::function<void(char*, char*)> tFunc);
  CommandObject parseCommand(const char* tParse);

  static void defaultErrorPrint(const char* tCommand); // simply echoes the error

private:
  std::map<std::string, CommandObject> functionMap;  // holds all commands
  std::function<void(const char*)> defaultFunc;
};
