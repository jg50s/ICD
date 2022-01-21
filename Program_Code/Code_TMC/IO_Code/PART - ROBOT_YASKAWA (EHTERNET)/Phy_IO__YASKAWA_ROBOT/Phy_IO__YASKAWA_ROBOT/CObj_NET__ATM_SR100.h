#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj_NET__ATM_SR100__DEF.h"
#include "CMng__RSP_MSG.h"

#include "CMng__Error_Code.h"


class CObj_NET__ATM_SR100 : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	CCommon_Error__USER_FNC mERROR__USER_FNC;

	// ..
	SCX__USER_LOG_CTRL xAPP_LOG_CTRL;
	SCX__USER_LOG_CTRL xDRV_LOG_CTRL;

	CII__EXT_FNC_MODE_CTRL *pII__EXT_MODE_CTRL;

	//
	bool bActive__LLx_MULTI_DOOR_VALVE;
	int  iLLx__MULTI_SLOT_SIZE;

	//
	CMng__RSP_MSG mMng__RSP_MSG;

	SCX__ETHERNET_JGLEE mX_Net;
	CString sEnd_InStr;
	CString sEnd_OutStr;

	// 
	int	 m_nCommState;
	int	 m_Rcv_Time;
	int	 m_Out_Time;

	//
	int  iFlag__APP_LOG;
	int  iFlag__DRV_LOG;

	int  iSim_Flag;
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	CX__VAR_STRING_CTRL  sCH__MON_COMMUNICATION_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_COMMUNICATION_INFO;

	CX__VAR_DIGITAL_CTRL dCH__OTR_IN_CFG__SIMUL_FLAG;
	CX__VAR_STRING_CTRL  sCH__OTR_IN_CFG__SIMUL_ALIGN_TIME;

	CX__VAR_STRING_CTRL  sCH__ACT_MSG;
	CX__VAR_STRING_CTRL  sCH__OTR_OUT_MON__COMM_STS;

	CX__VAR_STRING_CTRL  sCH__INR__ERROR_ID;
	CX__VAR_DIGITAL_CTRL dCH__INR_FLAG__ALGN_STS;

	// PARA CHANNEL
	CX__VAR_DIGITAL_CTRL dCH__OTR_IN_PARA__STN_NAME;
	CX__VAR_DIGITAL_CTRL dCH__OTR_IN_PARA__STN_SLOT;
	CX__VAR_DIGITAL_CTRL dCH__OTR_IN_PARA__ARM_TYPE;

	CX__VAR_ANALOG_CTRL  aCH__PARA_AL1_CCD_POS;

	// MATERIAL CHANNEL
	CX__VAR_DIGITAL_CTRL dCH__MON__ARM_A_MATERIAL_STATUS;
	CX__VAR_DIGITAL_CTRL dCH__MON__ARM_B_MATERIAL_STATUS;

	CX__VAR_STRING_CTRL  sCH__MON__ARM_A_MATERIAL_TITLE;
	CX__VAR_STRING_CTRL  sCH__MON__ARM_B_MATERIAL_TITLE;

	// CURRENT INFO ...
	CX__VAR_STRING_CTRL  sCH__CUR_AL1_STN_NUM;
	CX__VAR_STRING_CTRL  sCH__CUR_ST1_STN_NUM;
	
	CX__VAR_STRING_CTRL  sCH__CUR_LLx_STN_NUM[CFG_LLx__SIZE];
	CX__VAR_STRING_CTRL  sCH__CUR_LLx_1_STN_NUM[CFG_LLx__SIZE];
	CX__VAR_STRING_CTRL  sCH__CUR_LLx_2_STN_NUM[CFG_LLx__SIZE];

	CX__VAR_STRING_CTRL  sCH__CUR_LPx_STN_NUM[CFG_LPx__SIZE];

	// CFG CHANNEL ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_ACTION_CONFIRM_FLAG;

	CX__VAR_STRING_CTRL  sCH__OTR_OUT_CFG__ROM_DATE;
	CX__VAR_STRING_CTRL  sCH__OTR_OUT_CFG__ROM_VERSION;

	// SIMULATION CHANNEL ...
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__ROTATE_TIME;

	// LPx
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__LPx_PICK_TIME;
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__LPx_PLACE_TIME;

	// ALx
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__ALx_PICK_TIME;
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__ALx_PLACE_TIME;

	// LBx
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__LBx_PICK_TIME;
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__LBx_PLACE_TIME;

	// VISx
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__VISx_PICK_TIME;
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__VISx_PLACE_TIME;

	// SYSTEM STATUS ...
	CX__VAR_STRING_CTRL  sCH__MON_SYS_STS__MANIPULATOR_BATTERY;
	CX__VAR_STRING_CTRL  sCH__MON_SYS_STS__UNIT_STATUS;
	CX__VAR_STRING_CTRL  sCH__MON_SYS_STS__SERVO_STATUS;
	CX__VAR_STRING_CTRL  sCH__MON_SYS_STS__ERROR_STATUS;

	CX__VAR_STRING_CTRL  sCH__MON_SYS_STS__CONTROLLRT_BATTERY;
	CX__VAR_STRING_CTRL  sCH__MON_SYS_STS__WAFER_PRESENCE_STS1;
	CX__VAR_STRING_CTRL  sCH__MON_SYS_STS__WAFER_PRESENCE_STS2;

	// ERROR CODE ...
	CX__VAR_STRING_CTRL  sCH__MON_ERR_SYS__LEVEL;
	CX__VAR_STRING_CTRL  sCH__MON_ERR_STS__CODE;

	// ROBOT_STATUS ...
	CX__VAR_STRING_CTRL  sCH__MON_RB_STS__WAFER_SNS_ON_BLADE_1;
	CX__VAR_STRING_CTRL  sCH__MON_RB_STS__WAFER_SNS_ON_BLADE_2;
	CX__VAR_STRING_CTRL  sCH__MON_RB_STS__WAFER_GRIP_ON_BLADE_1;
	CX__VAR_STRING_CTRL  sCH__MON_RB_STS__WAFER_GRIP_ON_BLADE_2;

	CX__VAR_STRING_CTRL  sCH__MON_RB_STS__INTERLOCK_SIGNAL_X[_CFG__INTERLOCK_SIZE];

	// ...
	CX__VAR_STRING_CTRL  sCH__ROM_VER;
	CX__VAR_STRING_CTRL  sCH__ROM_DATE;

	CX__VAR_DIGITAL_CTRL dCH__LPx_SLOT_STATUS[CFG_LPx__SLOT_SIZE];

	CX__VAR_ANALOG_CTRL  aCH__CFG__ALIGN_AND_PICK_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG__PLACE_AND_ALIGN_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG__PICK_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG__PLACE_TIMEOUT;
	CX__VAR_DIGITAL_CTRL dCH__CFG_MAPPING_ACTION_SLIDE_OUT_CHECK;
	CX__VAR_ANALOG_CTRL  aCH__CFG_LP__PADDLE_CHECK_TIME;

	CX__VAR_DIGITAL_CTRL dCFG__CH__DYNAMIC_ALIGN_DIRECTION;

	CX__VAR_DIGITAL_CTRL dCH__CFG_MAPPING_DISABLE;
	CX__VAR_DIGITAL_CTRL dCH__CFG_ALIGN_SKIP;
	CX__VAR_DIGITAL_CTRL dCH__CFG_PAD_TYPE;

	CX__VAR_DIGITAL_CTRL xCH__LOCK_FLAG;

	// ...
	CX__VAR_STRING_CTRL sCH__INFO_VER_SYSTEM;
	CX__VAR_STRING_CTRL sCH__INFO_VER_SERVO;
	//

	// IO CHANNEL ...
	CString sDRV_UnitID;

	// DO 
	CX__VAR_DIGITAL_CTRL doCH__COMMAND;

	// DI 
	CX__VAR_DIGITAL_CTRL diCH__RB_STS;

	// SI
	CX__VAR_STRING_CTRL  siCH__VERSION;

	// ...
	CMng__Error_Code mMNG__ERR_CODE;

	// ERROR TEST ...
	CX__VAR_DIGITAL_CTRL  dCH__CFG_ACTIVE_ACKN_SEND;
	bool bActive__ACKN_Single;

	CX__VAR_DIGITAL_CTRL  dCH__CFG_ACTIVE_RECV_CNT_SINGLE;
	bool bActive__Recv_Cnt_Single;

	CX__VAR_DIGITAL_CTRL  dCH__ERROR_TEST__ACTIVE;
	CX__VAR_STRING_CTRL   sCH__ERROR_TEST__ERROR_CODE;
	//

	//-------------------------------------------------------------------------
	// Init -----
	CString sMODE__INIT;
	CString sMODE__HOME;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	int  Fnc__SIM_INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	int  Fnc__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// Pick -----
	CString sMODE__PICK;
	int  Call__PICK(CII_OBJECT__VARIABLE* p_variable,
					CII_OBJECT__ALARM* p_alarm,
					const CString& arm_type,
					const CString& stn_name,
					const CString& stn_slot);

	int  Fnc__SIM_PICK_TIME(CII_OBJECT__VARIABLE* p_variable,
						    CII_OBJECT__ALARM* p_alarm,
							const CString& arm_type,
							const CString& stn_name,
							const CString& stn_slot);
	int  Fnc__PICK(CII_OBJECT__VARIABLE* p_variable,
					CII_OBJECT__ALARM* p_alarm,
					const CString& arm_type,
					const CString& stn_name,
					const CString& stn_slot);

	// Place -----
	CString sMODE__PLACE;
	int  Call__PLACE(CII_OBJECT__VARIABLE* p_variable,
						CII_OBJECT__ALARM* p_alarm,
						const CString& arm_type,
						const CString& stn_name,
						const CString& stn_slot);

	int  Fnc__SIM_PLACE_TIME(CII_OBJECT__VARIABLE* p_variable,
							 CII_OBJECT__ALARM* p_alarm,
							 const CString& arm_type,
							 const CString& stn_name,
							 const CString& stn_slot);
	int  Fnc__PLACE(CII_OBJECT__VARIABLE* p_variable,
					CII_OBJECT__ALARM* p_alarm,
					const CString& arm_type,
					const CString& stn_name,
					const CString& stn_slot);

	// Rotate -----
	CString sMODE__ROTATE;
	int  Call__ROTATE(CII_OBJECT__VARIABLE* p_variable,
						CII_OBJECT__ALARM* p_alarm,
						const CString& arm_type,
						const CString& stn_name,
						const CString& stn_slot);

	int  Fnc__SIM_ROTATE(CII_OBJECT__VARIABLE* p_variable,
						CII_OBJECT__ALARM* p_alarm,
						const CString& arm_type,
						const CString& stn_name,
						const CString& stn_slot);
	int  Fnc__ROTATE(CII_OBJECT__VARIABLE* p_variable,
						CII_OBJECT__ALARM* p_alarm,
						const CString& arm_type,
						const CString& stn_name,
						const CString& stn_slot);

	// ...
	CString sMODE__CHECK_ERROR_CODE;
	int  Call__CHECK_ERROR_CODE(CII_OBJECT__VARIABLE* p_variable,
								CII_OBJECT__ALARM* p_alarm);

	// ...
	void Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	void Mon__PROC_RSP_MSG(CII_OBJECT__VARIABLE* p_variable,
					       CII_OBJECT__ALARM* p_alarm);

	int  _Proc__RSP_MSG();
	
	CString _Get__CHECK_SUM(const CString& s_cmmd);
	
	int  _Get__STRING_ARRAY(const CString& xxx_data,
						    const CString& str_delimiter,
							CStringArray& l_data);

	int  _Recv__CMMD(const CString& var_name, 
					 const bool act_mode, 
					 const CString& s_data, 
					 CString& r_data);
	int  _Send__CMMD(const CString& var_name, 
					 const CString& str__cmmd);

	int _Update__SYSTEM_STATUS(const CString& rsp_sts);
	int _Update__ERROR_CODE(const CString& rsp_errcd);
	int _Check__ERROR_CODE(const CString& err_code);

	int _Update__ROBOT_STATUS(const CString& rsp_sts);
	
	CString _Get__TRG_STN();	
	CString _Get__TRG_STN(const CString& stn_name, const CString& stn_slot);	
	CString _Get__TRG_SLOT();	
	CString _Get__ARM_MODE();	
	CString _Get__ARM_ID();	
	int _Check__ARM_WAFER();	

	int _Get__HEXA_FROM_ASCII(const unsigned char ch_ascii);
	int _Get__HEXA_FROM_ASCII(const CString& str_ascii);

	// ...
	int  Is__LOCAL(CII_OBJECT__ALARM* p_alarm);
	int  Is__OFFLINE(CII_OBJECT__ALARM* p_alarm);


	// ROBOT ...
	int  Seq__ROBOT_PICK(CII_OBJECT__VARIABLE* p_variable,
						 CII_OBJECT__ALARM* p_alarm,
						 const CString& arm_type,
						 const CString& stn_name,
						 const CString& stn_slot);

	int  Seq__ROBOT_PLACE(CII_OBJECT__VARIABLE* p_variable,
						  CII_OBJECT__ALARM* p_alarm,
						  const CString& arm_type,
						  const CString& stn_name,
						  const CString& stn_slot);

	int  Seq__ROBOT_ROTATE(CII_OBJECT__VARIABLE* p_variable,
							CII_OBJECT__ALARM* p_alarm,
							const CString& arm_type,
							const CString& stn_name,
							const CString& stn_slot);

	// ...
	int  Fnc__IS_COMM_ONLINE();
	int  Fnc__ONLINE_CHECK(CII_OBJECT__ALARM* p_alarm,const int alarm_check);

	// ...
	int  Drv__CMD_COM_INIT(const CString& var_name);

	// ...
	int  Fnc__StrTo2Word(const CString& data,
							const char section,
							CString *p_str1,
							CString *p_str2);

	int  Fnc__StrTo7Word(const CString& data,
							const char section,
							CString *p_str1,
							CString *p_str2,
							CString *p_str3,
							CString *p_str4,
							CString *p_str5,
							CString *p_str6,
							CString *p_str7);

	int  Fnc__IndexStrTo1Word(const CString& data,
							const char section,
							int index,
							CString *p_str1);
	int  Fnc__IndexStrTo4Word(const CString& data,
							const char section,
							int index,
							CString *p_str1,
							CString *p_str2,
							CString *p_str3,
							CString *p_str4);
	int  Fnc__IndexStrTo5Word(const CString& data,
							const char section,
							int index,
							CString *p_str1,
							CString *p_str2,
							CString *p_str3,
							CString *p_str4,
							CString *p_str5);

	int  Fnc__HexToDec(const CString& str_dec);
	int  Fnc__DecToBin(int dec,CString *p_str);

	// ...
	void Fnc__APP_LOG(const CString& log_msg);
	void Fnc__DRV_LOG(const CString& log_msg);
	void Fnc__DRV_LOG_FORMAT(const char *fmt, ...);
	void Fnc__ACT_MSG(const CString& act_msg);

	// ...
	int m_nRetryCount;
	int m_nTimeout;
	//


public:
	CObj_NET__ATM_SR100();
	~CObj_NET__ATM_SR100();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__VARIABLE_IO(p_io_variable);

	int __DEFINE__ALARM(p_alarm);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);	
	int __INITIALIZE__IO(p_io_para);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);

	//-------------------------------------------------------------------------
	int __Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data);
	int __Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index);
	int __Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data);

	int __Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data);
	int __Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index);
	int __Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data);
};
