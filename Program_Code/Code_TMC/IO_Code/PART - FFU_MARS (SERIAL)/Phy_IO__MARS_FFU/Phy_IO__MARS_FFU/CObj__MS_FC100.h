#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__MS_FC100__ALID.h"
#include "CObj__MS_FC100__DEF.h"


// ...
union UNION_2_BYTE__UINT
{
	unsigned short int uiDATA;
	char		 cBYTE[2];
};
union UNION_3_BYTE__UINT
{
	unsigned int uiDATA;
	char		 cBYTE[3];
};
union UNION_4_BYTE__UINT
{
	unsigned long uiDATA;
	char		 cBYTE[4];
};
union UNION_4_BYTE__FLOAT
{
	float fDATA;
	unsigned long uiDATA;
	char  cBYTE[4];
};


class CObj__MS_FC100 : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	SCX__USER_LOG_CTRL xLog_Ctrl__Drive;
	SCX__SERIAL	mX_Serial;

	int iSim_Mode;

	// ...
	int	m_nCommState;
	int	m_Rcv_Time;
	int m_nRetryCnt;
	//


	// ---------------------------------------------------------------------------------------------
	// INTERNAL PARAMETER ... 

	int iCOMM_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_COMMUNICATION_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_COMMUNICATION_INFO;

	// IO Channel ...
	CX__VAR_DIGITAL_CTRL diCH__FFU_Status_Get;
	CX__VAR_STRING_CTRL  sCH__FFU_Status__HEXA;
	CX__VAR_STRING_CTRL  sCH__FFU_Status__NO_CONNECTION;
	CX__VAR_STRING_CTRL  sCH__FFU_Status__FAN_ERROR;
	CX__VAR_STRING_CTRL  sCH__FFU_Status__DIF_PRESS_ERROR;
	CX__VAR_STRING_CTRL  sCH__FFU_Status__RPM_HIGH_ERROR;
	CX__VAR_STRING_CTRL  sCH__FFU_Status__RPM_LOW_ERROR;
	CX__VAR_STRING_CTRL  sCH__FFU_Status__DIF_PRESS_HIGH_ERROR;
	CX__VAR_STRING_CTRL  sCH__FFU_Status__DIF_PRESS_LOW_ERROR;
	CX__VAR_STRING_CTRL  sCH__FFU_Status__STABLE_TIME_ERROR;

	CX__VAR_DIGITAL_CTRL diCH__FFU_Group_Get;
	CX__VAR_DIGITAL_CTRL doCH__FFU_Group_Set;
	CX__VAR_ANALOG_CTRL  aCH__FFU_Group_Para_Set_RPM;
	CX__VAR_ANALOG_CTRL  aCH__FFU_Group_Para_Set_PRESSURE;

	CX__VAR_DIGITAL_CTRL diCH__FFU_Block_Get;
	CX__VAR_DIGITAL_CTRL doCH__FFU_Block_Set;
	CX__VAR_ANALOG_CTRL  aCH__FFU_Block_Para_Set_StartID;
	CX__VAR_ANALOG_CTRL  aCH__FFU_Block_Para_Set_Size;
	CX__VAR_ANALOG_CTRL  aCH__FFU_Block_Para_Set_RPM;
	CX__VAR_ANALOG_CTRL  aCH__FFU_Block_Para_Set_PRESSURE;

	CX__VAR_STRING_CTRL  sCH__FFU_FAN_X__STATE_HEXA[CFG__FAN_SIZE];
	CX__VAR_STRING_CTRL  sCH__FFU_FAN_X__RPM_PV[CFG__FAN_SIZE];
	CX__VAR_STRING_CTRL  sCH__FFU_FAN_X__RPM_SV[CFG__FAN_SIZE];
	CX__VAR_STRING_CTRL  sCH__FFU_FAN_X__DIFF_PRESS[CFG__FAN_SIZE];
	//

	// ---------------------------------------------------------------------------------------------
	// EXTERNAL PARAMETER ... 

	// 


	// ---------------------------------------------------------------------------------------------
	void Mon__ALM_REPORT(CII_OBJECT__ALARM *p_alarm);

	// ...
	unsigned char _Get_CheckSum(const unsigned char *s_data, const int s_len);

	int _Recv_Command(const unsigned char cmmd_type, 
		              unsigned char* r_data, 
					  const double set_sv = 0,
					  const double set_pressure = 0, 
					  const int block_id = 1,
					  const int block_sz = 4);

	// ...
	void Fnc__DRV_LOG_OF_MSG(const CString& log_msg);
	void Fnc__DRV_LOG_OF_DATA_ERROR();
	//


public:
	CObj__MS_FC100();
	~CObj__MS_FC100();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);	
	int __DEFINE__ALARM(p_alarm);

	int __DEFINE__VARIABLE_IO(p_io_variable);

	//-------------------------------------------------------------------------	
	int __INITIALIZE__OBJECT(p_variable, p_ext_obj_create);
	int __INITIALIZE__IO(p_io_para);

	//-------------------------------------------------------------------------	
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);

	int __CLOSE__OBJECT();

	//-------------------------------------------------------------------------
	int __Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data);
	int __Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index);
	int __Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data);

	int __Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data);
	int __Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index);
	int __Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data);
};
