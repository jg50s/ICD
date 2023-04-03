#include "StdAfx.h"
#include "CObj__CHM_FNC.h"
#include "CObj__CHM_FNC__DEF.h"
#include "CObj__CHM_FNC__ALID.h"

#include "Macro_Function.h"


// ...
int CObj__CHM_FNC::VAT__CALL_OBJECT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm, const CString& obj_mode)
{
	if(bActive__VAT_OBJ)
	{
		if(pOBJ_CTRL__VAT->Is__OBJ_BUSY() > 0)
		{
			pOBJ_CTRL__VAT->Abort__OBJECT();
		}

		int r_flag = pOBJ_CTRL__VAT->Call__OBJECT(obj_mode);
		if(r_flag < 0)
		{
			// Log ...
			{

			}
			return -1;
		}

		if(obj_mode.CompareNoCase(_APC_CMMD__CLOSE) == 0)
		{
			int count__apc_check = 0;
			
			while(1)
			{
				double cur_pos = aEXT_CH__VAT_CUR_POSITION->Get__VALUE();
				if(cur_pos < 0.1)		break;

				if(p_variable->Check__CTRL_ABORT() > 0)
				{
					return -11;
				}

				count__apc_check++;
				if(count__apc_check > 30)
				{
					int alm_id = ALID__APC_VALVE_CLOSE_TIMEOUT;
					CString alm_msg;
					CString alm_bff;
					CString r_act;

					alm_bff.Format(" * %s <- %.1f %% \n", 
									aEXT_CH__VAT_CUR_POSITION->Get__CHANNEL_NAME(),
									cur_pos);
					alm_msg += alm_bff;

					p_alarm->Check__ALARM(alm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
					return -21;
				}

				Sleep(90);
			}
		}
	}

	return 1;
}

int CObj__CHM_FNC::VAT__RUN_OBJECT(const CString& obj_mode)
{
	if(bActive__VAT_OBJ)
	{
		if(pOBJ_CTRL__VAT->Is__OBJ_BUSY() > 0)
		{
			pOBJ_CTRL__VAT->Abort__OBJECT();
		}

		return pOBJ_CTRL__VAT->Run__OBJECT(obj_mode);
	}

	return 1;
}
