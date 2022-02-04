#include "StdAfx.h"
#include "CObj__AUTO_PM.h"


extern void Macro__Get_Date(CString& date, CString& time);


// ...
int CObj__AUTO_PM::
Call__AUTO_PM(CII_OBJECT__VARIABLE *p_variable,
			  CII_OBJECT__ALARM *p_alarm)
{
	CString date;
	CString time;
	CString var_data;
	int flag;

	// ...
	{
		sCH__AUTO_PM__START_TIME->Set__DATA("");
		sCH__AUTO_PM__END_TIME->Set__DATA("");
		sCH__AUTO_PM__RESULT->Set__DATA("");

		//
		sCH__LeakCheck__START_TIME->Set__DATA("");
		sCH__LeakCheck__END_TIME->Set__DATA("");
		sCH__LeakCheck__RESULT->Set__DATA("");

		//
		sCH__FRC_CHECK__START_TIME->Set__DATA("");
		sCH__FRC_CHECK__END_TIME->Set__DATA("");
		sCH__FRC_CHECK__RESULT->Set__DATA("");

		//
		sCH__MfcCheck__START_TIME->Set__DATA("");
		sCH__MfcCheck__END_TIME->Set__DATA("");
		sCH__MfcCheck__RESULT->Set__DATA("");

		//
		sCH__VatCheck__START_TIME->Set__DATA("");
		sCH__VatCheck__END_TIME->Set__DATA("");
		sCH__VatCheck__RESULT->Set__DATA("");
	}

	// ...
	{
		Macro__Get_Date(date, time);
		var_data.Format("%s %s", date,time);

		sCH__AUTO_PM__START_TIME->Set__DATA(var_data);
	}

	flag = Fnc__AUTO_PM(p_variable,p_alarm);

	// ...
	{
		Macro__Get_Date(date, time);
		var_data.Format("%s %s", date,time);

		sCH__AUTO_PM__END_TIME->Set__DATA(var_data);
	}

	if(flag > 0)
	{
		sCH__AUTO_PM__RESULT->Set__DATA("OK");
	}
	else
	{
		sCH__AUTO_PM__RESULT->Set__DATA("ERROR");
	}

	// ...
	{
		var_data = "High VAC Pumping Started ...";
		sCH__OBJ_MSG->Set__DATA(var_data);
				
		pOBJ_CTRL__CHM->Dislink__UPPER_OBJECT();
		pOBJ_CTRL__CHM->Call__OBJECT(CMMD_MODE__CHM_HIGH_VAC_PUMP);
		pOBJ_CTRL__CHM->Link__UPPER_OBJECT();
	}

	return flag;
}
int CObj__AUTO_PM::
Fnc__AUTO_PM(CII_OBJECT__VARIABLE *p_variable,
			 CII_OBJECT__ALARM *p_alarm)
{	
	CString date;
	CString time;

	CString var_data;
	CString log_msg;
	int fnc_flag;

	
	// CHM HIGH-VAC ...
	{
		log_msg = "High VAC Pumping Started ...";
		sCH__OBJ_MSG->Set__DATA(log_msg);

		//
		fnc_flag = pOBJ_CTRL__CHM->Call__OBJECT(CMMD_MODE__CHM_HIGH_VAC_PUMP);
		
		if(fnc_flag < 0)
		{
			return -11;
		}
	}

	// OBJ : Leak Check ...
	{
		// ...
		{
			dCH__LeakCheck__CFG_CHECK_FLAG->Get__DATA(var_data);
			sCH__LeakCheck__CUR_CHECK_FLAG->Set__DATA(var_data);
				
			sCH__LeakCheck__START_TIME->Set__DATA("");
			sCH__LeakCheck__END_TIME->Set__DATA("");
			sCH__LeakCheck__RESULT->Set__DATA("");
		}
		
		if(sCH__LeakCheck__CUR_CHECK_FLAG->Check__DATA(STR__YES) > 0)
		{
			// ...
			{
				Macro__Get_Date(date, time);
				var_data.Format("%s %s", date,time);
				
				sCH__LeakCheck__START_TIME->Set__DATA(var_data);
			}

			// ...
			{
				log_msg = "Leak-Check Started ...";
				sCH__OBJ_MSG->Set__DATA(log_msg);
			}

			fnc_flag = pOBJ_CTRL__LEAK_CHECK->Call__OBJECT(CMMD_MODE__CHM_LEAK_CHECK);

			// ...
			{
				Macro__Get_Date(date, time);
				var_data.Format("%s %s", date,time);
				
				sCH__LeakCheck__END_TIME->Set__DATA(var_data);
			}

			if(fnc_flag < 0)
			{
				sCH__LeakCheck__RESULT->Set__DATA("ERROR");				
				return -12;
			}
			else
			{
				sCH__LeakCheck__RESULT->Set__DATA("OK");				
			}
		}
	}

	// OBJ : FRC_CHECK.X ...
	{
		// ...
		{
			dCH__FRC_CHECK__CFG_CHECK_FLAG->Get__DATA(var_data);
			sCH__FRC_CHECK__CUR_CHECK_FLAG->Set__DATA(var_data);

			sCH__FRC_CHECK__START_TIME->Set__DATA("");
			sCH__FRC_CHECK__END_TIME->Set__DATA("");
			sCH__FRC_CHECK__RESULT->Set__DATA("");
		}

		if(sCH__FRC_CHECK__CUR_CHECK_FLAG->Check__DATA(STR__YES) > 0)
		{
			// ...
			{
				Macro__Get_Date(date, time);
				var_data.Format("%s %s", date,time);

				sCH__FRC_CHECK__START_TIME->Set__DATA(var_data);
			}

			// ...
			{
				log_msg = "FRC1-Check Started ...";
				sCH__OBJ_MSG->Set__DATA(log_msg);
			}

			fnc_flag = 1;

			for(int i=0; i<iFRC_CHECK__SIZE; i++)
			{
				if(pOBJ_CTRL__FRC_CHECK_X[i]->Call__OBJECT(CMMD_MODE__FRC_FLOW_CHECK) < 0)			fnc_flag = -1;
			}

			// ...
			{
				Macro__Get_Date(date, time);
				var_data.Format("%s %s", date,time);

				sCH__FRC_CHECK__END_TIME->Set__DATA(var_data);
			}

			if(fnc_flag < 0)
			{
				sCH__FRC_CHECK__RESULT->Set__DATA("ERROR");				
				return -21;
			}
			else
			{
				sCH__FRC_CHECK__RESULT->Set__DATA("OK");				
			}
		}
	}

	// OBJ : GAUGE_CHECK ...
	{
		// ...
		{
			dCH__GaugeCheck__CFG_CHECK_FLAG->Get__DATA(var_data);
			sCH__GaugeCheck__CUR_CHECK_FLAG->Set__DATA(var_data);

			sCH__GaugeCheck__START_TIME->Set__DATA("");
			sCH__GaugeCheck__END_TIME->Set__DATA("");
			sCH__GaugeCheck__RESULT->Set__DATA("");
		}

		if(sCH__GaugeCheck__CUR_CHECK_FLAG->Check__DATA(STR__YES) > 0)
		{
			// ...
			{
				Macro__Get_Date(date, time);
				var_data.Format("%s %s", date,time);

				sCH__GaugeCheck__START_TIME->Set__DATA(var_data);
			}

			// ...
			{
				log_msg = "GAUGE-Check Started ...";
				sCH__OBJ_MSG->Set__DATA(log_msg);
			}

			fnc_flag = pOBJ_CTRL__GAUGE_CHECK->Call__OBJECT(CMMD_MODE__GAUGE_ALL_CHECK);

			// ...
			{
				Macro__Get_Date(date, time);
				var_data.Format("%s %s", date,time);

				sCH__GaugeCheck__END_TIME->Set__DATA(var_data);
			}

			if(fnc_flag < 0)
			{
				sCH__GaugeCheck__RESULT->Set__DATA("ERROR");				
				return -31;
			}
			else
			{
				sCH__GaugeCheck__RESULT->Set__DATA("OK");				
			}
		}
	}

	// OBJ : Vat Check ...
	{
		// ...
		{
			dCH__VatCheck__CFG_CHECK_FLAG->Get__DATA(var_data);
			sCH__VatCheck__CUR_CHECK_FLAG->Set__DATA(var_data);
			
			sCH__VatCheck__START_TIME->Set__DATA("");
			sCH__VatCheck__END_TIME->Set__DATA("");
			sCH__VatCheck__RESULT->Set__DATA("");
		}
		
		if(sCH__VatCheck__CUR_CHECK_FLAG->Check__DATA(STR__YES) > 0)
		{
			// ...
			{
				Macro__Get_Date(date, time);
				var_data.Format("%s %s", date,time);
				
				sCH__VatCheck__START_TIME->Set__DATA(var_data);
			}
			
			// ...
			{
				log_msg = "VAT-Conductance Started ...";
				sCH__OBJ_MSG->Set__DATA(log_msg);
			}
			
			// ...
			{
				var_data = dCH__VatCheck__CFG_CHECK_MODE->Get__STRING();
				sCH__VatCheck__CUR_CHECK_MODE->Set__DATA(var_data);
				dEXT_CH__VAT_CHECK__CFG_CHECK_TYPE->Set__DATA(var_data);
			}

			fnc_flag = pOBJ_CTRL__VAT_CHECK->Call__OBJECT(CMMD_MODE__VAT_POS_CONDUCT);
			
			// ...
			{
				Macro__Get_Date(date, time);
				var_data.Format("%s %s", date,time);
				
				sCH__VatCheck__END_TIME->Set__DATA(var_data);
			}
			
			if(fnc_flag < 0)
			{
				sCH__VatCheck__RESULT->Set__DATA("ERROR");				
				return -41;
			}
			else
			{
				sCH__VatCheck__RESULT->Set__DATA("OK");								
			}
		}
	}

	// OBJ : MFC Check ...
	{
		// ...
		{
			dCH__MfcCheck__CFG_CHECK_FLAG->Get__DATA(var_data);
			sCH__MfcCheck__CUR_CHECK_FLAG->Set__DATA(var_data);
	
			sCH__MfcCheck__START_TIME->Set__DATA("");
			sCH__MfcCheck__END_TIME->Set__DATA("");
			sCH__MfcCheck__RESULT->Set__DATA("");
		}

		if(sCH__MfcCheck__CUR_CHECK_FLAG->Check__DATA(STR__YES) > 0)
		{
			// ...
			{
				Macro__Get_Date(date, time);
				var_data.Format("%s %s", date,time);
				
				sCH__MfcCheck__START_TIME->Set__DATA(var_data);
			}

			// ...
			{
				log_msg = "MFC-CAL. Started ...";
				sCH__OBJ_MSG->Set__DATA(log_msg);
			}

			// ...
			{
				CString obj_mode;

				dCH__MfcCheck__CFG_CHECK_MODE->Get__DATA(obj_mode);
				sCH__MfcCheck__CUR_CHECK_MODE->Set__DATA(obj_mode);
			
				fnc_flag = pOBJ_CTRL__MFC_CHECK->Call__OBJECT(obj_mode);
			}

			// ...
			{
				Macro__Get_Date(date, time);
				var_data.Format("%s %s", date,time);
				
				sCH__MfcCheck__END_TIME->Set__DATA(var_data);
			}

			if(fnc_flag < 0)
			{
				sCH__MfcCheck__RESULT->Set__DATA("ERROR");				
				return -51;
			}
			else
			{
				sCH__MfcCheck__RESULT->Set__DATA("OK");				
			}
		}
	}

	return 1;
}
