#include <stdio.h>
#include <iostream>
#include "SFArchive.hpp"

char* arg[5];
class commandparser :  public SFArchive
{
public:
    commandparser(); //Default Constructor
    int main(int count, char* arg[]);
    ~commandparser(); //Destructor
};
