#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Apps_Header\SUI__INTERFACE_LINK1__HEADER.h"


#ifdef _DEBUG
	#pragma comment(lib, "C:\\Module_Linker\\SUI_Link_Res\\SUI_LIB\\SUI__INTERFACE_LINK1_D.lib")
#else
	#pragma comment(lib, "C:\\Module_Linker\\SUI_Link_Res\\SUI_LIB\\SUI__INTERFACE_LINK1_R.lib")
#endif


//----------------------------------------------------
extern "C"
{
UII__SCREEN_USER_LEVEL_CTRL* New__SCREEN_USER_LEVEL_CTRL();
UII__SEQ_VERSION_INFO_CTRL*  New__SEQ_VERSION_INFO_CTRL();

UII__ANALOG_PAD_CTRL*  New__ANALOG_PAD_CTRL();
UII__DIGITAL_PAD_CTRL* New__DIGITAL_PAD_CTRL();
UII__STRING_PAD_CTRL*  New__STRING_PAD_CTRL();

UII__FLASH_CTRL*       New__FLASH_CTRL();
UII__LAYERED_WIN_CTRL* New__LAYERED_WIN_CTRL();
};
//----------------------------------------------------


//----------------------------------------------------
class UIX__SCREEN_USER_LEVEL_CTRL
{
private:
	UII__SCREEN_USER_LEVEL_CTRL *m_pT;

public:
	UIX__SCREEN_USER_LEVEL_CTRL()
	{
		m_pT = New__SCREEN_USER_LEVEL_CTRL();
	}
	~UIX__SCREEN_USER_LEVEL_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	UII__SCREEN_USER_LEVEL_CTRL* operator->() const
	{
		return m_pT;
	}
};

class UIX__SEQ_VERSION_INFO_CTRL
{
private:
	UII__SEQ_VERSION_INFO_CTRL *m_pT;

public:
	UIX__SEQ_VERSION_INFO_CTRL()
	{
		m_pT = New__SEQ_VERSION_INFO_CTRL();
	}
	~UIX__SEQ_VERSION_INFO_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	UII__SEQ_VERSION_INFO_CTRL* operator->() const
	{
		return m_pT;
	}
};
//----------------------------------------------------

//----------------------------------------------------
class UIX__ANALOG_PAD_CTRL
{
private:
	UII__ANALOG_PAD_CTRL *m_pT;

public:
	UIX__ANALOG_PAD_CTRL()
	{
		m_pT = New__ANALOG_PAD_CTRL();
	}
	~UIX__ANALOG_PAD_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	UII__ANALOG_PAD_CTRL* operator->() const
	{
		return m_pT;
	}
};

class UIX__DIGITAL_PAD_CTRL
{
private:
	UII__DIGITAL_PAD_CTRL *m_pT;

public:
	UIX__DIGITAL_PAD_CTRL()
	{
		m_pT = New__DIGITAL_PAD_CTRL();
	}
	~UIX__DIGITAL_PAD_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	UII__DIGITAL_PAD_CTRL* operator->() const
	{
		return m_pT;
	}
};

class UIX__STRING_PAD_CTRL
{
private:
	UII__STRING_PAD_CTRL *m_pT;

public:
	UIX__STRING_PAD_CTRL()
	{
		m_pT = New__STRING_PAD_CTRL();
	}
	~UIX__STRING_PAD_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	UII__STRING_PAD_CTRL* operator->() const
	{
		return m_pT;
	}
};
//----------------------------------------------------

//----------------------------------------------------
class UIX__FLASH_CTRL
{
private:
	UII__FLASH_CTRL *m_pT;

public:
	UIX__FLASH_CTRL()
	{
		m_pT = New__FLASH_CTRL();
	}
	~UIX__FLASH_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	UII__FLASH_CTRL* operator->() const
	{
		return m_pT;
	}
};
//----------------------------------------------------

//----------------------------------------------------
class UIX__LAYERED_WIN_CTRL
{
private:
	UII__LAYERED_WIN_CTRL *m_pT;

public:
	UIX__LAYERED_WIN_CTRL()
	{
		m_pT = New__LAYERED_WIN_CTRL();
	}
	~UIX__LAYERED_WIN_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	UII__LAYERED_WIN_CTRL* operator->() const
	{
		return m_pT;
	}
};
//----------------------------------------------------
