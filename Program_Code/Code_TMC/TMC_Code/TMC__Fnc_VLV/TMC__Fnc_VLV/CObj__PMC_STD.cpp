#include "StdAfx.h"
#include "CObj__PMC_STD.h"
#include "CObj__PMC_STD__DEF.h"


//-------------------------------------------------------------------------
CObj__PMC_STD::CObj__PMC_STD()
{

}
CObj__PMC_STD::~CObj__PMC_STD()
{

}

//-------------------------------------------------------------------------
int CObj__PMC_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,  "INIT");
		ADD__CTRL_VAR(sMODE__MAINT, "MAINT");

		ADD__CTRL_VAR(sMODE__SV_CLOSE,      "SV_CLOSE");
		ADD__CTRL_VAR(sMODE__INIT_SV_CLOSE, "INIT_SV_CLOSE");

		ADD__CTRL_VAR(sMODE__SV_OPEN, "SV_OPEN");
	}
	return 1;
}
int CObj__PMC_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

int CObj__PMC_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;
	
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString def_name, def_data;

	// ...
	{
		def_name = "PM_SIZE";
		p_variable->Get__DEF_CONST_DATA(def_name, def_data);		
		m_nPM_LIMIT = atoi(def_data);

		if(m_nPM_LIMIT <= 0)	m_nPM_LIMIT = CFG_PMx__SIZE;
	}

	// ...
	{
		str_name = "OTR.IN.PARA.aPMC.ID";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"id",0,1,m_nPM_LIMIT,"");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PMC_ID, str_name);
	}

	return 1;
}
int CObj__PMC_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	return 1;
}

//-------------------------------------------------------------------------
int CObj__PMC_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString str_name;
	
	// VLV OBJECT
	{
		def_name = "OBJ__PM_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		pPM_VLV__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(def_data);

		str_name = "OTR.IN.PARA.aPMC.ID";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_PMC_ID, def_data,str_name);
	}

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__PMC_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	CString para__pmc_id;
	int i__pmc_id;

	// ...
	{
		aCH__PARA_PMC_ID->Get__DATA(para__pmc_id);
		aEXT_CH__PARA_PMC_ID->Set__DATA(para__pmc_id);

		i__pmc_id = atoi(para__pmc_id);
	}

	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s] (%1d)",mode,i__pmc_id);

		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	int flag = -1;

	// ...
	{
		IF__CTRL_MODE(sMODE__INIT)
		{
			flag = Call__INIT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__MAINT)
		{
			flag = Call__MAINT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__SV_CLOSE)
		{
			flag = Call__SV_CLOSE(p_variable,p_alarm,i__pmc_id);
		}
		ELSE_IF__CTRL_MODE(sMODE__INIT_SV_CLOSE)
		{
			flag = Call__INIT_SV_CLOSE(p_variable,p_alarm,i__pmc_id);
		}
		ELSE_IF__CTRL_MODE(sMODE__SV_OPEN)
		{
			flag = Call__SV_OPEN(p_variable,p_alarm,i__pmc_id);
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
int CObj__PMC_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{
	return 1;
}
