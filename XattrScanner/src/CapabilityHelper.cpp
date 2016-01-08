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

#include "CapabilityHelper.h"

#include <iostream>
#include <iomanip>

Capability::Capability()
{
	m_version = 0;
	m_capInheritable = 0;
	m_capPermitted = 0;
	m_capEfective = 0;
}

void Capability::dump()
{
	std::cout << std::hex;
	//std::cout << "Version: " << m_version; // (Same on whole device, no need to dump)
	std::cout << " capInheritable: 0x" << std::setfill('0') << std::setw(sizeof(m_capInheritable)*2) << m_capInheritable;
	std::cout << " capPermitted: 0x" << std::setw(sizeof(m_capPermitted)*2) << m_capPermitted;
	std::cout << " capEfective: 0x" << std::setw(2) << m_capEfective;
	std::cout << std::endl << std::dec << std::setfill(' ');
}


int CapabilityHelper::rawDataToCapability(std::vector<char> & buffer, Capability & cap)
{
	if(buffer.size()<sizeof(struct vfs_cap_data))
		return -1;

	struct vfs_cap_data * dcap = (struct vfs_cap_data*)&buffer[0];
	cap.m_version = dcap->magic_etc & 0xfffffffe;
	cap.m_capInheritable = ((unsigned long long)dcap->data[0].inheritable) | (((unsigned long long)dcap->data[1].inheritable  ) << 32 );
	cap.m_capPermitted = ((unsigned long long)dcap->data[0].permitted) | (((unsigned long long)dcap->data[1].permitted  ) << 32 );
	cap.m_capEfective = dcap->magic_etc & 0x1;
	return 0;
}