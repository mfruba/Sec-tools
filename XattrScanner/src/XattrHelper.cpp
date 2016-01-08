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


#include "XattrHelper.h"

#include <sys/types.h>
#include <sys/xattr.h>
#include <cstring>
#include <iostream>

#include "CapabilityHelper.h"


XattrHelper::XattrHelper()
{

}

int XattrHelper::getXattrList(std::string & filePath, std::list<Xattr> & list)
{
	ssize_t size = listxattr(filePath.c_str(), NULL, 0);
	
	if(size > 0)
	{
		char * attrBuff = new char[size];
		memset(attrBuff,0, size);

		if(attrBuff == NULL)
		{
			std::cerr << "attrBuff allocation failed!" << std::endl;
			return 0;
		}
		size = listxattr(filePath.c_str(), attrBuff, size);
		if(size >= 0)
		{
			Xattr attr;
			const char* p = attrBuff;
			do 
			{
				attr.m_attrName = std::string(p);
				list.push_back(attr);
				p += attr.m_attrName.size() + 1;
			} 
			while ( attrBuff+size > p );
			
			
		}
		else
		{
			std::cerr << "listxattr(" << filePath << ",...) failed!" << std::endl;
			return 0;
		}
		delete [] attrBuff;
	}

	return list.size();
}

int XattrHelper::getXattrValue(std::string & filePath, std::string & attrName, std::vector<char> & buff)
{
	ssize_t size = getxattr(filePath.c_str(), attrName.c_str(), NULL, 0);
	if(size > 0)
	{
		buff.resize(size);
		size = getxattr(filePath.c_str(), attrName.c_str(), &buff[0], buff.size());
	}
	return size;
}

int XattrHelper::dumpXattr(Xattr & xattr)
{
	if(xattr.m_attrName.compare( "security.capability") == 0)
	{
		Capability cap;
		if(CapabilityHelper::rawDataToCapability(xattr.m_attrValue,cap)!=-1)
		{
			cap.dump();
		}
	}
	else
	{
		std::string str(&xattr.m_attrValue[0],xattr.m_attrValue.size());
		xattr.dump();
		std::cout << "Value String ( " << str << " )"<< std::endl;
	}
	return 0;
}
