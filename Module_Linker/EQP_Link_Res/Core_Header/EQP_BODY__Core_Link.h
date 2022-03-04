#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Core_Header\EQP_HEADER__Core_Link.h"


extern "C"
{
CI_SEQ_DB_CTRL__Memory_Check* New_SEQ_DB_CTRL__Memory_Check();
void Del_SEQ_DB_CTRL__Memory_Check(CI_SEQ_DB_CTRL__Memory_Check* p_cls);

//	
CI_SEQ_DB__CTRL* New_SEQ_DB__CTRL();
void Del_SEQ_DB__CTRL(CI_SEQ_DB__CTRL* p_cls);

//
CI_SEQ_DB__RECIPE_ITEM_CTRL* New_SEQ_DB__RECIPE_ITEM_CTRL();
void Del_SEQ_DB__RECIPE_ITEM_CTRL(CI_SEQ_DB__RECIPE_ITEM_CTRL* p_cls);

CI_SEQ_DB__CONFIG_ITEM_CTRL* New_SEQ_DB__CONFIG_ITEM_CTRL();
void Del_SEQ_DB__CONFIG_ITEM_CTRL(CI_SEQ_DB__CONFIG_ITEM_CTRL* p_cls);

CI_SEQ_DB__CHANNEL_CTRL* New_SEQ_DB__CHANNEL_CTRL();
void Del_SEQ_DB__CHANNEL_CTRL(CI_SEQ_DB__CHANNEL_CTRL* p_cls);

CI_SEQ_DB__OBJECT_CTRL* New_SEQ_DB__OBJECT_CTRL();
void Del_SEQ_DB__OBJECT_CTRL(CI_SEQ_DB__OBJECT_CTRL* p_cls);

//
CI_SEQ_DB__SYSTEM_CONFIG_CTRL* New_SEQ_DB__SYSTEM_CONFIG_CTRL();
void Del_SEQ_DB__SYSTEM_CONFIG_CTRL(CI_SEQ_DB__SYSTEM_CONFIG_CTRL* p_cls);

CI_SEQ_DB__DATALOG_VIEW_CTRL* New_SEQ_DB__DATALOG_VIEW_CTRL();
void Del_SEQ_DB__DATALOG_VIEW_CTRL(CI_SEQ_DB__DATALOG_VIEW_CTRL* p_cls);

CI_SEQ_DB__MATERIAL_VIEW_CTRL* New_SEQ_DB__MATERIAL_VIEW_CTRL();
void Del_SEQ_DB__MATERIAL_VIEW_CTRL(CI_SEQ_DB__MATERIAL_VIEW_CTRL* p_cls);

CI_SEQ_DB__OBJECT_EDITOR_CTRL* New_SEQ_DB__OBJECT_EDITOR_CTRL();
void Del_SEQ_DB__OBJECT_EDITOR_CTRL(CI_SEQ_DB__OBJECT_EDITOR_CTRL* p_cls);

//
CI_SEQ_DB__OBJECT_INFO_CTRL* New_SEQ_DB__OBJECT_INFO_CTRL();
void Del_SEQ_DB__OBJECT_INFO_CTRL(CI_SEQ_DB__OBJECT_INFO_CTRL* p_cls);

CI_SEQ_DB__SYSTEM_DIR_INFO* New_SEQ_DB__SYSTEM_DIR_INFO();
void Del_SEQ_DB__SYSTEM_DIR_INFO(CI_SEQ_DB__SYSTEM_DIR_INFO* p_cls);

//
CII_AWI__OBJECT_VARIABLE_CTRL* New_II_AWI__OBJECT_VARIABLE_CTRL();
void Del_II_AWI__OBJECT_VARIABLE_CTRL(CII_AWI__OBJECT_VARIABLE_CTRL* p_cls);

CII_AWI__OBJECT_ALARM_CTRL* New_II_AWI__OBJECT_ALARM_CTRL();
void Del_II_AWI__OBJECT_ALARM_CTRL(CII_AWI__OBJECT_ALARM_CTRL* p_cls);

CII_AWI__OBJECT_UTILITY_CTRL* New_II_AWI__OBJECT_UTILITY_CTRL();
void Del_II_AWI__OBJECT_UTILITY_CTRL(CII_AWI__OBJECT_UTILITY_CTRL* p_cls);

//
CI_SEQ_CORE__QUERY_CTRL* New_SEQ_CORE__QUERY_CTRL();
void Del_SEQ_CORE__QUERY_CTRL(CI_SEQ_CORE__QUERY_CTRL* p_cls);

//
CII_EQP_CORE__SYSTEM_CTRL* New_EQP_CORE__SYSTEM_CTRL();
};


class CX_SEQ_DB_CTRL__Memory_Check
{
private:
	CI_SEQ_DB_CTRL__Memory_Check *m_pT;
	
public:
	CX_SEQ_DB_CTRL__Memory_Check()
	{
		m_pT = New_SEQ_DB_CTRL__Memory_Check();
	}
	~CX_SEQ_DB_CTRL__Memory_Check()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SEQ_DB_CTRL__Memory_Check(m_pT);
		}
	}
	
	CI_SEQ_DB_CTRL__Memory_Check* operator->() const
	{
		return m_pT;
	}
};

class CX_SEQ_CORE__QUERY_CTRL
{
private:
	CI_SEQ_CORE__QUERY_CTRL *m_pT;

public:
	CX_SEQ_CORE__QUERY_CTRL()
	{
		m_pT = New_SEQ_CORE__QUERY_CTRL();
	}
	~CX_SEQ_CORE__QUERY_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SEQ_CORE__QUERY_CTRL(m_pT);
		}
	}

	CI_SEQ_CORE__QUERY_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CX_EQP_CORE__SYSTEM_CTRL
{
private:
	CII_EQP_CORE__SYSTEM_CTRL *m_pT;

public:
	CX_EQP_CORE__SYSTEM_CTRL()
	{
		m_pT = New_EQP_CORE__SYSTEM_CTRL();
	}
	~CX_EQP_CORE__SYSTEM_CTRL()
	{
		if(m_pT != NULL)		delete m_pT;
	}

	CII_EQP_CORE__SYSTEM_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CX_II_AWI__OBJECT_UTILITY_CTRL
{
private:
	CII_AWI__OBJECT_UTILITY_CTRL *m_pT;

public:
	CX_II_AWI__OBJECT_UTILITY_CTRL()
	{
		m_pT = New_II_AWI__OBJECT_UTILITY_CTRL();
	}
	~CX_II_AWI__OBJECT_UTILITY_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_II_AWI__OBJECT_UTILITY_CTRL(m_pT);
		}
	}

	CII_AWI__OBJECT_UTILITY_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CX_II_AWI__OBJECT_VARIABLE_CTRL
{
private:
	CII_AWI__OBJECT_VARIABLE_CTRL *m_pT;

public:
	CX_II_AWI__OBJECT_VARIABLE_CTRL()
	{
		m_pT = New_II_AWI__OBJECT_VARIABLE_CTRL();
	}
	~CX_II_AWI__OBJECT_VARIABLE_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_II_AWI__OBJECT_VARIABLE_CTRL(m_pT);
		}
	}

	CII_AWI__OBJECT_VARIABLE_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CX_II_AWI__OBJECT_ALARM_CTRL
{
private:
	CII_AWI__OBJECT_ALARM_CTRL *m_pT;

public:
	CX_II_AWI__OBJECT_ALARM_CTRL()
	{
		m_pT = New_II_AWI__OBJECT_ALARM_CTRL();
	}
	~CX_II_AWI__OBJECT_ALARM_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_II_AWI__OBJECT_ALARM_CTRL(m_pT);
		}
	}

	CII_AWI__OBJECT_ALARM_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CX_SEQ_DB__CTRL
{
private:
	CI_SEQ_DB__CTRL *m_pT;

public:
	CX_SEQ_DB__CTRL()
	{
		m_pT = New_SEQ_DB__CTRL();
	}
	~CX_SEQ_DB__CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SEQ_DB__CTRL(m_pT);
		}
	}

	CI_SEQ_DB__CTRL* operator->() const
	{
		return m_pT;
	}
};

class CX_SEQ_DB__RECIPE_ITEM_CTRL
{
private:
	CI_SEQ_DB__RECIPE_ITEM_CTRL *m_pT;

public:
	CX_SEQ_DB__RECIPE_ITEM_CTRL()
	{
		m_pT = New_SEQ_DB__RECIPE_ITEM_CTRL();
	}
	~CX_SEQ_DB__RECIPE_ITEM_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SEQ_DB__RECIPE_ITEM_CTRL(m_pT);
		}
	}

	CI_SEQ_DB__RECIPE_ITEM_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CX_SEQ_DB__CONFIG_ITEM_CTRL
{
private:
	CI_SEQ_DB__CONFIG_ITEM_CTRL *m_pT;

public:
	CX_SEQ_DB__CONFIG_ITEM_CTRL()
	{
		m_pT = New_SEQ_DB__CONFIG_ITEM_CTRL();
	}
	~CX_SEQ_DB__CONFIG_ITEM_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SEQ_DB__CONFIG_ITEM_CTRL(m_pT);
		}
	}

	CI_SEQ_DB__CONFIG_ITEM_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CX_SEQ_DB__OBJECT_CTRL
{
private:
	CI_SEQ_DB__OBJECT_CTRL *m_pT;

public:
	CX_SEQ_DB__OBJECT_CTRL()
	{
		m_pT = New_SEQ_DB__OBJECT_CTRL();
	}
	~CX_SEQ_DB__OBJECT_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SEQ_DB__OBJECT_CTRL(m_pT);
		}
	}

	CI_SEQ_DB__OBJECT_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CX_SEQ_DB__CHANNEL_CTRL
{
private:
	CI_SEQ_DB__CHANNEL_CTRL *m_pT;

public:
	CX_SEQ_DB__CHANNEL_CTRL()
	{
		m_pT = New_SEQ_DB__CHANNEL_CTRL();
	}
	~CX_SEQ_DB__CHANNEL_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SEQ_DB__CHANNEL_CTRL(m_pT);
		}
	}

	CI_SEQ_DB__CHANNEL_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CX_SEQ_DB__SYSTEM_CONFIG_CTRL
{
private:
	CI_SEQ_DB__SYSTEM_CONFIG_CTRL *m_pT;

public:
	CX_SEQ_DB__SYSTEM_CONFIG_CTRL()
	{
		m_pT = New_SEQ_DB__SYSTEM_CONFIG_CTRL();
	}
	~CX_SEQ_DB__SYSTEM_CONFIG_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SEQ_DB__SYSTEM_CONFIG_CTRL(m_pT);
		}
	}

	CI_SEQ_DB__SYSTEM_CONFIG_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CX_SEQ_DB__SYSTEM_DIR_INFO
{
private:
	CI_SEQ_DB__SYSTEM_DIR_INFO *m_pT;

public:
	CX_SEQ_DB__SYSTEM_DIR_INFO()
	{
		m_pT = New_SEQ_DB__SYSTEM_DIR_INFO();
	}
	~CX_SEQ_DB__SYSTEM_DIR_INFO()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SEQ_DB__SYSTEM_DIR_INFO(m_pT);
		}
	}

	CI_SEQ_DB__SYSTEM_DIR_INFO* operator->() const
	{
		return m_pT;
	}
};

class CX_SEQ_DB__DATALOG_VIEW_CTRL
{
private:
	CI_SEQ_DB__DATALOG_VIEW_CTRL *m_pT;

public:
	CX_SEQ_DB__DATALOG_VIEW_CTRL()
	{
		m_pT = New_SEQ_DB__DATALOG_VIEW_CTRL();
	}
	~CX_SEQ_DB__DATALOG_VIEW_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SEQ_DB__DATALOG_VIEW_CTRL(m_pT);
		}
	}

	CI_SEQ_DB__DATALOG_VIEW_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CX_SEQ_DB__MATERIAL_VIEW_CTRL
{
private:
	CI_SEQ_DB__MATERIAL_VIEW_CTRL *m_pT;

public:
	CX_SEQ_DB__MATERIAL_VIEW_CTRL()
	{
		m_pT = New_SEQ_DB__MATERIAL_VIEW_CTRL();
	}
	~CX_SEQ_DB__MATERIAL_VIEW_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SEQ_DB__MATERIAL_VIEW_CTRL(m_pT);
		}
	}

	CI_SEQ_DB__MATERIAL_VIEW_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CX_SEQ_DB__OBJECT_EDITOR_CTRL
{
private:
	CI_SEQ_DB__OBJECT_EDITOR_CTRL *m_pT;

public:
	CX_SEQ_DB__OBJECT_EDITOR_CTRL()
	{
		m_pT = New_SEQ_DB__OBJECT_EDITOR_CTRL();
	}
	~CX_SEQ_DB__OBJECT_EDITOR_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SEQ_DB__OBJECT_EDITOR_CTRL(m_pT);
		}
	}

	CI_SEQ_DB__OBJECT_EDITOR_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CX_SEQ_DB__OBJECT_INFO_CTRL
{
private:
	CI_SEQ_DB__OBJECT_INFO_CTRL *m_pT;

public:
	CX_SEQ_DB__OBJECT_INFO_CTRL()
	{
		m_pT = New_SEQ_DB__OBJECT_INFO_CTRL();
	}
	~CX_SEQ_DB__OBJECT_INFO_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SEQ_DB__OBJECT_INFO_CTRL(m_pT);
		}
	}

	CI_SEQ_DB__OBJECT_INFO_CTRL* operator->() const
	{
		return m_pT;
	}
};
