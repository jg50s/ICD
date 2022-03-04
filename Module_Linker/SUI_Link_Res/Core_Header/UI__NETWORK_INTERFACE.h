#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\cinterface_gui__net_interface.h"


//----------------------------------------------------
extern "C"
{
CI_GUI__NET_CTRL* New_GUI__NET_CTRL();
};
//----------------------------------------------------


//----------------------------------------------------
class CX_GUI__NET_CTRL
{
private:
	CI_GUI__NET_CTRL *m_pT;

public:
	CX_GUI__NET_CTRL()
	{
		m_pT = New_GUI__NET_CTRL();
	}
	~CX_GUI__NET_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_GUI__NET_CTRL* operator->() const
	{
		return m_pT;
	}
};
//----------------------------------------------------
