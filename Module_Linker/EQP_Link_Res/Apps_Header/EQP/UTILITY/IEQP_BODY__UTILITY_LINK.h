#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\EQP\UTILITY\IEQP_HEADER__UTILITY_LINK.h"


extern "C"
{
	SCI__Memory_Check* New_SCI__Memory_Check();
	void Del_SCI__Memory_Check(SCI__Memory_Check* p_cls);

	SCI__USER_LOG_CTRL* New_SCI__USER_LOG_CTRL();
	void Del_SCI__USER_LOG_CTRL(SCI__USER_LOG_CTRL* p_cls);

	SCI__STEP_TIMER_CTRL* New_SCI__STEP_TIMER_CTRL();

	SCI__TIMER_CTRL* New_SCI__TIMER_CTRL();
	void Del_SCI__TIMER_CTRL(SCI__TIMER_CTRL* p_cls);

	SCI__ASYNC_TIMER_CTRL* New_SCI__ASYNC_TIMER_CTRL();
	void Del_SCI__ASYNC_TIMER_CTRL(SCI__ASYNC_TIMER_CTRL* p_cls);

	SCI__OBJECT_VARIABLE_CTRL* New_SCI__OBJECT_VARIABLE_CTRL();
	void Del_SCI__OBJECT_VARIABLE_CTRL(SCI__OBJECT_VARIABLE_CTRL* p_cls);

	SCI__OBJECT_ALARM_CTRL* New_SCI__OBJECT_ALARM_CTRL();
	void Del_SCI__OBJECT_ALARM_CTRL(SCI__OBJECT_ALARM_CTRL* p_cls);

	SCI__ALARM_CTRL* New_SCI__ALARM_CTRL();
	void Del_SCI__ALARM_CTRL(SCI__ALARM_CTRL* p_cls);

	SCI__RECIPE_FILE* New_SCI__RECIPE_FILE();
	void Del_SCI__RECIPE_FILE(SCI__RECIPE_FILE* p_cls);

	SCI__FILE_RCP_CTRL* New_SCI__FILE_RCP_CTRL();
	void Del_SCI__FILE_RCP_CTRL(SCI__FILE_RCP_CTRL* p_cls);

	SCI__FILE_RCP_INFO* New_SCI__FILE_RCP_INFO();
	void Del_SCI__FILE_RCP_INFO(SCI__FILE_RCP_INFO* p_cls);

	SCI__FILE_ROUTE_INFO* New_SCI__FILE_ROUTE_INFO();
	void Del_SCI__FILE_ROUTE_INFO(SCI__FILE_ROUTE_INFO* p_cls);

	SCI__FILE_ROUTE_CTRL* New_SCI__FILE_ROUTE_CTRL();
	void Del_SCI__FILE_ROUTE_CTRL(SCI__FILE_ROUTE_CTRL* p_cls);

	SCI__MATERIAL_LOG* New_SCI__MATERIAL_LOG();
	void Del_SCI__MATERIAL_LOG(SCI__MATERIAL_LOG* p_cls);

	SCI__LOT_SUMMARY* New_SCI__LOT_SUMMARY();
	void Del_SCI__LOT_SUMMARY(SCI__LOT_SUMMARY* p_cls);

	SCI__SCHEDULER_DB_CTRL* New_SCI__SCHEDULER_DB_CTRL();
	void Del_SCI__SCHEDULER_DB_CTRL(SCI__SCHEDULER_DB_CTRL* p_cls);

	SCI__JOB_CTRL* New_SCI__JOB_CTRL();
	void Del_SCI__JOB_CTRL(SCI__JOB_CTRL* p_cls);

	SCI__ANALOG_CHANNEL* New_SCI__ANALOG_CHANNEL();
	void Del_SCI__ANALOG_CHANNEL(SCI__ANALOG_CHANNEL* p_cls);

	SCI__DIGITAL_CHANNEL* New_SCI__DIGITAL_CHANNEL();
	void Del_SCI__DIGITAL_CHANNEL(SCI__DIGITAL_CHANNEL* p_cls);

	SCI__STRING_CHANNEL* New_SCI__STRING_CHANNEL();
	void Del_SCI__STRING_CHANNEL(SCI__STRING_CHANNEL* p_cls);

	SCI__VARIABLE_CTRL* New_SCI__VARIABLE_CTRL();
	void Del_SCI__VARIABLE_CTRL(SCI__VARIABLE_CTRL* p_cls);

	SCI__SEQ_INFO* New_SCI__SEQ_INFO();
	void Del_SCI__SEQ_INFO(SCI__SEQ_INFO* p_cls);

	SCI__FILE_CTRL* New_SCI__FILE_CTRL();
	void Del_SCI__FILE_CTRL(SCI__FILE_CTRL* p_cls);

	SCI__MODULE_INFO* New_SCI__MODULE_INFO();
	void Del_SCI__MODULE_INFO(SCI__MODULE_INFO* p_cls);

	SCI__PM_DATALOG* New_SCI__PM_DATALOG();
	void Del_SCI__PM_DATALOG(SCI__PM_DATALOG* p_cls);

	SCI__CONDITION* New_SCI__CONDITION();
	void Del_SCI__CONDITION(SCI__CONDITION* p_cls);

	SCI__CONDITION* New_SCI__CONDITION_EX(const CString obj_name,const CString& var_name,const CString& con_para,const CString& con_data);
	void Del_SCI__CONDITION_EX(SCI__CONDITION* p_cls);

	SCI__DEVICENET_INFO* New_SCI__DEVICENET_INFO();
	void Del_SCI__DEVICENET_INFO(SCI__DEVICENET_INFO* p_cls);

	SCI__CHANNEL_INFO* New_SCI__CHANNEL_INFO();
	void Del_SCI__CHANNEL_INFO(SCI__CHANNEL_INFO* p_cls);

	SCI__SERIAL_JG* New_SCI__SERIAL_JG();
	void Del_SCI__SERIAL_JG(SCI__SERIAL_JG* p_cls);

	SCI__SEQ_CORE__QUERY* New_SCI__SEQ_CORE__QUERY();
	void Del_SCI__SEQ_CORE__QUERY(SCI__SEQ_CORE__QUERY* p_cls);

	SCI__COMMON_FILE_CTRL* New_SCI__COMMON_FILE_CTRL();
	void Del_SCI__COMMON_FILE_CTRL(SCI__COMMON_FILE_CTRL* p_cls);

	SCI__DB_CTRL* New_SCI__DB_CTRL();
	void Del_SCI__DB_CTRL(SCI__DB_CTRL* p_cls);

	SCI__PM_CSV_LOG* New_SCI__PM_CSV_LOG();	
	void Del_SCI__PM_CSV_LOG(SCI__PM_CSV_LOG* p_cls);	

	SCI__CHANNEL_CTRL* New_SCI__CHANNEL_CTRL();
	void Del_SCI__CHANNEL_CTRL(SCI__CHANNEL_CTRL* p_cls);

	SCI__FILE_LINK_CTRL* New_SCI__FILE_LINK_CTRL();
	void Del_SCI__FILE_LINK_CTRL(SCI__FILE_LINK_CTRL* p_cls);

	SCI__COM_PORT* New_SCI__COM_PORT();
	void Del_SCI__COM_PORT(SCI__COM_PORT* p_cls);

	SCI__FILE_ROUTE_INFO__ETCHER_QUAD* New_SCI__FILE_ROUTE_INFO__ETCHER_QUAD();
	void Del_SCI__FILE_ROUTE_INFO__ETCHER_QUAD(SCI__FILE_ROUTE_INFO__ETCHER_QUAD* p_cls);

	// ...
	SCI__ETHERNET_JGLEE* New_SCI__ETHERNET_JGLEE();
	void Del_SCI__ETHERNET_JGLEE(SCI__ETHERNET_JGLEE* p_cls);

	SCI__ETHERNET_SERVER_JGLEE* New_SCI__ETHERNET_SERVER_JGLEE();
	void Del_SCI__ETHERNET_SERVER_JGLEE(SCI__ETHERNET_SERVER_JGLEE* p_cls);
	
	// ...
	SCI__SERIAL* New_SCI__SERIAL();
	void Del_SCI__SERIAL(SCI__SERIAL* p_cls);

	SCI__ASYNC_SERIAL* New_SCI__ASYNC_SERIAL();
	void Del_SCI__ASYNC_SERIAL(SCI__ASYNC_SERIAL* p_cls);

	// ...
	SCI__SYSTEM_CTRL* New_SCI__SYSTEM_CTRL();
}


// ...
class SCX__Memory_Check
{
private:
	SCI__Memory_Check *m_pT;
	
public:
	SCX__Memory_Check()
	{
		m_pT = New_SCI__Memory_Check();
	}
	~SCX__Memory_Check()
	{
		// if(m_pT != NULL)     delete m_pT;
		
		Del_SCI__Memory_Check(m_pT);
	}
	
	SCI__Memory_Check* operator->() const
	{
		return m_pT;
	}
	SCI__Memory_Check* Get__SCI_PTR()
	{
		return m_pT;
	}
};

class SCX__FILE_LINK_CTRL
{
private:
	SCI__FILE_LINK_CTRL *m_pT;

public:
	SCX__FILE_LINK_CTRL()
	{
		m_pT = New_SCI__FILE_LINK_CTRL();
	}
	~SCX__FILE_LINK_CTRL()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__FILE_LINK_CTRL(m_pT);
	}
	
	SCI__FILE_LINK_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__FILE_LINK_CTRL* Get__SCI_PTR()
	{
		return m_pT;
	}
};

class SCX__CHANNEL_CTRL
{
private:
	SCI__CHANNEL_CTRL *m_pT;

public:
	SCX__CHANNEL_CTRL()
	{
		m_pT = New_SCI__CHANNEL_CTRL();
	}
	~SCX__CHANNEL_CTRL()
	{
		// if(m_pT != NULL)     delete m_pT;
		
		Del_SCI__CHANNEL_CTRL(m_pT);
	}
	
	SCI__CHANNEL_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__CHANNEL_CTRL* Get__SCI_PTR()
	{
		return m_pT;
	}
};

class SCX__DB_CTRL
{
private:
	SCI__DB_CTRL *m_pT;

public:
	SCX__DB_CTRL()
	{
		m_pT = New_SCI__DB_CTRL();
	}
	~SCX__DB_CTRL()
	{
		// if(m_pT != NULL)     delete m_pT;
		
		Del_SCI__DB_CTRL(m_pT);
	}
	
	SCI__DB_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__DB_CTRL* Get__SCI_PTR()
	{
		return m_pT;
	}
};

class SCX__SEQ_CORE__QUERY
{
private:
	SCI__SEQ_CORE__QUERY *m_pT;

public:
	SCX__SEQ_CORE__QUERY()
	{
		m_pT = New_SCI__SEQ_CORE__QUERY();
	}
	~SCX__SEQ_CORE__QUERY()
	{
		// if(m_pT != NULL)     delete m_pT;
		
		Del_SCI__SEQ_CORE__QUERY(m_pT);
	}
	
	SCI__SEQ_CORE__QUERY* operator->() const
	{
		return m_pT;
	}
	SCI__SEQ_CORE__QUERY* Get__SCI_PTR()
	{
		return m_pT;
	}
};

class SCX__CHANNEL_INFO
{
private:
	SCI__CHANNEL_INFO *m_pT;

public:
	SCX__CHANNEL_INFO()
	{
		m_pT = New_SCI__CHANNEL_INFO();
	}
	~SCX__CHANNEL_INFO()
	{
		// if(m_pT != NULL)     delete m_pT;
		
		Del_SCI__CHANNEL_INFO(m_pT);
	}
	
	SCI__CHANNEL_INFO* operator->() const
	{
		return m_pT;
	}
	SCI__CHANNEL_INFO* Get__SCI_PTR()
	{
		return m_pT;
	}
};
class SCX__DEVICENET_INFO
{
private:
	SCI__DEVICENET_INFO *m_pT;

public:
	SCX__DEVICENET_INFO()
	{
		m_pT = New_SCI__DEVICENET_INFO();
	}
	~SCX__DEVICENET_INFO()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__DEVICENET_INFO(m_pT);
	}

	SCI__DEVICENET_INFO* operator->() const
	{
		return m_pT;
	}
	SCI__DEVICENET_INFO* Get__SCI_PTR()
	{
		return m_pT;
	}
};

class SCX__CONDITION
{
private:
	SCI__CONDITION *m_pT;

public:
	SCX__CONDITION()
	{
		m_pT = New_SCI__CONDITION();
	}
	~SCX__CONDITION()
	{
		// if(m_pT != NULL)     delete m_pT;
		
		Del_SCI__CONDITION(m_pT);
	}

	SCI__CONDITION* operator->() const
	{
		return m_pT;
	}
	SCI__CONDITION* Get__SCI_PTR()
	{
		return m_pT;
	}
};
class SCX__PM_DATALOG
{
private:
	SCI__PM_DATALOG *m_pT;

public:
	SCX__PM_DATALOG()
	{
		m_pT = New_SCI__PM_DATALOG();
	}
	~SCX__PM_DATALOG()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__PM_DATALOG(m_pT);
	}

	SCI__PM_DATALOG* operator->() const
	{
		return m_pT;
	}
};
class SCX__PM_CSV_LOG
{
private:
	SCI__PM_CSV_LOG *m_pT;

public:
	SCX__PM_CSV_LOG()
	{
		m_pT = New_SCI__PM_CSV_LOG();
	}
	~SCX__PM_CSV_LOG()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__PM_CSV_LOG(m_pT);
	}

	SCI__PM_CSV_LOG* operator->() const
	{
		return m_pT;
	}
};
class SCX__SEQ_INFO
{
private:
	SCI__SEQ_INFO *m_pT;

public:
	SCX__SEQ_INFO()
	{
		m_pT = New_SCI__SEQ_INFO();
	}
	~SCX__SEQ_INFO()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__SEQ_INFO(m_pT);
	}

	SCI__SEQ_INFO* operator->() const
	{
		return m_pT;
	}
	SCI__SEQ_INFO* Get__SCI_PTR()
	{
		return m_pT;
	}
};
class SCX__FILE_CTRL
{
private:
	SCI__FILE_CTRL *m_pT;

public:
	SCX__FILE_CTRL()
	{
		m_pT = New_SCI__FILE_CTRL();
	}
	~SCX__FILE_CTRL()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__FILE_CTRL(m_pT);
	}

	SCI__FILE_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__FILE_CTRL* Get__SCI_PTR()
	{
		return m_pT;
	}
};
class SCX__COMMON_FILE_CTRL
{
private:
	SCI__COMMON_FILE_CTRL *m_pT;

public:
	SCX__COMMON_FILE_CTRL()
	{
		m_pT = New_SCI__COMMON_FILE_CTRL();
	}
	~SCX__COMMON_FILE_CTRL()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__COMMON_FILE_CTRL(m_pT);
	}

	SCI__COMMON_FILE_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__COMMON_FILE_CTRL* Get__SCI_PTR()
	{
		return m_pT;
	}
};
class SCX__MODULE_INFO
{
private:
	SCI__MODULE_INFO *m_pT;

public:
	SCX__MODULE_INFO()
	{
		m_pT = New_SCI__MODULE_INFO();
	}
	~SCX__MODULE_INFO()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__MODULE_INFO(m_pT);
	}

	SCI__MODULE_INFO* operator->() const
	{
		return m_pT;
	}
};


class SCX__ANALOG_CHANNEL
{
private:
	SCI__ANALOG_CHANNEL *m_pT;

public:
	SCX__ANALOG_CHANNEL()
	{
		m_pT = New_SCI__ANALOG_CHANNEL();
	}
	~SCX__ANALOG_CHANNEL()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__ANALOG_CHANNEL(m_pT);
	}

	SCI__ANALOG_CHANNEL* operator->() const
	{
		return m_pT;
	}
	SCI__ANALOG_CHANNEL* Get__SCI_PTR()
	{
		return m_pT;
	}
};
class SCX__DIGITAL_CHANNEL
{
private:
	SCI__DIGITAL_CHANNEL *m_pT;

public:
	SCX__DIGITAL_CHANNEL()
	{
		m_pT = New_SCI__DIGITAL_CHANNEL();
	}
	~SCX__DIGITAL_CHANNEL()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__DIGITAL_CHANNEL(m_pT);
	}

	SCI__DIGITAL_CHANNEL* operator->() const
	{
		return m_pT;
	}
	SCI__DIGITAL_CHANNEL* Get__SCI_PTR()
	{
		return m_pT;
	}
};
class SCX__STRING_CHANNEL
{
private:
	SCI__STRING_CHANNEL *m_pT;

public:
	SCX__STRING_CHANNEL()
	{
		m_pT = New_SCI__STRING_CHANNEL();
	}
	~SCX__STRING_CHANNEL()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__STRING_CHANNEL(m_pT);
	}

	SCI__STRING_CHANNEL* operator->() const
	{
		return m_pT;
	}
	SCI__STRING_CHANNEL* Get__SCI_PTR()
	{
		return m_pT;
	}
};
class SCX__VARIABLE_CTRL
{
private:
	SCI__VARIABLE_CTRL *m_pT;

public:
	SCX__VARIABLE_CTRL()
	{
		m_pT = New_SCI__VARIABLE_CTRL();
	}
	~SCX__VARIABLE_CTRL()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__VARIABLE_CTRL(m_pT);
	}

	SCI__VARIABLE_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__VARIABLE_CTRL* Get__SCI_PTR()
	{
		return m_pT;
	}
};


class SCX__SCHEDULER_DB_CTRL
{
private:
	SCI__SCHEDULER_DB_CTRL *m_pT;

public:
	SCX__SCHEDULER_DB_CTRL ()
	{
		m_pT = New_SCI__SCHEDULER_DB_CTRL();
	}
	~SCX__SCHEDULER_DB_CTRL()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__SCHEDULER_DB_CTRL(m_pT);
	}

	SCI__SCHEDULER_DB_CTRL* operator->() const
	{
		return m_pT;
	}
};
class SCX__JOB_CTRL
{
private:
	SCI__JOB_CTRL *m_pT;

public:
	SCX__JOB_CTRL ()
	{
		m_pT = New_SCI__JOB_CTRL();
	}
	~SCX__JOB_CTRL()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__JOB_CTRL(m_pT);
	}

	SCI__JOB_CTRL* operator->() const
	{
		return m_pT;
	}
};


class SCX__LOT_SUMMARY
{
private:
	SCI__LOT_SUMMARY *m_pT;

public:
	SCX__LOT_SUMMARY()
	{
		m_pT = New_SCI__LOT_SUMMARY();
	}
	~SCX__LOT_SUMMARY()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__LOT_SUMMARY(m_pT);
	}

	SCI__LOT_SUMMARY* operator->() const
	{
		return m_pT;
	}
};
class SCX__MATERIAL_LOG
{
private:
	SCI__MATERIAL_LOG *m_pT;

public:
	SCX__MATERIAL_LOG()
	{
		m_pT = New_SCI__MATERIAL_LOG();
	}
	~SCX__MATERIAL_LOG()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__MATERIAL_LOG(m_pT);
	}

	SCI__MATERIAL_LOG* operator->() const
	{
		return m_pT;
	}
};


class SCX__FILE_ROUTE_INFO
{
private:
	SCI__FILE_ROUTE_INFO *m_pT;

public:
	SCX__FILE_ROUTE_INFO()
	{
		m_pT = New_SCI__FILE_ROUTE_INFO();
	}
	~SCX__FILE_ROUTE_INFO()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__FILE_ROUTE_INFO(m_pT);
	}

	SCI__FILE_ROUTE_INFO* operator->() const
	{
		return m_pT;
	}
};
class SCX__FILE_ROUTE_INFO__ETCHER_QUAD
{
private:
	SCI__FILE_ROUTE_INFO__ETCHER_QUAD *m_pT;
	
public:
	SCX__FILE_ROUTE_INFO__ETCHER_QUAD()
	{
		m_pT = New_SCI__FILE_ROUTE_INFO__ETCHER_QUAD();
	}
	~SCX__FILE_ROUTE_INFO__ETCHER_QUAD()
	{
		// if(m_pT != NULL)     delete m_pT;
		
		Del_SCI__FILE_ROUTE_INFO__ETCHER_QUAD(m_pT);
	}
	
	SCI__FILE_ROUTE_INFO__ETCHER_QUAD* operator->() const
	{
		return m_pT;
	}
};
class SCX__FILE_ROUTE_CTRL
{
private:
	SCI__FILE_ROUTE_CTRL *m_pT;

public:
	SCX__FILE_ROUTE_CTRL()
	{
		m_pT = New_SCI__FILE_ROUTE_CTRL();
	}
	~SCX__FILE_ROUTE_CTRL()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__FILE_ROUTE_CTRL(m_pT);
	}

	SCI__FILE_ROUTE_CTRL* operator->() const
	{
		return m_pT;
	}
};


class SCX__RECIPE_FILE
{
private:
	SCI__RECIPE_FILE *m_pT;

public:
	SCX__RECIPE_FILE()
	{
		m_pT = New_SCI__RECIPE_FILE();
	}
	~SCX__RECIPE_FILE()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__RECIPE_FILE(m_pT);
	}

	SCI__RECIPE_FILE* operator->() const
	{
		return m_pT;
	}
};
class SCX__FILE_RCP_CTRL
{
private:
	SCI__FILE_RCP_CTRL *m_pT;

public:
	SCX__FILE_RCP_CTRL()
	{
		m_pT = New_SCI__FILE_RCP_CTRL();
	}
	~SCX__FILE_RCP_CTRL()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__FILE_RCP_CTRL(m_pT);
	}

	SCI__FILE_RCP_CTRL* operator->() const
	{
		return m_pT;
	}
};
class SCX__FILE_RCP_INFO
{
private:
	SCI__FILE_RCP_INFO *m_pT;

public:
	SCX__FILE_RCP_INFO()
	{
		m_pT = New_SCI__FILE_RCP_INFO();
	}
	~SCX__FILE_RCP_INFO()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__FILE_RCP_INFO(m_pT);
	}

	SCI__FILE_RCP_INFO* operator->() const
	{
		return m_pT;
	}
};


class SCX__ALARM_CTRL
{
private:
	SCI__ALARM_CTRL *m_pT;

public:
	SCX__ALARM_CTRL()
	{
		m_pT = New_SCI__ALARM_CTRL();
	}
	~SCX__ALARM_CTRL()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__ALARM_CTRL(m_pT);
	}

	SCI__ALARM_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__ALARM_CTRL* Get__SCI_PTR()
	{
		return m_pT;
	}
};
class SCX__STEP_TIMER_CTRL
{
private:
	SCI__STEP_TIMER_CTRL *m_pT;

public:
	SCX__STEP_TIMER_CTRL()
	{
		m_pT = New_SCI__STEP_TIMER_CTRL();
	}
	~SCX__STEP_TIMER_CTRL()
	{
		if(m_pT != NULL)     delete m_pT;
	}

	SCI__STEP_TIMER_CTRL* operator->() const
	{
		return m_pT;
	}
};
class SCX__TIMER_CTRL
{
private:
	SCI__TIMER_CTRL *m_pT;

public:
	SCX__TIMER_CTRL()
	{
		m_pT = New_SCI__TIMER_CTRL();
	}
	~SCX__TIMER_CTRL()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__TIMER_CTRL(m_pT);
	}

	SCI__TIMER_CTRL* operator->() const
	{
		return m_pT;
	}
};
class SCX__ASYNC_TIMER_CTRL
{
private:
	SCI__ASYNC_TIMER_CTRL *m_pT;

public:
	SCX__ASYNC_TIMER_CTRL()
	{
		m_pT = New_SCI__ASYNC_TIMER_CTRL();
	}
	~SCX__ASYNC_TIMER_CTRL()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__ASYNC_TIMER_CTRL(m_pT);
	}

	SCI__ASYNC_TIMER_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__ASYNC_TIMER_CTRL* Get__PTR()
	{
		return m_pT;
	}
};

class SCX__OBJECT_VARIABLE_CTRL
{
private:
	SCI__OBJECT_VARIABLE_CTRL *m_pT;

public:
	SCX__OBJECT_VARIABLE_CTRL()
	{
		m_pT = New_SCI__OBJECT_VARIABLE_CTRL();
	}
	~SCX__OBJECT_VARIABLE_CTRL()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__OBJECT_VARIABLE_CTRL(m_pT);
	}

	SCI__OBJECT_VARIABLE_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__OBJECT_VARIABLE_CTRL* Get__SCI_PTR()
	{
		return m_pT;
	}
};
class SCX__OBJECT_ALARM_CTRL
{
private:
	SCI__OBJECT_ALARM_CTRL *m_pT;

public:
	SCX__OBJECT_ALARM_CTRL()
	{
		m_pT = New_SCI__OBJECT_ALARM_CTRL();
	}
	~SCX__OBJECT_ALARM_CTRL()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__OBJECT_ALARM_CTRL(m_pT);
	}

	SCI__OBJECT_ALARM_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__OBJECT_ALARM_CTRL* Get__SCI_PTR()
	{
		return m_pT;
	}
};

class SCX__SERIAL
{
private:
	SCI__SERIAL *m_pT;

public:
	SCX__SERIAL()
	{
		m_pT = New_SCI__SERIAL();
	}
	~SCX__SERIAL()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__SERIAL(m_pT);
	}

	SCI__SERIAL* operator->() const
	{
		return m_pT;
	}
	SCI__SERIAL* Get__SCI_PTR()
	{
		return m_pT;
	}
};
class SCX__ASYNC_SERIAL
{
private:
	SCI__ASYNC_SERIAL *m_pT;

public:
	SCX__ASYNC_SERIAL()
	{
		m_pT = New_SCI__ASYNC_SERIAL();
	}
	~SCX__ASYNC_SERIAL()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__ASYNC_SERIAL(m_pT);
	}

	SCI__ASYNC_SERIAL* operator->() const
	{
		return m_pT;
	}
	SCI__ASYNC_SERIAL* Get__SCI_PTR()
	{
		return m_pT;
	}
};
class SCX__SERIAL_JG
{
private:
	SCI__SERIAL_JG *m_pT;

public:
	SCX__SERIAL_JG()
	{
		m_pT = New_SCI__SERIAL_JG();
	}
	~SCX__SERIAL_JG()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__SERIAL_JG(m_pT);
	}

	SCI__SERIAL_JG* operator->() const
	{
		return m_pT;
	}
	SCI__SERIAL_JG* Get__SCI_PTR()
	{
		return m_pT;
	}
};
class SCX__COM_PORT
{
private:
	SCI__COM_PORT *m_pT;

public:
	SCX__COM_PORT()
	{
		m_pT = New_SCI__COM_PORT();
	}
	~SCX__COM_PORT()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__COM_PORT(m_pT);
	}

	SCI__COM_PORT* operator->() const
	{
		return m_pT;
	}
	SCI__COM_PORT* Get__SCI_PTR()
	{
		return m_pT;
	}
};

class SCX__ETHERNET_JGLEE
{
private:
	SCI__ETHERNET_JGLEE *m_pT;
	
public:
	SCX__ETHERNET_JGLEE()
	{
		m_pT = New_SCI__ETHERNET_JGLEE();
	}
	~SCX__ETHERNET_JGLEE()
	{
		// if(m_pT != NULL)     delete m_pT;
		
		Del_SCI__ETHERNET_JGLEE(m_pT);
	}
	
	SCI__ETHERNET_JGLEE* operator->() const
	{
		return m_pT;
	}
	SCI__ETHERNET_JGLEE* Get__SCI_PTR()
	{
		return m_pT;
	}
};

class SCX__ETHERNET_SERVER_JGLEE
{
private:
	SCI__ETHERNET_SERVER_JGLEE *m_pT;
	
public:
	SCX__ETHERNET_SERVER_JGLEE()
	{
		m_pT = New_SCI__ETHERNET_SERVER_JGLEE();
	}
	~SCX__ETHERNET_SERVER_JGLEE()
	{
		Del_SCI__ETHERNET_SERVER_JGLEE(m_pT);
	}
	
	SCI__ETHERNET_SERVER_JGLEE* operator->() const
	{
		return m_pT;
	}
	SCI__ETHERNET_SERVER_JGLEE* Get__SCI_PTR()
	{
		return m_pT;
	}
};

class SCX__USER_LOG_CTRL
{
private:
	SCI__USER_LOG_CTRL *m_pT;

public:
	SCX__USER_LOG_CTRL()
	{
		m_pT = New_SCI__USER_LOG_CTRL();
	}
	~SCX__USER_LOG_CTRL()
	{
		// if(m_pT != NULL)     delete m_pT;

		Del_SCI__USER_LOG_CTRL(m_pT);
	}

	SCI__USER_LOG_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__USER_LOG_CTRL* Get__SCI_PTR()
	{
		return m_pT;
	}
};

class SCX__SYSTEM_CTRL
{
private:
	SCI__SYSTEM_CTRL *m_pT;

public:
	SCX__SYSTEM_CTRL()
	{
		m_pT = New_SCI__SYSTEM_CTRL();
	}
	~SCX__SYSTEM_CTRL()
	{
		if(m_pT != NULL)     delete m_pT;
	}

	SCI__SYSTEM_CTRL* operator->() const
	{
		return m_pT;
	}
	SCI__SYSTEM_CTRL* Get__SCI_PTR()
	{
		return m_pT;
	}
};
