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

#include <fstream>      
#include <iostream>
#include <ctime>
#include "SFArchive.hpp"
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include<set>
#include <iostream>

int main()
{
	 

	while (true){

		std::string usercommand;
		std::string command;
		std::string archive;
		std::string filename;

		int count;

		std::vector<std::string> cmds;
		std::cout << "sfarchiver ";
		std::getline(std::cin, usercommand);
		std::istringstream ss(usercommand);
		std::string temp;
		while (ss >> temp)
		{
			cmds.push_back(temp);
		}
	
		count = cmds.size();
		std:: cout << cmds.at(0)<<std::endl;
		std::cout << "size" <<cmds.size()<< std::endl;
		std::cout << command << std::endl;
	
		
		if (count == 1){
			command = cmds.at(0);
		}

		else if (count == 2)
		{
			command = cmds.at(0);
			archive = cmds.at(1);

			std::cout << command << std::endl;
			std::cout << archive << std::endl;
		}
		else if (count == 3)
		{
			command = cmds.at(0);
			archive = cmds.at(1);
			filename = cmds.at(2);

			std::cout << command << std::endl;
			std::cout << archive << std::endl;
			std::cout << filename << std::endl;

		}
	
		else
		{
			std::cout << "Invalid number of arguments";
		}


		if (command == "add")
		{
			if (count == 3)
			{
			SFArchive sfa(archive);
			sfa.addFile(filename);
			}
			else
			{
				std::cout << "Invalid Command";
			}
		}

		else if (command == "del")
		{
			if (count == 3)
			{
				SFArchive sfa(archive);
				sfa.deleteFile(filename);
			}
			else
			{
				std::cout << "Invalid Command";
			}
		}

		else if (command == "list" || command == "-l")
		{
			if (count == 3)
			{
				SFArchive sfa(archive);
				sfa.listFiles(filename);
			}

			else if (count == 2)
			{
				SFArchive sfa(archive);
				sfa.listFiles();
			}

			else
			{
				std::cout << "Invalid Command";
			}
		}

		else if (command == "find")
		{
			if (count == 3)
			{
				SFArchive sfa(archive);
				sfa.find(filename);
			}
			else
			{
				std::cout << "Invalid Command";
			}
		}


		else if (command == "extract")
		{
			if (count == 3)
			{
				SFArchive sfa(archive);
				sfa.extractFile(filename);
			}
			else
			{
				std::cout << "Invalid Command";
			}
		}

		else if (command == "version" || command == "-v")
		{
			
			SFArchive::printVersionInfo();
		}

		else
		{
			std::cout << "Invalid Command";
			
		}


	}
	return 0;
}
