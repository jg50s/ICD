#include "StdAfx.h"
#include "CObj_NET__VAC_PERSIMMON.h"
#include "CObj_NET__VAC_PERSIMMON__DEF.h"
#include "CObj_NET__VAC_PERSIMMON__ALID.h"



//-------------------------------------------------------------------------	
int  CObj_NET__VAC_PERSIMMON
::Call__GOUP(CII_OBJECT__VARIABLE* p_variable,
			 CII_OBJECT__ALARM* p_alarm,
			 const CString& act_cmmd,
			 const CString& stn_name, 
			 const CString& arm_type,
			 const CString& stn_slot)
{

	return Fnc_ERROR(p_alarm, act_cmmd,stn_name,arm_type);
}
int  CObj_NET__VAC_PERSIMMON
::Call__GODOWN(CII_OBJECT__VARIABLE* p_variable,
			   CII_OBJECT__ALARM* p_alarm,
			   const CString& act_cmmd,
			   const CString& stn_name, 
			   const CString& arm_type,
			   const CString& stn_slot)
{

	return Fnc_ERROR(p_alarm, act_cmmd,stn_name,arm_type);
}

int  CObj_NET__VAC_PERSIMMON
::Call__RQ_STN(CII_OBJECT__VARIABLE* p_variable,
			   CII_OBJECT__ALARM* p_alarm,
			   const CString& act_cmmd,
			   const CString& stn_name, 
			   const CString& arm_type)
{

	return Fnc_ERROR(p_alarm, act_cmmd,stn_name,arm_type);
}
int  CObj_NET__VAC_PERSIMMON
::Call__SET_STN(CII_OBJECT__VARIABLE* p_variable,
				CII_OBJECT__ALARM* p_alarm,
				const CString& act_cmmd,
				const CString& stn_name, 
				const CString& arm_type)
{

	return Fnc_ERROR(p_alarm, act_cmmd,stn_name,arm_type);
}

int  CObj_NET__VAC_PERSIMMON
::Call__TEACHED_CPTR_SAVE(CII_OBJECT__VARIABLE* p_variable,
						  CII_OBJECT__ALARM* p_alarm,
						  const CString& act_cmmd,
						  const CString& stn_name, 
						  const CString& arm_type)
{

	return Fnc_ERROR(p_alarm, act_cmmd,stn_name,arm_type);
}

// ...
int  CObj_NET__VAC_PERSIMMON
::Fnc_ERROR(CII_OBJECT__ALARM* p_alarm,
		    const CString& act_cmmd,
		    const CString& stn_name, 
		    const CString& arm_type)
{
	int alm_id = ALID__FUNCTION_NOT_EXIST;
	CString alm_msg;
	CString alm_bff;
	CString r_act;

	alm_msg.Format(" * command  : [%s] \n", act_cmmd);	
	alm_bff.Format(" * arm_tyoe : [%s] \n", arm_type);
	alm_msg += alm_bff;
	alm_bff.Format(" * stn_name : [%s] \n", stn_name);
	alm_msg += alm_bff;

	p_alarm->Popup__ALARM_With_MESSAGE(alm_id, alm_msg, r_act);
	return -1;
}
