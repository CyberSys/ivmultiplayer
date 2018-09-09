//============== IV:Multiplayer - https://github.com/Neproify/ivmultiplayer ==============
//
// File: CIVWeaponInfo.cpp
// Project: Client.Core
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVWeaponInfo.h"
#include <CLogFile.h>

CIVWeaponInfo::CIVWeaponInfo()
	: m_weaponType (WEAPON_TYPE_MAX)
	, m_pWeaponInfo(NULL)
{
}

CIVWeaponInfo::CIVWeaponInfo(eWeaponType weaponType, IVWeaponInfo * pWeaponInfo)
	: m_weaponType(weaponType),
	m_pWeaponInfo(pWeaponInfo)
{
}

CIVWeaponInfo::~CIVWeaponInfo()
{
}