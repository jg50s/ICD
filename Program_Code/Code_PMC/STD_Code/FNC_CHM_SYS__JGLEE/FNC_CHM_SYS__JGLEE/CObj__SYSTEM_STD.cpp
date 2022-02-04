#include "StdAfx.h"
#include "CObj__SYSTEM_STD.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__SYSTEM_STD::CObj__SYSTEM_STD()
{

}
CObj__SYSTEM_STD::~CObj__SYSTEM_STD()
{

}

//-------------------------------------------------------------------------
int CObj__SYSTEM_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,	"SYSTEM_INIT");
		ADD__CTRL_VAR(sMODE__MAINT, "SYSTEM_MAINT");

		ADD__CTRL_VAR(sMODE__TRANSFER_INIT, "TRANSFER_INIT");
	}
	return 1;
}
int CObj__SYSTEM_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

int CObj__SYSTEM_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	int i;

	// OBJ ...
	{
		str_name = "OBJ.TIMER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_TIMER, str_name);
	}

	// CFG : SYSTEM ...
	{
		str_name = "CFG.CHAMBER.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"NORMAL TEST","");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_CHAMBER_MODE, str_name);

		str_name = "CFG.WAFER.STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"NO YES","");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_WAFER_STATUS, str_name);

		//
		str_name = "CFG.PART.STABLE.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PART_STABLE_SEC, str_name);
	}

	// CFG : RF_SYS ...
	{
		// RF_GEN 
		for(i=0; i<_RF_SYS__GEN_SIZE; i++)
		{
			int id = i + 1;

			str_name.Format("CFG.SYS_INIT.RF_GEN.%1d", id);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "DISABLE ENABLE", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_SYS_INIT__RF_GEN_X[i], str_name);

			str_name.Format("LINK.OBJ_NAME.RF_GEN.%1d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__LINK_OBJ_NAME__RF_GEN_X[i], str_name);

			str_name.Format("LINK.OBJ_ACTIVE.RF_GEN.%1d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__LINK_OBJ_ACTIVE__RF_GEN_X[i], str_name);
		}

		// RF_MAT 
		for(i=0; i<_RF_SYS__MAT_SIZE; i++)
		{
			int id = i + 1;

			str_name.Format("CFG.SYS_INIT.RF_MAT.%1d", id);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "DISABLE ENABLE", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_SYS_INIT__RF_MAT_X[i], str_name);

			str_name.Format("LINK.OBJ_NAME.RF_MAT.%1d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__LINK_OBJ_NAME__RF_MAT_X[i], str_name);

			str_name.Format("LINK.OBJ_ACTIVE.RF_MAT.%1d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__LINK_OBJ_ACTIVE__RF_MAT_X[i], str_name);
		}

		// ESC_DC_SUPPLY
		{
			str_name = "CFG.SYS_INIT.ESC_DC_SUPPLY";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "DISABLE ENABLE", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_SYS_INIT__ESC_DC_SUPPLY, str_name);

			str_name = "LINK.OBJ_NAME.ESC_DC_SUPPLY";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__LINK_OBJ_NAME__ESC_DC_SUPPLY, str_name);
		
			str_name = "LINK.OBJ_ACTIVE.ESC_DC_SUPPLY";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__LINK_OBJ_ACTIVE__ESC_DC_SUPPLY, str_name);
		}

		// ESC_BACK_HE
		{
			str_name = "CFG.SYS_INIT.ESC_BACK_HE";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "DISABLE ENABLE", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_SYS_INIT__ESC_BACK_HE, str_name);

			str_name = "LINK.OBJ_NAME.ESC_BACK_HE";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__LINK_OBJ_NAME__ESC_BACK_HE, str_name);

			str_name = "LINK.OBJ_ACTIVE.ESC_BACK_HE";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__LINK_OBJ_ACTIVE__ESC_BACK_HE, str_name);
		}
	}

	// CFG : HEATER_SYS ...
	{
		for(i=0; i<_HTR_SYS__PART_SIZE; i++)
		{
			int id = i + 1;

			str_name.Format("CFG.SYS_INIT.HEATER.%1d", id);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "DISABLE ENABLE", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_SYS_INIT__HEATER_X[i], str_name);

			str_name.Format("LINK.OBJ_NAME.HEATER.%1d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__LINK_OBJ_NAME__HEATER_X[i], str_name);
			
			str_name.Format("LINK.OBJ_ACTIVE.HEATER.%1d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__LINK_OBJ_ACTIVE__HEATER_X[i], str_name);
		}
	}

	// CFG : CHAMBER ...
	{
		// LIFT_PIN ...
		{
			str_name = "CFG.SYS_INIT.CHM.LIFT_PIN_DOWN";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "DISABLE ENABLE", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_SYS_INIT_CHM_LIFT_PIN_DOWN, str_name);

			str_name = "LINK.OBJ_NAME.CHM.LIFT_PIN_DOWN";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__LINK_OBJ_NAME_CHM_LIFT_PIN_DOWN, str_name);

			str_name = "LINK.OBJ_ACTIVE.CHM.LIFT_PIN_DOWN";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__LINK_OBJ_ACTIVE_CHM_LIFT_PIN_DOWN, str_name);
		}

		// DECHUCK ...
		{
			str_name = "CFG.SYS_INIT.CHM.DECHUCK";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "DISABLE ENABLE", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_SYS_INIT_CHM_DECHUCK, str_name);

			str_name = "LINK.OBJ_NAME.CHM.DECHUCK";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__LINK_OBJ_NAME_CHM_DECHUCK, str_name);

			str_name = "LINK.OBJ_ACTIVE.CHM.DECHUCK";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__LINK_OBJ_ACTIVE_CHM_DECHUCK, str_name);
		}
	}

	return 1;
}
int CObj__SYSTEM_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	//.....
	CString title;
	title.Format("%s : ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	//.....
	{
		alarm_id = ALID__SYSTEM_INIT_ALARM;
		alarm_title  = title;
		alarm_title += "SYSTEM INIT FAILED.";

		alarm_msg = "System Component Initialize Action Failed.";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	return 1;
}

int CObj__SYSTEM_STD::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__SYSTEM_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString obj_name;
	CString var_name;
	int i;

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
	CCommon_Utility x_utility;

	// OBJ : DB_INF ...
	{
		def_name = "OBJ__DB_INF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		//
		var_name = "SLOT01.STATUS";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__WAFER_STATUS, obj_name,var_name);
	}

	// OBJ : DB_SYS ...
	{
		def_name = "OBJ__DB_SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		//
		var_name = "FUNCTION.MSG";		
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__FNC_MSG, obj_name,var_name);
	}

	// OBJ  LINK ...
	{
		def_name = "DATA.OBJ_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iOBJ_SIZE = atoi(def_data);
		if(iOBJ_SIZE > _LINK_OBJ__MAX)
		{
			CString msg;

			msg.Format("Max. External Object Count is %d, Current: %d", _LINK_OBJ__MAX, iOBJ_SIZE);
			MessageBox(NULL, msg, "Error", MB_ICONERROR|MB_OK|MB_TOPMOST);

			iOBJ_SIZE = _LINK_OBJ__MAX;
			return 1;
		}

		//
		sList__OBJ_NAME.RemoveAll();

		for(int i=0; i<iOBJ_SIZE; i++)
		{
			int id = i + 1;

			def_name.Format("LINK_OBJ.TITLE.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sList__OBJ_NAME.Add(def_data);

			def_name.Format("LINK_OBJ.NAME.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
			pOBJ_CTRL__LIST[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
		}
	}

	// LINK : PART OBJ
	{
		// RF_SYS ...
		{
			// 1.
			{
				def_name = "RF_GEN.OBJ_SIZE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

				iRF_SYS__GEN_SIZE = atoi(def_data);
				if(iRF_SYS__GEN_SIZE > _RF_SYS__GEN_SIZE)			iRF_SYS__GEN_SIZE = _RF_SYS__GEN_SIZE;

				for(i=0; i<iRF_SYS__GEN_SIZE; i++)
				{
					int id = i + 1;

					def_name.Format("RF_GEN.OBJ_TITLE.%1d", id);
					p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
					sList__RF_SYS__GEN_NAME.Add(def_data);
					sCH__LINK_OBJ_NAME__RF_GEN_X[i]->Set__DATA(def_data);

					def_name.Format("RF_GEN.OBJ_NAME.%1d", id);
					p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
					pOBJ_CTRL__RF_SYS__GEN_X[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
				}

				for( ; i<_RF_SYS__GEN_SIZE; i++)
				{
					sCH__LINK_OBJ_NAME__RF_GEN_X[i]->Set__DATA("___");
				}
			}
			// 2.
			{
				def_name = "RF_MAT.OBJ_SIZE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

				iRF_SYS__MAT_SIZE = atoi(def_data);
				if(iRF_SYS__MAT_SIZE > _RF_SYS__MAT_SIZE)			iRF_SYS__MAT_SIZE = _RF_SYS__MAT_SIZE;

				for(i=0; i<iRF_SYS__MAT_SIZE; i++)
				{
					int id = i + 1;

					def_name.Format("RF_MAT.OBJ_TITLE.%1d", id);
					p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
					sList__RF_SYS__MAT_NAME.Add(def_data);
					sCH__LINK_OBJ_NAME__RF_MAT_X[i]->Set__DATA(def_data);

					def_name.Format("RF_MAT.OBJ_NAME.%1d", id);
					p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
					pOBJ_CTRL__RF_SYS__MAT_X[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
				}

				for( ; i<_RF_SYS__MAT_SIZE; i++)
				{
					sCH__LINK_OBJ_NAME__RF_MAT_X[i]->Set__DATA("___");
				}
			}
			// 3.
			{
				def_name = "RF_SYS.ESC_DC_SUPPLY";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

				bool def_check = x_utility.Check__Link(obj_name);
				bACTIVE_RF_SYS__ESC_DC_SUPPLY = def_check;

				if(def_check)
				{
					pOBJ_CTRL__RF_SYS_ESC_DC_SUPPLY = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
				}

				sCH__LINK_OBJ_NAME__ESC_DC_SUPPLY->Set__DATA(obj_name);
			}
			// 4.
			{
				def_name = "RF_SYS.ESC_BACK_HE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

				bool def_check = x_utility.Check__Link(obj_name);
				bACTIVE_RF_SYS__ESC_BACK_HE = def_check;

				if(def_check)
				{
					pOBJ_CTRL__RF_SYS_ESC_BACK_HE = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
				}

				sCH__LINK_OBJ_NAME__ESC_BACK_HE->Set__DATA(obj_name);
			}
		}

		// HEATER_SYS ...
		{
			// 1.
			{
				def_name = "HEATER.OBJ_SIZE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

				iHTR_SYS__PART_SIZE = atoi(def_data);
				if(iHTR_SYS__PART_SIZE > _HTR_SYS__PART_SIZE)			iHTR_SYS__PART_SIZE = _HTR_SYS__PART_SIZE;

				for(i=0; i<iHTR_SYS__PART_SIZE; i++)
				{
					int id = i + 1;

					def_name.Format("HEATER.OBJ_TITLE.%1d", id);
					p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
					sList__HTR_SYS__PART_NAME.Add(def_data);
					sCH__LINK_OBJ_NAME__HEATER_X[i]->Set__DATA(def_data);

					def_name.Format("HEATER.OBJ_NAME.%1d", id);
					p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
					pOBJ_CTRL__HTR_SYS__PART_X[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
				}

				for( ; i<_HTR_SYS__PART_SIZE; i++)
				{
					sCH__LINK_OBJ_NAME__HEATER_X[i]->Set__DATA("___");
				}
			}
		}

		// CHAMBER ...
		{
			// 1.
			{
				def_name = "OBJ_CHAMBER.LIFT_PIN";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

				bool def_check = x_utility.Check__Link(obj_name);
				bACTIVE_CHM__LIFT_PIN = def_check;

				if(def_check)
				{
					pOBJ_CTRL__CHM_LIFT_PIN = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
				}

				sCH__LINK_OBJ_NAME_CHM_LIFT_PIN_DOWN->Set__DATA(obj_name);
			}
			// 2.
			{
				def_name = "OBJ_CHAMBER.DECHUCK";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
				
				bool def_check = x_utility.Check__Link(obj_name);
				bACTIVE_CHM__DECHUCK = def_check;

				if(def_check)
				{
					pOBJ_CTRL__CHM_DECHUCK = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
				}

				sCH__LINK_OBJ_NAME_CHM_DECHUCK->Set__DATA(obj_name);
			}
		}
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__SYSTEM_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	// ...
	{
		CString log_msg;

		log_msg.Format("Start ... :  [%s]",mode);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	int flag = -1;

	// ...
	{
		IF__CTRL_MODE(sMODE__INIT)
		{
			flag = Call__INIT(p_variable, p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__MAINT)
		{
			flag = Call__MAINT(p_variable, p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__TRANSFER_INIT)
		{
			flag = Call__TRANSFER_INIT(p_variable, p_alarm);
		}
		else
		{
			flag = -1;
		}
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;

		log_msg.Format("Aborted ... :  [%s]",mode);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	else
	{
		CString log_msg;

		log_msg.Format("Completed ... :  [%s]",mode);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}
int CObj__SYSTEM_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}


//-------------------------------------------------------------------------
int  CObj__SYSTEM_STD
::Alarm__CHECK_RETRY_ABORT(CII_OBJECT__ALARM* p_alarm,CString msg, const int alarm_id)
{
	CString r_act;

	p_alarm->Check__ALARM(alarm_id,r_act);
	p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, msg, r_act);
	if(r_act.CompareNoCase("RETRY") == 0)		return 1;

	return -1;
}
void CObj__SYSTEM_STD
::Alarm__POST_CHECK(CII_OBJECT__ALARM* p_alarm, CString msg, const int alarm_id)
{
	CString r_act;
	p_alarm->Check__ALARM(alarm_id, r_act);
	p_alarm->Post__ALARM_With_MESSAGE(alarm_id, msg);
}

