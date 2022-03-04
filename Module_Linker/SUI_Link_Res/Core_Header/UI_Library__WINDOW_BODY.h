#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\UI_Library__WINDOW_HEADER.h"


//------------------------------------------------------
extern "C"
{
CInterface_Lib__WINDOW* New_LIB__WINDOW();
CI__WIN_CTRL* New__WIN_CTRL();
CI__SYSTEM_INFO* New__SYSTEM_INFO();
};
//------------------------------------------------------


//------------------------------------------------------
class CX__SYSTEN_INFO
{
private:
	CI__SYSTEM_INFO *m_pT;

public:
	CX__SYSTEN_INFO()
	{
		m_pT = New__SYSTEM_INFO();
	}
	~CX__SYSTEN_INFO()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI__SYSTEM_INFO* operator->() const
	{
		return m_pT;
	}
};

class CX__WINDOW_CTRL
{
private:
	CInterface_Lib__WINDOW *m_pT;

public:
	CX__WINDOW_CTRL()
	{
		m_pT = New_LIB__WINDOW();
	}
	~CX__WINDOW_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CInterface_Lib__WINDOW* operator->() const
	{
		return m_pT;
	}
};

class CX__WIN_CTRL
{
private:
	CI__WIN_CTRL *m_pT;

public:
	CX__WIN_CTRL()
	{
		m_pT = New__WIN_CTRL();
	}
	~CX__WIN_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI__WIN_CTRL* operator->() const
	{
		return m_pT;
	}
};
//------------------------------------------------------
