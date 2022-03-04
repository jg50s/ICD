#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\SUI__SERVICE_LINK__HEADER.h"


//----------------------------------------------------
extern "C"
{
CGui__Service_Ctrl*	New__Gui_Service_Ctrl();
};
//----------------------------------------------------


//----------------------------------------------------
class XGui__Service_Ctrl
{
private:
	CGui__Service_Ctrl *m_pT;

public:
	XGui__Service_Ctrl()
	{
		m_pT = New__Gui_Service_Ctrl();
	}
	~XGui__Service_Ctrl()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CGui__Service_Ctrl* operator->() const
	{
		return m_pT;
	}
};
//----------------------------------------------------
