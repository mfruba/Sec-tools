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

#ifndef __XATTR_HELPER_H_INCLUDED__
#define __XATTR_HELPER_H_INCLUDED__

#include "Config.h"
#include "Xattr.h"
#include <list>
#include <string>
#include <vector>


class XattrHelper 
{ 

private:


public:
	XattrHelper();
	static int getXattrList(std::string & filePath, std::list<Xattr> & list);
	static int getXattrValue(std::string & filePath, std::string & attrName, std::vector<char> & buff);
	static int dumpXattr(Xattr & xattr);



};

#endif 
