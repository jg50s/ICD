#include "StdAfx.h"
#include "CObj__PMx_EX.h"
#include "CObj__PMx_EX__ALID.h"


//-------------------------------------------------------------------------
CObj__PMx_EX::CObj__PMx_EX()
{

}
CObj__PMx_EX::~CObj__PMx_EX()
{

}

//-------------------------------------------------------------------------
int CObj__PMx_EX::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	return 1;
}
int CObj__PMx_EX::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__INFO_CTRL							1


int CObj__PMx_EX::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CString str_name;
	CString part_name;
	int i;

	// PMx CTRL ...
	{
		str_name = "PMx_CTRL.SEL_ID";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__PMx_CTRL__SEL_ID,str_name);

		for(i=0;i<CFG__PMC_SIZE;i++)
		{
			str_name.Format("PMx_CTRL.LOCK_FLAG.%1d", i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__PMx_CTRL__LOCK_FLAG[i],str_name);
		}
	}

	// PROCESS INFO ...
	{
		str_name = "PMC.PROC.LOTID";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PROC_LOTID, str_name);

		str_name = "PMC.PROC.RECIPEID";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PROC_RECIPEID, str_name);

		str_name = "PMC.PROC.CUR_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PROC_CUR_TIME, str_name);

		str_name = "PMC.PROC.TOTAL_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PROC_TOTAL_TIME, str_name);

		str_name = "PMC.PROC.CUR_STEP";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PROC_CUR_STEP, str_name);

		str_name = "PMC.PROC.TOTAL_STEP";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PROC_TOTAL_STEP, str_name);

		//
		str_name = "PMC.STEP.CUR_TIME";    
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_STEP_CUR_TIME, str_name);

		str_name = "PMC.STEP.TOTAL_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_STEP_TOTAL_TIME, str_name);

		str_name = "PMC.STEP.CUR_NAME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_STEP_CUR_NAME, str_name);

		str_name = "PMC.STEP.CUR_TYPE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_STEP_CUR_TYPE, str_name);

		str_name = "PMC.STEP.EPD_DETECT_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_STEP_EPD_DETECT_TIME, str_name);

		str_name = "PMC.STEP.OVERETCH_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_STEP_EPD_OVERETCH_TIME, str_name);

		str_name = "PMC.STEP.OVERETCH_PERCENT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_STEP_EPD_OVERETCH_PERCENT, str_name);

		str_name = "PMC.STEP.OBJ_SUB_MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_STEP_OBJ_MAIN_MSG, str_name);

		str_name = "PMC.STEP.OBJ_MAIN_MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_STEP_OBJ_SUB_MSG, str_name);
	}

	// SYSTEM INFO ...
	{
		str_name = "PMC_SYS.OBJ_STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_OBJ_STATUS, str_name);
	
		str_name = "PMC_SYS.LIFT_PIN_STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_LIFT_PIN_STS, str_name);

		str_name = "PMC_SYS.CHUCK_STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_CHUCK_STS, str_name);

		str_name = "PMC_SYS.SLIT_VLV_STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_SLIT_VLV_STS, str_name);

		str_name = "PMC_SYS.PRC_STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_PRC_STS, str_name);

		str_name = "PMC_SYS.SLOT01_STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_SLOT01_STATUS, str_name);

		str_name = "PMC_SYS.PRESSURE_STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_PRESSURE_STATUS, str_name);

		str_name = "PMC_SYS.PRESSURE_VALUE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_PRESSURE_VALUE, str_name);

		str_name = "PMC_SYS.RF_ON_STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_RF_ON_STS, str_name);
		
		str_name = "PMC_SYS.WAP_CUR_POS_STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_WAP_CUR_POS_STS, str_name);

		//
		str_name = "PMC_SYS.SENSOR.CHM_BALLAST";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_SENSOR_CHM_BALLAST, str_name);

		str_name = "PMC_SYS.SENSOR.PIN_UP";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_SENSOR_PIN_UP, str_name);

		str_name = "PMC_SYS.SENSOR.PIN_MIDDLE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_SENSOR_PIN_MIDDLE, str_name);

		str_name = "PMC_SYS.SENSOR.PIN_DOWN";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_SENSOR_PIN_DOWN, str_name);

		str_name = "PMC_SYS.SENSOR.ATM";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_SENSOR_ATM, str_name);

		str_name = "PMC_SYS.SENSOR.VAC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_SENSOR_VAC, str_name);

		str_name = "PMC_SYS.SENSOR.500mTorr";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_SENSOR_500mTorr, str_name);

		str_name = "PMC_SYS.SENSOR.100mTorr";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_SENSOR_100mTorr, str_name);

		//
		str_name = "PMC_SYS.APC.CUR_PRESSURE_mTORR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_APC_CUR_PRESSURE_mTORR, str_name);

		str_name = "PMC_SYS.APC.CUR_POSITION_GET";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_APC_CUR_POSITION_GET, str_name);

		str_name = "PMC_SYS.APC.CUR_POSITION_PER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_SYS_APC_CUR_POSITION_PER, str_name);
	}

	// MFC ITEM ...
	for(i=0;i<CFG__MFC_SIZE;i++)
	{
		str_name.Format("PMC_PART.MFC%1d.NAME", i+1);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_MFC_NAME[i], str_name);
		
		str_name.Format("PMC_PART.MFC%1d.FLOW_SET", i+1);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_MFC_FLOW_SET[i], str_name);
		
		str_name.Format("PMC_PART.MFC%1d.FLOW_GET", i+1);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_MFC_FLOW_GET[i], str_name);
	}

	for(i=0;i<CFG__RF_SIZE;i++)
	{
			 if(i == 0)		part_name = "RF2MHz";
		else if(i == 1)		part_name = "RF27MHz";
		else if(i == 2)		part_name = "RF60MHz";
		else				continue;

		str_name.Format("PMC_PART.%s.ON_STATUS_SET", part_name);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_RFx_ON_STATUS_SET[i], str_name);

		str_name.Format("PMC_PART.%s.ON_STATUS_GET", part_name);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_RFx_ON_STATUS_GET[i], str_name);

		str_name.Format("PMC_PART.%s.POWER_SET", part_name);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_RFx_POWER_SET[i], str_name);

		str_name.Format("PMC_PART.%s.RAMP_SET", part_name);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_RFx_RAMP_SET[i], str_name);

		str_name.Format("PMC_PART.%s.FORWARD_POWER_GET", part_name);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_RFx_FORWARD_POWER_GET[i], str_name);
		
		str_name.Format("PMC_PART.%s.REFLECT_POWER_GET", part_name);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_RFx_REFLECT_POWER_GET[i], str_name);

		str_name.Format("PMC_PART.%s.MONITRING_STATUS", part_name);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_RFx_MONITRING_STATUS[i], str_name);
		
		str_name.Format("PMC_PART.%s.FREQUENCY_START_SET", part_name);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_RFx_FREQUENCY_START_SET[i], str_name);

		str_name.Format("PMC_PART.%s.FREQUENCY_POWER_SET", part_name);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_RFx_FREQUENCY_POWER_SET[i], str_name);

		str_name.Format("PMC_PART.%s.FREQUENCY_POWER_GET", part_name);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_RFx_FREQUENCY_POWER_GET[i], str_name);
	}

	// MATCHER ITEM ...
	for(i=0; i<CFG__RF_SIZE; i++)
	{
		int id = i + 1;

		str_name.Format("PMC_PART.MAT%1d.ON_STATUS", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_MATx_ON_STATUS[i], str_name);

		str_name.Format("PMC_PART.MAT%1d.TUNE_STATUS", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_MATx_TUNE_STATUS[i], str_name);
		
		str_name.Format("PMC_PART.MAT%1d.CONTROL_MODE", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_MATx_CONTROL_MODE[i], str_name);

		str_name.Format("PMC_PART.MAT%1d.CUR_LOAD_POS", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_MATx_CUR_LOAD_POS[i], str_name);

		str_name.Format("PMC_PART.MAT%1d.CUR_TUNE_POS", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_MATx_CUR_TUNE_POS[i], str_name);
	}

	// TEMPERATURE ITEM ...
	for(i=0; i<iHTR_SIZE; i++)
	{
		int id = i + 1;

		str_name.Format("PMC_PART.HTR%1d.TEMP_SET", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_HTRx_TEMP_SET[i], str_name);

		str_name.Format("PMC_PART.HTR%1d.TEMP_GET", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_HTRx_TEMP_GET[i], str_name);
	}

	// ESC ...
	{
		str_name = "PMC_PART.ESC.TOTAL_VOLT_SET";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_ESC_TOTAL_VOLT_SET, str_name);

		str_name = "PMC_PART.ESC.TOTAL_VOLT_GET";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_ESC_TOTAL_VOLT_GET, str_name);

		str_name = "PMC_PART.ESC.BIAS_VOLT_SET";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_ESC_BIAS_VOLT_SET, str_name);

		str_name = "PMC_PART.ESC.BIAS_VOLT_GET";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_ESC_BIAS_VOLT_GET, str_name);

		str_name = "PMC_PART.ESC.COOLANT_GET";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_ESC_COOLANT_GET, str_name);

		str_name = "PMC_PART.ESC.POWER_ON_STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_ESC_POWER_ON_STATUS, str_name);
		
		str_name = "PMC_PART.ESC.REVERSE_POLARITY_STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_ESC_REVERSE_POLARITY_STATUS, str_name);
		
		str_name = "PMC_PART.ESC.COOLANT_FLOW_STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_ESC_COOLANT_FLOW_STATUS, str_name);
	}

	// He : Inner / Outer ...
	for(i=0; i<CFG__He_SIZE; i++)
	{
			 if(i == 0)		part_name = "He_INNER";
		else if(i == 1)		part_name = "He_OUTER";
		else				continue;

		//
		str_name.Format("PMC_PART.%s.PRESSURE_SET", part_name);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_He_CTRL_PRESSURE_SET[i], str_name);

		str_name.Format("PMC_PART.%s.PRESSURE_GET", part_name);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_He_CTRL_PRESSURE_GET[i], str_name);

		str_name.Format("PMC_PART.%s.FLOW_GET", part_name);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_PART_He_CTRL_FLOW_GET[i], str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__INFO_CTRL);
	}
	return 1;
}

int CObj__PMx_EX::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	// ...
	int alarm_id;
	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	
	// ...
	{
		alarm_id = ALID__OBJECT_MODE_UNKNOWN;

		alarm_title  = title;
		alarm_title += "OBJECT MODE : UNKNOWN";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("ABORT");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

int CObj__PMx_EX::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	mERROR__USER_FNC.Set__OBJ_NAME(sObject_Name);
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	// ...
	{

	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__PMx_EX::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;
	int i;
	int k;


	// PMx INFO ...
	{
		// PM SIZE ...
		{
			def_name = "DATA.PM_SIZE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
			iPMC_SIZE = atoi(def_data);
			if(iPMC_SIZE > CFG__PMC_SIZE)		iPMC_SIZE = CFG__PMC_SIZE;
		}

		for(i=0; i<iPMC_SIZE; i++)
		{
			def_name.Format("OBJ__PM%1d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

			// PROC INFO  ...
			{
				var_name = "LOTID";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PROC_LOTID[i], def_data,var_name);

				var_name = "RECIPE";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PROC_RECIPEID[i], def_data,var_name);

				//
				var_name = "PHY_PMC.PROC.CUR_TIME";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PROC_CUR_TIME[i], def_data,var_name);

				var_name = "PHY_PMC.PROC.TOTAL_TIME";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PROC_TOTAL_TIME[i], def_data,var_name);

				var_name = "PHY_PMC.PROC.CUR_STEP";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PROC_CUR_STEP[i], def_data,var_name);

				var_name = "PHY_PMC.PROC.TOTAL_STEP";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PROC_TOTAL_STEP[i], def_data,var_name);

				//
				var_name = "PHY_PMC.STEP.CUR_TIME";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_STEP_CUR_TIME[i], def_data,var_name);
	
				var_name = "PHY_PMC.STEP.TOTAL_TIME";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_STEP_TOTAL_TIME[i], def_data,var_name);	

				var_name = "PHY_PMC.STEP.CUR_NAME";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_STEP_CUR_NAME[i], def_data,var_name);

				var_name = "PHY_PMC.STEP.CUR_TYPE";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_STEP_CUR_TYPE[i], def_data,var_name);

				var_name = "PHY_PMC.STEP.EPD_DETECT_TIME";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_STEP_EPD_DETECT_TIME[i], def_data,var_name);
	
				var_name = "PHY_PMC.STEP.EPD_OVERETCH_TIME";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_STEP_EPD_OVERETCH_TIME[i], def_data,var_name);

				var_name = "PHY_PMC.STEP.EPD_OVERETCH_PERCENT";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_STEP_EPD_OVERETCH_PERCENT[i], def_data,var_name);

				var_name = "PHY_PMC.STEP.OBJ_MAIN_MSG";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_STEP_OBJ_MAIN_MSG[i], def_data,var_name);

				var_name = "PHY_PMC.STEP.OBJ_SUB_MSG";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_STEP_OBJ_SUB_MSG[i], def_data,var_name);
			}

			// SYSTEM INFO ...
			{
				var_name = "OBJ.VIRTUAL.STATUS";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_OBJ_STATUS[i], def_data,var_name);
	
				//
				var_name = "LIFT.PIN.STS";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_LIFT_PIN_STS[i], def_data,var_name);

				var_name = "CHUCK.STS";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_CHUCK_STS[i], def_data,var_name);

				var_name = "SLIT.VLV.STS";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_SLIT_VLV_STS[i], def_data,var_name);

				var_name = "RF.ON.STS";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_RF_ON_STS[i], def_data,var_name);

				var_name = "WAP.CUR.POS.STS";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_WAP_CUR_POS_STS[i], def_data,var_name);

				//
				var_name = "PRC.STS";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_PRC_STS[i], def_data,var_name);

				//
				var_name = "SLOT01.STATUS";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_SLOT01_STATUS[i], def_data,var_name);

				//
				var_name = "PRESSURE.STATUS";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_PRESSURE_STATUS[i], def_data,var_name);

				var_name = "PRESSURE.VALUE";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_PRESSURE_VALUE[i], def_data,var_name);

				// ...
				var_name = "PHY_PMC.SENSOR.CHM.BALLAST";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_SENSOR_CHM_BALLAST[i], def_data,var_name);

				var_name = "PHY_PMC.SENSOR.PIN.UP";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_SENSOR_PIN_UP[i], def_data,var_name);

				var_name = "PHY_PMC.SENSOR.PIN.MIDDLE";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_SENSOR_PIN_MIDDLE[i], def_data,var_name);

				var_name = "PHY_PMC.SENSOR.PIN.DOWN";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_SENSOR_PIN_DOWN[i], def_data,var_name);

				var_name = "PHY_PMC.SENSOR.ATM";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_SENSOR_ATM[i], def_data,var_name);

				var_name = "PHY_PMC.SENSOR.VAC";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_SENSOR_VAC[i], def_data,var_name);

				var_name = "PHY_PMC.SENSOR.500mTorr";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_SENSOR_500mTorr[i], def_data,var_name);

				var_name = "PHY_PMC.SENSOR.100mTorr";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_SENSOR_100mTorr[i], def_data,var_name);

				//
				var_name = "PHY_PMC.APC.CUR.PRESSURE.mTORR";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_APC_CUR_PRESSURE_mTORR[i], def_data,var_name);

				var_name = "PHY_PMC.APC.CUR.POSITION.GET";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_APC_CUR_POSITION_GET[i], def_data,var_name);

				var_name = "PHY_PMC.APC.CUR.POSITION.PER";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_SYS_APC_CUR_POSITION_PER[i], def_data,var_name);
			}
		}
	}

	// DB OBJ ...
	{
		def_name = "OBJ__DB";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		for(i=0; i<iPMC_SIZE; i++)
		{
			var_name.Format("PM%1d.USE", i+1);
			LINK__EXT_VAR_DIGITAL_CTRL(xEXT_CH__PMx_USE_FLAG[i], obj_name,var_name);
		}
	}

	// PART ITEM ...
	for(k=0; k<iPMC_SIZE; k++)
	{
		int chm_id = k + 1;

		// MFC ITEM ...
		{
			def_name.Format("%1d.DATA.MFC.SIZE", chm_id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			iMFC_SIZE = atoi(def_data);
			if(iMFC_SIZE > CFG__MFC_SIZE)			iMFC_SIZE = CFG__MFC_SIZE;

			for(i=0; i<iMFC_SIZE; i++)
			{
				int mfc_id = i + 1;

				// NAME
				def_name.Format("%1d.CH.MFC%1d.NAME", chm_id,mfc_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_MFC_NAME[k][i], obj_name,var_name);

				// FLOW GET
				def_name.Format("%1d.CH.MFC%1d.FLOW_SET", chm_id,mfc_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_MFC_FLOW_SET[k][i], obj_name,var_name);

				// FLOW SET
				def_name.Format("%1d.CH.MFC%1d.FLOW_GET", chm_id,mfc_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_MFC_FLOW_GET[k][i], obj_name,var_name);
			}
		}

		// RF ITEM ...
		{
			for(i=0;i<CFG__RF_SIZE;i++)
			{
				int rf_id = i + 1;

				// 
				def_name.Format("%1d.CH.RF%1d.ON_STATUS_SET", chm_id,rf_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_RFx_ON_STATUS_SET[k][i], obj_name,var_name);

				//
				def_name.Format("%1d.CH.RF%1d.ON_STATUS_GET", chm_id,rf_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_RFx_ON_STATUS_GET[k][i], obj_name,var_name);

				//
				def_name.Format("%1d.CH.RF%1d.POWER_SET", chm_id,rf_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_RFx_POWER_SET[k][i], obj_name,var_name);

				//
				def_name.Format("%1d.CH.RF%1d.RAMP_SET", chm_id,rf_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_RFx_RAMP_SET[k][i], obj_name,var_name);

				//
				def_name.Format("%1d.CH.RF%1d.FORWARD_POWER_GET", chm_id,rf_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_RFx_FORWARD_POWER_GET[k][i], obj_name,var_name);	

				//
				def_name.Format("%1d.CH.RF%1d.REFLECT_POWER_GET", chm_id,rf_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_RFx_REFLECT_POWER_GET[k][i], obj_name,var_name);

				//
				def_name.Format("%1d.CH.RF%1d.MONITORING_STATUS", chm_id,rf_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_RFx_MONITRING_STATUS[k][i], obj_name,var_name);

				//
				def_name.Format("%1d.CH.RF%1d.FREQUENCY_START_SET", chm_id,rf_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_RFx_FREQUENCY_START_SET[k][i], obj_name,var_name);

				//
				def_name.Format("%1d.CH.RF%1d.FREQUENCY_POWER_SET", chm_id,rf_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_RFx_FREQUENCY_POWER_SET[k][i], obj_name,var_name);

				//
				def_name.Format("%1d.CH.RF%1d.FREQUENCY_POWER_GET", chm_id,rf_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_RFx_FREQUENCY_POWER_GET[k][i], obj_name,var_name);
			}
		}

		// MATCHER ITEM ...
		{
			for(i=0;i<CFG__RF_SIZE;i++)
			{
				int rf_id = i + 1;

				//
				def_name.Format("%1d.CH.MAT%1d.ON_STATUS", chm_id,rf_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_MATx_ON_STATUS[k][i], obj_name,var_name);

				def_name.Format("%1d.CH.MAT%1d.TUNE_STATUS", chm_id,rf_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_MATx_TUNE_STATUS[k][i], obj_name,var_name);

				def_name.Format("%1d.CH.MAT%1d.CONTROL_MODE", chm_id,rf_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_MATx_CONTROL_MODE[k][i], obj_name,var_name);

				def_name.Format("%1d.CH.MAT%1d.CUR_LOAD_POS", chm_id,rf_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_MATx_CUR_LOAD_POS[k][i], obj_name,var_name);

				def_name.Format("%1d.CH.MAT%1d.CUR_TUNE_POS", chm_id,rf_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_MATx_CUR_TUNE_POS[k][i], obj_name,var_name);
			}
		}

		// TEMPERATURE ITEM ...
		{
			def_name.Format("%1d.DATA.HEATER.SIZE", chm_id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			int iHTR_SIZE = atoi(def_data);
			if(iHTR_SIZE > CFG__HTR_SIZE)		iHTR_SIZE = CFG__HTR_SIZE;
			
			for(i=0; i<iHTR_SIZE; i++)
			{
				int h_id = i + 1;

				def_name.Format("%1d.CH.HTR%1d.TEMP_SET", chm_id,h_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_HTRx_TEMP_SET[k][i], obj_name,var_name);

				def_name.Format("%1d.CH.HTR%1d.TEMP_GET", chm_id,h_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_HTRx_TEMP_GET[k][i], obj_name,var_name);
			}
		}

		// ESC ...
		{
			def_name.Format("%1d.CH.ESC.TOTAL_VOLT_SET", chm_id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_ESC_TOTAL_VOLT_SET[k], obj_name,var_name);

			def_name.Format("%1d.CH.ESC.TOTAL_VOLT_GET", chm_id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_ESC_TOTAL_VOLT_GET[k], obj_name,var_name);

			def_name.Format("%1d.CH.ESC.BIAS_VOLT_SET", chm_id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_ESC_BIAS_VOLT_SET[k], obj_name,var_name);

			def_name.Format("%1d.CH.ESC.BIAS_VOLT_GET", chm_id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_ESC_BIAS_VOLT_GET[k], obj_name,var_name);	

			def_name.Format("%1d.CH.ESC.COOLANT_GET", chm_id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_ESC_COOLANT_GET[k], obj_name,var_name);

			def_name.Format("%1d.CH.ESC.POWER_ON_STATUS", chm_id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_ESC_POWER_ON_STATUS[k], obj_name,var_name);

			def_name.Format("%1d.CH.ESC.REVERSE_POLARITY_STATUS", chm_id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_ESC_REVERSE_POLARITY_STATUS[k], obj_name,var_name);

			def_name.Format("%1d.CH.ESC.COOLANT_FLOW_STATUS", chm_id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_ESC_COOLANT_FLOW_STATUS[k], obj_name,var_name);
		}

		// He Inner / Outer - ITEM ...
		for(i=0; i<CFG__He_SIZE; i++)
		{
			int he_id = i + 1;

			//
			def_name.Format("%1d.CH.He_%1d.PRESSURE_SET", chm_id,he_id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_He_CTRL_PRESSURE_SET[k][i], obj_name,var_name);

			def_name.Format("%1d.CH.He_%1d.PRESSURE_GET", chm_id,he_id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_He_CTRL_PRESSURE_GET[k][i], obj_name,var_name);

			def_name.Format("%1d.CH.He_%1d.FLOW_GET", chm_id,he_id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PART_He_CTRL_FLOW_GET[k][i], obj_name,var_name);
		}
	}
	
	return 1;
}

//-------------------------------------------------------------------------
int CObj__PMx_EX::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
		CString bff;
		CString alarm_msg;
		CString r_act;

		bff.Format("Object Name : %s\n",sObject_Name);
		alarm_msg  = bff;
		bff.Format("Unknown Object Mode : \"%s\"\n",mode);
		alarm_msg += bff;

		p_alarm->Popup__ALARM_With_MESSAGE(ALID__OBJECT_MODE_UNKNOWN,alarm_msg,r_act);
	}

	return flag;
}
int CObj__PMx_EX::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__INFO_CTRL:
			Mon__INFO_CTRL(p_variable,p_alarm);
			break;
	}
	return 1;
}
