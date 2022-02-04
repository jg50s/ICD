#include "StdAfx.h"
#include "CObj__STEP_FNC.h"
#include "CObj__STEP_FNC__DEF.h"


// ...
void CObj__STEP_FNC
::_Fnc_Mon__RCP_Matcher_Top__Ctrl_Req(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString log_msg;
	CString log_bff;

	CString str__hf_ctrl_mode;
	CString str__hf_matcher_c1;
	CString str__hf_matcher_c2;
	
	// ...
	{
		log_msg = "_Fnc_Mon__RCP_Matcher_Top__Ctrl_Req() : Started ... \n";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}


	while(1)
	{
		WaitForSingleObject(hEVENT__RCP_MATCHER_CTRL, INFINITE);	
		ResetEvent(hEVENT__RCP_MATCHER_CTRL);


		if(sCH__RCP_MATCHER_TOP__CTRL_REQ->Check__DATA(STR__YES) < 0)
		{
			continue;
		}
		sCH__RCP_MATCHER_TOP__CTRL_REQ->Set__DATA("");

		// MATCHER_TOP : PLASMA ...
		if(bActive__OBJ_CTRL__MAT_TOP)
		{
			dCH__RCP_PLASMA_CTRL_MODE->Get__DATA(str__hf_ctrl_mode);
			aCH__RCP_PLASMA_MATCHER_C1_OUTPUT->Get__DATA(str__hf_matcher_c1);
			aCH__RCP_PLASMA_MATCHER_C2_OUTPUT->Get__DATA(str__hf_matcher_c2);

			if(str__hf_ctrl_mode.CompareNoCase("AUTO") == 0)		dEXT_CH__MAT_TOP__PLASMA_MODE_SET->Set__DATA("AUTO_PRESET");
			else													dEXT_CH__MAT_TOP__PLASMA_MODE_SET->Set__DATA("MANUAL");

			aEXT_CH__MAT_TOP__PLASMA_LOAD_POS->Set__DATA(str__hf_matcher_c1);
			aEXT_CH__MAT_TOP__PLASMA_TUNE_POS->Set__DATA(str__hf_matcher_c2);
		}

		// ...
		{
			sCH__OBJ_SUB_MSG->Set__DATA("Matcher (HF & LF) Control Started ...");

			// ...
			{
				log_msg  = "\n";
				log_msg += "Matcher (HF & LF) Start \n";

				// ...
				{
					log_msg += "1. HF  ... \n"; 

					log_bff.Format("   1)  Ctrl_Mode : %s \n", str__hf_ctrl_mode);
					log_msg += log_bff;

					log_bff.Format("   2)  C1 : %s \n", str__hf_matcher_c1);
					log_msg += log_bff;

					log_bff.Format("   3)  C2 : %s \n", str__hf_matcher_c2);
					log_msg += log_bff;
				}

				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			pOBJ_CTRL__MAT_TOP->Call__OBJECT("PROC_START");
		}

		// ...
	}
}

