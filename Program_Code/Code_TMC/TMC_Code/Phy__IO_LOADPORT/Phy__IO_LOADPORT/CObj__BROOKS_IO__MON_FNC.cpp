#include "StdAfx.h"
#include "CObj__BROOKS_IO.h"
#include "CObj__BROOKS_IO__DEF.h"


//------------------------------------------------------------------------------------
void CObj__BROOKS_IO::
Mon__PIO_TRANSFER_MONITOR(CII_OBJECT__VARIABLE* p_variable,
						  CII_OBJECT__ALARM* p_alarm)
{
	CString var_data;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.5);


		if(bActive__LINK_PIO)
		{
			var_data = dEXT_CH__LPx_PIO__TRANSFER_SNS->Get__STRING();
			dCH__OTR_OUT_dLP_PIO_TRANSFER->Set__DATA(var_data);

			var_data = sCH__MON_ACTIVE_FA_AUTO->Get__STRING();
			sEXT_CH__LPx_PIO__MON_ACTIVE_FA_AUTO->Set__DATA(var_data);
		}
	}
}


//------------------------------------------------------------------------------------
void CObj__BROOKS_IO::
Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,
				CII_OBJECT__ALARM* p_alarm)
{
	CString var_data;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.5);


		if(iSIM_FLAG > 0)
		{
			if(sCH__COMM_STS->Check__DATA("ONLINE") < 0)
			{
				sCH__COMM_STS->Set__DATA("ONLINE");
			}
		}
		else
		{
			if(diEXT_CH__LPx__COMM_STS->Check__DATA("OFFLINE") > 0)
			{
				sCH__COMM_STS->Set__DATA("OFFLINE");

				// ...
				{
					CString r_act;
					int alarm_id = ALID__OFFLINE_ALARM;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);
				}
			}
			else
			{
				sCH__COMM_STS->Set__DATA("ONLINE");
			}
		}

		if(sCH__MON_ACTIVE_FA_AUTO->Check__DATA(STR__YES) > 0)
		{
			sCH__MON_ACTIVE_FA_AUTO->Set__DATA(STR__YES);

			Seq_LAMP(LAMP_AUTO, "ON", "AUTO_LAMP", "Mon__IO_MONITOR");
		}
		else
		{
			sCH__MON_ACTIVE_FA_AUTO->Set__DATA(STR__NO);

			Seq_LAMP(LAMP_AUTO, "OFF", "AUTO_LAMP", "Mon__IO_MONITOR");
		}
	}
}

//------------------------------------------------------------------------------------
void CObj__BROOKS_IO::
Mon__IO_CH_OUT_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	SCX__TIMER_CTRL cx_timer_ctrl;
	CString var_data;

	Sleep(1000);


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		// CLAMP STATE ...
		{
			if((diEXT_CH__LPx__UNCLAMP->Check__DATA("OFF")  > 0)
			&& (diEXT_CH__LPx__CLAMP->Check__DATA("ON")     > 0))
			{
				dCH__OTR_OUT_MON_dLP_CLAMP_STS->Set__DATA("CLAMP");

				dCH__LP__UNCLAMP_STS->Set__DATA("OFF");
				dCH__LP__CLAMP_STS->Set__DATA("ON");
			}
			else if((diEXT_CH__LPx__UNCLAMP->Check__DATA("ON")  > 0)
				 && (diEXT_CH__LPx__CLAMP->Check__DATA("OFF")   > 0))
			{
				dCH__OTR_OUT_MON_dLP_CLAMP_STS->Set__DATA("UNCLAMP");

				dCH__LP__CLAMP_STS->Set__DATA("OFF");
				dCH__LP__UNCLAMP_STS->Set__DATA("ON");
			}
			else
			{
				dCH__OTR_OUT_MON_dLP_CLAMP_STS->Set__DATA("UNKNOWN");

				dCH__LP__CLAMP_STS->Set__DATA("ON");
				dCH__LP__UNCLAMP_STS->Set__DATA("ON");
			}
		}

		// FOUP STATE ...
		{
			if( (diEXT_CH__LPx__FOUP_PRESENT->Check__DATA("ON") > 0) 
			&& 	(diEXT_CH__LPx__FOUP_PLACED->Check__DATA("ON")  > 0) )
			{
				dCH__OTR_OUT_MON_dLP_CST_STS->Set__DATA("EXIST");
			}
			else if( (diEXT_CH__LPx__FOUP_PRESENT->Check__DATA("OFF") > 0) 
			     &&  (diEXT_CH__LPx__FOUP_PLACED->Check__DATA("OFF")  > 0) )
			{	
				dCH__OTR_OUT_MON_dLP_CST_STS->Set__DATA("NONE");
			}
			else
			{
				dCH__OTR_OUT_MON_dLP_CST_STS->Set__DATA("UNKNOWN");
			}
		}

		// DOOR STATE ...
		{
			if( (diEXT_CH__LPx__DOOR_RET->Check__DATA("ON") > 0) 
			&& 	(diEXT_CH__LPx__DOOR_UP->Check__DATA("ON")  > 0) )
			{
				dCH__OTR_OUT_MON_dLP_DOOR_STS->Set__DATA("CLOSE");
			}
			else if( (diEXT_CH__LPx__DOOR_EXT->Check__DATA("ON") > 0) 
				 &&  (diEXT_CH__LPx__DOOR_DN->Check__DATA("ON")  > 0) )
			{
				dCH__OTR_OUT_MON_dLP_DOOR_STS->Set__DATA("OPEN");
			}
			else
			{
				dCH__OTR_OUT_MON_dLP_DOOR_STS->Set__DATA("UNKNOWN");
			}
		}

		// SHUTTLE STATE ...
		{
			if( (diEXT_CH__LPx__SHUTTLE_IN->Check__DATA("ON")   > 0) 
			&&  (diEXT_CH__LPx__SHUTTLE_OUT->Check__DATA("OFF") > 0) )
			{
				dCH__OTR_OUT_MON_dLP_SHUTL_STS->Set__DATA("LOAD");
			}
			else if( (diEXT_CH__LPx__SHUTTLE_IN->Check__DATA("OFF") > 0) 
				 &&  (diEXT_CH__LPx__SHUTTLE_OUT->Check__DATA("ON") > 0) )
			{
				dCH__OTR_OUT_MON_dLP_SHUTL_STS->Set__DATA("UNLOAD");
			}
			else
			{
				dCH__OTR_OUT_MON_dLP_SHUTL_STS->Set__DATA("UNKNOWN");
			}
		}

		 // ...
	}
}

void CObj__BROOKS_IO::
Mon__IO_CST_EXIST_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	SCX__TIMER_CTRL cx_timer_ctrl;
	CString var_data;
	double nCnt = 0;
	double nTarget_Cnt;

	Sleep(1000);

	aCFG_CST_PROPERLY_EXIST_TIME->Get__DATA(var_data);
	nTarget_Cnt = atof(var_data)*0.01;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		if( (diEXT_CH__LPx__FOUP_PRESENT->Check__DATA("ON") > 0) 
		&& 	(diEXT_CH__LPx__FOUP_PLACED->Check__DATA("ON")  > 0) )
		{
			nCnt++;

			if(nTarget_Cnt <= nCnt)
			{
				dCH__OTR_OUT_MON_dLP_CST_STS->Set__DATA("EXIST");
				nCnt = 0;
			}
			else
			{
				continue;			
			}
		}
		else if( (diEXT_CH__LPx__FOUP_PRESENT->Check__DATA("OFF") > 0) 
			 &&  (diEXT_CH__LPx__FOUP_PLACED->Check__DATA("OFF")  > 0) )
		{
			dCH__OTR_OUT_MON_dLP_CST_STS->Set__DATA("NONE");
			nCnt = 0;
		}
		else
		{
			dCH__OTR_OUT_MON_dLP_CST_STS->Set__DATA("UNKNOWN");
			nCnt = 0;
		}
	}
}

int CObj__BROOKS_IO::
Fnc__LD_buttonMon(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString    szData_bak			= "~";
	CString    szNotPressedData_bak	= "~";
	CString    szLDBT;
	CString    szclamp_sts;
	CString    szExist;
	CString	   szDoor;
	CString    fnc_name = "Fnc__LD_buttonMon";
	CString    szCfg_Data;
	int        nCnt = 0;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		diEXT_CH__LPx__LOAD_BTN->Get__DATA(szLDBT);
		aCFG_ACCESS_SW_TIMEOUT->Get__DATA(szCfg_Data);		// 3 sec..

		if(szLDBT.CompareNoCase("ON") == 0)
		{
			if(atoi(szCfg_Data) > nCnt)
			{
				_sleep(900);
				nCnt++;
				continue;
			}
			nCnt = 0;

			if(strcmp(szData_bak, szLDBT) != 0)
			{
				Fnc__APP_LOG("--------> Load Button [UNLOAD LAMP OFF, LOAD LAMP ON] Started !! ---------->");

				Seq_LAMP(LAMP_UNLOAD, "OFF", "UNLOAD_LAMP", fnc_name);
				Seq_LAMP(LAMP_LOAD,   "ON",  "LOAD_LAMP",   fnc_name);

				Fnc__APP_LOG("<-------- Load Button [UNLOAD LAMP OFF, LOAD LAMP ON] Completed !! <-------\n");

				if(Is__LP_AUTO_MODE() < 0)		// manual
				{
					dCH__OTR_OUT_MON_dLP_CLAMP_STS->Get__DATA(szclamp_sts);
					dCH__OTR_OUT_MON_dLP_CST_STS->Get__DATA(szExist);
					dCH__OTR_OUT_MON_dLP_DOOR_STS->Get__DATA(szDoor);

					if(dCH__CFG_LOAD_CLAMP_OPT->Check__DATA(STR__BUTTON) > 0)
					{
						if((szclamp_sts.CompareNoCase("UNCLAMP") == 0)
						&& (szExist.CompareNoCase("EXIST")       == 0))
						{
							Fnc__APP_LOG("--------> Load Button [CLAMP] Started !! ---------->");

							Fnc__CLAMP(p_variable, p_alarm, fnc_name);

							Fnc__APP_LOG("<-------- Load Button Completed !! <-------");

						}
					}
				}

				szData_bak = szLDBT;
				szNotPressedData_bak = "~";
			}
		}
		else
		{
			nCnt = 0;

			if(strcmp(szNotPressedData_bak, szLDBT) != 0)
			{
				if(Is__LP_AUTO_MODE() < 0)		// manual
				{
					if(dCH__OTR_OUT_MON_dLP_CST_STS->Check__DATA("EXIST") > 0)
					{
						if(dCH__CFG_LOAD_CLAMP_OPT->Check__DATA(STR__BUTTON) > 0)
						{
							Seq_LAMP(LAMP_LOAD,   "ON",  "LOAD_LAMP",   "Fnc__LD_buttonMon()");

							Sleep(500);

							Seq_LAMP(LAMP_LOAD,   "OFF", "LOAD_LAMP",   "Fnc__LD_buttonMon()");
						}
					}
				}
			}

			szData_bak = "~";
		}

		// ...
	}

	return 1;
}

int CObj__BROOKS_IO::
Fnc__UNLD_buttonMon(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString    szData_bak			= "~";
	CString    szNotPressedData_bak	= "~";
	CString    szLDBT;
	CString    szclamp_sts;
	CString    szExist;
	CString	   szDoor;
	CString    fnc_name = "Fnc__UNLD_buttonMon";
	CString    szCfg_Data;
	int        nCnt = 0;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		diEXT_CH__LPx__UNLOAD_BTN->Get__DATA(szLDBT);
		aCFG_ACCESS_SW_TIMEOUT->Get__DATA(szCfg_Data);		// 3 sec..

		if(szLDBT.CompareNoCase("ON") == 0)
		{
			if(atoi(szCfg_Data) > nCnt)
			{
				_sleep(900);
				nCnt++;
				continue;
			}
			nCnt = 0;

			if(strcmp(szData_bak, szLDBT) != 0)
			{
				Fnc__APP_LOG("--------> Unload Button [UNLOAD LAMP ON, LOAD LAMP OFF] Started !! ---------->");

				Seq_LAMP(LAMP_LOAD,   "OFF",  "LOAD_LAMP", fnc_name);
				Seq_LAMP(LAMP_UNLOAD, "ON", "UNLOAD_LAMP", fnc_name);

				Fnc__APP_LOG("<-------- Unload Button [UNLOAD LAMP ON, LOAD LAMP OFF] Completed !! <-------\n");

				if(Is__LP_AUTO_MODE() < 0)		// manual
				{
					dCH__OTR_OUT_MON_dLP_CLAMP_STS->Get__DATA(szclamp_sts);
					dCH__OTR_OUT_MON_dLP_CST_STS->Get__DATA(szExist);
					dCH__OTR_OUT_MON_dLP_DOOR_STS->Get__DATA(szDoor);

					if(dCH__CFG_UNLD_CLAMP_OPT->Check__DATA(STR__BUTTON) > 0)
					{
						if((szclamp_sts.CompareNoCase("CLAMP") == 0) 
						&& (szDoor.CompareNoCase("CLOSE")      == 0) 
						&& (szExist.CompareNoCase("EXIST")     == 0))  
						{
							Fnc__APP_LOG("--------> Unload Button [UNCLAMP] Started !! ---------->");

							Fnc__UNCLAMP(p_variable, p_alarm, fnc_name);

							Fnc__APP_LOG("<-------- Unload Button Completed !! <-------");
						}
					}
				}

				szData_bak = szLDBT;
				szNotPressedData_bak = "~";
			}
		}
		else
		{
			nCnt = 0;

			if(strcmp(szNotPressedData_bak, szLDBT) != 0)
			{
				if(Is__LP_AUTO_MODE() < 0)		// manual
				{
					if(dCH__OTR_OUT_MON_dLP_CST_STS->Check__DATA("EXIST") > 0)
					{
						if(dCH__CFG_UNLD_CLAMP_OPT->Check__DATA(STR__BUTTON) > 0)
						{
							Seq_LAMP(LAMP_UNLOAD,   "ON",  "UNLOAD_LAMP",   "Fnc__UNLD_buttonMon()");
							
							Sleep(500);
							
							Seq_LAMP(LAMP_UNLOAD,   "OFF", "UNLOAD_LAMP",   "Fnc__UNLD_buttonMon()");
						}
					}
				}
			}

			szData_bak = "~";
		}

		// ...
	}

	return 1;
}
