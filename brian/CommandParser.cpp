#include <string>
#include <iostream>
#include <map>
#include <functional>
#include "CommandParser.hpp"

CommandObject::CommandObject() {}

CommandObject::CommandObject(std::function<void()> tExecuteZero) : argCount(0), executeNone(tExecuteZero) {}

CommandObject::CommandObject(std::function<void(char*)> tExecuteOne) : argCount(1), executeOne(tExecuteOne) {}

CommandObject::CommandObject(std::function<void(char*, char*)> tExecuteTwo) : argCount(2), executeTwo(tExecuteTwo) {}

bool CommandObject::isInvalid() const {
  return executeNone==nullptr && executeOne==nullptr && executeTwo==nullptr;
}

void CommandObject::operator()() const {
  if(executeNone != nullptr)
    executeNone();
}

void CommandObject::operator()(char* tFirst) const {
  if(executeOne != nullptr)
    executeOne(tFirst);
}

void CommandObject::operator()(char* tFirst, char* tSec) const {
  if(executeTwo != nullptr)
    executeTwo(tFirst, tSec);
}

size_t CommandObject::getArgCount(void) const {
  return argCount;
}

CommandParser::CommandParser(std::function<void(const char*)> tDefault) : defaultFunc(tDefault) {}

bool CommandParser::addCommand(const char* tCommand, std::function<void()> tFunc) {
  return functionMap.emplace(tCommand, tFunc).second;
}

bool CommandParser::addCommand(const char* tCommand, std::function<void(char*)> tFunc) {
  return functionMap.emplace(tCommand, tFunc).second;
}

bool CommandParser::addCommand(const char* tCommand, std::function<void(char*, char*)> tFunc) {
  return functionMap.emplace(tCommand, tFunc).second;
}

CommandObject CommandParser::parseCommand(const char* tParse) {
  auto where = functionMap.find(tParse);
  if(where == functionMap.end()) {
    if(defaultFunc != nullptr)
      defaultFunc(tParse);
    return CommandObject();
  }
  return where->second;
}

void CommandParser::defaultErrorPrint(const char* tCommand) {
  std::cout << "Invalid command \"" << tCommand << "\" was given." << std::endl;
}
