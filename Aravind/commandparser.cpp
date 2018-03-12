#include <iostream>
#include "SFArchive.hpp"
#include "commandparser.hpp"

commandparser::commandparser()
{
}

commandparser::~commandparser()
{
}

int commandparser :: main(int count, char *arg[])
{
    std::string command;
    std::string archive;
    std::string filename;

    if(count<2)
    {
        std::cout<<"Invalid Command"<<std::endl;
        return 1;
    }

    command = arg[1];
    archive = arg[2];
    filename = arg[3];

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

    else if(command == "version" || command == "-v")
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
