#include "StdAfx.h"
#include "CObj__CHM_FNC.h"
#include "CObj__CHM_FNC__DEF.h"
#include "CObj__CHM_FNC__ALID.h"


// ...
void CObj__CHM_FNC::
Mon__PRESSURE_STATUS(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	double  cur_chm_press;
	double  ref_atm_press;
	double  ref_vac_press;
	CString pre_slit_vlv_sts;

	CString var_data;

	if(iActive__SIM_MODE > 0)
	{
		if(bActive__CHM_LID_STATE)
		{
			dEXT_CH__CHM_LID_STATE->Set__DATA(sCHM_LID__CLOSE_STATE);
		}
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);	


		if(bActive__VAT_OBJ)
		{
			int active_pumping = -1;

			double cur_pos = aEXT_CH__VAT_CUR_POSITION->Get__VALUE();

			if(cur_pos >= 50)
			{
				active_pumping = 1;
			}
			if(bActive__PHY_VAC_VLV)
			{
				if(sEXT_CH__VAC_VLV__MON_PUMPING_STATE->Check__DATA(STR__PUMPING) > 0)
				{
					active_pumping = 1;
				}
			}

			if(active_pumping > 0)		sCH__MON_PUMPING_STATE->Set__DATA(STR__PUMPING);
			else						sCH__MON_PUMPING_STATE->Set__DATA(STR__IDLE);
		}

		// ...
		{
			ref_atm_press = aCH__CFG_ATM_REF_PRESSURE->Get__VALUE();
			ref_vac_press = aCH__CFG_VAC_REF_PRESSURE->Get__VALUE();

			cur_chm_press = aEXT_CH__CHM_PRESSURE_TORR->Get__VALUE();

				 if(cur_chm_press >= ref_atm_press)			sEXT_CH__CHM_PRESSURE_STATE->Set__DATA(STR__ATM);
			else if(cur_chm_press <= ref_vac_press)			sEXT_CH__CHM_PRESSURE_STATE->Set__DATA(STR__VAC);
			else											sEXT_CH__CHM_PRESSURE_STATE->Set__DATA(STR__BTW);
		}
	}
}

