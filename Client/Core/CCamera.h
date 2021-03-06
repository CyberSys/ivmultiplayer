//============== IV:Multiplayer - https://github.com/Neproify/ivmultiplayer ==============
//
// File: CCamera.h
// Project: Client.Core
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==============================================================================

#pragma once

#include "IV/CIVCam.h"
#include "IV/CIVPed.h"

class CCamera
{
private:
	CIVCam *		m_pGameCam;
	CIVCam *		m_pScriptCam;
	bool			m_bScriptCamActive;

	int				m_iCameraAttached;
	unsigned int	m_uiCameraAttachedHandle;
public:
	CCamera();
	~CCamera();

	CIVCam * GetGameCam() { return m_pGameCam; }
	CIVCam * GetScriptCam() { return m_pScriptCam; }
	void     ActivateScriptCam();
	void     DeactivateScriptCam();
	void     Reset();
	void     SetBehindPed(CIVPed * pPed);
	void     SetPosition(const CVector3& vecPosition);
	void     GetPosition(CVector3& vecPosition);
	void     SetLookAt(const CVector3& vecLookAt, bool bWorldLoad = true);
	void     GetLookAt(CVector3& vecLookAt);
	void	 Attach(unsigned int uiHandle, bool bVehicleOrPlayer, int iPointType, CVector3 vecOffset);
	bool	 IsOnScreen(const CVector3& vecPosition);

	int				IsCameraAttached() { return m_iCameraAttached; }
	unsigned int	GetCameraAttachedHandle() { return m_uiCameraAttachedHandle; }
};
