#include "StdAfx.h"
#include "CObj__MFC_IO__DEF.h"
#include "CObj__MFC_IO.h"

#include "CCommon_Utility.h"


//--------------------------------------------------------------------------------
CObj__MFC_IO::CObj__MFC_IO()
{
	pII_ALARM = NULL;
}
CObj__MFC_IO::~CObj__MFC_IO()
{

}

//--------------------------------------------------------------------------------
int CObj__MFC_IO::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__TEST_1, "TEST.1");
	}
	return 1;
}
int CObj__MFC_IO::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}


// ...
#define MON_ID__MONITOR									1


int CObj__MFC_IO::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	// ...
	CString def_name;
	CString def_data;
	CString obj_name;
	CString var_name;
	CString ch_name;
	int i;
	int k;

	// ...
	CCommon_Utility x_utility;
	bool def_check;

	// OBJ ...
	{
		var_name = "OBJ.MSG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, var_name);
	}

	// OBJ.MFC_SIZE ...
	{
		def_name = "OBJ.MFC_SIZE";
		p_variable->Get__DEF_CONST_DATA(def_name, def_data);

		iSIZE__MFC_OBJ = atoi(def_data);
		if(iSIZE__MFC_OBJ > CFG_SIZE__MFC_OBJ)			iSIZE__MFC_OBJ = CFG_SIZE__MFC_OBJ;

		//
		sList_Channel__MFC_DO_VLV_IN.RemoveAll();
		sList_Channel__MFC_DO_VLV_OUT.RemoveAll();
		sList_Channel__MFC_DO_VLV_PURGE.RemoveAll();

		for(i=0; i<iSIZE__MFC_OBJ; i++)
		{
			int mfc_id = i + 1;

			//
			def_name.Format("CH__DO_VLV_IN.%1d", mfc_id);
			p_variable->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);

			if(def_check)		sList_Channel__MFC_DO_VLV_IN.Add(ch_name);
			else				sList_Channel__MFC_DO_VLV_IN.Add("");

			//
			def_name.Format("CH__DO_VLV_OUT.%1d", mfc_id);
			p_variable->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);

			if(def_check)		sList_Channel__MFC_DO_VLV_OUT.Add(ch_name);
			else				sList_Channel__MFC_DO_VLV_OUT.Add("");

			//
			def_name.Format("CH__DO_VLV_PURGE.%1d", mfc_id);
			p_variable->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);

			if(def_check)		sList_Channel__MFC_DO_VLV_PURGE.Add(ch_name);
			else				sList_Channel__MFC_DO_VLV_PURGE.Add("");
		}
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__MONITOR);
	}
	return 1;
}
int CObj__MFC_IO::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	int	alarm_id;
	CString	alarm_title;
	CString	alarm_msg;
	CString alarm_bff;
	CStringArray l_act;
	int i;

	// MFCx Flow Setting ...
	for(i=0;i<CFG_SIZE__MFC_OBJ;i++)
	{
		alarm_id = ALID__MFCx_FLOW_INTERLOCK + i;

		alarm_bff.Format("Interlock: MFC%1d Flow Setting", i+1);	
		alarm_title  = title;
		alarm_title += alarm_bff;

		alarm_msg.Format("Can not set MFC%1d's flow. \n", i+1);

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// MFCx Primary Valve -> Open ...
	for(i=0;i<CFG_SIZE__MFC_OBJ;i++)
	{
		alarm_id = ALID__MFCx_PRIMARY_VLV_OPEN_INTERLOCK + i;

		alarm_bff.Format("Interlock: MFC%1d's Primary Valve Open", i+1);	
		alarm_title  = title;
		alarm_title += alarm_bff;

		alarm_msg.Format("MFC%1d의 primary-valve를 Open 할 수 없습니다. \n", i+1);

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// MFCx Secondary Valve -> Open ...
	for(i=0;i<CFG_SIZE__MFC_OBJ;i++)
	{
		alarm_id = ALID__MFCx_SECONDARY_VLV_OPEN_INTERLOCK + i;

		alarm_bff.Format("Interlock: MFC%1d's Secondary Valve Open", i+1);	
		alarm_title  = title;
		alarm_title += alarm_bff;

		alarm_msg.Format("Can not open MFC%1d's secondary valve. \n", i+1);

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// MFCx Purge Valve -> Open ...
	for(i=0;i<CFG_SIZE__MFC_OBJ;i++)
	{
		alarm_id = ALID__MFCx_PURGE_VLV_OPEN_INTERLOCK + i;

		alarm_bff.Format("Interlock: MFC%1d's Purge Valve Open", i+1);	
		alarm_title  = title;
		alarm_title += alarm_bff;

		alarm_msg.Format("MFC%1d의 purge-valve를 Open 할 수 없습니다. \n", i+1);

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// MFC Value Interlock ...
	for(i=0;i<CFG_SIZE__MFC_OBJ;i++)
	{
		alarm_id = ALID__MFCx_VALUE_INTERLOCK + i;

		alarm_bff.Format("Value Interlock: MFC%1d's Valve Open Interlock !", i+1);	
		alarm_title  = title;
		alarm_title += alarm_bff;

		alarm_msg.Format("MFC%1d's all valve will be closed ! \n", i+1);

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// Gas Box Not Closed Interlock ...
	for(i=0;i<CFG_SIZE__MFC_OBJ;i++)
	{
		alarm_id = ALID__GAS_BOX_NOT_CLOSED_INTERLOCK + i;

		alarm_bff.Format("Gas Box Door Not Closed - Interlock: MFC%1d's Valve Open Interlock !", i+1);	
		alarm_title  = title;
		alarm_title += alarm_bff;

		alarm_msg.Format("MFC%1d's all valve will be closed ! \n", i+1);

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	return 1;
}


//--------------------------------------------------------------------------------
#define LINK__CHANNEL(CLS_CH)							\
ch_name.Format("%s+%s",obj_name,var_name);				\
CLS_CH->Register__CHANNEL_NAME(ch_name);


int CObj__MFC_IO::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	// ...
	{
		CString file_name;
		CString log_msg;

		// APP Log ...
		{
			file_name.Format("%s__APP.log", sObject_Name);

			log_msg  = "\n\n";
			log_msg += "//------------------------------------------------------------------------";

			xI__APP_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
			xI__APP_LOG_CTRL->SET__PROPERTY(file_name,12*1,60);

			xI__APP_LOG_CTRL->DISABLE__TIME_LOG();
			xI__APP_LOG_CTRL->WRITE__LOG(log_msg);

			xI__APP_LOG_CTRL->ENABLE__TIME_LOG();
			xI__APP_LOG_CTRL->WRITE__LOG("   START   \n");
		}
	}

	// ...
	CString def_name;
	CString def_data;
	CString obj_name;
	CString var_name;
	CString ch_name;
	int i;
	int k;

	// ...
	CCommon_Utility x_utility;
	bool def_check;

	// OBJ.MFC_SIZE ...
	{
		def_name = "OBJ.MFC_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iSIZE__MFC_OBJ = atoi(def_data);
		if(iSIZE__MFC_OBJ > CFG_SIZE__MFC_OBJ)			iSIZE__MFC_OBJ = CFG_SIZE__MFC_OBJ;

		//
		for(i=0; i<iSIZE__MFC_OBJ; i++)
		{
			int mfc_id = i + 1;

			// VLV.IN ...
			{
				def_name.Format("CH__DO_VLV_IN.%1d", mfc_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				def_check = x_utility.Check__Link(ch_name);
				bActive__MFC_DO_VLV_IN_X[i] = def_check;

				if(def_check)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__MFC_DO_VLV_IN_X[i], obj_name,var_name);
				}
			}

			// VLV.OUT ...
			{
				def_name.Format("CH__DO_VLV_OUT.%1d", mfc_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				def_check = x_utility.Check__Link(ch_name);
				bActive__MFC_DO_VLV_OUT_X[i] = def_check;

				if(def_check)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__MFC_DO_VLV_OUT_X[i], obj_name,var_name);
				}
			}

			// VLV.PURGE ...
			{
				def_name.Format("CH__DO_VLV_PURGE.%1d", mfc_id);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				def_check = x_utility.Check__Link(ch_name);
				bActive__MFC_DO_VLV_PURGE_X[i] = def_check;

				if(def_check)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__MFC_DO_VLV_PURGE_X[i], obj_name,var_name);
				}
			}
		}
	}

	// OBJ DB_SUS ...
	{
		def_name = "OBJ__DB_SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		for(i=0; i<iSIZE__MFC_OBJ; i++)
		{
			for(k=0; k<CFG_INTERLOCK__MFC_SIZE; k++)
			{
				var_name.Format("CFG.INTERLOCK.MFC%1d.MFC_TYPE%1d", i+1,k+1);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_INTERLOCK_MFC_TYPE[i][k], obj_name,var_name);
			}
		}
	}

	// LINK IO ...
	{
		def_name = "CH__GAS_BOX_COVER.DI_CHANNEL";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(diEXT_CH__GAS_BOX_CONVER, obj_name,var_name);

		def_name = "DATA__GAS_BOX_COVER.NORMAL_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
		sGAS_BOX_COVER__NORMAL_STATE = def_data;
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__MFC_IO
::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	CString msg;

	// ...
	{
		msg.Format("%s Started...",mode);
		sCH__OBJ_MSG->Set__DATA(msg);

		xI__APP_LOG_CTRL->WRITE__LOG(msg);
	}

	int flag = -1;

	// ...
	{
		IF__CTRL_MODE(sMODE__TEST_1)			flag = Call__TEST_1(p_variable, p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		msg.Format("%s Aborted (%1d)", mode, flag);
	}
	else
	{
		msg.Format("%s Completed (%1d)", mode, flag);
	}	

	// ...
	{
		sCH__OBJ_MSG->Set__DATA(msg);

		xI__APP_LOG_CTRL->WRITE__LOG(msg);
	}
	return flag;
}

int CObj__MFC_IO::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == MON_ID__MONITOR)			Mon__MONITOR(p_variable,p_alarm);

	return 1;
}
