#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_SYSTEM.h"
#include "CMng__Error_Code.h"


class CObj_NET__VAC_PERSIMMON : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;
	int m_nPM_LIMIT;
	int m_nSTN_NUM_MAX;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	SCX__USER_LOG_CTRL xAPP_LOG_CTRL;
	SCX__USER_LOG_CTRL xDRV_LOG_CTRL;

	//
	CII__EXT_FNC_MODE_CTRL *pII__EXT_MODE_CTRL;
	CII__EXT_FNC_VAR_CTRL  *pII__EXT_VAR_CTRL;
	CII__EXT_USER_FNC_CTRL *pII__EXT_FNC_CTRL;

	CString m_szRoot;

	// SCX__SERIAL	mX_Serial;
	SCX__ETHERNET_JGLEE mX_Net;
	CString sEnd_InStr;
	CString sEnd_OutStr;

	int	 m_nCommState;

	//
	int  iFlag__APP_LOG;
	int  iFlag__DRV_LOG;

	int  iSim_Flag;

	// ...
	CString  m_sStationA;
	CString  m_sStationB;
	CString  m_sCptr_StationA;
	CString  m_sCptr_StationB;
	CString  m_sRPos;
	CString  m_sZPos;
	CString  m_sSlot;
	CString  m_sWfrSnsIntlk;

	CString  m_sRO_OFFSET;
	CString  m_sTO_OFFSET;

	CString  m_sSTN_R_SET_VAL;
	CString  m_sSTN_T_SET_VAL;

	// 
	CString  m_sBefore_Stn_Retract_ArmA;
	CString  m_sBefore_Stn_Retract_ArmB;

	struct CPTR_TUNED_VAL 
	{
		double ro_tuned_val;
		double to_tuned_val;
	};
	CPTR_TUNED_VAL ARM_A_m_set_cptr_tune_val;
	CPTR_TUNED_VAL ARM_B_m_set_cptr_tune_val;

	// ...
	CMng__Error_Code mMNG__ERR_CODE;

	// ERROR TEST ...
	CX__VAR_DIGITAL_CTRL  dCH__ERROR_TEST__ACTIVE;
	CX__VAR_STRING_CTRL   sCH__ERROR_TEST__ERROR_CODE;
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// ...
	CX__VAR_STRING_CTRL  sCH__MON_COMMUNICATION_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_COMMUNICATION_INFO;

	CX__VAR_STRING_CTRL  sCH__OTR_OUT_MON__COMM_STS;

	CX__VAR_DIGITAL_CTRL xCH__LOCK_FLAG;		// Only Interface ...

	// ...
	CX__VAR_STRING_CTRL	 sCH__ACT_MSG;
	CX__VAR_STRING_CTRL	 sCH__VERSION;
	CX__VAR_STRING_CTRL	 sCH__ERRID;

	CX__VAR_STRING_CTRL  sCH__DRV_RB_STS;

	// PARA CHANNEL
	CX__VAR_DIGITAL_CTRL dCH__OTR_IN_PARA__STN_NAME;
	CX__VAR_DIGITAL_CTRL dCH__OTR_IN_PARA__STN_SLOT;
	CX__VAR_DIGITAL_CTRL dCH__OTR_IN_PARA__ARM_TYPE;
	CX__VAR_STRING_CTRL  sCH__ACTION_STS;
	//

	CX__VAR_STRING_CTRL sCH__ARM_A_BEFORE_MODE_STS;
	CX__VAR_STRING_CTRL sCH__ARM_B_BEFORE_MODE_STS;

	CX__VAR_ANALOG_CTRL  aCH__SET_STN_R_VALUE;
	CX__VAR_ANALOG_CTRL  aCH__SET_STN_T_VALUE;

	CX__VAR_STRING_CTRL  sCH__Estimated_R_OFFSET;
	CX__VAR_STRING_CTRL  sCH__Estimated_T_OFFSET;

	// CONFIG CHANNEL
	CX__VAR_ANALOG_CTRL  aCH__OTR_IN_CFG__LLx_STN_NUM[CFG_LLx__SIZE];
	CX__VAR_ANALOG_CTRL  aCH__OTR_IN_CFG__PMx_STN_NUM[CFG_PMx__SIZE];	

	CX__VAR_ANALOG_CTRL  aCH__OTR_IN_CFG_LLx_CPTR_SNS_NUM[CFG_LLx__SIZE];
	CX__VAR_ANALOG_CTRL  aCH__OTR_IN_CFG_PMx_CPTR_SNS_NUM[CFG_PMx__SIZE];
	
	// MATERIAL CHANNEL ...
	CX__VAR_DIGITAL_CTRL dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS;
	CX__VAR_DIGITAL_CTRL dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS;
	
	CX__VAR_STRING_CTRL  sCH__OTR_OUT_MON__ARM_A_MATERIAL_TITLE;
	CX__VAR_STRING_CTRL  sCH__OTR_OUT_MON__ARM_B_MATERIAL_TITLE;

	// DA Offset ...
	CX__VAR_STRING_CTRL  sCH__DA_RESULT_R_OFFSET_DEG;
	CX__VAR_STRING_CTRL  sCH__DA_RESULT_T_OFFSET_MM;

	// Simulation Channel ...
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__ROTATE_TIME;
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__LLx_MOVE_TIME;
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__PMx_MOVE_TIME;

	// DA Info ...
	CX__VAR_STRING_CTRL  sCH__CPTR_SNS_FULL_VAL;

	CX__VAR_STRING_CTRL  sCH__RQ_STN_FULL_VAL;
	CX__VAR_STRING_CTRL  sCH__RQSTN_SNS_R_VALUE;
	CX__VAR_STRING_CTRL  sCH__RQSTN_SNS_T_VALUE;
	CX__VAR_STRING_CTRL  sCH__RQSTN_SNS_Z_VALUE;

	CX__VAR_STRING_CTRL  sCH__WFR_CEN_DATA__FULL_VAL;
	CX__VAR_STRING_CTRL  sCH__WCD__RSns_LeadEdge_RadialValue;
	CX__VAR_STRING_CTRL  sCH__WCD__RSns_LeadEdge_ThetaValue;
	CX__VAR_STRING_CTRL  sCH__WCD__RSns_TrailEdge_RadialValue;
	CX__VAR_STRING_CTRL  sCH__WCD__RSns_TrailEdge_ThetaValue;
	CX__VAR_STRING_CTRL  sCH__WCD__LSns_LeadEdge_RadialValue;
	CX__VAR_STRING_CTRL  sCH__WCD__LSns_LeadEdge_ThetaValue;
	CX__VAR_STRING_CTRL  sCH__WCD__LSns_TrailEdge_RadialValue;
	CX__VAR_STRING_CTRL  sCH__WCD__LSns_TrailEdge_ThetaValue;
	CX__VAR_STRING_CTRL  sCH__WCD__CSns_Offset_RadialValue;
	CX__VAR_STRING_CTRL  sCH__WCD__CSns_Offset_ThetaValue;
	CX__VAR_STRING_CTRL  sCH__WCD__CSns_Offset_X_Value;
	CX__VAR_STRING_CTRL  sCH__WCD__CSns_Offset_Y_Value;
	//


	// IO CHANNEL ...
	// SI
	CX__VAR_STRING_CTRL  siCH__VERSION;

	// AI 
	CX__VAR_ANALOG_CTRL  aiCH__ERRID;

	// DO 
	CX__VAR_DIGITAL_CTRL doCH__COMMAND;
	CX__VAR_DIGITAL_CTRL doCH__STN_A;
	CX__VAR_DIGITAL_CTRL doCH__STN_B;
	CX__VAR_DIGITAL_CTRL doCH__CPTR_STN_A;
	CX__VAR_DIGITAL_CTRL doCH__CPTR_STN_B;
	CX__VAR_DIGITAL_CTRL doCH__SLOT;
	CX__VAR_DIGITAL_CTRL doCH__ZPOS;
	CX__VAR_DIGITAL_CTRL doCH__RPOS;
	CX__VAR_DIGITAL_CTRL doCH__ARM_A_MAT;
	CX__VAR_DIGITAL_CTRL doCH__ARM_B_MAT;
	CX__VAR_DIGITAL_CTRL doCH__ARM_WFR_SNS;
	
	// DI 
	CX__VAR_DIGITAL_CTRL diCH__RB_STS_READ;
	CX__VAR_DIGITAL_CTRL diCH__ARM_A_READ;
	CX__VAR_DIGITAL_CTRL diCH__ARM_B_READ;
	CX__VAR_DIGITAL_CTRL diCH__ARM_A_MAT_READ;
	CX__VAR_DIGITAL_CTRL diCH__ARM_B_MAT_READ;

	// AO 
	CX__VAR_ANALOG_CTRL  aoCH_RO_OFFSET;
	CX__VAR_ANALOG_CTRL  aoCH_TO_OFFSET;
	CX__VAR_ANALOG_CTRL  aoCH_STN_R_VAL;
	CX__VAR_ANALOG_CTRL  aoCH_STN_T_VAL;
	//


	//-------------------------------------------------------------------------
	// Init -----
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable,
					CII_OBJECT__ALARM* p_alarm);

	int  Fnc__SIM_INIT(CII_OBJECT__VARIABLE* p_variable,
					   CII_OBJECT__ALARM* p_alarm);
	int  Fnc__INIT(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm);

	// Pick -----
	CString sMODE__PICK;
	int  Call__PICK(CII_OBJECT__VARIABLE* p_variable,
					CII_OBJECT__ALARM* p_alarm,
					const CString& para__stn_name,
					const CString& para__arm_type,
					const CString& para__stn_slot);

	int  _Wait__SIM_SEC(CII_OBJECT__VARIABLE* p_variable,
					    const CString& para__stn_name);

	int  Fnc__PICK(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm,
				   const CString& para__stn_name,
				   const CString& para__arm_type,
				   const CString& para__stn_slot);
	int  _Fnc__PICK(CII_OBJECT__VARIABLE* p_variable,
					CII_OBJECT__ALARM* p_alarm,
					const CString& para__stn_name,
					const CString& para__arm_type,
					const CString& para__stn_slot);
	
	// Place -----
	CString sMODE__PLACE;
	int  Call__PLACE(CII_OBJECT__VARIABLE* p_variable,
					 CII_OBJECT__ALARM* p_alarm,
					 const CString& para__stn_name,
					 const CString& para__arm_type,
					 const CString& para__stn_slot);

	int  Fnc__PLACE(CII_OBJECT__VARIABLE* p_variable,
					CII_OBJECT__ALARM* p_alarm,
					const CString& para__stn_name,
					const CString& para__arm_type,
					const CString& para__stn_slot);
	int  _Fnc__PLACE(CII_OBJECT__VARIABLE* p_variable,
					 CII_OBJECT__ALARM* p_alarm,
					 const CString& para__stn_name,
					 const CString& para__arm_type,
					 const CString& para__stn_slot);

	// Rotate -----
	CString sMODE__ROTATE;
	int  Call__ROTATE(CII_OBJECT__VARIABLE* p_variable,
					  CII_OBJECT__ALARM* p_alarm,
					  const CString& para__stn_name, 
					  const CString& para__arm_type,
					  const CString& para__stn_slot);

	int  Fnc__ROTATE(CII_OBJECT__VARIABLE* p_variable,
					 CII_OBJECT__ALARM* p_alarm,
					 const CString& para__stn_name, 
					 const CString& para__arm_type,
					 const CString& para__stn_slot);

	// Home -----
	CString sMODE__HOME;
	int  Call__HOME(CII_OBJECT__VARIABLE* p_variable,
					CII_OBJECT__ALARM* p_alarm);

	int  Fnc__HOME(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm);


	//---------------------------------------------------------------------
	int  Fnc__EXTEND_ACT(CII_OBJECT__VARIABLE* p_variable,
						  CII_OBJECT__ALARM* p_alarm,
						  const bool act_pick,
						  const CString& para__stn_name, 
						  const CString& para__arm_type,
						  const CString& para__stn_slot);
	int  _Fnc__EXTEND_ACT(CII_OBJECT__VARIABLE* p_variable,
						  CII_OBJECT__ALARM* p_alarm,
						  const bool act_pick,
						  const CString& para__stn_name, 
						  const CString& para__arm_type,
						  const CString& para__stn_slot);

	int  Fnc__RETRACT_ACT(CII_OBJECT__VARIABLE* p_variable,
						   CII_OBJECT__ALARM* p_alarm,
						   const bool act_pick,
						   const CString& para__stn_name, 
						   const CString& para__arm_type,
						   const CString& para__stn_slot);
	int  _Fnc__RETRACT_ACT(CII_OBJECT__VARIABLE* p_variable,
						   CII_OBJECT__ALARM* p_alarm,
						   const bool act_pick,
						   const CString& para__stn_name, 
						   const CString& para__arm_type,
						   const CString& para__stn_slot);

	//---------------------------------------------------------------------
	CString sMODE__EXTEND;
	int  Call__EXTEND(CII_OBJECT__VARIABLE* p_variable,
					 CII_OBJECT__ALARM* p_alarm,
					 const CString& act_cmmd,
					 const CString& para__stn_name, 
					 const CString& para__arm_type,
					 const CString& para__stn_slot);

	CString sMODE__RETRACT;
	int  Call__RETRACT(CII_OBJECT__VARIABLE* p_variable,
					 CII_OBJECT__ALARM* p_alarm,
					 const CString& act_cmmd,
					 const CString& para__stn_name, 
					 const CString& para__arm_type,
					 const CString& para__stn_slot);

	CString sMODE__GOUP;
	int  Call__GOUP(CII_OBJECT__VARIABLE* p_variable,
					 CII_OBJECT__ALARM* p_alarm,
					 const CString& act_cmmd,
					 const CString& para__stn_name, 
					 const CString& para__arm_type,
					 const CString& para__stn_slot);

	CString sMODE__GODOWN;
	int  Call__GODOWN(CII_OBJECT__VARIABLE* p_variable,
					 CII_OBJECT__ALARM* p_alarm,
					 const CString& act_cmmd,
					 const CString& para__stn_name, 
					 const CString& para__arm_type,
					 const CString& para__stn_slot);

	CString sMODE__RQ_STN;
	int  Call__RQ_STN(CII_OBJECT__VARIABLE* p_variable,
					 CII_OBJECT__ALARM* p_alarm,
					 const CString& act_cmmd,
					 const CString& para__stn_name, 
					 const CString& para__arm_type);
					 
	CString sMODE__SET_STN;
	int  Call__SET_STN(CII_OBJECT__VARIABLE* p_variable,
					   CII_OBJECT__ALARM* p_alarm,
					   const CString& act_cmmd,
					   const CString& para__stn_name, 
					   const CString& para__arm_type);

	CString sMODE__TEACHED_CPTR_SAVE;
	int  Call__TEACHED_CPTR_SAVE(CII_OBJECT__VARIABLE* p_variable,
     						     CII_OBJECT__ALARM* p_alarm,
								 const CString& act_cmmd,
							     const CString& para__stn_name, 
							     const CString& para__arm_type);

	int  Fnc_ERROR(CII_OBJECT__ALARM* p_alarm,
				   const CString& act_cmmd,
				   const CString& para__stn_name, 
				   const CString& para__arm_type);

	//---------------------------------------------------------------------
	CString sMODE__RQ_WFR_CEN_DATA;
	int  Call__RQ_WFR_CEN_DATA(CII_OBJECT__VARIABLE* p_variable,
							   CII_OBJECT__ALARM* p_alarm);

	CString sMODE__CHECK_ERROR_CODE;
	int  Call__CHECK_ERROR_CODE(CII_OBJECT__VARIABLE* p_variable,
								CII_OBJECT__ALARM* p_alarm);

	// ...
	int  _Call__ROBOT_ACTION(CII_OBJECT__VARIABLE* p_variable, 
							 const CString& cmmd_act,
							 const CString& stn_name);
	int  _Wait__ROBOT_ACTION(CII_OBJECT__VARIABLE* p_variable,
							 const CString& stn_name);

	// ...
	void Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// ...
	int Is__OFFLINE(CII_OBJECT__ALARM* p_alarm);
	
	CString	Get__CFG_STN_NUM(const CString& stn_name);	
	CString	Get__CFG_DYNAMIC_ALGN_USE(const CString& stn_name);	
	CString Get__CFG_STN_CPTR_NUM(const CString& stn_name);
	
	// ...
	int _Update__WFR_CEN_DATA(CII_OBJECT__VARIABLE* p_variable);
	
	// ...
	void Fnc__APP_LOG(const CString& log_msg);
	void Fnc__DRV_LOG(const CString& log_msg);
	void Fnc__ACT_MSG(const CString& act_msg);	

	// ...
	int _Check__ERROR_CODE(const CString& err_code);
	
	CString _Get__Error_Msg_Of_Error_Code(const int err_code, 
		                                  const CString& err_msg);
	int _Get__Error_Msg_Info(const int err_code,
							 CString& err_name,
							 CString& err_ment,
							 CString& err_act_);

	// ...
	int  Proc__CMMD_RSP(const CString& var_name, 
						const CString& s_cmmd,
						const double to_sec,
						const BOOL active_prt,
						CStringArray& l_rsp,
						CStringArray& l_err);

	int  Check__MSG_KEY_WORD(const CString& str_data, 
							 const CString& key_word, 
							 CStringArray& l_para);
	
	CString Get__STRING_OF_LIST(const CStringArray& l_str);
	//


public:
	CObj_NET__VAC_PERSIMMON();
	~CObj_NET__VAC_PERSIMMON();

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
