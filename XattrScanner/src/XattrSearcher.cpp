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

#include "XattrSearcher.h"

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <algorithm>


bool XattrSearcher::XattrBlacklist::operator() (const Xattr & value)
{
	return std::find( m_blacklist.begin(), m_blacklist.end(), value.m_attrName) != m_blacklist.end(); 
}


XattrSearcher::XattrSearcher():m_fs("/")
{
	
	
}

XattrSearcher::XattrSearcher(std::string searchPath):m_fs(searchPath)
{
	
}


unsigned int XattrSearcher::runSearch()
{
	std::function<int (const char *, const struct stat *, int, struct FTW *)> fn = std::bind(&XattrSearcher::handleNFTW, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);

	m_fs.setCustomHandleNFTW(fn);
	m_fs.runSearch();

	
	std::cout << "Done" << std::endl;

	return 0;
}

std::list<std::string> & XattrSearcher::getPaths()
{
	return m_fs.getPaths();
}

void XattrSearcher::setSearchPath(std::string & path)
{
	m_fs.setSearchPath(path);
}

void XattrSearcher::blacklistXattr(std::string xattrName)
{
	m_xattrsBlacklist.m_blacklist.push_back(xattrName);
}

//Grabbing all file paths into memory consumes to much memory, we have to search xattrs in runtime :(
int XattrSearcher::handleNFTW(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
	if(S_ISREG(sb->st_mode))
	{
		m_xattrs.clear();
		std::string path(fpath);
		 
		int num = XattrHelper::getXattrList(path, m_xattrs);
		
		if(num > 0)
		{
			num = removeBlacklisted(m_xattrs);
		}

		if(num > 0)
		{
			std::cout << "[+] (" << num << ") " << path << std::endl;
			
		  	for (m_xit=m_xattrs.begin(); m_xit!=m_xattrs.end(); ++m_xit)
		  	{
		  		XattrHelper::getXattrValue(path, m_xit->m_attrName, m_xit->m_attrValue);
		    	XattrHelper::dumpXattr(*m_xit);
		  	}	
		  	std::cout << std::endl;	
	  	}
	}
	return 0;
}

int XattrSearcher::removeBlacklisted(std::list<Xattr> & xattrList)
{
	xattrList.remove_if(m_xattrsBlacklist);
	return xattrList.size();
}
