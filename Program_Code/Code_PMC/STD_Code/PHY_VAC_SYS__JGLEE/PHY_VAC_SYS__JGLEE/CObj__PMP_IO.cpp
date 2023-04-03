#include "StdAfx.h"
#include "CObj__PMP_IO.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__PMP_IO::CObj__PMP_IO()
{

}
CObj__PMP_IO::~CObj__PMP_IO()
{

}

//-------------------------------------------------------------------------
int CObj__PMP_IO::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		ADD__CTRL_VAR(sMODE__LOCAL, "LOCAL");
		ADD__CTRL_VAR(sMODE_REMOTE, "REMOTE");

		ADD__CTRL_VAR(sMODE__PUMP_ON,  "ON");
		ADD__CTRL_VAR(sMODE__PUMP_OFF, "OFF");
	}
	return 1;
}
int CObj__PMP_IO::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}


// ...
#define MON_ID__STATE_CHECK					1


int CObj__PMP_IO::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// OBJ ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// MON.PART ...
	{
		str_name = "MON.PART.DEF_TYPE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PART_DEF_TYPE, str_name);

		str_name = "MON.PART.ERROR.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_PART_ERROR_ACTIVE, str_name);
	}

	// MON ...
	{
		str_name = "MON.COMM.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMM_STATE, str_name);

		str_name = "MON.PUMP.POWER.SNS";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_PUMP_POWER_SNS, str_name);

		str_name = "MON.VAC.ON.SNS";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_VAC_ON_SNS, str_name);

		//
		str_name = "MON.PRESSURE.TORR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PRESSURE_TORR, str_name);

		str_name = "MON.PRESSURE.mTORR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PRESSURE_mTORR, str_name);
	}

	// CFG ...
	{
		str_name = "CFG.PUMP.PRESSURE.HIGH.LIMIT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 3, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PUMP_PRESSURE_HIGH_LIMIT, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATE_CHECK);
	}
	return 1;
}
int CObj__PMP_IO::__DEFINE__ALARM(p_alarm)
{

	iLIST_ALID__PART.RemoveAll();

	return 1;
}

//-------------------------------------------------------------------------
int CObj__PMP_IO::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{	
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xI_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xI_LOG_CTRL->SET__PROPERTY(file_name, 24*5, 60);

		xI_LOG_CTRL->DISABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG(log_msg);

		xI_LOG_CTRL->ENABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	CCommon_Utility x_utility;
	bool def_check;

	// PUMP.MANUAL_TYPE ...
	{
		def_name = "PUMP.CONTROL_TYPE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			 if(def_data.CompareNoCase("MANUAL") == 0)		iPUMP__CTRL_TYPE = _PMP_CTRL_TYPE__MANUAL;
		else if(def_data.CompareNoCase("IO") == 0)			iPUMP__CTRL_TYPE = _PMP_CTRL_TYPE__IO;
		else												iPUMP__CTRL_TYPE = _PMP_CTRL_TYPE__OBJECT;

		//
		if(iPUMP__CTRL_TYPE == _PMP_CTRL_TYPE__OBJECT)
		{
			sCH__MON_PART_DEF_TYPE->Set__DATA("OBJECT");

			//
			def_name = "OBJ__PUMP";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
			
			pOBJ_CTRL__PUMP = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			// LINK_OBJ.MODE...
			{
				def_name = "PUMP_MODE.ON";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
				sPUMP_MODE__ON = def_data;

				def_name = "PUMP_MODE.OFF";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
				sPUMP_MODE__OFF = def_data;
			}

			// MON ...
			{
				var_name = "MON.COMM.STS";
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__PUMP_OBJ__MON_COMM_STATE, obj_name,var_name);
			}
		}		
		else if(iPUMP__CTRL_TYPE == _PMP_CTRL_TYPE__IO)
		{
			sCH__MON_PART_DEF_TYPE->Set__DATA("IO");

			def_name = "CH__DO_PUMP_SET";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_PUMP_SET, obj_name,var_name);
		}
		else
		{
			sCH__MON_PART_DEF_TYPE->Set__DATA("MANUAL");

		}
	}
	
	// PUMP.IO ...
	{
		// DI.PUMP_POWER_STS 
		{
			def_name = "CH__DI_PUMP_POWER_SNS";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__DI_PUMP_POWER_SNS = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_PUMP_POWER_SNS, obj_name,var_name);
			}
		}

		// DI.PUMP_VAC_SNS 
		{
			def_name = "CH__DI_PUMP_VAC_SNS";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__DI_PUMP_VAC_SNS = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_PUMP_VAC_SNS, obj_name,var_name);
			}
		}

		// AI.PUMP_PRESSURE_TORR
		{
			def_name = "CH__AI_PUMP_PRESSURE_TORR";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		
			def_check = x_utility.Check__Link(ch_name);
			bActive__AI_PUMP_PRESSURE_TORR = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_PUMP_PRESSURE_TORR, obj_name,var_name);
			}
		}
		// AI.PUMP_PRESSURE_mTORR
		{
			def_name = "CH__AI_PUMP_PRESSURE_mTORR";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__AI_PUMP_PRESSURE_mTORR = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_PUMP_PRESSURE_mTORR, obj_name,var_name);
			}
		}
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__PMP_IO::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	int flag = -1;

	// ...
	{
		CString log_msg;

		CString upper_obj_name = p_ext_mode_ctrl->Get__UPPER_OBJECT_NAME();

		if(upper_obj_name.GetLength() > 0)			log_msg.Format("Start [%s] ... by %s", mode, upper_obj_name);
		else										log_msg.Format("Start [%s] ... ", mode);
		
		sCH__OBJ_MSG->Set__DATA(log_msg);

		log_msg += "\n";
		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		     IF__CTRL_MODE(sMODE__INIT)			flag = Call__INIT(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__LOCAL)		flag = Call__LOCAL(p_variable);
		ELSE_IF__CTRL_MODE(sMODE_REMOTE)		flag = Call__REMOTE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__PUMP_ON)		flag = Call__PUMP_ON(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PUMP_OFF)		flag = Call__PUMP_OFF(p_variable);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xI_LOG_CTRL->WRITE__LOG(log_msg);	
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}
int CObj__PMP_IO::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATE_CHECK)		Fnc__STATE_CHECK(p_variable, p_alarm);

	return 1;
}

