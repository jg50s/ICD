#include "StdAfx.h"
#include "CObj__PMC_RMM.h"

#include "CMacro_FA.h"
extern CMacro_FA mFA_Link;


// ...
int  CObj__PMC_RMM::
Call__CFG_ITEM_RANGE_CHECK(CII_OBJECT__VARIABLE *p_variable,
						   CII_OBJECT__ALARM *p_alarm)
{
	CI_FA_DB__PPBODY_CTRL* p_ppbody_ctrl = mFA_Link.Get_PPBODY_CTRL();

	// ...
	{
		CString item_name;
		CString min_data;
		CString max_data;
		int flag;

		CString log_msg;
		CString log_bff;

		sCH__PARA_ITEM_NAME->Get__DATA(item_name);
		flag = p_ppbody_ctrl->Get__CFG_ITEM_RANGE_OF_PMx(iPM_ID,-1, item_name,min_data,max_data);

		log_msg = "Call__CFG_ITEM_RANGE_CHECK() \n\n";
		log_bff.Format("Flag : %1d \n", flag);
		log_msg += log_bff;
		log_bff.Format("item_name  : %s \n", item_name);
		log_msg += log_bff;
		log_bff.Format("  min_data : %s \n", min_data);
		log_msg += log_bff;
		log_bff.Format("  max_data : %s \n", max_data);
		log_msg += log_bff;

		MessageBox(NULL,log_msg,sObject_Name,MB_OK|MB_TOPMOST);
	}
	return 1;
}
int  CObj__PMC_RMM::
Call__STEP_ITEM_RANGE_CHECK(CII_OBJECT__VARIABLE *p_variable,
							CII_OBJECT__ALARM *p_alarm)
{
	CI_FA_DB__PPBODY_CTRL* p_ppbody_ctrl = mFA_Link.Get_PPBODY_CTRL();

	// ...
	{
		CString item_name;
		CString min_data;
		CString max_data;
		int flag;

		CString log_msg;
		CString log_bff;

		sCH__PARA_ITEM_NAME->Get__DATA(item_name);
		flag = p_ppbody_ctrl->Get__STEP_ITEM_RANGE_OF_PMx(iPM_ID,-1, item_name,min_data,max_data);

		log_msg = "Call__STEP_ITEM_RANGE_CHECK() \n\n";
		log_bff.Format("Flag : %1d \n", flag);
		log_msg += log_bff;
		log_bff.Format("item_name  : %s \n", item_name);
		log_msg += log_bff;
		log_bff.Format("  min_data : %s \n", min_data);
		log_msg += log_bff;
		log_bff.Format("  max_data : %s \n", max_data);
		log_msg += log_bff;

		MessageBox(NULL,log_msg,sObject_Name,MB_OK|MB_TOPMOST);
	}
	return 1;
}

