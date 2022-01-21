#include "StdAfx.h"
#include "CObj__VIRTUAL_TYPE.h"


//--------------------------------------------------------------------------------
CObj__VIRTUAL_TYPE::CObj__VIRTUAL_TYPE()
{

}
CObj__VIRTUAL_TYPE::~CObj__VIRTUAL_TYPE()
{

}

//--------------------------------------------------------------------------------
int CObj__VIRTUAL_TYPE::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,             "INIT");

		ADD__CTRL_VAR(sMODE__MULTI_PAGE_READ,  "MULTI_PAGE_READ");
		ADD__CTRL_VAR(sMODE__PAGE_READ,        "PAGE_READ");
		ADD__CTRL_VAR(sMODE__MID_READ,		   "CID_READ");

		ADD__CTRL_VAR(sMODE__MULTI_PAGE_WRITE, "MULTI_PAGE_WRITE");
		ADD__CTRL_VAR(sMODE__PAGE_WRITE,       "RF_PAGE_WRITE");
		ADD__CTRL_VAR(sMODE__MID_WRITE,        "RF_CID_WRITE");		
	}
	return 1;
}
int CObj__VIRTUAL_TYPE::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}


// ...
#define  MON_ID__IO_MONITOR									2

// ...
#define APP_DSP__COMM_STS									\
	"OFFLINE  ONLINE"

#define APP_DSP__OFF_ON										\
	"OFF  ON"

#define APP_DSP__FAILURE_CODE								\
	"NONE AUTOFAIL EXFAIL WRITEFAIL NOTAG						\
INVALID1 UNKNOWN UNCONFIG CHECK VOIDACKN LOCKED MSGLEN		\
INVALID2 NOACKN"


int CObj__VIRTUAL_TYPE::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// ...
	{
		str_name = "sAPP.COMM.STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__COMM_STS,str_name);

		str_name = "sMSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MSG,str_name);
	}

	// ...
	{
		str_name = "PAGE1.NUM";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"num",0,1,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__PAGE1_NUM,str_name);

		str_name = "PAGE2.NUM";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"num",0,1,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__PAGE2_NUM,str_name);

		//
		str_name = "READ_PAGE.DATA";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__READ_PAGE_DATA,str_name);

		str_name = "WRITE_PAGE.DATA";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__WRITE_PAGE_DATA,str_name);
	}

	// ...
	{
		str_name = "OTR.OUT.MON.sCID.STRING";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__READ_MID_PAGE_DATA,str_name);

		str_name = "OTR.IN.dLP.FA.MODE";
		STD__ADD_DIGITAL(str_name, "MANUAL AUTO");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_LP__FA_MODE,str_name);

		str_name = "OTR.IN.dLP.FA.SERVICE.MODE";
		STD__ADD_DIGITAL(str_name, "NO YES");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_LP__FA_SERVICE_MODE,str_name);
	}

	// ...
	{
		str_name = "WRITE_MID_PAGE.DATA";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__WRITE_MID_PAGE_DATA,str_name);

		str_name = "CFG.dREAD.PAGE1.AND.2.ONLY";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "FALSE TRUE", "");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_READ_PAGE1_AND_2_ONLY,str_name);

		str_name = "CFG.dTAG.READ.ID.INSTALLED";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "FALSE TRUE", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_TAG_READ_ID_INSTALLED_CHECK_SKIP,str_name);
	}

	// Parameters ...
	{
		str_name = "CFG.dTAG.PARAM.READ.MODE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "", 0, 0, 2, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TAG_PARAM_READ_MODE,str_name);

		str_name = "CFG.dTAG.PARAM.READ.PAGE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "", 0, 1, 17, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TAG_PARAM_READ_PAGE,str_name);

		str_name = "CFG.dTAG.PARAM.RS232.MAX.REPEAT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "", 0, 0, 99, "10");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TAG_PARAM_RS232_MAX_REPEAT,str_name);

		str_name = "CFG.dTAG.PARAM.RS232.REPEAT.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 99, "20");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TAG_PARAM_RS232_REPEAT_TIME,str_name);

		str_name = "CFG.dTAG.PARAM.RW.MAX.REPEAT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 99, "10");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TAG_PARAM_RW_MAX_REPEAT,str_name);

		str_name = "CFG.dTAG.PARAM.RW.REPEAT.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 99, "20");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TAG_PARAM_RW_REPEAT_TIME,str_name);

		str_name = "CFG.dTAG.PARAM.WATCH.PORT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 1, "0");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TAG_PARAM_WATCH_PORT,str_name);

		str_name = "dDEVICE.ADDRESS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "0 1 2 3 4 5 6 7 8 9 A B C D E F", "");
		LINK__VAR_DIGITAL_CTRL(dCH__DEVICE_ADDRESS,str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(7.0,MON_ID__IO_MONITOR);
	}
	return 1;
}

int CObj__VIRTUAL_TYPE::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	return 1;
}

int CObj__VIRTUAL_TYPE::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	CString str_name;
	int i;


	// Digital
	{
		// DO  -----------------------------
		{
			str_name = "edo.HEART.BEAT";
			IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__HEART_BEAT, str_name);
		}

		// DI  -----------------------------
		{
			str_name = "edi.COMM.STS";
			IO__ADD_DIGITAL_READ(str_name, APP_DSP__COMM_STS);
			LINK__IO_VAR_DIGITAL_CTRL(diCH__COMM_STS, str_name);

			str_name = "edi.FAILURE.CODE";
			IO__ADD_DIGITAL_READ(str_name, APP_DSP__FAILURE_CODE);
			LINK__IO_VAR_DIGITAL_CTRL(diCH__FAILURE_CODE, str_name);
		}
	}

	// String
	{
		// SO  -----------------------------
		{
			for(i=0; i<CFG__PAGE_SIZE; i++)
			{
				str_name.Format("eso.WRITE.PAGE.DATA%02d",i+1);
				IO__ADD_STRING_WRITE(str_name);
				LINK__IO_VAR_STRING_CTRL(soCH__WRITE_PAGE_DATA[i], str_name);
			}
		}

		// SI  -----------------------------
		{
			for(i=0; i<CFG__PAGE_SIZE; i++)
			{
				str_name.Format("esi.READ.PAGE.DATA%02d",i+1);
				IO__ADD_STRING_READ__MANUAL(str_name);
				LINK__IO_VAR_STRING_CTRL(siCH__READ_PAGE_DATA[i], str_name);
			}
		}
	}

	return 1;
}

//--------------------------------------------------------------------------------
int CObj__VIRTUAL_TYPE::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString str_name;

	m_nCommState = OFFLINE;
	m_Rcv_Time	 = 5000;

	iFlag_Log =  1;
	iSim_Flag = -1;

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		if(x_seq_info->Is__SIMULATION_MODE() > 0)
		{
			iSim_Flag =  1;		
		}
		else
		{
			iSim_Flag = -1;
		}
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
int CObj__VIRTUAL_TYPE::__INITIALIZE__IO(p_io_para)
{
	// ...
	{
		m_Term_Str[0] = CR;	
		m_Term_Str[1] = 0;

		sSTR__ERROR_VALUE = "NONE";
	}

	diCH__COMM_STS->Set__DATA("ONLINE");
	return 1;
}

//--------------------------------------------------------------------------------
int CObj__VIRTUAL_TYPE::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]",mode);

		Fnc__LOG(log_msg);
		Fnc__MSG(log_msg);
	}

	int flag = -1;

	// ...
	{
		     IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__MULTI_PAGE_READ)		flag = Call__MULTI_PAGE_READ(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PAGE_READ)			flag = Call__PAGE_READ(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__MULTI_PAGE_WRITE)		flag = Call__MULTI_PAGE_WRITE(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PAGE_WRITE)			flag = Call__PAGE_WRITE(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__MID_WRITE)			flag = Call__MID_WRITE(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__MID_READ)				flag = Call__MID_READ(p_variable,p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		Fnc__LOG(log_msg);
		Fnc__MSG(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		Fnc__LOG(log_msg);
		Fnc__MSG(log_msg);
	}

	return flag;
}

int CObj__VIRTUAL_TYPE::__CALL__MONITORING(id, p_variable, p_alarm)
{
	switch(id)
	{
		case MON_ID__IO_MONITOR:
			Mon__IO_MONITOR(p_variable,p_alarm);
			break;
	}

	return 1;
}
