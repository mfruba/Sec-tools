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

#include "Xattr.h"
#include <iostream>
#include <iomanip>

Xattr::Xattr()
{

}

void Xattr::dump()
{
	std::cout << "Name: " << m_attrName << " Value: "  ;
	std::cout << std::hex << std::setfill('0');
	for(size_t i = 0; i < m_attrValue.size(); ++i)
		std::cout << "\\x"  << std::setw(2) << (unsigned int)((unsigned char)m_attrValue[i]); 

	std::cout << std::endl;
	std::cout << std::dec << std::setfill(' ');
}