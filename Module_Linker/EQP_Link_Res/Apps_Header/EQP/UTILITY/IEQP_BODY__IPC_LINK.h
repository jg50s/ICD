#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\EQP\UTILITY\IEQP_HEADER__IPC_LINK.h"


extern "C"
{
SCI__IPC_INTERFACE_CTRL*  New__IPC_INTERFACE_CTRL();

};


class SCX__IPC_INTERFACE_CTRL
{
private:
	SCI__IPC_INTERFACE_CTRL *m_pT;

public:
	SCX__IPC_INTERFACE_CTRL()
	{
		m_pT = New__IPC_INTERFACE_CTRL();
	}
	~SCX__IPC_INTERFACE_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	SCI__IPC_INTERFACE_CTRL* operator->() const
	{
		return m_pT;
	}
};
