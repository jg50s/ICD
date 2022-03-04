#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Core_Header\EQP_HEADER__Core_NET_Link.h"


//-----------------------------------------------------------------------
extern "C"
{
CI_SEQ_DB__INet_CTRL* New_SEQ_DB__INet_CTRL();
void Del_SEQ_DB__INet_CTRL(CI_SEQ_DB__INet_CTRL* p_cls);
};
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
class CX_SEQ_DB__INet_CTRL
{
private:
	CI_SEQ_DB__INet_CTRL *m_pT;

public:
	CX_SEQ_DB__INet_CTRL()
	{
		m_pT = New_SEQ_DB__INet_CTRL();
	}
	~CX_SEQ_DB__INet_CTRL()
	{
		// delete m_pT;
		Del_SEQ_DB__INet_CTRL(m_pT);
	}

	CI_SEQ_DB__INet_CTRL* operator->() const
	{
		return m_pT;
	}
};
//-----------------------------------------------------------------------
