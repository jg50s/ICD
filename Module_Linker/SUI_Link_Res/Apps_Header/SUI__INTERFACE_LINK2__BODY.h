#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Apps_Header\SUI__INTERFACE_LINK2__HEADER.h"


#ifdef _DEBUG
	#pragma comment(lib, "C:\\Module_Linker\\SUI_Link_Res\\SUI_LIB\\SUI__INTERFACE_LINK2_D.lib")
#else
	#pragma comment(lib, "C:\\Module_Linker\\SUI_Link_Res\\SUI_LIB\\SUI__INTERFACE_LINK2_R.lib")
#endif


//----------------------------------------------------
extern "C"
{
CGI_FILE__PASSWORD_CTRL* New_CGI_FILE__PASSWORD_CTRL();
CGI_FILE__ALARM_CTRL*    New_CGI_FILE__ALARM_CTRL();
CGI__UTILITY_CTRL*	     New_CGI__UTILITY_CTRL();
CGI_FILE__PM_CTRL*		 New_CGI_FILE__PM_CTRL();
CGI_FILE__DATALOG_CTRL*  New_CGI_FILE__DATALOG_CTRL();
CGI_FILE__ROOT_CTRL*     New_CGI_FILE__ROOT_CTRL();
CGI__CONFIG_CTRL*		 New_CGI__CONFIG_CTRL();
CGI__SYSTEM_CTRL*		 New_CGI__SYSTEM_CTRL();
};
//----------------------------------------------------


//----------------------------------------------------
class CGX_FILE__PASSWORD_CTRL
{
private:
	CGI_FILE__PASSWORD_CTRL *m_pT;

public:
	CGX_FILE__PASSWORD_CTRL()
	{
		m_pT = New_CGI_FILE__PASSWORD_CTRL();
	}
	~CGX_FILE__PASSWORD_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CGI_FILE__PASSWORD_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CGX_FILE__ALARM_CTRL
{
private:
	CGI_FILE__ALARM_CTRL *m_pT;

public:
	CGX_FILE__ALARM_CTRL()
	{
		m_pT = New_CGI_FILE__ALARM_CTRL();
	}
	~CGX_FILE__ALARM_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CGI_FILE__ALARM_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CGX__UTILITY_CTRL
{
private:
	CGI__UTILITY_CTRL *m_pT;

public:
	CGX__UTILITY_CTRL()
	{
		m_pT = New_CGI__UTILITY_CTRL();
	}
	~CGX__UTILITY_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CGI__UTILITY_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CGX_FILE__PM_CTRL
{
private:
	CGI_FILE__PM_CTRL *m_pT;

public:
	CGX_FILE__PM_CTRL()
	{
		m_pT = New_CGI_FILE__PM_CTRL();
	}
	~CGX_FILE__PM_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CGI_FILE__PM_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CGX_FILE__DATALOG_CTRL
{
private:
	CGI_FILE__DATALOG_CTRL *m_pT;

public:
	CGX_FILE__DATALOG_CTRL()
	{
		m_pT = New_CGI_FILE__DATALOG_CTRL();
	}
	~CGX_FILE__DATALOG_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CGI_FILE__DATALOG_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CGX_FILE__ROOT_CTRL
{
private:
	CGI_FILE__ROOT_CTRL *m_pT;

public:
	CGX_FILE__ROOT_CTRL()
	{
		m_pT = New_CGI_FILE__ROOT_CTRL();
	}
	~CGX_FILE__ROOT_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CGI_FILE__ROOT_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CGX__CONFIG_CTRL
{
private:
	CGI__CONFIG_CTRL *m_pT;

public:
	CGX__CONFIG_CTRL()
	{
		m_pT = New_CGI__CONFIG_CTRL();
	}
	~CGX__CONFIG_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CGI__CONFIG_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CGX__SYSTEM_CTRL
{
private:
	CGI__SYSTEM_CTRL *m_pT;

public:
	CGX__SYSTEM_CTRL()
	{
		m_pT = New_CGI__SYSTEM_CTRL();
	}
	~CGX__SYSTEM_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CGI__SYSTEM_CTRL* operator->() const
	{
		return m_pT;
	}
};
//----------------------------------------------------
