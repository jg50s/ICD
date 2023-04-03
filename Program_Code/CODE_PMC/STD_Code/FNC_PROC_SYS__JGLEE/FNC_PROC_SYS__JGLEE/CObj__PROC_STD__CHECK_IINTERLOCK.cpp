#include "StdAfx.h"
#include "CObj__PROC_STD.h"
#include "CObj__PROC_STD__DEF.h"


// ...
int CObj__PROC_STD
::_Check__DI_INTERLOCK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	bool active__di_err = false;

	CString err_msg;
	CString err_bff;
	
	if(dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_GAS_BOX->Check__DATA(STR__ON) > 0)
	{
		active__di_err = true;
		
		err_bff.Format("Gas_Box's heavy message is \"%s\" \n",
						sEXT_CH__MON_INTERLOCK_HEAVY_MSG_GAS_BOX->Get__STRING());
		err_msg += err_bff;
	}
	if(dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_CHAMBER->Check__DATA(STR__ON) > 0)
	{
		active__di_err = true;

		err_bff.Format("Chamber's heavy message is \"%s\" \w",
						sEXT_CH__MON_INTERLOCK_HEAVY_MSG_CHAMBER->Get__STRING());
		err_msg += err_bff;
	}
	if(dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_RF_SYS->Check__DATA(STR__ON) > 0)
	{
		active__di_err = true;

		err_bff.Format("RF_System's heavy message is \"%s\" \n", 
						sEXT_CH__MON_INTERLOCK_HEAVY_MSG_RF_SYS->Get__STRING());
		err_msg += err_bff;
	}

	if(active__di_err)
	{
		int alm_id = ALID__DI_SENSOR__HEAVY_ERRPR;
		CString r_act;

		p_alarm->Check__ALARM(alm_id, r_act);
		p_alarm->Post__ALARM_With_MESSAGE(alm_id, err_msg);
		return -1;
	}

	return 1;
}
