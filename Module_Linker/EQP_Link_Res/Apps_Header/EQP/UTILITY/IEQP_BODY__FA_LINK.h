#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\EQP\UTILITY\IEQP_HEADER__FA_LINK.h"


extern "C"
{
	SCI__FA_CTRL*  New_SCI__FA_CTRL();
}


class SCX__FA_CTRL
{
private:
	SCI__FA_CTRL *m_pT;

public:
	SCX__FA_CTRL()
	{
		m_pT = New_SCI__FA_CTRL();
	}
	~SCX__FA_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}
	
	SCI__FA_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__FA_CTRL* Get__PTR()
	{
		return m_pT;
	}
};
