#include "StdAfx.h"
#include "CObj_Mng__PART_STD.h"


//-------------------------------------------------------------------------
CObj_Mng__PART_STD::CObj_Mng__PART_STD()
{

}
CObj_Mng__PART_STD::~CObj_Mng__PART_STD()
{

}

//-------------------------------------------------------------------------
int CObj_Mng__PART_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	/*
	CString str_name;

	str_name = "PRO_START";
	ADD__MODE_VAR(sMODE__PRO_START,str_name);
	//
	*/
	return 1;
}
int CObj_Mng__PART_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__PART_CTRL							1


int CObj_Mng__PART_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CString str_name;
	int part_id;
	int p;
	int k;

	for(p=0; p<CFG__PMx_SIZE; p++)
	{
		CString pm_name;
		pm_name.Format("PM%1d", p+1);

		for(k=0;k<CFG__PART_SIZE;k++)
		{
			part_id = k + 1;

			// 1. ITEM
			str_name.Format("%s.PART%1d.ITEM", pm_name,part_id);
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__PART_ITEM_X[p][k],str_name);

			// 2. CHANGE DAY
			str_name.Format("%s.PART%1d.CHANGE_DAY", pm_name,part_id);
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__PART_CHANGE_DAY_X[p][k],str_name);

			// 3. REF DAY
			str_name.Format("%s.PART%1d.REF_DAY", pm_name,part_id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name,"Day",0,0,9999,"");
			LINK__VAR_ANALOG_CTRL(xCH__PART_REF_DAY_X[p][k],str_name);
			
			// 4. REF COUNT
			str_name.Format("%s.PART%1d.REF_COUNT", pm_name,part_id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name,"Count",0,0,9999,"");
			LINK__VAR_ANALOG_CTRL(xCH__PART_REF_COUNT_X[p][k],str_name);
			
			// 5. CUR DAY
			str_name.Format("%s.PART%1d.CUR_DAY", pm_name,part_id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name,"Day",0,0,9999,"");
			LINK__VAR_ANALOG_CTRL(xCH__PART_CUR_DAY_X[p][k],str_name);
			
			// 6. CUR COUNT
			str_name.Format("%s.PART%1d.CUR_COUNT", pm_name,part_id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name,"Count",0,0,9999,"");
			LINK__VAR_ANALOG_CTRL(xCH__PART_CUR_COUNT_X[p][k],str_name);
			
			// 7. PERCENT
			str_name.Format("%s.PART%1d.PERCENT", pm_name,part_id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name,"%",0,0,100,"");
			LINK__VAR_ANALOG_CTRL(xCH__PART_PERCENT_X[p][k],str_name);
			
			// 8. RESET
			str_name.Format("%s.PART%1d.RESET", pm_name,part_id);
			STD__ADD_DIGITAL_WITH_COMMENT(str_name,"NO  YES","");
			LINK__VAR_DIGITAL_CTRL(xCH__PART_RESET_X[p][k],str_name);

			// 9. COMMENT
			str_name.Format("%s.PART%1d.COMMENT", pm_name,part_id);
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__PART_COMMENT_X[p][k],str_name);
		}

		// ALL RESET
		str_name.Format("%s.PART.ALL.RESET", pm_name);
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,"NO  YES","");
		LINK__VAR_DIGITAL_CTRL(xCH__PART_ALL_RESET_X[p],str_name);

		// POPUP PERIOD
		str_name.Format("%s.POPUP.PERIOD", pm_name);
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"hour",0,1,24,"");
		LINK__VAR_ANALOG_CTRL(xCH__POPUP_PERIOD_X[p],str_name);

		str_name.Format("%s.POPUP.CUR.DAY", pm_name);
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__POPUP_CUR_DAY_X[p],str_name);

		//
		str_name.Format("%s.MSG.WIN", pm_name);
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__MSG_WIN_X[p],str_name);

		for(k=0; k<CFG__EXCHANGE_SIZE; k++)
		{
			str_name.Format("%s.PART.EXCHANGE.MSG%1d", pm_name,k+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__PART_EXCHANGE_MSG_X[p][k],str_name);
		}

		//
		str_name.Format("%s.ALERT.UNIT", pm_name);
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__ALERT_UNIT_X[p],str_name);

		str_name.Format("%s.ALERT.TIME", pm_name);
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__ALERT_TIME_X[p],str_name);

		str_name.Format("%s.ALERT.PART.NAME", pm_name);
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__ALERT_PART_NAME_X[p],str_name);

		str_name.Format("%s.ALERT.PART.REF.DAY", pm_name);
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__ALERT_PART_REF_DAY_X[p],str_name);

		str_name.Format("%s.ALERT.PART.REF.COUNT", pm_name);
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__ALERT_PART_REF_COUNT_X[p],str_name);

		str_name.Format("%s.ALERT.PART.CUR.COUNT", pm_name);
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__ALERT_PART_CUR_COUNT_X[p],str_name);
	}

	// ...
	CString d_list;
	CString str_item;

	for(k=0; k<CFG__PART_SIZE; k++)
	{
		str_item.Format("ITEM%1d ", k+1);
		d_list += str_item;
	}

	for(p=0; p<CFG__PMx_SIZE; p++)
	{
		CString pm_name;
		pm_name.Format("PM%1d", p+1);

		//
		str_name.Format("%s.SEL.PART.ITEM", pm_name);
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, d_list, "");
		LINK__VAR_DIGITAL_CTRL(dCH__SEL_PART_ITEM_X[p],str_name);

		str_name.Format("%s.SEL.PART.REF.DAY", pm_name);
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__SEL_PART_REF_DAY_X[p],str_name);
	
		str_name.Format("%s.SEL.PART.REF.COUNT", pm_name);
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__SEL_PART_REF_COUNT_X[p],str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(5.0,MON_ID__PART_CTRL);
	}
	return 1;
}

int CObj_Mng__PART_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;

	// ...
	{
		alarm_title  = title;
		alarm_title += "OBJECT MODE : UNKNOWN";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("ABORT");
	
		ADD__ALARM_EX(ALID__OBJECT_MODE_UNKNOWN,alarm_title,alarm_msg,l_act);
	}
	return 1;
}

int CObj_Mng__PART_STD::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	mERROR__USER_FNC.Set__OBJ_NAME(sObject_Name);
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj_Mng__PART_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;
	int p;

	// ...
	def_name = "DATA.PMx_SIZE";
	p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

	iPMx_SIZE = atoi(def_data);
	if(iPMx_SIZE > CFG__PMx_SIZE)		iPMx_SIZE = CFG__PMx_SIZE;

	for(p=0; p<iPMx_SIZE; p++)
	{
		CString pm_name;
		pm_name.Format("PM%1d", p+1);

		// MODULE USE ...
		{
			def_name.Format("%s.CH_CFG_MODULE_USE", pm_name);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);

			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(xEXT_CH__CFG_MODULE_USE_X[p], obj_name,var_name);
		}
		// MATERIAL COUNT ...
		{
			def_name.Format("%s.CH_MATERIAL_COUNT", pm_name);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);

			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(xEXT_CH__MODULE_MATERIAL_COUNT_X[p], obj_name,var_name);
		}
		// POPUP WIN NAME ...
		{
			def_name.Format("%s.POPUP_WIN_NAME", pm_name);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

			sSTR__POPUP_WIN_NAME_X[p] = def_data;
		}
		// CEID ...
		{
			def_name.Format("%s.CEID__PART_CHANGE_ALERT", pm_name);
			p_ext_obj_create->Get__DEF_CONST_DATA_EX(def_name,def_data,-1);

			if(def_data.GetLength() > 0)		iCEID__PART_CHANGE_ALERT_X[p] = atoi(def_data);
			else								iCEID__PART_CHANGE_ALERT_X[p] = 0;
		}

		xCH__ALERT_UNIT_X[p]->Set__DATA("DAY");
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj_Mng__PART_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	/*
	IF__OBJ_MODE(sMODE__PRO_START)		flag = Call__PRO_START(p_variable);

	else
	*/
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

int CObj_Mng__PART_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__PART_CTRL:
			Mon__PART_CTRL(p_variable,p_alarm);
			break;
	}
	return 1;
}
