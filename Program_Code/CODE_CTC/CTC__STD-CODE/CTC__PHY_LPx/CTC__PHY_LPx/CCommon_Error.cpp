#include "StdAfx.h"
#include "CCommon_Error.h"


//------------------------------------------------------------------------------------------------
CCommon_Error__MODULE_OBJ::CCommon_Error__MODULE_OBJ()
{

}
CCommon_Error__MODULE_OBJ::~CCommon_Error__MODULE_OBJ()
{

}

// ...
int CCommon_Error__MODULE_OBJ
::Call__ERROR__MODULE_OBJ(const CString& upper_obj,
						  const CString& ch_ctrl,
						  const CString& ch_mode,
						  const CString& ch_status,
						  const int err_type,
						  const CString& err_msg,
						  CII_OBJECT__ALARM *p_alarm)
{
	CString msg;
	CString bff;

	bff.Format("Upper Object : %s\n",upper_obj);
	msg += bff;

	bff.Format("Ctrl Channel : %s\n",ch_ctrl);
	msg += bff;

	bff.Format("Mode Channel : %s\n",ch_mode);
	msg += bff;

	bff.Format("Status Channel : %s\n",ch_status);
	msg += bff;

	bff.Format("Error Type : %1d\n",err_type);
	msg += bff;

	bff.Format("Error MSG : [%s]\n",err_msg);
	msg += bff;

	if(p_alarm == NULL)
	{
		MessageBox(NULL,msg,"CTC__PHY_LPx - Call__ERROR__MODULE_OBJ()",MB_OK|MB_TOPMOST|MB_ICONERROR);
	}
	else
	{
		CString r_act;
		p_alarm->Popup__ALARM_With_MESSAGE(ALID__MODULE_OBJ__CALL_ERROR,msg,r_act);
	}
	return 1;
}

int CCommon_Error__MODULE_OBJ
::Call__ERROR__ABORTED(const CString& upper_obj,
					   const CString& obj_mode,
					   CII_OBJECT__ALARM *p_alarm)
{
	CString alm_msg;
	CString alm_bff;
	CString r_act;

	alm_bff.Format("Upper Object : %s\n", upper_obj);
	alm_msg += alm_bff;

	alm_bff.Format("Object Mode  : %s\n", obj_mode);
	alm_msg += alm_bff;

	p_alarm->Popup__ALARM_With_MESSAGE(ALID__MODULE_OBJ__ABORTED, alm_msg, r_act);
	return 1;
}

int CCommon_Error__MODULE_OBJ
::Call__ERROR__OFFLINE(const CString& upper_obj,
					   const CString& obj_mode,
					   CII_OBJECT__ALARM *p_alarm)
{
	CString alm_msg;
	CString alm_bff;
	CString r_act;

	alm_bff.Format("Upper Object : %s\n",upper_obj);
	alm_msg += alm_bff;

	alm_bff.Format("Object Mode  : %s\n",obj_mode);
	alm_msg += alm_bff;

	p_alarm->Popup__ALARM_With_MESSAGE(ALID__MODULE_OBJ__OFFLINE, alm_msg, r_act);
	return 1;
}

int CCommon_Error__MODULE_OBJ
::Call__ERROR__NOT_STANDBY(const CString& upper_obj,
						   const CString& obj_mode,
						   CII_OBJECT__ALARM *p_alarm)
{
	CString alm_msg;
	CString alm_bff;
	CString r_act;

	alm_bff.Format("Upper Object : %s\n",upper_obj);
	alm_msg += alm_bff;

	alm_bff.Format("Object Mode  : %s\n",obj_mode);
	alm_msg += alm_bff;

	p_alarm->Popup__ALARM_With_MESSAGE(ALID__MODULE_OBJ__NOT_STANDBY, alm_msg, r_act);
	return 1;
}


//------------------------------------------------------------------------------------------------
CCommon_Error__DEF_VARIABLE::CCommon_Error__DEF_VARIABLE()
{

}
CCommon_Error__DEF_VARIABLE::~CCommon_Error__DEF_VARIABLE()
{

}

// ...
int CCommon_Error__DEF_VARIABLE
::Call__ERROR__GET_DEF_DIGITAL_DESCRIPTION(const CString& obj_name,
										   const CString& dsc_name)
{
	CString alm_msg;
	CString alm_bff;

	alm_bff.Format("Object Name : %s\n", obj_name);
	alm_msg += alm_bff;

	alm_bff.Format("Description Name : %s\n", dsc_name);
	alm_msg += alm_bff;

	MessageBox(NULL, alm_msg, "CCommon_Error__DEF_VARIABLE::Call__ERROR__GET_DEF_DIGITAL_DESCRIPTION()", MB_OK|MB_TOPMOST|MB_ICONERROR);
	return 1;
}

int CCommon_Error__DEF_VARIABLE
:: Call__ERROR__GET_DEF_CONST_DATA(const CString& obj_name,
								   const CString& def_var)
{
	CString alm_msg;
	CString alm_bff;

	alm_bff.Format("Object Name : %s\n", obj_name);
	alm_msg += alm_bff;

	alm_bff.Format("Define Variable : %s\n", def_var);
	alm_msg += alm_bff;

	MessageBox(NULL, alm_msg, "CCommon_Error__DEF_VARIABLE::Call__ERROR__GET_DEF_CONST_DATA()", MB_OK|MB_TOPMOST|MB_ICONERROR);
	return 1;
}

int CCommon_Error__DEF_VARIABLE
::Call__ERROR__GET_CHANNEL_TYPE_CTRL(const CString& ch_type,
								     const CString& obj_name,
								     const CString& var_name)
{
	CString alm_msg;
	CString alm_bff;

	alm_bff.Format("Channel Type : %s\n",ch_type);
	alm_msg += alm_bff;

	alm_bff.Format("Object Name : %s\n",obj_name);
	alm_msg += alm_bff;

	alm_bff.Format("Variable Name : %s\n",var_name);
	alm_msg += alm_bff;

	MessageBox(NULL, alm_msg, "CCommon_Error__DEF_VARIABLE::Call__ERROR__GET_CHANNEL_TYPE_CTRL()", MB_OK|MB_TOPMOST|MB_ICONERROR);
	return 1;
}
