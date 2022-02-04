#include "StdAfx.h"
#include "CObj__AUTO_PM.h"



//-------------------------------------------------------------------------
CObj__AUTO_PM::CObj__AUTO_PM()
{

}
CObj__AUTO_PM::~CObj__AUTO_PM()
{

}


//-------------------------------------------------------------------------
int CObj__AUTO_PM::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__AUTO_PM, "AUTO_PM");
	}
	return 1;
}
int CObj__AUTO_PM::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define DEF_LIST__NO_YES					\
"NO  YES"

#define DEF_LIST__MFC_CHECK					\
"PARTIAL.PRESSURE  MFC.CAL  ALL.CHECK"		

#define DEF_LIST__VAT_CHECK					\
"N2_5%  User_Define"


int CObj__AUTO_PM::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;


	//-------------------------------------------------------------------------
	CString str_name;
	int i;

	// ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		//
		str_name = "AUTO_PM.START_TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__AUTO_PM__START_TIME, str_name);

		str_name = "AUTO_PM.END_TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__AUTO_PM__END_TIME, str_name);

		str_name = "AUTO_PM.RESULT";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__AUTO_PM__RESULT, str_name);
	}

	// ...	
	{
		str_name = "LeakCheck.CFG.CHECK_FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DEF_LIST__NO_YES, "");
		LINK__VAR_DIGITAL_CTRL(dCH__LeakCheck__CFG_CHECK_FLAG, str_name);

		str_name = "LeakCheck.CUR.CHECK_FLAG";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LeakCheck__CUR_CHECK_FLAG, str_name);

		str_name = "LeakCheck.START_TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LeakCheck__START_TIME, str_name);

		str_name = "LeakCheck.END_TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LeakCheck__END_TIME, str_name);

		str_name = "LeakCheck.RESULT";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LeakCheck__RESULT, str_name);
	}

	// ...	
	{
		str_name = "FRC_CHECK.CFG.CHECK_FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DEF_LIST__NO_YES, "");
		LINK__VAR_DIGITAL_CTRL(dCH__FRC_CHECK__CFG_CHECK_FLAG, str_name);

		str_name = "FRC_CHECK.CUR.CHECK_FLAG";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__FRC_CHECK__CUR_CHECK_FLAG, str_name);

		str_name = "FRC_CHECK.START_TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__FRC_CHECK__START_TIME, str_name);

		str_name = "FRC_CHECK.END_TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__FRC_CHECK__END_TIME, str_name);

		str_name = "FRC_CHECK.RESULT";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__FRC_CHECK__RESULT, str_name);
	}

	// ...	
	{
		str_name = "GaugeCheck.CFG.CHECK_FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DEF_LIST__NO_YES, "");
		LINK__VAR_DIGITAL_CTRL(dCH__GaugeCheck__CFG_CHECK_FLAG, str_name);

		str_name = "GaugeCheck.CUR.CHECK_FLAG";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__GaugeCheck__CUR_CHECK_FLAG, str_name);

		str_name = "GaugeCheck.START_TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__GaugeCheck__START_TIME, str_name);

		str_name = "GaugeCheck.END_TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__GaugeCheck__END_TIME, str_name);

		str_name = "GaugeCheck.RESULT";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__GaugeCheck__RESULT, str_name);
	}

	// ...
	{
		str_name = "MfcCheck.CFG.CHECK_FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DEF_LIST__NO_YES, "");
		LINK__VAR_DIGITAL_CTRL(dCH__MfcCheck__CFG_CHECK_FLAG, str_name);

		str_name = "MfcCheck.CUR.CHECK_FLAG";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__MfcCheck__CUR_CHECK_FLAG, str_name);

		//
		str_name = "MfcCheck.CFG.CHECK_MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DEF_LIST__MFC_CHECK, "");
		LINK__VAR_DIGITAL_CTRL(dCH__MfcCheck__CFG_CHECK_MODE, str_name);

		str_name = "MfcCheck.CUR.CHECK_MODE";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__MfcCheck__CUR_CHECK_MODE, str_name);

		//
		str_name = "MfcCheck.START_TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__MfcCheck__START_TIME, str_name);

		str_name = "MfcCheck.END_TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__MfcCheck__END_TIME, str_name);

		str_name = "MfcCheck.RESULT";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__MfcCheck__RESULT, str_name);
	}

	// ...
	{
		str_name = "VatCheck.CFG.CHECK_FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DEF_LIST__NO_YES, "");
		LINK__VAR_DIGITAL_CTRL(dCH__VatCheck__CFG_CHECK_FLAG, str_name);

		str_name = "VatCheck.CUR.CHECK_FLAG";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__VatCheck__CUR_CHECK_FLAG, str_name);

		//
		str_name = "VatCheck.CFG.CHECK_MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DEF_LIST__VAT_CHECK, "");
		LINK__VAR_DIGITAL_CTRL(dCH__VatCheck__CFG_CHECK_MODE, str_name);

		str_name = "VatCheck.CUR.CHECK_MODE";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__VatCheck__CUR_CHECK_MODE, str_name);

		//
		str_name = "VatCheck.START_TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__VatCheck__START_TIME, str_name);

		str_name = "VatCheck.END_TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__VatCheck__END_TIME, str_name);

		str_name = "VatCheck.RESULT";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__VatCheck__RESULT, str_name);
	}

	return 1;
}

int CObj__AUTO_PM::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

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

	// ...
	{
		alarm_id = ALID__FNC_CANNOT_RUN;

		alarm_title  = title;
		alarm_title += "AUTO PM : Utility Program Can't run !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

int CObj__AUTO_PM::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	mERROR__USER_FNC.Set__OBJ_NAME(sObject_Name);
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}


//-------------------------------------------------------------------------
int CObj__AUTO_PM::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	// ...
	{
		p_ext_obj_create->Link__DEF_VARIABLE__ERROR_FEEDBACK(&mERROR__DEF_VAR);
	}

	// ...
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;
	int i;

	// SYSTEM CHANNEL ...
	{
		def_name = "CH.FNC.NAME";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);

		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYS_FNC_NAME,obj_name,var_name);
	}

	// OBJ : CHM CTRL ...
	{
		def_name = "OBJ.CHM_CTRL";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		pOBJ_CTRL__CHM = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}

	// OBJ : Leak Check ...
	{
		def_name = "OBJ.LEAK_CHECK";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		pOBJ_CTRL__LEAK_CHECK = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}

	// OBJ : FRC_CHECK.X ...
	{
		def_name = "OBJ.FRC_CHECK.SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iFRC_CHECK__SIZE = atoi(def_data);
		if(iFRC_CHECK__SIZE > _MAX__FRC_CHECK)			iFRC_CHECK__SIZE = _MAX__FRC_CHECK;

		for(i=0; i<iFRC_CHECK__SIZE; i++)
		{
			int id = i + 1;

			obj_name.Format("OBJ.FRC_CHECK.%1d", id);
			pOBJ_CTRL__FRC_CHECK_X[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
		}
	}

	// OBJ : GAUGE_CHECK ...
	{
		def_name = "OBJ.GAUGE_CHECK";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		pOBJ_CTRL__GAUGE_CHECK = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}

	// OBJ : VAT_CHECK ...
	{
		def_name = "OBJ.VAT_CHECK";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		pOBJ_CTRL__VAT_CHECK = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		//
		var_name = "CFG.CHECK_TYPE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__VAT_CHECK__CFG_CHECK_TYPE, obj_name,var_name);
	}

	// OBJ : MFC_CHECK ...
	{
		def_name = "OBJ.MFC_CHECK";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		pOBJ_CTRL__MFC_CHECK = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}

	return 1;
}


//-------------------------------------------------------------------------
int CObj__AUTO_PM::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	if(sEXT_CH__SYS_FNC_NAME->Check__DATA("") < 0)
	{
		int alarm_id = ALID__FNC_CANNOT_RUN;
		CString alm_msg;
		CString alm_bff;
		CString r_act;
		CString var_data;

		sEXT_CH__SYS_FNC_NAME->Get__DATA(var_data);
		alm_msg.Format("Now, %s is running.\n",var_data);
		alm_bff.Format("Please, after %s is finished, run DGF Utility Program.\n",var_data);
		alm_msg += alm_bff;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
		return -1;
	}


	// ...
	int flag = -1;

	// ...
	{
		IF__CTRL_MODE(sMODE__AUTO_PM)
		{
			flag = Call__AUTO_PM(p_variable,p_alarm);
		}
		else
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
	}

	return flag;
}
int CObj__AUTO_PM::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
