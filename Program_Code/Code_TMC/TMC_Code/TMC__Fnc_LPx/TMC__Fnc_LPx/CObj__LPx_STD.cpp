#include "StdAfx.h"
#include "CObj__LPx_STD.h"


//-------------------------------------------------------------------------
CObj__LPx_STD::CObj__LPx_STD()
{

}
CObj__LPx_STD::~CObj__LPx_STD()
{

}

//-------------------------------------------------------------------------
int CObj__LPx_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		ADD__CTRL_VAR(sMODE__PREPLOAD, "PREPLOAD");
		ADD__CTRL_VAR(sMODE__LOAD,     "LOAD");

		ADD__CTRL_VAR(sMODE__RLSUNLOAD, "RLSUNLOAD");
		ADD__CTRL_VAR(sMODE__UNLOAD,    "UNLOAD");

		ADD__CTRL_VAR(sMODE__CLAMP,   "CLAMP");
		ADD__CTRL_VAR(sMODE__UNCLAMP, "UNCLAMP");

		ADD__CTRL_VAR(sMODE__CID_READ,      "CID_READ");
		ADD__CTRL_VAR(sMODE__RF_PAGE_READ,  "PAGE_READ");
		ADD__CTRL_VAR(sMODE__RF_CID_WRITE,  "RF_CID_WRITE");
		ADD__CTRL_VAR(sMODE__RF_PAGE_WRITE, "RF_PAGE_WRITE");

		ADD__CTRL_VAR(sMODE__MAP, "MAP");

		ADD__CTRL_VAR(sMODE__EXTENDPADDLE,   "EXTENDPADDLE");
		ADD__CTRL_VAR(sMODE__RETRACTPADDLE,  "RETRACTPADDLE");
		ADD__CTRL_VAR(sMODE__PADDLEDOWN,     "PADDLEDOWN");
		ADD__CTRL_VAR(sMODE__PADDLEUP,       "PADDLEUP");
		ADD__CTRL_VAR(sMODE__LATCH,          "LATCH");
		ADD__CTRL_VAR(sMODE__UNLATCH,        "UNLATCH");
		ADD__CTRL_VAR(sMODE__CLOSEDOOR,      "CLOSEDOOR");
		ADD__CTRL_VAR(sMODE__OPENDOOR,       "OPENDOOR");
		ADD__CTRL_VAR(sMODE__VACON,          "VACON");
		ADD__CTRL_VAR(sMODE__VACOFF,         "VACOFF");
		ADD__CTRL_VAR(sMODE__EXTENDSHUTTLE,  "SHUTTLEOUT");
		ADD__CTRL_VAR(sMODE__RETRACTSHUTTLE, "SHUTTLEIN");
	}
	return 1;
}
int CObj__LPx_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define APP_DSP__SHUTTLE_STS			"UNKNOWN  UNLOAD  LOAD"
#define APP_DSP__DOOR_STS				"UNKNOWN  CLOSE   OPEN"
#define APP_DSP__CST_STS				"UNKNOWN  EXIST   NONE"
#define APP_DSP__CLAMP_STS				"UNKNOWN  UNCLAMP  CLAMP"

#define APP_DSP__CFG_CST_INIT_MODE		"FULL  EMPTY  RANDOM"
#define APP_DSP__CFG_CST_MATERIAL_SIZE	"300mm  200mm"

#define APP_DSP__DISABLE_ENABLE			"DISABLE  ENABLE"


int CObj__LPx_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString dsc_item_list;
	int i;

	// ...
	{
		str_name = "PIO.TRANSFER";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__PIO_TRANSFER,str_name);

		str_name = "SHUTTLE.STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__SHUTTLE_STS,"");
		LINK__VAR_DIGITAL_CTRL(dCH__SHUTTLE_STATUS,str_name);

		str_name = "CST.STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__CST_STS,"");
		LINK__VAR_DIGITAL_CTRL(dCH__CST_STATUS,str_name);

		str_name = "CLAMP.STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__CLAMP_STS,"");
		LINK__VAR_DIGITAL_CTRL(dCH__CLAMP_STATUS,str_name);

		str_name = "DOOR.STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__DOOR_STS,"");
		LINK__VAR_DIGITAL_CTRL(dCH__DOOR_STATUS,str_name);

		str_name = "CID.STRING";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__CID_STRING,str_name);
	}

	// ...
	{
		p_variable->Get__STD_DESCRIPTION(DSP__SLOT_STATUS,dsc_item_list);

		for(i=0;i<CFG_LP_MAX_SLOT;i++)
		{
			str_name.Format("SLOT%002d.STATUS",i+1);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name,dsc_item_list,"");

			LINK__VAR_DIGITAL_CTRL(dCH__SLOT_STATUS[i],str_name);
		}

		// ...
		str_name = "CFG.CST.INIT.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__CFG_CST_INIT_MODE,"");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_CST_INIT_MODE,str_name);

		str_name = "CFG.CST.MATERIAL.SIZE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__CFG_CST_MATERIAL_SIZE,"");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_CST_MATERIAL_SIZE,str_name);

		str_name = "CFG.LPn.ID.READER.DISABLE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_LPn_ID_Reader_Disable,str_name);

		str_name = "CFG.dUNDOCK.POSITION.TAG.READ";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"FALSE TRUE","rec:TRUE");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_UNDOCK_POSITION_TAG_READ,str_name);
	}

	return 1;
}

int CObj__LPx_STD::__DEFINE__ALARM(p_alarm)
{

	return 1;
}

//-------------------------------------------------------------------------
int CObj__LPx_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString str_name;

	// LPx_ID
	{
		def_name = "LPx.ID";
		p_variable->Get__DEF_CONST_DATA(def_name,def_data);

		iLPx_ID = atoi(def_data);
	}

	// OBJ__LPx
	{
		def_name = "OBJ.LPx";
		p_variable->Get__DEF_CONST_DATA(def_name,def_data);

		pLPx__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(def_data);
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
int CObj__LPx_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	// ...
	{
		CString log_msg;

		log_msg.Format("Start ... :  [%s]", mode);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	int flag = -1;

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PREPLOAD)				flag = Call__PREPLOAD(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__LOAD)					flag = Call__LOAD(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__RLSUNLOAD)			flag = Call__RLSUNLOAD(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__UNLOAD)				flag = Call__UNLOAD(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__CLAMP)				flag = Call__CLAMP(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__UNCLAMP)				flag = Call__UNCLAMP(mode,p_variable);

		ELSE_IF__CTRL_MODE(sMODE__CID_READ)				flag = Call__CID_READ(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__RF_PAGE_READ)			flag = Call__RF_PAGE_READ(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__RF_CID_WRITE)			flag = Call__RF_CID_WRITE(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__RF_PAGE_WRITE)		flag = Call__RF_PAGE_WRITE(mode,p_variable);

		ELSE_IF__CTRL_MODE(sMODE__MAP)					flag = Call__MAP(mode,p_variable);

		ELSE_IF__CTRL_MODE(sMODE__EXTENDPADDLE)			flag = Call__EXTENDPADDLE(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__RETRACTPADDLE)		flag = Call__RETRACTPADDLE(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PADDLEDOWN)			flag = Call__PADDLE_DOWN(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PADDLEUP)				flag = Call__PADDLE_UP(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__LATCH)				flag = Call__LATCH(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__UNLATCH)				flag = Call__UNLATCH(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__CLOSEDOOR)			flag = Call__CLOSEDOOR(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__OPENDOOR)				flag = Call__OPENDOOR(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__VACON)				flag = Call__VACON(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__VACOFF)				flag = Call__VACOFF(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__EXTENDSHUTTLE)		flag = Call__EXTENDSHUTTLE(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__RETRACTSHUTTLE)		flag = Call__RETRACTSHUTTLE(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__HALT)					flag = Call__HALT(mode,p_variable);

		else									
		{

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

int CObj__LPx_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
