#include "StdAfx.h"
#include "CObj__CHM_STD.h"
#include "CObj__CHM_STD__DEF.h"
#include "CObj__CHM_STD__ALID.h"


//----------------------------------------------------------------------------------------------------
void CObj__CHM_STD
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	SCX__TIMER_CTRL cx_timer_ctrl;

	CString str__atm_sns;
	CString str__vac_sns;
	CString var__data;

	if(iSim_Flag > 0)
	{
		diEXT_CH__ATM_SENSOR->Set__DATA(sDATA__ATM_OFF);
		diEXT_CH__VAC_SENSOR->Set__DATA(sDATA__VAC_ON);

		aiEXT_CH__TMC_CHM__PRESSURE_TORR->Set__DATA("0.001");
	}
	
	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);
		
		// PRESSURE ...
		{
			aiEXT_CH__TMC_CHM__PRESSURE_TORR->Get__DATA(var__data);
			aCH__TMC_CHM_PRESSURE_TORR->Set__DATA(var__data);

			double cur_press_mtorr = atof(var__data) * 1000.0;
			var__data.Format("%.1f", cur_press_mtorr);
			aCH__TMC_CHM_PRESSURE_mTORR->Set__DATA(var__data);
		}	

		// jglee : 2020.10.20
		if(bActive__ATM_SNS_Virtual_Type)
		{
			aiEXT_CH__TMC_CHM__PRESSURE_TORR->Get__DATA(var__data);
			double cur_press = atof(var__data);

			aCH__CFG_FAST_VENT_PRESSURE_TORR->Get__DATA(var__data);
			double cfg_press = atof(var__data);

			if(cur_press < cfg_press)
			{
				diEXT_CH__ATM_SENSOR->Set__DATA(sDATA__ATM_OFF);
			}
			else
			{
				diEXT_CH__ATM_SENSOR->Set__DATA(sDATA__ATM_ON);
			}
		}

		// ...
		{
			double cur_press;
			double ref_atm_press;
			double ref_vac_press;
			double atm_range_min, atm_range_max;
			double tolerance_atm_press;

			// Get Pressure Value ...
			aCH__TMC_CHM_PRESSURE_TORR->Get__DATA(var__data);
			cur_press = atof(var__data);

			aEXT_CH__CFG_REF_ATM_PRESSURE->Get__DATA(var__data);
			ref_atm_press = atof(var__data);

			aEXT_CH__CFG_REF_VAC_PRESSURE->Get__DATA(var__data);
			ref_vac_press = atof(var__data);

			// Get ATM Tolerance...
			aCH__CFG_ATM_PRESS_STS_TOLERANCE->Get__DATA(var__data);
			tolerance_atm_press = atof(var__data);

			atm_range_min = ref_atm_press - tolerance_atm_press;
			atm_range_max = ref_atm_press + tolerance_atm_press;

			// Get Sensor Value ...
			diEXT_CH__ATM_SENSOR->Get__DATA(str__atm_sns);
			diEXT_CH__VAC_SENSOR->Get__DATA(str__vac_sns);

			if((cur_press >= atm_range_min) 
			&& ( (str__atm_sns.CompareNoCase(STR__ON) == 0) && (str__vac_sns.CompareNoCase(STR__OFF) == 0)) )
			{
				dCH__TMC_CHM_PRESSURE_STATUS->Set__DATA(STR__ATM);
			}
			else if(((cur_press <= ref_vac_press) && (cur_press > 0)) 
				 &&  ( (str__atm_sns.CompareNoCase(STR__OFF) == 0) && (str__vac_sns.CompareNoCase(STR__ON) == 0)) )
			{
				dCH__TMC_CHM_PRESSURE_STATUS->Set__DATA(STR__VAC);
			}
			else
			{
				dCH__TMC_CHM_PRESSURE_STATUS->Set__DATA(STR__BTW);
			}			
		}

		// ...
		{
			if(diEXT_CH__ATM_SENSOR->Check__DATA(sDATA__ATM_ON) > 0)
			{
				dCH__TMC_CMH_VAC_SNS->Set__DATA(STR__OFF);
			}
			else
			{
				dCH__TMC_CMH_VAC_SNS->Set__DATA(STR__ON);
			}
		}

		Update__PUMP_VLV_STS(p_alarm);

		Fnc__INTERLOCK(p_variable,p_alarm);
	}	
}

void CObj__CHM_STD
::Fnc__INTERLOCK(CII_OBJECT__VARIABLE* p_variable,
			     CII_OBJECT__ALARM* p_alarm)
{
	if(Check__VENT_ALL_VLV__CLOSE(p_alarm) < 0)
	{			
		if(Check__PUMP_ALL_VLV__CLOSE(p_alarm) < 0)
		{
			Fnc__VENT_ALL_VLV__CLOSE(p_alarm);

			// ...
			{
				int alarm_id = ALID__VENT_VALVE__PUMP_INTERLOCK;
				CString r_act;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);
			}
		}
	}		

	// PUMP INTERLOCK ...
	if((sEXT_CH__MON_PUMP_COMM_STS->Check__DATA(STR__ONLINE) < 0) 
	|| (sEXT_CH__MON_PUMP_RUN_STS->Check__DATA(STR__ON) < 0))
	{
		if(Check__PUMP_ALL_VLV__CLOSE(p_alarm) < 0)
		{
			Fnc__PUMP_ALL_VLV__CLOSE(p_alarm);

			// ...
			{
				int alarm_id = ALID__PUMP_OFFLINE_OFF_INTERLOCK;
				CString r_act;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);
			}
		}
	}
	
	// ...
}

int CObj__CHM_STD
::Fnc__CNTS_PG_Disable(CII_OBJECT__VARIABLE* p_variable, 
					   CString sLogEnDis)
{
	double dblTemp = 0.0;
	CString sTemp, sGet_Obj_Mode, sGet_Obj_Sts;

	// 1. MFC SETZERO, 
	aoEXT_CH__BALLAST_N2_SET->Get__DATA(sTemp);	dblTemp = atof(sTemp);
	if(dblTemp != 0.0)	
	{
		aoEXT_CH__BALLAST_N2_SET->Set__DATA("0.0");
	}

	// 2. PGV Valve "Close"
	doEXT_CH__BALLAST_VALVE_SET->Get__DATA(sTemp);
	if(sTemp.CompareNoCase("Close") != 0)	
	{
		doEXT_CH__BALLAST_VALVE_SET->Set__DATA("Close");
	}

	// 3. DATALOG "DISABLE"
	if(sLogEnDis.CompareNoCase("DATALOG_STOP") == 0)
	{
		m_xI_DATALOG_OBJ_CTRL->Get__OBJ_MODE(sGet_Obj_Mode);
		m_xI_DATALOG_OBJ_CTRL->Get__OBJECT_STATUS(sGet_Obj_Sts);
		
		if(m_nDatalog_Flag > 0)
		{
			m_xI_DATALOG_OBJ_CTRL->Run__OBJECT("DISABLE");
			m_nDatalog_Flag = -1;
		}
	}

	return 1;
}

int CObj__CHM_STD
::Fnc__MON__TM_Purge_PID_Ctrl(CII_OBJECT__VARIABLE* p_variable, 
						      CII_OBJECT__ALARM *p_alarm)
{
	CString    szData, szData_bak;
	CString    szData_DOOR_bak, szData_CLAMP_bak;

	szData_bak			= "~";
	szData_DOOR_bak		= "~";
	szData_CLAMP_bak	= "~";

	int nFlag = 1;


	// PID -- Control ...
	SCX__USER_LOG_CTRL xSPECIAL_INF_Log;
	CString sINF_Log;
	
	xSPECIAL_INF_Log->CREATE__SUB_DIRECTORY("PID_LOG");
	xSPECIAL_INF_Log->SET__PROPERTY("PID LOG", 120, 60);
	xSPECIAL_INF_Log->WRITE__LOG("----------->> PID LOG START !! <<--------------");
	
	
	// PID -- Control ...
	#define	KP		1		// 비례항 gain
	#define	KI		0.01	// 적분항 gain
	#define	KD		0.01	// 미분항 gain

	CString sMsg, sTemp, sGet_Obj_Mode, sGet_Obj_Sts;
	
	double error, Paction = 0.0, Daction = 0.0, Iaction = 0.0, lastError = 0.0, time = 0.1;
	double dMVPcnt = 0.0;
	double setPoint;
	double measurement = 0.0, output = 0;

	double dblMFC_Ctrl_Val = 0.0;
	double dblMFC_Old_Val = 0.0;
	CString szMFC_SET_VAL;
	double dblKP = 1, dblKI = 0.01, dblKD = 0.01;
	double dblTemp = 0.0;
	double dblTemp_Old = 0.0;

	double dblMFC_Set_Val		= 0.0;
	double dblMFC_Set_Val_Old	= 0.0;

	CString sGET_TM_OBJ_STS;
	
	int nPGSet_RUN     = -1;
	int nPGSet_DISABLE = -1;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		if(dTM_BALLAST_CTRL_INIT_FLAG->Check__DATA("NONE") > 0)	
		{
			continue;			
		}

		// ...
		p_variable->Get__CTRL_STATUS(sGET_TM_OBJ_STS);

		if((sGET_TM_OBJ_STS.CompareNoCase("RUN")   == 0) 
		|| (sGET_TM_OBJ_STS.CompareNoCase("ABORT") == 0))
		{
			// 초기화 !!
			error     = 0.0;
			Paction   = 0.0;
			Iaction   = 0.0;
			Daction   = 0.0;
			output	  = 0.0;
			lastError = 0.0;
			time = 0.1;

			// PG Valve, MFC Set Zero !!
			if(nPGSet_RUN < 0)
			{
				Fnc__CNTS_PG_Disable(p_variable, "DATALOG_CONTINUE");
				nPGSet_RUN = 1;
			}
			continue;
		}
						
		if(dCFG_CH__TM_BALLAST_CONTROL->Check__DATA(STR__DISABLE) > 0)
		{
			// 1. Disable function
			if(nPGSet_DISABLE < 0)
			{
				Fnc__CNTS_PG_Disable(p_variable, "DATALOG_STOP");
				nPGSet_DISABLE = 1;
			}
			
			// 초기화 !!
			error     = 0.0;
			Paction   = 0.0;
			Iaction   = 0.0;
			Daction   = 0.0;
			output	  = 0.0;
			lastError = 0.0;
			time = 0.1;

			continue;
		}
		else if(dCFG_CH__TM_BALLAST_MODE->Check__DATA(STR__VALVE) > 0)
		{			
			continue;
		}

		if(dCFG_CH__TM_BALLAST_CONTROL->Check__DATA(STR__DISABLE) > 0)
		{
			if(doEXT_CH__FAST_PUMP_VLV__SET->Check__DATA("Open") > 0)
			{
				nPGSet_RUN     = -1;
				nPGSet_DISABLE = -1;

				// 1. MFC Set !!
				dblTemp = aCFG_CH__TM_BALLAST_N2_VALUE->Get__VALUE();
				dblMFC_Set_Val = aoEXT_CH__BALLAST_N2_SET->Get__VALUE();
	
				if(dblMFC_Set_Val != dblTemp)	
					aoEXT_CH__BALLAST_N2_SET->Set__DATA(sTemp);
			}
			else		
			{
				Fnc__CNTS_PG_Disable(p_variable, "DATALOG_CONTINUE");
			}

			if(dCFG_CH__TM_BALLAST_DATALOG_ENDIS->Check__DATA("ENABLE") > 0)
			{
				m_xI_DATALOG_OBJ_CTRL->Get__OBJ_MODE(sGet_Obj_Mode);
				m_xI_DATALOG_OBJ_CTRL->Get__OBJECT_STATUS(sGet_Obj_Sts);
				
				if(m_nDatalog_Flag < 0)
				{
					m_xI_DATALOG_OBJ_CTRL->Run__OBJECT("ENABLE");
					m_nDatalog_Flag = 1;
				}					
			}
			else
			{
				m_xI_DATALOG_OBJ_CTRL->Get__OBJ_MODE(sGet_Obj_Mode);
				m_xI_DATALOG_OBJ_CTRL->Get__OBJECT_STATUS(sGet_Obj_Sts);

				if(m_nDatalog_Flag > 0)
				{
					m_xI_DATALOG_OBJ_CTRL->Run__OBJECT("DISABLE");
					m_nDatalog_Flag = -1;
				}
			}

			continue;
		}

		if(dCFG_CH__TM_BALLAST_DATALOG_ENDIS->Check__DATA("ENABLE") > 0)
		{
			m_xI_DATALOG_OBJ_CTRL->Get__OBJ_MODE(sGet_Obj_Mode);
			m_xI_DATALOG_OBJ_CTRL->Get__OBJECT_STATUS(sGet_Obj_Sts);

			if( m_nDatalog_Flag < 0 )
			{
				m_xI_DATALOG_OBJ_CTRL->Run__OBJECT("ENABLE");
				m_nDatalog_Flag = 1;
			}
		}
		else
		{
			m_xI_DATALOG_OBJ_CTRL->Get__OBJ_MODE(sGet_Obj_Mode);
			m_xI_DATALOG_OBJ_CTRL->Get__OBJECT_STATUS(sGet_Obj_Sts);
			
			if( m_nDatalog_Flag > 0 )
			{
				m_xI_DATALOG_OBJ_CTRL->Run__OBJECT("DISABLE");
				m_nDatalog_Flag = -1;
			}
		}
			
		// 0. Get PID Gain !!
		aCFG_CH__TM_BALLAST_N2_P_GAIN->Get__DATA(sTemp);
		dblKP = atof(sTemp);

		aCFG_CH__TM_BALLAST_N2_I_GAIN->Get__DATA(sTemp);
		dblKI = atof(sTemp);

		aCFG_CH__TM_BALLAST_N2_D_GAIN->Get__DATA(sTemp);
		dblKD = atof(sTemp);
			
		// 1.사용자가 원하는 목표값.
		aCFG_CH__TM_BALLAST_N2_VALUE->Get__DATA(sTemp);	setPoint = atof(sTemp);

		// 2.현재 측정된 pressure.
		aiEXT_CH__TMC_CHM__PRESSURE_TORR->Get__DATA(sTemp);	measurement = atof(sTemp);	// 장비 test 땐 이걸로...
		measurement = measurement*1000;		// mTorr 로 변환 !!
			
		// 3. error 편차 측정.
		error   =  setPoint - measurement;
		Paction =  dblKP*error;
		Iaction = dblKI*time*error;
		Daction  = dblKD*(error-lastError)/time;

		output = Paction + Iaction + Daction;
		lastError = error;

		sTemp.Format("%f", output);
		sTM_BALLAST_OUTPUT_RESULT->Set__DATA(sTemp);

		// UPC에 Setting !!
		{
			nPGSet_RUN     = -1;
			nPGSet_DISABLE = -1;

			// 1. PGV Valve "Open"
			doEXT_CH__BALLAST_VALVE_SET->Get__DATA(sTemp);
			if(sTemp.CompareNoCase("Open") != 0)	
				doEXT_CH__BALLAST_VALVE_SET->Set__DATA("Open");

			// 2.
			sTemp.Format("%.3f", output*0.001);		// mTorr로 Setting..
			aoEXT_CH__BALLAST_N2_SET->Set__DATA(sTemp);
		}

		time = 0.1;
	}
	
	return 1;
}
