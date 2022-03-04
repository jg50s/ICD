#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Core_Header\EQP_HEADER__UI_Link.h"


//-----------------------------------------------------------------------
extern "C"
{
CI_SEQ_UI__ALARM_CTRL* New_SEQ_UI__ALARM_CTRL();
};
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
class CX_SEQ_UI__ALARM_CTRL
{
private:
	CI_SEQ_UI__ALARM_CTRL *m_pT;

public:
	CX_SEQ_UI__ALARM_CTRL()
	{
		m_pT = New_SEQ_UI__ALARM_CTRL();
	}
	~CX_SEQ_UI__ALARM_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_SEQ_UI__ALARM_CTRL* operator->() const
	{
		return m_pT;
	}
};
//-----------------------------------------------------------------------

