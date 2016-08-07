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
#include <fstream>
#include <string>
#include <cstring>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int try2Open(const char * path, int flags)
{
	int fd = open(path, flags);
	if(fd != -1)
	{	
		std::cout << path << std::endl;
		close(fd);
		return 1;
	}
	return 0;
}

int scanFileList(std::string & fileList, int mode)
{
	std::cout << "Scanning Start..." << std::endl;
	std::ifstream infile(fileList);
	if(!infile.is_open())
	{
		std::cerr << "Cannot open fileList, qutting..." << std::endl;
		return 0;
	}
	std::string file;
	while (std::getline(infile, file) )
	{
		try2Open(file.c_str(), mode);
	}
	std::cout << "Scanning End." << std::endl;
	return 1;
}

void showHelp()
{
	std::cerr << "Usage:" << std::endl 
			<< " try2open list /data/local/tmp/list.txt r" << std::endl
			<< " try2open list /data/local/tmp/list.txt w" << std::endl
			<< " try2open single /dev/hiddenFile r" << std::endl << std::endl
			<< " try2open list list.txt mode - try to open all files listed in list txt" << std::endl	
			<< " try2open single /dev/hiddenFile mode - try to open /dev/hiddenFile" << std::endl
			<< " 	mode parameter can be specified 'r' for read only open or 'w' for write only open." << std::endl;
}

int char2flags(char flag)
{
	switch(flag)
	{
		case 'R':
		case 'r':
			return O_RDONLY;
			break;
		case 'W':
		case 'w':
			return O_WRONLY;
			break;
	}
	return O_RDONLY;
}

int main(int argc, char ** argv)
{
	int optInd = 1;
	if(optInd >= argc)
	{
		showHelp();
		return -1;
	}
	else if( strcmp(argv[optInd], "list") == 0 )
	{
		optInd++;
		if (optInd+1 >= argc)
		{
			std::cerr << "Please provide file path to file which contains list of paths to test and open mode (r|w)." << std::endl;
			showHelp();
			return -1;
		}
		std::string fileList = argv[optInd++];
		int mode = char2flags(argv[optInd++][0]);
		scanFileList(fileList, mode);
	}
	else if( strcmp(argv[optInd], "single") == 0 )
	{
		optInd++;
		if (optInd+1 >= argc)
		{
			std::cerr << "Please provide file path to test and open mode (r|w)." << std::endl;
			showHelp();
			return -1;
		}
		std::string file = argv[optInd++];
		int mode = char2flags(argv[optInd++][0]);
		try2Open(file.c_str(), mode);
	}	
	
	return 0;
}