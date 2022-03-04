#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\SUI__MODULE_CTRL__HEADER.h"


//----------------------------------------------------
extern "C"
{
CGui__DB_Ctrl*	New__Gui_DB_Ctrl();
};
//----------------------------------------------------


//----------------------------------------------------
class XGui__DB_Ctrl
{
private:
	CGui__DB_Ctrl *m_pT;

public:
	XGui__DB_Ctrl()
	{
		m_pT = New__Gui_DB_Ctrl();
	}
	~XGui__DB_Ctrl()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CGui__DB_Ctrl* operator->() const
	{
		return m_pT;
	}
};
//----------------------------------------------------
