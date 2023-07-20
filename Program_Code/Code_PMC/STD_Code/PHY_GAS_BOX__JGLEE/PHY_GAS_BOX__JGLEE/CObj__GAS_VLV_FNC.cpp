#include "StdAfx.h"
#include "CObj__GAS_VLV_FNC.h"
#include "CObj__GAS_VLV_FNC__ALID.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__GAS_VLV_FNC::CObj__GAS_VLV_FNC()
{

}
CObj__GAS_VLV_FNC::~CObj__GAS_VLV_FNC()
{

}

//-------------------------------------------------------------------------
int CObj__GAS_VLV_FNC::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__ALL_CLOSE,	"ALL_CLOSE");
		ADD__CTRL_VAR(sMODE__MFC_ALL_CLOSE,	"MFC.ALL_CLOSE");

		ADD__CTRL_VAR(sMODE__PROC_READY, "PROC_READY");

		ADD__CTRL_VAR(sMODE__SV_OPEN,  "SV_OPEN");
		ADD__CTRL_VAR(sMODE__SV_CLOSE, "SV_CLOSE");

		ADD__CTRL_VAR(sMODE__FV_OPEN,  "FV_OPEN");
		ADD__CTRL_VAR(sMODE__FV_CLOSE, "FV_CLOSE");

		ADD__CTRL_VAR(sMODE__MFC_CONTROL, "MFC_CONTROL");
		ADD__CTRL_VAR(sMODE__MFC_CLOSE,   "MFC_CLOSE");
		ADD__CTRL_VAR(sMODE__MFC_OPEN,    "MFC_OPEN");

		ADD__CTRL_VAR(sMODE__GAS_LINE_PURGE, "GAS_LINE_PURGE");
		ADD__CTRL_VAR(sMODE__CHM_LINE_PURGE, "CHM_LINE_PURGE");

		ADD__CTRL_VAR(sMODE__LINE_PURGE_WITH_N2, "LINE_PURGE_WITH_N2");

		ADD__CTRL_VAR(sMODE__CHM_BALLAST_FLOW,	 "CHM_BALLAST_FLOW");
		ADD__CTRL_VAR(sMODE__TRANS_BALLAST_FLOW, "TRANS_BALLAST_FLOW");
		ADD__CTRL_VAR(sMODE__BALLAST_CLOSE,		 "BALLAST_CLOSE");
	}
	return 1;
}
int CObj__GAS_VLV_FNC::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__STATE					1


int CObj__GAS_VLV_FNC::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// OBJ ...
	{
		str_name = "OBJ.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_STATUS, str_name);

		str_name = "OBJ.MESSAGE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// PARA.INTERLOCK ...
	{
		str_name = "PARA.INTERLOCK.SKIP";
		STD__ADD_DIGITAL(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_INTERLOCK_SKIP, str_name);
	}

	// PARA ...
	{
		str_name = "PARA.MFC.INDEX";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_MFC_INDEX, str_name);

		//
		str_name = "PARA.MFC.TYPE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "", "");
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_MFC_TYPE, str_name);

		str_name = "PARA.MFC.FLOW";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sccm",1,0,10000,"");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_MFC_FLOW, str_name);

		str_name = "PARA.N2.FLOW.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec",0,5,1000,"");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_N2_FLOW_TIME, str_name);

		str_name = "PARA.PURGE.CYCLE.COUNT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "num",0,1,1000,"");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PURGE_CYCLE_COUNT, str_name);

		str_name = "PARA.PURGE.TEST.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "ALL SINGLE","");
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_PURGE_TEST_MODE, str_name);

		str_name = "PARA.SINGLE_TEST.GAS_TYPE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "","");
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_SINGLE_TEST_GAS_TYPE, str_name);

		str_name = "PARA.PURGE.DELAY.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec",0,0,1000,"");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PURGE_DELAY_SEC, str_name);

		//
		str_name = "CUR.MFC.GAS.NAME";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__CUR_MFC_GAS_NAME, str_name);

		str_name = "CUR.N2.FLOW.TIME";
		STD__ADD_ANALOG(str_name, "sec",0,0,1000);
		LINK__VAR_ANALOG_CTRL(aCH__CUR_N2_FLOW_TIME, str_name);

		str_name = "CUR.PURGE.CYCLE.COUNT";
		STD__ADD_ANALOG(str_name, "num",0,0,1000);
		LINK__VAR_ANALOG_CTRL(aCH__CUR_PURGE_CYCLE_COUNT, str_name);

		str_name = "CUR.PURGE.DELAY.SEC";
		STD__ADD_ANALOG(str_name, "sec",0,0,10000);
		LINK__VAR_ANALOG_CTRL(aCH__CUR_PURGE_DELAY_SEC, str_name);
	}

	// CFG : WAP ...
	{
		str_name = "CFG.WAP.AUTO.LEARN.GAS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_WAP_AUTO_LEARN_GAS, str_name);

		str_name = "CFG.WAP.AUTO.LEARN.GAS.FLOW";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sccm", 0, 10, 10000, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_WAP_AUTO_LEARN_GAS_FLOW, str_name);

		str_name = "CFG.WAP.AUTO.LEARN.START.DELAY";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_WAP_AUTO_LEARN_START_DELAY, str_name);	
	}

	// CFG : Ballast ...
	{
		CString list_gas = "";
		CString str_gas;

		list_gas  = STR__N2_Ballast;
		list_gas += " ";

		for(int i=0; i<_MAX__MFC_OBJ; i++)
		{
			str_gas.Format("GAS%02d ", i+1);
			list_gas += str_gas;
		}

		// Transfer ...
		{
			str_name = "CFG.TRANSFER.BALLAST.GAS.ID";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, list_gas, "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_TRANSFER_BALLAST_GAS_ID, str_name);

			str_name = "CFG.TRANSFER.BALLAST.GAS.FLOW";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sccm", 0, 0, 10000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_TRANSFER_BALLAST_GAS_FLOW, str_name);

			str_name = "CUR.TRANSFER.BALLAST.GAS.NAME";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__CUR_TRANSFER_BALLAST_GAS_NAME, str_name);
		}
		// Chamber ...
		{
			str_name = "CFG.CHAMBER.BALLAST.GAS.ID";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, list_gas, "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_CHAMBER_BALLAST_GAS_ID, str_name);

			str_name = "CFG.CHAMBER.BALLAST.GAS.FLOW";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sccm", 0, 0, 10000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_CHAMBER_BALLAST_GAS_FLOW, str_name);

			str_name = "CUR.CHAMBER.BALLAST.GAS.NAME";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__CUR_CHAMBER_BALLAST_GAS_NAME, str_name);
		}
	}

	p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATE);
	return 1;
}

int CObj__GAS_VLV_FNC::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	// ...
	{
		alarm_id = ALID__CHM_STATE__NOT_PUMPING;

		alarm_title  = title;
		alarm_title += "Chamber가 Pumping 상태가 아닙니다. \n";

		alarm_msg = "Chamber Pumping 후에 작업을 진행하시기 바랍니다.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__DRY_PUMP_STATE__NOT_ON;

		alarm_title  = title;
		alarm_title += "Dry-Pump 상태가 \"ON\"이 아닙니다. \n";

		alarm_msg = "Dry-Pump를 \"ON\" 시킨 다음에 작업을 진행하시기 바랍니다.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

int CObj__GAS_VLV_FNC::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__GAS_VLV_FNC::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{	
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;

	CCommon_Utility x_utility;
	bool def_check;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name, 24*5, 60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	CStringArray l_mfc_type;
	CStringArray l_ballast_mfc_type;
	int i;

	// OBJ.DB_INF ...
	{
		def_name = "OBJ__DB_INF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		var_name = "CFG.TRANSFER.MODE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_TRANSFER_MODE, obj_name,var_name);
	}

	// OBJ.DB_SYS ...
	{
		def_name = "OBJ__DB_SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		var_name = "ACTIVE.INTERLOCK.CHAMBER.VENT";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__ACTIVEINTERLOCK_CHAMBER_VENT, obj_name,var_name);
	}

	// OBJ : CHM_PUMPING_STATE 
	{
		def_name = "CH__CHM_PUMPING_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_PUMPING_STATE, obj_name,var_name);
	}

	// OBJ : DRY_PUMPING_STATE 
	{
		def_name = "CH__DRY_PUMPING_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__DRY_PUMPING_STATE, obj_name,var_name);
	}

	// OBJ : GAS_VLV
	{
		def_name = "OBJ__GAS_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pOBJ_CTRL__GAS = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}

	// OBJ : FRC_X ...
	{
		def_name = "OBJ.FRC_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iFRC_SIZE = atoi(def_data);
		if(iFRC_SIZE > _MAX__FRC_OBJ)		iFRC_SIZE = _MAX__FRC_OBJ;

		for(i=0; i<iFRC_SIZE; i++)
		{
			int id = i + 1;

			def_name.Format("OBJ.FRC%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

			pOBJ_CTRL__FRC_X[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
		}
	}
	// OBJ : DFG_VLV ...
	{
		def_name = "OBJ__DGF_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__DGF_VLV = def_check;

		if(def_check)
		{
			pOBJ_CTRL__DGF_VLV = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
		}
	}

	// OBJ : MFC ...
	{
		def_name = "OBJ.MFC_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		iMFC_SIZE = atoi(def_data);

		if(iMFC_SIZE > _MAX__MFC_OBJ)
		{
			CString msg;
			msg.Format("Max. External MFC Object Count is %d, Current: %d", _MAX__MFC_OBJ, iMFC_SIZE);
			MessageBox(NULL, msg, "Error", MB_ICONERROR|MB_OK|MB_TOPMOST);

			iMFC_SIZE = _MAX__MFC_OBJ;
		}

		sList__GAS_TYPE.RemoveAll();

		for(i=0; i<iMFC_SIZE; i++)
		{
			def_name.Format("OBJ.MFC%1d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

			pOBJ_CTRL__MFC[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			def_name.Format("OBJ.ID%1d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			sList__GAS_TYPE.Add(def_data);
			l_mfc_type.Add(def_data);
			l_ballast_mfc_type.Add(def_data);

			//
			var_name = "CFG.MFC.USE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_MFC_USE[i],  obj_name,var_name);

			var_name = "CFG.GAS.NAME";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CFG_GAS_NAME[i],   obj_name,var_name);

			var_name = "CFG.MFC.MIN.VALUE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_MFC_MIN_VALUE[i],  obj_name,var_name);
			
			var_name = "CFG.MFC.MAX.VALUE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_MFC_MAX_VALUE[i], obj_name,var_name);
		
			var_name = "CFG.MFC.DEC.VALUE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_MFC_DEC_VALUE[i], obj_name,var_name);

			//
			var_name = "PARA.SET.FLOW";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_SET_FLOW[i],  obj_name,var_name);

			//
			var_name = "MON.MFC.STATE";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MON_MFC_STATE[i], obj_name,var_name);
		}
	}

	// Item Change ...
	{
		var_name = STR__N2_Ballast;
		l_ballast_mfc_type.InsertAt(0, var_name);

		p_variable->Change__DIGITAL_LIST(dCH__PARA_MFC_TYPE->Get__VARIABLE_NAME(),          l_mfc_type);
		p_variable->Change__DIGITAL_LIST(dCH__CFG_WAP_AUTO_LEARN_GAS->Get__VARIABLE_NAME(), l_mfc_type);
		
		p_variable->Change__DIGITAL_LIST(dCH__CFG_CHAMBER_BALLAST_GAS_ID->Get__VARIABLE_NAME(),  l_ballast_mfc_type);
		p_variable->Change__DIGITAL_LIST(dCH__CFG_TRANSFER_BALLAST_GAS_ID->Get__VARIABLE_NAME(), l_ballast_mfc_type);

		//
		l_mfc_type.InsertAt(0, "ALL");
		p_variable->Change__DIGITAL_LIST(dCH__PARA_SINGLE_TEST_GAS_TYPE->Get__VARIABLE_NAME(), l_mfc_type);
	}

	// OBJ.CTRL ...
	{
		var_name = "CTRL";
		LINK__EXT_VAR_DIGITAL_CTRL(dCH__OBJ_CTRL, sObject_Name,var_name);
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__GAS_VLV_FNC::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

LOOP_RETRY:

	// ...
	int flag = 1;

	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg.Format("Start [%s] ... By %s", mode, p_ext_mode_ctrl->Get__UPPER_OBJECT_NAME());
		sCH__OBJ_MSG->Set__DATA(log_msg);

		log_msg += "\n";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	bool active__interlock_check = true;

	if(dCH__PARA_INTERLOCK_SKIP->Check__DATA(STR__YES) > 0)			active__interlock_check = false;

	if(active__interlock_check)
	{
		if((mode.CompareNoCase(sMODE__MFC_CONTROL)        == 0)
		|| (mode.CompareNoCase(sMODE__CHM_BALLAST_FLOW)   == 0)
		|| (mode.CompareNoCase(sMODE__TRANS_BALLAST_FLOW) == 0))
		{
			if(sEXT_CH__CHM_PUMPING_STATE->Check__DATA("PUMPING") < 0)
			{
				bool active__pumping_check = true;

				if(dEXT_CH__CFG_TRANSFER_MODE->Check__DATA(STR__ATM) > 0)
				{
					if((mode.CompareNoCase(sMODE__CHM_BALLAST_FLOW)   == 0)
					|| (mode.CompareNoCase(sMODE__TRANS_BALLAST_FLOW) == 0))
					{
						active__pumping_check = false;
					}
				}

				if(active__pumping_check)
				{
					int alm_id = ALID__CHM_STATE__NOT_PUMPING;
					CString alm_msg;
					CString r_act;
		
					alm_msg.Format("\"%s\" 명령을 수행 할 수 없습니다. \n", mode);

					p_alarm->Popup__ALARM_With_MESSAGE(alm_id, alm_msg, r_act);

					if(r_act.CompareNoCase(ACT__RETRY) == 0)
					{
						// ...
						{
							CString log_msg;
							CString log_bff;

							log_msg  = "\n";
							log_msg += "Chamber State is not \"Pumping\". \n";

							log_bff.Format("  * %s <- %s \n",
										   sEXT_CH__CHM_PUMPING_STATE->Get__CHANNEL_NAME(),
										   sEXT_CH__CHM_PUMPING_STATE->Get__STRING());
							log_msg += log_bff;

							xLOG_CTRL->WRITE__LOG(log_msg);
						}
						goto LOOP_RETRY;
					}

					flag = -101;
				}
			}
		}

		if((mode.CompareNoCase(sMODE__GAS_LINE_PURGE)     == 0)
		|| (mode.CompareNoCase(sMODE__CHM_LINE_PURGE)     == 0)
		|| (mode.CompareNoCase(sMODE__LINE_PURGE_WITH_N2) == 0))
		{
			if(sEXT_CH__DRY_PUMPING_STATE->Check__DATA("ON") < 0)
			{
				int alm_id = ALID__DRY_PUMP_STATE__NOT_ON;
				CString alm_msg;
				CString r_act;

				alm_msg.Format("\"%s\" 명령을 수행 할 수 없습니다. \n", mode);

				p_alarm->Popup__ALARM_With_MESSAGE(alm_id, alm_msg, r_act);

				if(r_act.CompareNoCase(ACT__RETRY) == 0)
				{
					// ...
					{
						CString log_msg;
						CString log_bff;

						log_msg  = "\n";
						log_msg += "Dry-Pump is not \"ON\". \n";

						log_bff.Format("  * %s <- %s \n",
										sEXT_CH__DRY_PUMPING_STATE->Get__CHANNEL_NAME(),
										sEXT_CH__DRY_PUMPING_STATE->Get__STRING());
						log_msg += log_bff;

						xLOG_CTRL->WRITE__LOG(log_msg);
					}
					goto LOOP_RETRY;
				}

				flag = -101;
			}

			if(flag > 0)
			{
				dEXT_CH__ACTIVEINTERLOCK_CHAMBER_VENT->Set__DATA(STR__OFF);
			}
		}
	}

	if(flag > 0)
	{
			 IF__CTRL_MODE(sMODE__ALL_CLOSE)				flag = Call__ALL_CLOSE(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__MFC_ALL_CLOSE)			flag = Call__MFC_ALL_CLOSE(p_variable);

	    ELSE_IF__CTRL_MODE(sMODE__PROC_READY)				flag = Call__PROC_READY(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__SV_OPEN)					flag = Call__SV_OPEN(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__SV_CLOSE)					flag = Call__SV_CLOSE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__FV_OPEN)					flag = Call__FV_OPEN(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__FV_CLOSE)					flag = Call__FV_CLOSE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__MFC_CONTROL)				flag = Call__MFC_CONTROL(p_variable, false);
		ELSE_IF__CTRL_MODE(sMODE__MFC_CLOSE)				flag = Call__MFC_CLOSE(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__MFC_OPEN)					flag = Call__MFC_CONTROL(p_variable, true);

		ELSE_IF__CTRL_MODE(sMODE__GAS_LINE_PURGE)			flag = Call__GAS_LINE_PURGE(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__CHM_LINE_PURGE)			flag = Call__CHM_LINE_PURGE(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__LINE_PURGE_WITH_N2)		flag = Call__LINE_PURGE_WITH_N2(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__CHM_BALLAST_FLOW)			flag = Call__CHM_BALLAST_FLOW(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__TRANS_BALLAST_FLOW)		flag = Call__TRANS_BALLAST_FLOW(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__BALLAST_CLOSE)			flag = Call__BALLAST_CLOSE(p_variable);
	}

	if((mode.CompareNoCase(sMODE__GAS_LINE_PURGE)     == 0)
	|| (mode.CompareNoCase(sMODE__CHM_LINE_PURGE)     == 0)
	|| (mode.CompareNoCase(sMODE__LINE_PURGE_WITH_N2) == 0))
	{
		dEXT_CH__ACTIVEINTERLOCK_CHAMBER_VENT->Set__DATA(STR__ON);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted (%d)... :  [%s]", flag, mode);

		xLOG_CTRL->WRITE__LOG(log_msg);		
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

	// ...
	{
		sCH__PARA_MFC_INDEX->Set__DATA("");
		dCH__PARA_INTERLOCK_SKIP->Set__DATA(STR__NO);
	}
	return flag;
}

int CObj__GAS_VLV_FNC::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATE)
	{
		Mon__STATE(p_variable, p_alarm);
	}

	return 1;
}
