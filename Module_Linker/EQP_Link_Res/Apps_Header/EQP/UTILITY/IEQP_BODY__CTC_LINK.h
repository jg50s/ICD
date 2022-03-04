#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\EQP\UTILITY\IEQP_HEADER__CTC_LINK.h"


extern "C"
{
	SCI__CTC__SCH_MATERIAL_CTRL* New_SCI__CTC__SCH_MATERIAL_CTRL();
	void Del_SCI__CTC__SCH_MATERIAL_CTRL(SCI__CTC__SCH_MATERIAL_CTRL* p_cls);

	SCI__CTC__JOB_FILE_CTRL* New_SCI__CTC__JOB_FILE_CTRL();
	void Del_SCI__CTC__JOB_FILE_CTRL(SCI__CTC__JOB_FILE_CTRL* p_cls);

	SCI__CTC__CJOB_CTRL* New_SCI__CTC__CJOB_CTRL();
	void Del_SCI__CTC__CJOB_CTRL(SCI__CTC__CJOB_CTRL* p_cls);

	SCI__CTC__MODULE_OBJ* New_SCI__CTC__MODULE_OBJ();
	void Del_SCI__CTC__MODULE_OBJ(SCI__CTC__MODULE_OBJ* p_cls);
	
	SCI__CTC__LOT_SUMMARY_CTRL* New_SCI__CTC__LOT_SUMMARY_CTRL();
	void Del_SCI__CTC__LOT_SUMMARY_CTRL(SCI__CTC__LOT_SUMMARY_CTRL* p_cls);

	SCI__CTC__MATERIAL_LOG_CTRL* New_SCI__CTC__MATERIAL_LOG_CTRL();
	void Del_SCI__CTC__MATERIAL_LOG_CTRL(SCI__CTC__MATERIAL_LOG_CTRL* p_cls);

	SCI__LCD_DB_CTRL* New_SCI__LCD_DB_CTRL();
	void Del_SCI__LCD_DB_CTRL(SCI__LCD_DB_CTRL* p_cls);

	SCI__FTP_CTRL* New_SCI__FTP_CTRL();
	void Del_SCI__FTP_CTRL(SCI__FTP_CTRL* p_cls);

	CII__COMMON_CODE__ERROR_FEEDBACK__MODULE_OBJ* New_CII__COMMON_CODE__ERROR_FEEDBACK__MODULE_OBJ();
	void Del_CII__COMMON_CODE__ERROR_FEEDBACK__MODULE_OBJ(CII__COMMON_CODE__ERROR_FEEDBACK__MODULE_OBJ* p_cls);

	//
	SCI__Memory_Check__SC_Library__CTC_CTRL* New_SCI__Memory_Check__SC_Library__CTC_CTRL();
	void Del_SCI__Memory_Check__SC_Library__CTC_CTRL(SCI__Memory_Check__SC_Library__CTC_CTRL* p_cls);

	SCI__Memory_Check__SC__NET_CTRL* New_SCI__Memory_Check__SC__NET_CTRL();
	void Del_SCI__Memory_Check__SC__NET_CTRL(SCI__Memory_Check__SC__NET_CTRL* p_cls);

	SCI__Memory_Check__SC__DB_CTRL* New_SCI__Memory_Check__SC__DB_CTRL();
	void Del_SCI__Memory_Check__SC__DB_CTRL(SCI__Memory_Check__SC__DB_CTRL* p_cls);

	//
	SCI__LOT_LOG_CTRL* New_SCI__LOT_LOG_CTRL();
	void Del_SCI__LOT_LOG_CTRL(SCI__LOT_LOG_CTRL* p_cls);
}


// ...
class SCX__Memory_Check__SC__NET_CTRL
{
private:
	SCI__Memory_Check__SC__NET_CTRL *m_pT;
	
public:
	SCX__Memory_Check__SC__NET_CTRL()
	{
		m_pT = New_SCI__Memory_Check__SC__NET_CTRL();
	}
	~SCX__Memory_Check__SC__NET_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SCI__Memory_Check__SC__NET_CTRL(m_pT);
		}
	}
	
	SCI__Memory_Check__SC__NET_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__Memory_Check__SC__NET_CTRL* Get__SCI_PTR()
	{
		return m_pT;
	}
};

class SCX__Memory_Check__SC_Library__CTC_CTRL
{
private:
	SCI__Memory_Check__SC_Library__CTC_CTRL *m_pT;
	
public:
	SCX__Memory_Check__SC_Library__CTC_CTRL()
	{
		m_pT = New_SCI__Memory_Check__SC_Library__CTC_CTRL();
	}
	~SCX__Memory_Check__SC_Library__CTC_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SCI__Memory_Check__SC_Library__CTC_CTRL(m_pT);
		}
	}
	
	SCI__Memory_Check__SC_Library__CTC_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__Memory_Check__SC_Library__CTC_CTRL* Get__SCI_PTR()
	{
		return m_pT;
	}
};

class SCX__Memory_Check__SC__DB_CTRL
{
private:
	SCI__Memory_Check__SC__DB_CTRL *m_pT;
	
public:
	SCX__Memory_Check__SC__DB_CTRL()
	{
		m_pT = New_SCI__Memory_Check__SC__DB_CTRL();
	}
	~SCX__Memory_Check__SC__DB_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SCI__Memory_Check__SC__DB_CTRL(m_pT);
		}
	}
	
	SCI__Memory_Check__SC__DB_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__Memory_Check__SC__DB_CTRL* Get__SCI_PTR()
	{
		return m_pT;
	}
};

class SCX__LOT_LOG_CTRL
{
private:
	SCI__LOT_LOG_CTRL *m_pT;
	
public:
	SCX__LOT_LOG_CTRL()
	{
		m_pT = New_SCI__LOT_LOG_CTRL();
	}
	~SCX__LOT_LOG_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SCI__LOT_LOG_CTRL(m_pT);
		}
	}
	
	SCI__LOT_LOG_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__LOT_LOG_CTRL* Get__SCI_PTR()
	{
		return m_pT;
	}
};


// ...
class CX__COMMON_CODE__ERROR_FEEDBACK__MODULE_OBJ
{
private:
	CII__COMMON_CODE__ERROR_FEEDBACK__MODULE_OBJ *m_pT;
	
public:
	CX__COMMON_CODE__ERROR_FEEDBACK__MODULE_OBJ()
	{
		m_pT = New_CII__COMMON_CODE__ERROR_FEEDBACK__MODULE_OBJ();
	}
	~CX__COMMON_CODE__ERROR_FEEDBACK__MODULE_OBJ()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_CII__COMMON_CODE__ERROR_FEEDBACK__MODULE_OBJ(m_pT);
		}
	}
	
	CII__COMMON_CODE__ERROR_FEEDBACK__MODULE_OBJ* operator->() const
	{
		return m_pT;
	}
	CII__COMMON_CODE__ERROR_FEEDBACK__MODULE_OBJ* Get__SCI_PTR()
	{
		return m_pT;
	}
};


// ...
class SCX__FTP_CTRL
{
private:
	SCI__FTP_CTRL *m_pT;

public:
	SCX__FTP_CTRL()
	{
		m_pT = New_SCI__FTP_CTRL();
	}
	~SCX__FTP_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SCI__FTP_CTRL(m_pT);
		}
	}
	
	SCI__FTP_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__FTP_CTRL* Get__PTR()
	{
		return m_pT;
	}
};

//
class SCX__CTC__SCH_MATERIAL_CTRL
{
private:
	SCI__CTC__SCH_MATERIAL_CTRL *m_pT;

public:
	SCX__CTC__SCH_MATERIAL_CTRL()
	{
		m_pT = New_SCI__CTC__SCH_MATERIAL_CTRL();
	}
	~SCX__CTC__SCH_MATERIAL_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SCI__CTC__SCH_MATERIAL_CTRL(m_pT);
		}
	}
	
	SCI__CTC__SCH_MATERIAL_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__CTC__SCH_MATERIAL_CTRL* Get__PTR()
	{
		return m_pT;
	}
};

//
class SCX__CTC__JOB_FILE_CTRL
{
private:
	SCI__CTC__JOB_FILE_CTRL *m_pT;

public:
	SCX__CTC__JOB_FILE_CTRL()
	{
		m_pT = New_SCI__CTC__JOB_FILE_CTRL();
	}
	~SCX__CTC__JOB_FILE_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SCI__CTC__JOB_FILE_CTRL(m_pT);
		}
	}
	
	SCI__CTC__JOB_FILE_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__CTC__JOB_FILE_CTRL* Get__PTR()
	{
		return m_pT;
	}
};

//
class SCX__CTC__MODULE_OBJ
{
private:
	SCI__CTC__MODULE_OBJ *m_pT;

public:
	SCX__CTC__MODULE_OBJ()
	{
		m_pT = New_SCI__CTC__MODULE_OBJ();
	}
	~SCX__CTC__MODULE_OBJ()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SCI__CTC__MODULE_OBJ(m_pT);
		}
	}
	
	SCI__CTC__MODULE_OBJ* operator->() const
	{
		return m_pT;
	}
	SCI__CTC__MODULE_OBJ* Get__PTR()
	{
		return m_pT;
	}
};

//
class SCX__CTC__LOT_SUMMARY_CTRL
{
private:
	SCI__CTC__LOT_SUMMARY_CTRL *m_pT;

public:
	SCX__CTC__LOT_SUMMARY_CTRL()
	{
		m_pT = New_SCI__CTC__LOT_SUMMARY_CTRL();
	}
	~SCX__CTC__LOT_SUMMARY_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SCI__CTC__LOT_SUMMARY_CTRL(m_pT);
		}
	}
	
	SCI__CTC__LOT_SUMMARY_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__CTC__LOT_SUMMARY_CTRL* Get__PTR()
	{
		return m_pT;
	}
};

//
class SCX__CTC__MATERIAL_LOG_CTRL
{
private:
	SCI__CTC__MATERIAL_LOG_CTRL *m_pT;

public:
	SCX__CTC__MATERIAL_LOG_CTRL()
	{
		m_pT = New_SCI__CTC__MATERIAL_LOG_CTRL();
	}
	~SCX__CTC__MATERIAL_LOG_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SCI__CTC__MATERIAL_LOG_CTRL(m_pT);
		}
	}
	
	SCI__CTC__MATERIAL_LOG_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__CTC__MATERIAL_LOG_CTRL* Get__PTR()
	{
		return m_pT;
	}
};

//
class SCX__LCD_DB_CTRL
{
private:
	SCI__LCD_DB_CTRL *m_pT;

public:
	SCX__LCD_DB_CTRL()
	{
		m_pT = New_SCI__LCD_DB_CTRL();
	}
	~SCX__LCD_DB_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SCI__LCD_DB_CTRL(m_pT);
		}
	}
	
	SCI__LCD_DB_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__LCD_DB_CTRL* Get__PTR()
	{
		return m_pT;
	}
};

