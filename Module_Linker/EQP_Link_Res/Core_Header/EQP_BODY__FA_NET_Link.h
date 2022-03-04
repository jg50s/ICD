#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Core_Header\EQP_HEADER__FA_NET_Link.h"


//------------------------------------------------------
extern "C"
{
CI_FA_NET__CTRL* New_FA_NET__CTRL();
void Del_FA_NET__CTRL(CI_FA_NET__CTRL* p_cls);

};
//------------------------------------------------------


//------------------------------------------------------
class CX_FA_NET__CTRL
{
private:
	CI_FA_NET__CTRL *m_pT;

public:
	CX_FA_NET__CTRL()
	{
		m_pT = New_FA_NET__CTRL();
	}
	~CX_FA_NET__CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_FA_NET__CTRL(m_pT);
		}
	}

	CI_FA_NET__CTRL* operator->() const
	{
		return m_pT;
	}
	CI_FA_NET__CTRL* Get__PTR()
	{
		return m_pT;
	}	
};
//------------------------------------------------------

