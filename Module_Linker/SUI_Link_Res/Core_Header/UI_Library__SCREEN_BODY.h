#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\UI_Library__SCREEN_HEADER.h"


//------------------------------------------------------
extern "C"
{
CInterface__CHANNEL_CTRL*		 New_LIB__CHANNEL_CTRL();
CInterface__SCREEN_CHANNEL_CTRL* New_LIB__SCREEN_CHANNEL_CTRL();
CInterface__SYS_INFO*            New_LIB__SYS_INFO();
CInterface__LOG_CHANNEL_CTRL*	 New_LIB__LOG_CHANNEL_CTRL();

};
//------------------------------------------------------


//------------------------------------------------------
class CX__CHANNEL_CTRL
{
private:
	CInterface__CHANNEL_CTRL *m_pT;

public:
	CX__CHANNEL_CTRL()
	{
		m_pT = New_LIB__CHANNEL_CTRL();
	}
	~CX__CHANNEL_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CInterface__CHANNEL_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CX__LOG_CHANNEL_CTRL
{
private:
	CInterface__LOG_CHANNEL_CTRL *m_pT;
	
public:
	CX__LOG_CHANNEL_CTRL()
	{
		m_pT = New_LIB__LOG_CHANNEL_CTRL();
	}
	~CX__LOG_CHANNEL_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}
	
	CInterface__LOG_CHANNEL_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CX__SCREEN_CHANNEL_CTRL
{
private:
	CInterface__SCREEN_CHANNEL_CTRL *m_pT;

public:
	CX__SCREEN_CHANNEL_CTRL()
	{
		m_pT = New_LIB__SCREEN_CHANNEL_CTRL();
	}
	~CX__SCREEN_CHANNEL_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CInterface__SCREEN_CHANNEL_CTRL* operator->() const
	{
		return m_pT;
	}
};	

class CX__SYS_INFO
{
private:
	CInterface__SYS_INFO *m_pT;

public:
	CX__SYS_INFO()
	{
		m_pT = New_LIB__SYS_INFO();
	}
	~CX__SYS_INFO()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CInterface__SYS_INFO* operator->() const
	{
		return m_pT;
	}
};
//------------------------------------------------------
