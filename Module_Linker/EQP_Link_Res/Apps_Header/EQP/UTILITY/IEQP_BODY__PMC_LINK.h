#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\EQP\UTILITY\IEQP_HEADER__PMC_LINK.h"


extern "C"
{
	SCI__PMC__DCOP_CTRL*  New_SCI__PMC__DCOP_CTRL();
}


class SCX__PMC__DCOP_CTRL
{
private:
	SCI__PMC__DCOP_CTRL *m_pT;

public:
	SCX__PMC__DCOP_CTRL()
	{
		m_pT = New_SCI__PMC__DCOP_CTRL();
	}
	~SCX__PMC__DCOP_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}
	
	SCI__PMC__DCOP_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__PMC__DCOP_CTRL* Get__PTR()
	{
		return m_pT;
	}
};
