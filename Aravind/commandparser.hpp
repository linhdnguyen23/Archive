#include <stdio.h>
#include <iostream>
#include "SFArchive.hpp"

char* arg[5];
class commandparser :  public SFArchive
{
public:
    commandparser(); //Default Constructor
    int main();
    int func(int count, vector<std::string> arg);
    ~commandparser(); //Destructor
};
