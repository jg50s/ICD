#include "StdAfx.h"
#include "CObj_NET__VAC_PERSIMMON.h"
#include "CObj_NET__VAC_PERSIMMON__DEF.h"
#include "CObj_NET__VAC_PERSIMMON__ALID.h"

#include "math.h"
#include "CCommon_DEF.h"

#include "Macro_Function.h"


//------------------------------------------------------------------------------------
void CObj_NET__VAC_PERSIMMON
::Fnc__ACT_MSG(const CString& act_msg)
{
	sCH__ACT_MSG->Set__DATA(act_msg);
}

void CObj_NET__VAC_PERSIMMON
::Fnc__APP_LOG(const CString& log_msg)
{
	if(iFlag__APP_LOG < 1)		return;

	xAPP_LOG_CTRL->WRITE__LOG(log_msg);
}

void CObj_NET__VAC_PERSIMMON
::Fnc__DRV_LOG(const CString& log_msg)
{
	if(iFlag__DRV_LOG < 1)		return;

	xDRV_LOG_CTRL->WRITE__LOG(log_msg);
}


// ...
int CObj_NET__VAC_PERSIMMON
::_Update__WFR_CEN_DATA(CII_OBJECT__VARIABLE* p_variable)
{
	CString log_msg;
	CString log_bff;

	sCH__WFR_CEN_DATA__FULL_VAL->Set__DATA("");

	// ...
	{
		CString cmmd__arm_act = _Cmmd__Wfr_Cen_Data;
		_Call__ROBOT_ACTION(p_variable, cmmd__arm_act, "");	
	}

	// ...
	CString ch__wcd_data = sCH__WFR_CEN_DATA__FULL_VAL->Get__STRING();

	// ...
	{
		log_msg = "\n";
		log_bff.Format(" * WFR_CEN_DATA : Report ... \n");
		log_msg += log_bff;
		log_bff.Format(" * %s <- %s \n",
						sCH__WFR_CEN_DATA__FULL_VAL->Get__CHANNEL_NAME(),
						ch__wcd_data);
		log_msg += log_bff;

		Fnc__APP_LOG(log_msg);
	}

	// Data Initial ...
	{
		CString ch_data = "";

		sCH__WCD__RSns_LeadEdge_RadialValue->Set__DATA(ch_data);
		sCH__WCD__RSns_LeadEdge_ThetaValue->Set__DATA(ch_data);
		sCH__WCD__RSns_TrailEdge_RadialValue->Set__DATA(ch_data);
		sCH__WCD__RSns_TrailEdge_ThetaValue->Set__DATA(ch_data);

		sCH__WCD__LSns_LeadEdge_RadialValue->Set__DATA(ch_data);
		sCH__WCD__LSns_LeadEdge_ThetaValue->Set__DATA(ch_data);
		sCH__WCD__LSns_TrailEdge_RadialValue->Set__DATA(ch_data);
		sCH__WCD__LSns_TrailEdge_ThetaValue->Set__DATA(ch_data);

		sCH__WCD__CSns_Offset_RadialValue->Set__DATA(ch_data);
		sCH__WCD__CSns_Offset_ThetaValue->Set__DATA(ch_data);
		sCH__WCD__CSns_Offset_X_Value->Set__DATA(ch_data);
		sCH__WCD__CSns_Offset_Y_Value->Set__DATA(ch_data);
	}

	// ...
	{
		CString key_word = "DATA";
		CStringArray l_para;

		Check__MSG_KEY_WORD(ch__wcd_data,key_word, l_para);

		int i_limit = l_para.GetSize();
		int i;

		log_msg = "\n";

		for(i=0; i<i_limit; i++)
		{
			CString ch_data = l_para[i];

			log_bff.Format(" * %02d) [%s] \n", i+1,ch_data);
			log_msg += log_bff;

			// RT ...
				 if(i == 1)		sCH__WCD__RSns_LeadEdge_RadialValue->Set__DATA(ch_data);
			else if(i == 2)		sCH__WCD__RSns_LeadEdge_ThetaValue->Set__DATA(ch_data);
			else if(i == 3)		sCH__WCD__RSns_TrailEdge_RadialValue->Set__DATA(ch_data);
			else if(i == 4)		sCH__WCD__RSns_TrailEdge_ThetaValue->Set__DATA(ch_data);

			// LFT ...
			else if(i == 6)		sCH__WCD__LSns_LeadEdge_RadialValue->Set__DATA(ch_data);
			else if(i == 7)		sCH__WCD__LSns_LeadEdge_ThetaValue->Set__DATA(ch_data);
			else if(i == 8)		sCH__WCD__LSns_TrailEdge_RadialValue->Set__DATA(ch_data);
			else if(i == 9)		sCH__WCD__LSns_TrailEdge_ThetaValue->Set__DATA(ch_data);

			// CEN ...
			else if(i == 11)
			{
				double cur_deg = atof(ch_data) / 1000.0;
				
				ch_data.Format("%.3f", cur_deg);
				sCH__WCD__CSns_Offset_RadialValue->Set__DATA(ch_data);
			}
			else if(i == 12)
			{
				double cur_mm = atof(ch_data) / 1000.0;

				ch_data.Format("%.3f", cur_mm);
				sCH__WCD__CSns_Offset_ThetaValue->Set__DATA(ch_data);
			}
			else if(i == 13)
			{
				double cur_mm = atof(ch_data) / 1000.0;

				ch_data.Format("%.3f", cur_mm);
				sCH__WCD__CSns_Offset_X_Value->Set__DATA(ch_data);
			}
			else if(i == 14)
			{
				double cur_mm = atof(ch_data) / 1000.0;

				ch_data.Format("%.3f", cur_mm);
				sCH__WCD__CSns_Offset_Y_Value->Set__DATA(ch_data);
			}
		}

		if(iSim_Flag > 0)
		{
			CString ch__da_deg = "000247";
			CString ch__da_mm  = "-00025";
			CString ch_data;

			double cur_deg = atof(ch__da_deg) / 1000.0;
			double cur_mm = atof(ch__da_mm) / 1000.0;

			ch_data.Format("%.3f", cur_deg);
			sCH__WCD__CSns_Offset_RadialValue->Set__DATA(ch_data);

			ch_data.Format("%.3f", cur_mm);
			sCH__WCD__CSns_Offset_ThetaValue->Set__DATA(ch_data);
		}

		// ...
		{
			CString ch_data;

			ch_data = sCH__WCD__CSns_Offset_RadialValue->Get__STRING();
			sCH__DA_RESULT_R_OFFSET_DEG->Set__DATA(ch_data);

			ch_data = sCH__WCD__CSns_Offset_ThetaValue->Get__STRING();
			sCH__DA_RESULT_T_OFFSET_MM->Set__DATA(ch_data);
		}

		// Offset Result ...
		{
			log_msg += " * Offset Result ... \n";

			// R
			log_bff.Format(" ** %s <- [%s] \n", 
							sCH__WCD__CSns_Offset_RadialValue->Get__CHANNEL_NAME(),
							sCH__WCD__CSns_Offset_RadialValue->Get__STRING());						
			log_msg += log_bff;

			// T
			log_bff.Format(" ** %s <- [%s] \n", 
							sCH__WCD__CSns_Offset_ThetaValue->Get__CHANNEL_NAME(),
							sCH__WCD__CSns_Offset_ThetaValue->Get__STRING());
			log_msg += log_bff;

			// X
			log_bff.Format(" ** %s <- [%s] \n", 
							sCH__WCD__CSns_Offset_X_Value->Get__CHANNEL_NAME(),
							sCH__WCD__CSns_Offset_X_Value->Get__STRING());						
			log_msg += log_bff;

			// Y
			log_bff.Format(" ** %s <- [%s] \n", 
							sCH__WCD__CSns_Offset_Y_Value->Get__CHANNEL_NAME(),
							sCH__WCD__CSns_Offset_Y_Value->Get__STRING());
			log_msg += log_bff;
		}

		Fnc__APP_LOG(log_msg);
	}

	return 1;
}
