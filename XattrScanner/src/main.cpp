/*
* Copyright (C) 2016  Mateusz Fruba <m.fruba+opensource@gmail.com>
* 
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*  
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*  
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>
*
*/

#include <iostream>

#include "FileSearcher.h"
#include "XattrHelper.h"
#include "XattrSearcher.h"

#include <list>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>

void showHelp(char * name);

int main(int argc, char ** argv)
{

	if(argc == 1)
	{
		showHelp(argv[0]);
		return 0;
	}

	int opt;
	int funcToRun = -1;
	std::string scanPath;
	XattrSearcher xs;

    while ((opt = getopt (argc, argv, "p:s:")) != EOF)
    {    
    	switch (opt)
        {
        case 'p':    
        	{ 
	            scanPath = optarg;
	            funcToRun = 0;	
            }
            break;
        case 's':    
        	{ 
	            xs.blacklistXattr( optarg );
	     		std::cout <<"Blacklisting: " << optarg << std::endl;       
            }
            break;
        case '?':
            std::cerr << "Unknown option character '" << (char)opt << "'." << std::endl << std::endl;
            showHelp(argv[0]);
            return 1;
        default:
        	showHelp(argv[0]);
        	return 0;
        }
	}

	switch(funcToRun)
	{
		case 0:	
		{
			std::cout <<"Scanning: " << scanPath << std::endl;
			xs.setSearchPath(scanPath);
			xs.runSearch();
		}
			break;
		default:
			showHelp(argv[0]);
			break;
	}

	
	return 0;
}

void showHelp(char * name)
{
	std::cerr << "Usage:" << std::endl;
	std::cerr << name << " -p pathToScan" << std::endl;
	std::cerr << name << " -s blacklistAttribute" << std::endl;
	std::cerr << "Example:" << std::endl;
	std::cerr << name << " -p /usr/bin/" << std::endl;
	std::cerr << name << " -p /usr/bin/ -s security.selinux -s asd" << std::endl;
}
