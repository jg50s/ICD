#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\EQP\UTILITY\IEQP_HEADER__DEBUG_LINK.h"


extern "C"
{
	SCI__CONSOLE_CTRL *New_SCI__Console_Ctrl();
	void Del_SCI__Console_Ctrl(SCI__CONSOLE_CTRL* p_cls);
	
	SCI__DEBUG_CTRL *New_SCI__Debug_Ctrl();
	void Del_SCI__Debug_Ctrl(SCI__DEBUG_CTRL* p_cls);
}


class SCX__CONSOLE_CTRL
{
private:
	SCI__CONSOLE_CTRL *m_pT;

public:
	SCX__CONSOLE_CTRL()
	{
		m_pT = New_SCI__Console_Ctrl();
	}
	~SCX__CONSOLE_CTRL()
	{
		Del_SCI__Console_Ctrl(m_pT);
	}
	
	SCI__CONSOLE_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__CONSOLE_CTRL* Get__SCI_PTR()
	{
		return m_pT;
	}
};

class SCX__DEBUG_CTRL
{
private:
	SCI__DEBUG_CTRL *m_pT;
	
public:
	SCX__DEBUG_CTRL()
	{
		m_pT = New_SCI__Debug_Ctrl();
	}
	~SCX__DEBUG_CTRL()
	{
		Del_SCI__Debug_Ctrl(m_pT);
	}
	
	SCI__DEBUG_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__DEBUG_CTRL* Get__SCI_PTR()
	{
		return m_pT;
	}
};

