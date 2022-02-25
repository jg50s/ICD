#include "StdAfx.h"
#include "CObj_Fnc__SINGLE_ARM_STD.h"


// ...
int  CObj_Fnc__SINGLE_ARM_STD
::Call__SCH_DB_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString str_msg;
	CString str_bff;

	str_msg = "SCH_DB Check ... \n";

	str_bff.Format("ATM_RB__Is_Available() : %1d \n", ATM_RB__Is_Available());
	str_msg += str_bff;

	str_bff.Format("xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE()     : %1d \n", xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE());
	str_msg += str_bff;

	str_bff.Format("xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE()   : %1d \n", xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE());
	str_msg += str_bff;

	str_bff.Format("xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) : %1d \n", xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES));
	str_msg += str_bff;

	MessageBox(NULL, str_msg, sObject_Name, MB_OK);
	return 1;
}

