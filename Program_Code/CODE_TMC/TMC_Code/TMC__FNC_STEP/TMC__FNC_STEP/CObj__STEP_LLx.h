#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__STEP_LLx__ALID.h"
#include "CObj__STEP_LLx__DEF.h"


class CDS__LEARNED_ITEM_INFO
{
public:
	int iSTEP_ID;
	
	CString sDATA__APC;

	CString sDATA__RF_BIAS__FREQUENCY;
			
	CString sDATA__MAT_2MHz_LOAD_POS;
	
	CString sDATA__MAT_2MHz_TUNE_POS;

	// ...
	void Copy_From(const CDS__LEARNED_ITEM_INFO& src_item)
	{
		iSTEP_ID = src_item.iSTEP_ID;
		
		sDATA__APC = src_item.sDATA__APC;
		
		sDATA__RF_BIAS__FREQUENCY  = src_item.sDATA__RF_BIAS__FREQUENCY;
		
		sDATA__MAT_2MHz_LOAD_POS  = src_item.sDATA__MAT_2MHz_LOAD_POS;
		
		sDATA__MAT_2MHz_TUNE_POS  = src_item.sDATA__MAT_2MHz_TUNE_POS;
	}
};
class CDS__LEARNED_ITEM_CTRL
{
public:
	CPtrArray pList__ITEM;

	// ...
	~CDS__LEARNED_ITEM_CTRL()
	{
		Init__ALL_ITEM();
	}

	void Init__ALL_ITEM()
	{
		CDS__LEARNED_ITEM_INFO *p_info;

		int limit = pList__ITEM.GetSize();
		int i;

		for(i=0;i<limit;i++)
		{
			p_info = (CDS__LEARNED_ITEM_INFO*) pList__ITEM[i];
			delete p_info;
		}

		pList__ITEM.RemoveAll();
	}
	void Load__ITEM(const CDS__LEARNED_ITEM_INFO& src_item)
	{
		// ...
		CDS__LEARNED_ITEM_INFO *p_item = NULL;
		int check_flag = -1;

		int limit = pList__ITEM.GetSize();
		int i;

		for(i=0;i<limit;i++)
		{
			p_item = (CDS__LEARNED_ITEM_INFO*) pList__ITEM[i];
			
			if(p_item->iSTEP_ID != src_item.iSTEP_ID)
			{
				continue;
			}

			check_flag = 1;
			break;
		}

		if(check_flag < 0)
		{
			p_item = new CDS__LEARNED_ITEM_INFO;
			pList__ITEM.Add(p_item);
		}

		p_item->Copy_From(src_item);
	}
	int Get__DB_ITEM(const int db_index,CDS__LEARNED_ITEM_INFO* p_item)
	{
		// ...
		CDS__LEARNED_ITEM_INFO *p_db;
		
		if(db_index < 0)							return -1;
		if(db_index >= pList__ITEM.GetSize())		return -1;

		// ...
		{
			p_db = (CDS__LEARNED_ITEM_INFO*) pList__ITEM[db_index];
			p_item->Copy_From(*p_db);
		}
		return 1;
	}
};


class CObj__STEP_LLx : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	SCX__USER_LOG_CTRL xLOG_CTRL;
	int iSIM_FLAG;

	// SCX__PMC__DCOP_CTRL xDCOP_CTRL;
	
	// ...
	CDS__LEARNED_ITEM_CTRL mDB__LEARNED_ITEM_CTRL;
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// ...
	int iOBJ_BUSY_FLAG;

	// ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;
	CX__VAR_STRING_CTRL  sCH__OBJ_SUB_MSG;

	// Config Channel ...
	CX__VAR_ANALOG_CTRL  aCH__CFG_ESC_MAX_TEMP_DIFFERENCE;
	
	// ...
	CX__VAR_STRING_CTRL  sCH__CUR_PROC_TYPE;
	CX__VAR_STRING_CTRL  sCH__XFER_BALLAST_CTRL_FLAG;

	CX__VAR_STRING_CTRL  sCH__RCP_FILE_PATH;
	CX__VAR_DIGITAL_CTRL dCH__RCP_DATA_APP_LOG;
	CX__VAR_ANALOG_CTRL  aCH__RCP_MON_STEP_NO;
	CX__VAR_ANALOG_CTRL  aCH__RCP_FDC_STEP_TIME;

    CX__VAR_STRING_CTRL  sCH__STEP_TIME_COUNT;
	SCX__TIMER_CTRL		 xI_TIMER;

	//
	CX__VAR_STRING_CTRL  sCH__EXCEPTION_COMMAND;

	CX__VAR_STRING_CTRL  sCH__EXCEPTION_CONTINUE_REQ;
	CX__VAR_STRING_CTRL  sCH__EXCEPTION_CONTINUE_STEP_OVER_TIME;

	//
	CX__VAR_STRING_CTRL  sCH__STEP_TIME_ABORT_FLAG;

	// ...
	CX__VAR_STRING_CTRL  sCH__FDC_PIN_STATUS;

	// WAFER COUNT - INFO .....
	CX__VAR_STRING_CTRL  sCH__TOTAL_COUNT_START_DATE;
	CX__VAR_ANALOG_CTRL  aCH__WAFER_TOTAL_COUNT;

	CX__VAR_STRING_CTRL  sCH__CURRENT_COUNT_START_DATE;
	CX__VAR_ANALOG_CTRL  aCH__WAFER_CURRENT_COUNT;
	CX__VAR_DIGITAL_CTRL dCH__WAFER_CURRENT_COUNT_RESET;
	CX__VAR_DIGITAL_CTRL dCH__WAFER_TOTAL_COUNT_RESET;

	// ...
	CX__VAR_STRING_CTRL  sCH__ACTIVE__MFC_CLOSE_DELAY;
	CX__VAR_ANALOG_CTRL  aCH__CFG_STEP_DELAY_MFC_CLOSE;
	
	// RECIPE : STEP ...
	CX__VAR_STRING_CTRL  sCH__RCP_STEP_MESSAGE;
	CX__VAR_DIGITAL_CTRL dCH__RCP_STEP_MODE;
	CX__VAR_ANALOG_CTRL  aCH__RCP_STEP_TIME;

	CX__VAR_DIGITAL_CTRL dCH__RCP_APC_MODE;
	CX__VAR_ANALOG_CTRL  aCH__RCP_APC_PRESSURE;
	CX__VAR_ANALOG_CTRL  aCH__RCP_APC_POSITION;
	CX__VAR_ANALOG_CTRL  aCH__RCP_APC_PRESET_POS;
	CX__VAR_ANALOG_CTRL  aCH__RCP_APC_HOLD_DELAY;

	CX__VAR_ANALOG_CTRL  aCH__RCP_GAS_N2_FLOW;

	CX__VAR_DIGITAL_CTRL dCH__RCP_LIFT_PIN_MODE;

	CX__VAR_ANALOG_CTRL  aCH__RCP_LOOP_START;
	CX__VAR_ANALOG_CTRL  aCH__RCP_LOOP_REPEAT;

	// RECIPE : CFG ...
	CX__VAR_ANALOG_CTRL  aCH__CFG_PARA_STEP_TIME;

	CX__VAR_DIGITAL_CTRL dCH__CFG_PARA_APC_MODE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_PARA_APC_PRESSURE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_PARA_APC_POSITION;

	CX__VAR_ANALOG_CTRL  aCH__CFG_PARA_GAS_N2_FLOW;

	CX__VAR_DIGITAL_CTRL dCH__CFG_PARA_LIFT_PIN_MODE;
	//


	//---------------------------------------------------------------------
	CX__VAR_STRING_CTRL  sCH__CUR_LOTID;
	CX__VAR_STRING_CTRL  sCH__PRE_LOTID;
	CX__VAR_STRING_CTRL  sCH__LEARNED_APPLY_STATUS;

	// LEARNED DATA ...    
	CX__VAR_DIGITAL_CTRL dCH__CFG_LEARNED_APPLY_MODE;
	CX__VAR_STRING_CTRL  sCH__LEARNED_RESULT;
		
	
	//---------------------------------------------------------------------
	// RANGE PARAETER ...
	CX__VAR_ANALOG_CTRL  aCH__CFG_RANGE_ZERO;
	CX__VAR_DIGITAL_CTRL dCH__CFG_IO_INTERLOCK_SKIP;
	//


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// LINK_DB : STEP ...
	CX__VAR_DIGITAL_CTRL dEXT_CH__SLOT01_STATUS;
	CX__VAR_STRING_CTRL  sEXT_CH__CUR_LOTID;

	// LINK_DB : RCP ...
	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_PARA_MFC_N2_RANGE_MIN;
	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_PARA_MFC_N2_RANGE_MAX;
	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_PARA_MFC_N2_RANGE_DEC;
	//
	
	//----------------------------------------------------------------------------
	// OBJ : LLx_CHM ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__LLx_CHM;

	// OBJ : APC ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__APC;

	CX__VAR_DIGITAL_CTRL dEXT_CH__APC_OBJ__CTRL;
	CX__VAR_ANALOG_CTRL	 aEXT_CH__APC_OBJ__PARA_PRESSURE;
	CX__VAR_ANALOG_CTRL	 aEXT_CH__APC_OBJ__PARA_POSITION;
	CX__VAR_ANALOG_CTRL	 aEXT_CH__APC_OBJ__PARA_PRE_POS_VALUE;
	CX__VAR_ANALOG_CTRL	 aEXT_CH__APC_OBJ__PARA_PRE_POS_SEC;

	CX__VAR_DIGITAL_CTRL dEXT_CH__APC_OBJ__ABORT_FLAG;
	CX__VAR_DIGITAL_CTRL dEXT_CH__APC_OBJ__STABLE_FLAG;

	// OBJ : MFC ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__MFC_N2;

	CX__VAR_DIGITAL_CTRL dEXT_CH__MFC_N2__OBJ_CTRL;
	CX__VAR_DIGITAL_CTRL dEXT_CH__MFC_N2__CFG_USE_FLAG;

	CX__VAR_ANALOG_CTRL	 aEXT_CH__MFC_N2__SET_FLOW;
	CX__VAR_ANALOG_CTRL  aEXT_CH__MFC_N2__GET_FLOW;

	CX__VAR_STRING_CTRL  sEXT_CH__MFC_N2__CFG_GASx_NAME;
	CX__VAR_DIGITAL_CTRL dEXT_CH__MFC_N2__ABORT_FLAG;
	CX__VAR_DIGITAL_CTRL dEXT_CH__MFC_N2__STABLE_FLAG;

	// OBJ : FNC_PROC ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__PROC;

	CX__VAR_STRING_CTRL  sEXT_CH__EXCEPTION_ACT;
	CX__VAR_ANALOG_CTRL  aEXT_CH__STEP_CUR_NUM;
	CX__VAR_STRING_CTRL  sEXT_CH__LAST_STEP_FLAG;
	CX__VAR_STRING_CTRL  sEXT_CH__RCP_FILE_UPLOAD_FLAG;
	//

	// RCP : PRE_PARAMETER ...
	CX__VAR_STRING_CTRL  sCH__PRE_RCP_APC_CTRL;	
	CX__VAR_STRING_CTRL  sCH__PRE_RCP_MFC_SET_FLOW;
	//


	//-------------------------------------------------------------------------
	// OBJ - MODE 

	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__RCP_DATA_INIT;
	int Call__RCP_DATA_INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__READY;
	int Call__READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__START;
	int Call__START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__PROC;
	CString sMODE__CFG_PROC;
	int Call__PROC(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const bool cfg_mode);

	CString sMODE__PROC_SYSTEN_INIT;
	int Call__PROC_SYSTEM_INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	int Fnc__PROC_SYSTEM_INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm,CString& err_msg);

	// ...
	int  Fnc__PROC(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool cfg_mode);	
	
	int  Init__PRE_RCP_ITEM();
	void Control__RECIPE_DELAY_PARAMETER(const double step_sec, const int set_req = -1);

	// ...
	int iPRC_FLAG;

	int iSTEP_CHANGE_FLAG;
	int iSTEP_COUNT;

	int iTOLERANCE_ABORT_FLAG;

	// ...
	CString sMODE__ABORT;
	int Call__ABORT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm);
	int Fnc__ABORT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	
	CString sMODE__END;
	int Call__END(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__STEP_DB_CHECK;
	int Call__STEP_DB_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm);


	// ...
	void Mon__Wafer_Count_Ctrl(CII_OBJECT__VARIABLE* p_variable,
							   CII_OBJECT__ALARM* p_alarm);

	// ...
	int Fnc__CHECK_PART_ERROR(CII_OBJECT__VARIABLE *p_variable,
							  CII_OBJECT__ALARM *p_alarm);

	int Fnc__INIT_PART_ERROR(CII_OBJECT__VARIABLE *p_variable,
							 CII_OBJECT__ALARM *p_alarm);

	int Fnc__CHECK_PART_STABLE(CII_OBJECT__VARIABLE *p_variable,
							   CII_OBJECT__ALARM *p_alarm);

	int Get__PART_UNSTABLE_MSG(CString& err_msg);

	// ...
	void Alarm__POST_CHECK(CII_OBJECT__ALARM *p_alarm, CString msg, const int alarm_id);

	int Check__STEP_CONTROL();

	// ...
	void ALL_OBJ__WAIT(CII_OBJECT__VARIABLE *p_variable,const int mfc_check = 1);
	void ALL_OBJ__WAIT_SEC(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	void ALL_OBJ__ABORTED_TO_AVAILABLE(CII_OBJECT__VARIABLE *p_variable);
	void ALL_MFC__ABORTED_TO_AVAILABLE(CII_OBJECT__VARIABLE *p_variable);

	void MFC_OBJ__WAIT(CII_OBJECT__VARIABLE *p_variable);

	int  ALL_OBJ__ABORT_WAIT(CII_OBJECT__VARIABLE *p_variable,
							 CII_OBJECT__ALARM *p_alarm,
						     CString& err_msg,
							 const int delay_flag = 1);

	// ...
	int Fnc__OBJ_Abort_Check(const CString& log_id,const int mfc_check = -1);
	
	int Fnc__OBJ_Avaliable_Check(const CString& log_id);
	int Fnc__Get_OBJ_Not_Available_List(CString& part_list);

	// MFCx OBJ - FNC .....
	int ANY_MFC_OBJ__Check_ABORTED();
	int ALL_MFC_OBJ__Check_AVAILABLE();
	
	int ALL_MFC_OBJ__Start_MODE(const CString& mode_name);
	int ALL_MFC_OBJ__Wait_MODE(const CString& log_id);
	int ALL_MFC_OBJ__Call_MODE(const CString& mode_name,const CString& log_id);
	int ALL_MFC_OBJ__Abort_Call_MODE(const CString& mode_name,const CString& log_id);

	// APC OBJ - FNC .....
	int APC_OBJ__Start_MODE(const CString& mode_name);
	int APC_OBJ__Wait_MODE(const CString& log_id);
	int APC_OBJ__Status_MODE(const CString& log_id);
	int APC_OBJ__Call_MODE(const CString& mode_name, const CString& log_id);
	int APC_OBJ__Abort_Call_MODE(const CString& mode_name, const CString& log_id);
	//


public:
	CObj__STEP_LLx();
	~CObj__STEP_LLx();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);
	
	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	int __Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl);
	
	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);
	
	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
