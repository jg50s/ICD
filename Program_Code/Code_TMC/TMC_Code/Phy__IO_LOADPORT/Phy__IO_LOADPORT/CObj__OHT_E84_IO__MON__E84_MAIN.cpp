#include "StdAfx.h"
#include "CObj__OHT_E84_IO.h"
#include "CObj__OHT_E84_IO__DEF.h"


//------------------------------------------------------------------------------------
void CObj__OHT_E84_IO::
Mon__IO_E84_MAIN(CII_OBJECT__VARIABLE* p_variable,
				 CII_OBJECT__ALARM* p_alarm)
{
	CString get_str_obj_mode;
	CString get_str_obj_sts;

	int n_ret_cs_valid_wait;
	int n_call_ret;


	while (1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		// ÃÊ±âÈ­ ...
		{
			dCH__OTR_OUT_dLP_PIO_TRANSFER->Set__DATA(_NO);
			dCH__E84_RUN_SNS->Set__DATA(_STOP);

			dCH__PIO_RESET->Set__DATA(_OFF);
		}

		pPHY_IO_LPx__OBJ->Get__OBJ_MODE(get_str_obj_mode);
		int n_obj_sts = pPHY_IO_LPx__OBJ->Get__OBJECT_STATUS();

		if((get_str_obj_mode.CompareNoCase(STR_MODE_PREPLOAD) == 0) 
		|| (get_str_obj_mode.CompareNoCase(STR_MODE_UNLOAD)   == 0))
		{
			if(n_obj_sts != OBJECT_STATUS__RUN)
			{
				Set__HOAVBL(_OFF);
				continue;
			}
		}
		else
		{
			Set__HOAVBL(_OFF);
			continue;
		}

		Sleep(100);

		if(Is__LP_AUTO_MODE() > 0)
		{
			Set__AllOff_Except_ES();
			Set__HOAVBL(_ON);

			// 3. CS0, VALID [ON] Waiting....
			Fnc__E84_LOG("Full Auto... CS and VALID [ON] Waiting... !!");
			n_ret_cs_valid_wait = Fnc__CS_VALID_WAITING(p_variable, p_alarm, get_str_obj_mode);

			if(n_ret_cs_valid_wait == OBJ_AVAILABLE)
			{
				// PIO Start !!
			}
			else if(n_ret_cs_valid_wait == SEQ_COMPLETE)
			{
				dCH__E84_RUN_SNS->Set__DATA(_DONE);
				_sleep(1000);
				continue;
			}
			else
			{
				continue;
			}

			if(get_str_obj_mode.CompareNoCase(STR_MODE_PREPLOAD) == 0)
			{
				sCH__CUR_CHECK_TPx->Set__DATA("__");
				n_call_ret = Fnc__LOAD(p_variable, p_alarm);
				sCH__CUR_CHECK_TPx->Set__DATA("");

				_sleep(1000);
			}
			else
			{
				sCH__CUR_CHECK_TPx->Set__DATA("__");
				n_call_ret = Fnc__UNLOAD(p_variable, p_alarm);
				sCH__CUR_CHECK_TPx->Set__DATA("");

				_sleep(1000);
			}

			if(n_call_ret == SEQ_COMPLETE)
			{
				dCH__E84_RUN_SNS->Set__DATA(_DONE); 
				_sleep(1000);
			}

			Set__AllOff_Except_ES();
		}
		else
		{
			Set__HOAVBL("OFF");
			Set__AllOff_Except_ES();
		}

		Sleep(100);
	}
}

