#include "StdAfx.h"
#include "CObj__PMC_RMM.h"

#include "CMacro_FA.h"
extern CMacro_FA mFA_Link;


// ...
void CObj__PMC_RMM::
Mon__PARAMETER_RAMGE_CHANGE(CII_OBJECT__VARIABLE* p_variable)
{
	CI_FA_DB__PPBODY_CTRL* p_ppbody_ctrl = mFA_Link.Get_PPBODY_CTRL();

	// ...
	int pm_id = iPM_ID;
	int stage_id = -1;

	CString item_name;
	double min_value;
	double max_value;

	CString var_data;
	int i;

	// ...
	CString pre__mfc_flow_min[CFG__MFC_SIZE];
	CString pre__mfc_flow_max[CFG__MFC_SIZE];

	CString pre__rf_freq_min[CFG__RFx_SIZE];
	CString pre__rf_freq_max[CFG__RFx_SIZE];

	CString pre__esc_bias_volt_max;


	while(1)
	{
		MONITORING_TIMER_RETURN(500);

		// ...
		int check_flag;

		// MFC ...
		for(i=0; i<CFG__MFC_SIZE; i++)
		{
			check_flag = -1;

			if(sCH__MFCx_FLOW_MIN[i]->Check__DATA(pre__mfc_flow_min[i]) < 0)
			{
				sCH__MFCx_FLOW_MIN[i]->Get__DATA(pre__mfc_flow_min[i]);
				min_value = atof(pre__mfc_flow_min[i]);

				check_flag = 1;
			}
			if(sCH__MFCx_FLOW_MAX[i]->Check__DATA(pre__mfc_flow_max[i]) < 0)
			{
				sCH__MFCx_FLOW_MAX[i]->Get__DATA(pre__mfc_flow_max[i]);
				max_value = atof(pre__mfc_flow_max[i]);

				check_flag = 1;
			}

			if(check_flag < 0)
			{
				continue;
			}

			item_name = sPPNAME__MFCx_FLOW[i];
			p_ppbody_ctrl->Set__STEP_ITEM_RANGE_OF_PMx(pm_id,stage_id, item_name,min_value,max_value);
		}

		// RFx ...
		for(i=0; i<CFG__RFx_SIZE; i++)
		{
			check_flag = -1;

			if(sCH__RFx_FREQ_MIN[i]->Check__DATA(pre__rf_freq_min[i]) < 0)
			{
				sCH__RFx_FREQ_MIN[i]->Get__DATA(pre__rf_freq_min[i]);
				min_value = atof(pre__rf_freq_min[i]);

				check_flag = 1;
			}
			if(sCH__RFx_FREQ_MAX[i]->Check__DATA(pre__rf_freq_max[i]) < 0)
			{
				sCH__RFx_FREQ_MAX[i]->Get__DATA(pre__rf_freq_max[i]);
				max_value = atof(pre__rf_freq_max[i]);

				check_flag = 1;
			}

			if(check_flag < 0)
			{
				continue;
			}

			// ...
			{
				item_name = sPPNAME__RFx_FREQ_PRESET[i];
				p_ppbody_ctrl->Set__STEP_ITEM_RANGE_OF_PMx(pm_id,stage_id, item_name,min_value,max_value);

				item_name = sPPNAME__RFx_FREQ_OUTPUT[i];
				p_ppbody_ctrl->Set__STEP_ITEM_RANGE_OF_PMx(pm_id,stage_id, item_name,min_value,max_value);

				item_name = sPPNAME__RFx_FREQ_LEARNED[i];
				p_ppbody_ctrl->Set__STEP_ITEM_RANGE_OF_PMx(pm_id,stage_id, item_name,min_value,max_value);
			}
		}

		// ESC Bias Voltage ...	
		{
			if(sCH__ESC_BIAS_VOLTAGE_MAX->Check__DATA(pre__esc_bias_volt_max) < 0)
			{
				sCH__ESC_BIAS_VOLTAGE_MAX->Get__DATA(pre__esc_bias_volt_max);

				min_value = 0.0;
				max_value = atof(pre__esc_bias_volt_max);

				item_name = sPPNAME__ESC_BIAS_VOLTAGE_MAX;
				p_ppbody_ctrl->Set__STEP_ITEM_RANGE_OF_PMx(pm_id,stage_id, item_name,min_value,max_value);
			}			
		}

		// ...
	}
}
