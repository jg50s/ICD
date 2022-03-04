#include "C:\GES__Application_Interface\Interface_Header\UI\UTILITY\UI__MdbLink_Header.h"


#ifndef  _UI__MDBLINK_BODY_H_
#define  _UI__MDBLINK_BODY_H_


//----------------------------------------------------
extern "C"
{
UII__GOI_EXE_MDB_LINK_CTRL* New__GOI_EXE_MDB_LINK_CTRL();
};
//----------------------------------------------------


//----------------------------------------------------
//.....
class UIX__GOI_EXE_MDB_LINK_CTRL
{
private:
	UII__GOI_EXE_MDB_LINK_CTRL *m_pT;

public:
	UIX__GOI_EXE_MDB_LINK_CTRL()
	{
		m_pT = New__GOI_EXE_MDB_LINK_CTRL();
	}
	~UIX__GOI_EXE_MDB_LINK_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	UII__GOI_EXE_MDB_LINK_CTRL* operator->() const
	{
		return m_pT;
	}
	UII__GOI_EXE_MDB_LINK_CTRL* Get_PTR()
	{
		return m_pT;
	}
};
//----------------------------------------------------


#endif

