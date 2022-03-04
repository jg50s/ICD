#include "C:\GES__Application_Interface\Interface_Header\UI\UTILITY\UI__ExeNetLink_Header.h"


#ifndef  _UI__ExeNetLink_BODY_H_
#define  _UI__ExeNetLink_BODY_H_


//----------------------------------------------------
extern "C"
{
UII__ExeNetLink_Ctrl* New__ExeNetLink_Ctrl();
};
//----------------------------------------------------


//----------------------------------------------------
// ...
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


#endif

