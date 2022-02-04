#include "StdAfx.h"
#include "CObj__VAC_VLV_FNC.h"


//-------------------------------------------------------------------------
CObj__VAC_VLV_FNC::CObj__VAC_VLV_FNC()
{

}
CObj__VAC_VLV_FNC::~CObj__VAC_VLV_FNC()
{

}

//-------------------------------------------------------------------------
int CObj__VAC_VLV_FNC::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ....
	{
		ADD__CTRL_VAR(sMODE__ALL_CLOSE,     "ALL_CLOSE");
		ADD__CTRL_VAR(sMODE__FR_SR_CLOSE,   "FR_SR_CLOSE");

		ADD__CTRL_VAR(sMODE__SR_OPEN,		"SR_OPEN");
		ADD__CTRL_VAR(sMODE__SR_CLOSE,		"SR_CLOSE");

		ADD__CTRL_VAR(sMODE__FR_OPEN_ALL,	"FR_OPEN");
		ADD__CTRL_VAR(sMODE__FR_OPEN_IO,	"FR_OPEN.IO");
		ADD__CTRL_VAR(sMODE__FR_CLOSE,		"FR_CLOSE");

		ADD__CTRL_VAR(sMODE__EXHAUST_OPEN,  "EXHAUST_OPEN");
		ADD__CTRL_VAR(sMODE__EXHAUST_CLOSE, "EXHAUST_CLOSE");

		//
		ADD__CTRL_VAR(sMODE__APC_OPEN,		"APC_OPEN");
		ADD__CTRL_VAR(sMODE__APC_CLOSE,		"APC_CLOSE");
		ADD__CTRL_VAR(sMODE__APC_POSITION,  "APC_POSITION");

		//
		ADD__CTRL_VAR(sMODE__APC_BALLAST_CTRL,	"APC_BALLAST_CTRL");
		ADD__CTRL_VAR(sMODE__APC_BALLAST_POS,	"APC_BALLAST_POS");
	}
	return 1;
}
int CObj__VAC_VLV_FNC::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__STATE_CHECK						1


int CObj__VAC_VLV_FNC::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name, item_list;

	// OBJ ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// PARA ...
	{
		str_name = "PARA.APC_POSITION";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 1, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_APC_POSITION, str_name);
	}

	// MON ...
	{
		str_name = "MON.PUMPING.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PUMPING_STATE, str_name);

		//
		str_name = "APC.BALLAST.MODE";
		STD__ADD_DIGITAL(str_name, "CHAMBER TRANSFER");
		LINK__VAR_DIGITAL_CTRL(dCH__APC_BALLAST_MODE, str_name);

		str_name = "XFER.BALLAST_WAIT_SKIP.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_XFER_BALLAST_WAIT_SKIP_FLAG, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3, MON_ID__STATE_CHECK);
	}
	return 1;
}

int CObj__VAC_VLV_FNC::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s : ",sObject_Name);

	// ...
	{

	}
	return 1;
}

int CObj__VAC_VLV_FNC::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	// ...
	{

	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__VAC_VLV_FNC::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{	
	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name,12*1,60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	CString def_name;
	CString ch_name;
	CString obj_name;
	CString var_name;

	// External Object Link
	{
		//
		{
			def_name = "OBJ__VAC_VLV";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

			pOBJ_CTRL__VAC_VLV = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "MON.PUMPING.STATE";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__VAC_VLV__MON_PUMPING_STATE, obj_name,var_name);
		}

		//
		{
			def_name = "OBJ__APC_VLV";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

			pOBJ_CTRL__APC_VLV = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.PRESSURE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_VLV__PARA_PRESSURE, obj_name,var_name);

			var_name = "PARA.POSITION";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_VLV__PARA_POSITION, obj_name,var_name);

			var_name = "MON.POSITION";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__APC_VLV__MON_POSITION, obj_name,var_name);
		}
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__VAC_VLV_FNC::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	int flag = -1;

	// ...
	{
		     IF__CTRL_MODE(sMODE__ALL_CLOSE)			flag = Call__ALL_CLOSE(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__FR_SR_CLOSE)			flag = Call__FR_SR_CLOSE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__SR_OPEN)				flag = Call__SR_OPEN(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__SR_CLOSE)				flag = Call__SR_CLOSE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__FR_OPEN_ALL)			flag = Call__FR_OPEN(p_variable,  1);
		ELSE_IF__CTRL_MODE(sMODE__FR_OPEN_IO)			flag = Call__FR_OPEN(p_variable, -1);
		ELSE_IF__CTRL_MODE(sMODE__FR_CLOSE)				flag = Call__FR_CLOSE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__EXHAUST_OPEN)			flag = Call__EXHAUST_OPEN(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__EXHAUST_CLOSE)		flag = Call__EXHAUST_CLOSE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__APC_OPEN)				flag = Call__APC_OPEN(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__APC_CLOSE)			flag = Call__APC_CLOSE(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__APC_POSITION)			flag = Call__APC_POSITION(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__APC_BALLAST_CTRL)		flag = Call__APC_BALLAST_CTRL(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__APC_BALLAST_POS)		flag = Call__APC_BALLAST_POS(p_variable);
	}

	// ...
	{
		sCH__PARA_XFER_BALLAST_WAIT_SKIP_FLAG->Set__DATA("");
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);			
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}

int CObj__VAC_VLV_FNC::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATE_CHECK)		return Mon__STATE_CHECK(p_variable,p_alarm);

	return 1;
}
