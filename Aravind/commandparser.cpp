#include <stdio.h>
#include <iostream.h>
#include <vector>
#include <sstream>
#include <string>
#include "SFArchive.hpp"
#include "commandparser.hpp"

commandparser::commandparser()
{   
}

commandparser::~commandparser()
{  
}

int commandparser :: main()
{
     while(true)
    {
    std::string usercommand;
    std::string command;
    std::string archive;
    std::string filename;
    int count;
    vector<std::string> cmds;
    std::cout<<"sfarchiver ";
    std::getline(std::cin,usercommand);
    std::istringstream ss(usercommand);
    std::string temp;
    while(ss>>temp)
    {
        cmds.push_back(temp);
    }
    count = cmds.size();
    func(count,cmds);
    return 1;
}
int commandparser :: func(int count, vector<std::string> arg)
{
    if(count<2)
    {
        std::cout<<"Invalid Command"<<std::endl;
        return 1;
    }
    
    if(count == 2)
    {
    command = arg[1];
    }
    else if(count == 3)
    {
    command = arg[1];
    archive = arg[2];
    }
    else if(count == 4)
    {
    command = arg[1];
    archive = arg[2];   
    filename = arg[3];
    }
    else
    {
    std::cout<<"Invalid number of arguments";
    }
    commandparser sfa;
    
    if(command == "add")
    {
        if(count==4)
        {
            sfa.SFArchive(archive);
            sfa.addFile(filename);
        }
        else
        {
            std::cout<<"Invalid Command";
        }
    }

    else if(command == "del")
    {
        if(count==4)
        {
            sfa.SFArchive(archive);
            sfa.deleteFile(filename);
        }
        else
        {
            std::cout<<"Invalid Command";
        }
    }
    
    else if(command == "list" || command == "l")
    {
        if(count==4)
        {
            sfa.SFArchive(archive);
            sfa.listFile(filename);
        }
        
        else if(count==3)
        {
            sfa.SFArchive(archive);
            sfa.listFiles();
        }
        
        else
        {
            std::cout<<"Invalid Command";
        }
    }

    //else if(command == "find")
    //{
    //    if(count==4)
    //    {
    //        sfa.find(archive, filename);
    //    }
    //    else
    //    {
    //        std::cout<<"Invalid Command";
    //    }
    //}
    
    else if(command == "extract")
    {
        if(count==4)
        {
            sfa.SFArchive(archive);
            sfa.extractFile(filename);
        }
        else
        {
            std::cout<<"Invalid Command";
        }
    }
    
    else if(command == "version" || command == "v")
    {
        sfa.printVersionInfo();
    }
    
    else
    {
        std::cout<<"Invalid Command";
        return 1;
    }

    return 0;
    }
}
