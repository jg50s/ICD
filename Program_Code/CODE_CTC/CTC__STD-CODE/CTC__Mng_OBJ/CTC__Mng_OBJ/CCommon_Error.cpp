#include "StdAfx.h"
#include "CCommon_Error.h"


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
