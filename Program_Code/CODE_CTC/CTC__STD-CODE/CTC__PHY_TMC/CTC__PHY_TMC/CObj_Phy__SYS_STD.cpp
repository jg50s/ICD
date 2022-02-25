#include "StdAfx.h"
#include "CObj_Phy__SYS_STD.h"

#include "CCommon_System.h"


//-------------------------------------------------------------------------
CObj_Phy__SYS_STD::CObj_Phy__SYS_STD()
{

}
CObj_Phy__SYS_STD::~CObj_Phy__SYS_STD()
{

}

//-------------------------------------------------------------------------
int CObj_Phy__SYS_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__TIME_INIT,    "TIME_INIT");
		ADD__CTRL_VAR(sMODE__SYSTEM_INIT,  "SYSTEM_INIT");
		ADD__CTRL_VAR(sMODE__AUTO_INIT,    "AUTO_INIT");

		ADD__CTRL_VAR(sMODE__CTC_TO_TMC,   "CTC_TO_TMC");
		ADD__CTRL_VAR(sMODE__TMC_TO_CTC,   "TMC_TO_CTC");
		ADD__CTRL_VAR(sMODE__SYSTEM_MAINT, "SYSTEM_MAINT");

		ADD__CTRL_VAR(sMODE__JOB_START_READY, "JOB_START_READY");
	}
	return 1;
}

int CObj_Phy__SYS_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  MON_ID__OBJECT_STATUS					1

#define  DSP__MODE								\
"TIME_INIT  SYSTEM_INIT  AUTO_INIT				\
CTC_TO_TMC  TMC_TO_CTC  SYSTEM_MAINT			\
JOB_START_READY "


int CObj_Phy__SYS_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CString str_name;

	// ...
	{
		CString dsp_item;
		p_variable->Get__STD_DESCRIPTION("STD_OBJ_CTRL",dsp_item);

		str_name = "TMC_SYS.CTRL";
		STD__ADD_DIGITAL(str_name,dsp_item);
		LINK__VAR_DIGITAL_CTRL(xCH__OBJ_CTRL,str_name);

		dVAR__MODE = "TMC_SYS.MODE";
		STD__ADD_DIGITAL(dVAR__MODE,DSP__MODE);
	}

	// ...
	{
		CString dsp_item;
		p_variable->Get__STD_DESCRIPTION("STD_OBJ_STATUS",dsp_item);

		str_name = "OBJ.STATUS";
		STD__ADD_DIGITAL(str_name,dsp_item);
		LINK__VAR_DIGITAL_CTRL(xCH__OBJ_STATUS,str_name);

		str_name = "MODULE.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__MODULE_TIME,str_name);
	}

	// SIM CFG ...
	{
		str_name = "SCH_TEST.CFG.INIT.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_INIT_SEC, str_name);

		str_name = "SCH_TEST.CFG.CTC_TO_TMC.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_CTC_TO_TMC, str_name);

		str_name = "SCH_TEST.CFG.TMC_TO_CTC.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_TMC_TO_CTC, str_name);

		str_name = "SCH_TEST.CFG.SYSTEM_MAINT.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_SYSTEM_MAINT, str_name);

		str_name = "SCH_TEST.CFG.JOB_START_READY.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_JOB_START_READY, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__OBJECT_STATUS);
	}
	return 1;
}

int CObj_Phy__SYS_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;

	// ...
	ALARM_DEFINE__MODULE_OBJECT;

	// ...
	{
		alarm_title  = title;
		alarm_title += "OBJECT MODE : UNKNOWN";

		alarm_msg = "";
	
		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(ALID__OBJECT_MODE_UNKNOWN,alarm_title,alarm_msg,l_act);
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj_Phy__SYS_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	// ...
	{
		xI_Module_Obj->Link__ERROR_FEEDBACK(&mERROR__MODULE_OBJ);

		//
		xI_Module_Obj->Link__Object_Name(sObject_Name);

		xI_Module_Obj->Register__Module_Status_Channel(xCH__OBJ_STATUS->Get__VARIABLE_NAME());
		xI_Module_Obj->Register__Module_Mode_Channel(dVAR__MODE);
		xI_Module_Obj->Register__Module_Ctrl_Channel(xCH__OBJ_CTRL->Get__VARIABLE_NAME());

		xI_Module_Obj->Disable__CTCINUSE_TO_STANDBY();

		// ...
		{
			CString data_const;
			p_ext_obj_create->Get__DEF_CONST_DATA_EX("FLAG.REPORT_ABORTED_ALARM",data_const,-1);

			if(data_const.CompareNoCase(STR__DISABLE) == 0)
			{
				xI_Module_Obj->Disable__REPORT_ABORTED_ALARM();
			}
		}
	}

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xI_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xI_LOG_CTRL->SET__PROPERTY(file_name,24*7,60);

		xI_LOG_CTRL->DISABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG(log_msg);

		xI_LOG_CTRL->ENABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	CString def_name;
	CString def_data;
	CString obj_name;
	CString var_name;
	int i;

	// DB_CFG ...
	{
		def_name = "DB_CFG_NAME";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		//
		var_name = "SCH_TEST.CFG.TMC_DUMMY_BY_CTC";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC, obj_name,var_name);
	}

	// OBJ_EFEM_ROBOT ...
	{
		def_name = "OBJ_EFEM_ROBOT";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
		
		pOBJ_CTRL__EFEM_ROBOT = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}
	// OBJ_VAC_ROBOT ...
	{
		def_name = "OBJ_VAC_ROBOT";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
		
		pOBJ_CTRL__VAC_ROBOT = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}
	// OBJ_LPx ...
	{
		def_name = "LP_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iLP_SIZE = atoi(def_data);
		if(iLP_SIZE > CFG_LP_LIMIT)
			iLP_SIZE = CFG_LP_LIMIT;
		
		for(i=0; i<iLP_SIZE; i++)
		{
			def_name.Format("OBJ_LP%1d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

			pOBJ_CTRL__LPx[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
		}
	}
	// OBJ_ALx ...
	{
		def_name = "OBJ_AL1";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pOBJ_CTRL__AL1 = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}
	// OBJ_LLx ...
	{
		def_name = "LLx_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iLLx_SIZE = atoi(def_data);
		if(iLLx_SIZE > CFG_LLx_LIMIT)			iLLx_SIZE = CFG_LLx_LIMIT;
		
		for(i=0; i<iLLx_SIZE; i++)
		{
			def_name.Format("OBJ_LL%1d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

			pOBJ_CTRL__LLx[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
		}
	}
	// OBJ_TMC_CHM ...
	{
		def_name = "OBJ_TMC_CHM";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pOBJ_CTRL__TMC_CHM = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}
	// OBJ_PMx ...
	{
		def_name = "PM_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iPM_SIZE = atoi(def_data);
		if(iPM_SIZE > CFG_PM_LIMIT)
			iPM_SIZE = CFG_PM_LIMIT;

		for(i=0; i<iPM_SIZE; i++)
		{
			def_name.Format("OBJ_PM%1d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

			pOBJ_CTRL__PMx[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "SLIT.VLV.STS";
			LINK__EXT_VAR_DIGITAL_CTRL(pEXT_CH__PMx_SLIT_VLV[i], obj_name,var_name);
		}
	}

	iPRC_STS = -1;
	xCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
	return 1;
}

//-------------------------------------------------------------------------
int CObj_Phy__SYS_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	xI_Sync_Ctrl.Thread__LOCK();
	iPRC_STS = 1;

	xI_Module_Obj->Enable__ERROR_CHECK__NOT_STANDBY();

	// ...
	int flag = -1;

	// ...
	{
			 IF__CTRL_MODE(sMODE__TIME_INIT)			flag = Call__TIME_INIT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__SYSTEM_INIT)			flag = Call__SYSTEM_INIT(p_variable);
		
		ELSE_IF__CTRL_MODE(sMODE__AUTO_INIT)			flag = Call__AUTO_INIT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__CTC_TO_TMC)			flag = Call__CTC_TO_TMC(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__TMC_TO_CTC)			flag = Call__TMC_TO_CTC(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__SYSTEM_MAINT)			flag = Call__SYSTEM_MAINT(p_variable);
		
		ELSE_IF__CTRL_MODE(sMODE__JOB_START_READY)
		{
			xI_Module_Obj->Disable__ERROR_CHECK__NOT_STANDBY();

			flag = Call__JOB_START_READY(p_variable);
		}
		else
		{
			CString bff;
			CString alarm_msg;
			CString r_act;

			bff.Format("Object Name : %s\n",sObject_Name);
			alarm_msg  = bff;
			bff.Format("Unknown Object Mode : \"%s\"\n",mode);
			alarm_msg += bff;

			p_alarm->Popup__ALARM_With_MESSAGE(ALID__OBJECT_MODE_UNKNOWN,alarm_msg,r_act);		
		}
	}

	iPRC_STS = -1;
	xI_Sync_Ctrl.Thread__UNLOCK();

	return flag;
}

int CObj_Phy__SYS_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__OBJECT_STATUS:
			Mon__Obj_Status(p_variable,p_alarm);
			break;
	}

	return 1;
}
