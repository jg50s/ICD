#include "C:\GES__Application_Interface\Interface_Header\UI\UTILITY\UI__IPC_Interface_Header.h"


#ifndef  _UI__IPC_INTERFACE_BODY_H_
#define  _UI__IPC_INTERFACE_BODY_H_


//----------------------------------------------------
extern "C"
{
UII__IPC_INTERFACE_CTRL*  New__IPC_INTERFACE_CTRL();

};
//----------------------------------------------------


//----------------------------------------------------
class UIX__IPC_INTERFACE_CTRL
{
private:
	UII__IPC_INTERFACE_CTRL *m_pT;

public:
	UIX__IPC_INTERFACE_CTRL()
	{
		m_pT = New__IPC_INTERFACE_CTRL();
	}
	~UIX__IPC_INTERFACE_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	UII__IPC_INTERFACE_CTRL* operator->() const
	{
		return m_pT;
	}

};
//----------------------------------------------------


#endif

