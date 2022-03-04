#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Apps_Header\SUI__EXE_LINK__HEADER.h"


//----------------------------------------------------
extern "C"
{
UII__ExeNetLink_Ctrl* New__ExeNetLink_Ctrl();
};
//----------------------------------------------------


//----------------------------------------------------
class UIX__ExeNetLink_Ctrl
{
private:
	UII__ExeNetLink_Ctrl *m_pT;

public:
	UIX__ExeNetLink_Ctrl()
	{
		m_pT = New__ExeNetLink_Ctrl();
	}
	~UIX__ExeNetLink_Ctrl()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	UII__ExeNetLink_Ctrl* operator->() const
	{
		return m_pT;
	}
	UII__ExeNetLink_Ctrl* Get_PTR()
	{
		return m_pT;
	}
};
//----------------------------------------------------
