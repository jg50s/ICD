#include "StdAfx.h"
#include "CObj_Fnc__DUAL_ARM_STD.h"


// ...
int  CObj_Fnc__DUAL_ARM_STD
::Call__SCH_DB_CHECK(CII_OBJECT__VARIABLE *p_variable)
{
	CString str_msg;
	CString str_bff;

	str_msg = "SCH_DB Check ... \n";

	// Arm_A
	{
		CString arm_type = "A";

		IDS__SCH_MATERIAL_STATUS ds_info;
		int flag = xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_info);

		str_bff.Format("Arm_Type : [%s] \n", arm_type);
		str_msg += str_bff;

		str_bff.Format(" * flag [%1d] \n", flag);
		str_msg += str_bff;

		str_bff.Format(" * Position [%s] \n", ds_info.sMATERIAL_POS);
		str_msg += str_bff;

		str_bff.Format(" * Status   [%s] \n", ds_info.sMATERIAL_STS);
		str_msg += str_bff;
	}
	// Arm_B
	{
		CString arm_type = "B";

		IDS__SCH_MATERIAL_STATUS ds_info;
		int flag = xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_info);

		str_bff.Format("Arm_Type : [%s] \n", arm_type);
		str_msg += str_bff;

		str_bff.Format(" * flag [%1d] \n", flag);
		str_msg += str_bff;

		str_bff.Format(" * Position [%s] \n", ds_info.sMATERIAL_POS);
		str_msg += str_bff;

		str_bff.Format(" * Status   [%s] \n", ds_info.sMATERIAL_STS);
		str_msg += str_bff;
	}

	MessageBox(NULL, str_msg, sObject_Name, MB_OK);

	xSCH_MATERIAL_CTRL->Check__STS_DB();
	xSCH_MATERIAL_CTRL->Check__RCP_DB();
	return 1;
}

