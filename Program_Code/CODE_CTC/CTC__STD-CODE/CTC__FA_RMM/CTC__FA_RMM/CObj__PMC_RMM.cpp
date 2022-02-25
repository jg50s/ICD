#include "StdAfx.h"
#include "CObj__PMC_RMM.h"



//-------------------------------------------------------------------------
CObj__PMC_RMM::CObj__PMC_RMM()
{

}
CObj__PMC_RMM::~CObj__PMC_RMM()
{

}

//-------------------------------------------------------------------------
int CObj__PMC_RMM::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;
	iPM_ID = -1;

	// ...
	{
		ADD__CTRL_VAR(sMODE__CFG_ITEM_RANGE_CHECK,  "CFG_ITEM.RANGE_CHECK");
		ADD__CTRL_VAR(sMODE__STEP_ITEM_RANGE_CHECK, "STEP_ITEM.RANGE_CHECK");
	}
	return 1;
}
int CObj__PMC_RMM::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  MON_ID__RAMGE_CHANGE					1


int CObj__PMC_RMM::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CString part_name;
	CString var_name;
	int i;

	// ...
	{
		// Parameter Channel ...
		{
			var_name = "PARA.ITEM_NAME";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__PARA_ITEM_NAME, var_name);
		}

		// MFC Size ...
		for(i=0; i<CFG__MFC_SIZE; i++)
		{
			var_name.Format("MFC%1d.FLOW.MIN", i+1);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MFCx_FLOW_MIN[i], var_name);

			var_name.Format("MFC%1d.FLOW.MAX", i+1);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__MFCx_FLOW_MAX[i], var_name);

			//
			sPPNAME__MFCx_FLOW[i].Format("MFC_GAS%1d_FLOW", i+1);
		}

		// RFx : PLASMA, BIAS ...
		for(i=0; i<CFG__RFx_SIZE; i++)
		{
			     if(i == 0)		part_name = "PALSMA";
			else if(i == 1)		part_name = "BIAS";
			else				continue;

			var_name.Format("RF_%s.FREQ.MIN", part_name);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__RFx_FREQ_MIN[i], var_name);

			var_name.Format("RF_%s.FREQ.MAX", part_name);			
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__RFx_FREQ_MAX[i], var_name);

			//
			sPPNAME__RFx_FREQ_PRESET[i].Format("RF_%s_FREQUENCY_PRESET",   part_name);
			sPPNAME__RFx_FREQ_OUTPUT[i].Format("RF_%s_FREQUENCY_OUTPUT",   part_name);
			sPPNAME__RFx_FREQ_LEARNED[i].Format("RF_%s_FREQUENCY_LEARNED", part_name);
		}

		// ESC Bias Voltage ...	
		{
			var_name = "ESC.BIAS_VOLTAGE.MAX";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__ESC_BIAS_VOLTAGE_MAX, var_name);

			//
			sPPNAME__ESC_BIAS_VOLTAGE_MAX = "ESC_Bias_VOLT_THRESHOLD";
		}
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3, MON_ID__RAMGE_CHANGE);
	}
	return 1;
}

int CObj__PMC_RMM::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	return 1;
}

int CObj__PMC_RMM::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{

	return 1;
}


//-------------------------------------------------------------------------
int CObj__PMC_RMM::__INITIALIZE__OBJECT(p_variable, p_ext_obj_create)
{	
	CString def_name;
	CString def_data;

	// ...
	{	
		def_name = "PM_ID";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		iPM_ID = atoi(def_data);
	}
	return 1;
}
int CObj__PMC_RMM::__START__OBJECT()
{

	return 1;
}


//-------------------------------------------------------------------------
int CObj__PMC_RMM::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	int flag = -1;

	// ...
	{
			 IF__CTRL_MODE(sMODE__CFG_ITEM_RANGE_CHECK)			flag = Call__CFG_ITEM_RANGE_CHECK(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__STEP_ITEM_RANGE_CHECK)		flag = Call__STEP_ITEM_RANGE_CHECK(p_variable,p_alarm);
	}

	return flag;
}
int CObj__PMC_RMM::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == MON_ID__RAMGE_CHANGE)		
	{
		Mon__PARAMETER_RAMGE_CHANGE(p_variable);
		return 1;
	}

	return -1;
}
