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

#ifndef __CAPACBILITY_HELPER_H_INCLUDED__
#define __CAPACBILITY_HELPER_H_INCLUDED__

#include <vector>


//SYSCALL raw data format
#include <linux/types.h>

#define VFS_CAP_REVISION_2	0x02000000
#define VFS_CAP_U32_2           2
#define VFS_CAP_U32             VFS_CAP_U32_2
struct vfs_cap_data {
	__le32 magic_etc;            /* Little endian */
	struct {
		__le32 permitted;    /* Little endian */
		__le32 inheritable;  /* Little endian */
	} data[VFS_CAP_U32];
};

class Capability
{
public:
	unsigned long m_version;
	unsigned long long m_capInheritable;
	unsigned long long m_capPermitted;
	unsigned int m_capEfective; // 0 or 1; 1 means capEffective will be applied

	Capability();
	void dump();
};


class CapabilityHelper
{
public:
	static int rawDataToCapability(std::vector<char> & buffer, Capability & cap);

};

#endif 