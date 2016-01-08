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

#ifndef __FILE_SEARCHER_H_INCLUDED__
#define __FILE_SEARCHER_H_INCLUDED__

#include "Config.h"
#include <functional>
#include <list>
#include <string>


class FileSearcher 
{ 

private:
	std::list<std::string> m_files;
	std::string m_searchPath;
	std::function<int (const char *, const struct stat *, int, struct FTW *)> m_customHandleNFTW;
	//
	int custom_nftw(const char *path, std::function<int (const char *, const struct stat *, int, struct FTW *)> fn, int nfds, int ftwflags);
	int handleNFTW(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf);

public:
	FileSearcher();
	FileSearcher(std::string searchPath);
	unsigned int runSearch();

	std::list<std::string> & getPaths();

	void setSearchPath(std::string & path);
	void setCustomHandleNFTW(std::function<int (const char *, const struct stat *, int, struct FTW *)> fn);


};

#endif 
