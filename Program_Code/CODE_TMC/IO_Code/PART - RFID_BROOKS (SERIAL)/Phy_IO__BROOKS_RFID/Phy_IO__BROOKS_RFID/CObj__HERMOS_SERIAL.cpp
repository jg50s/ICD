#include "StdAfx.h"
#include "CObj__HERMOS_SERIAL.h"
#include "CObj__HERMOS_SERIAL__DEF.h"


//--------------------------------------------------------------------------------
CObj__HERMOS_SERIAL::CObj__HERMOS_SERIAL()
{

}
CObj__HERMOS_SERIAL::~CObj__HERMOS_SERIAL()
{

}

//--------------------------------------------------------------------------------
int CObj__HERMOS_SERIAL::__DEFINE__CONTROL_MODE(obj,l_mode)
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
int CObj__HERMOS_SERIAL::__DEFINE__VERSION_HISTORY(version)
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


int CObj__HERMOS_SERIAL::__DEFINE__VARIABLE_STD(p_variable)
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

		str_name = "MON.ACTIVE.FA.AUTO";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ACTIVE_FA_AUTO, str_name);
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

int CObj__HERMOS_SERIAL::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	//.....
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	//.....
	alarm_id = ALID__OFFLINE_ALARM_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : Offline [Full Auto]";

	alarm_msg  = "1. Check the Serial cable.\n";
	alarm_msg += "2. Check the RF Reader power.\n";

	l_act.RemoveAll();
	l_act.Add("CHECK");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);


	//.....
	alarm_id = ALID__OFFLINE_ALARM_NOT_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : Offline [Not Full Auto]";

	alarm_msg  = "1. Check the Serial cable.\n";
	alarm_msg += "2. Check the RF Reader power.\n";

	l_act.RemoveAll();
	l_act.Add("RETRY");
	l_act.Add("IGNORE");
	l_act.Add("ABORT");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__OFFLINE_ALARM;

	alarm_title  = title;
	alarm_title += "RF Reader : Offline";

	alarm_msg  = "1. Check the Serial cable.\n";
	alarm_msg += "2. Check the RF Reader power.\n";

	l_act.RemoveAll();
	l_act.Add("RETRY");
	l_act.Add("ABORT");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_AUTOFAIL;

	alarm_title  = title;
	alarm_title += "RF Reader : Auto Fail";

	alarm_msg = "1. Automatic reading is not possible.\n";

	l_act.RemoveAll();
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_AUTOFAIL_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : Auto Fail [Full Auto]";

	alarm_msg = "1. Automatic reading is not possible.\n";

	l_act.RemoveAll();
	l_act.Add("CHECK");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_AUTOFAIL_NOT_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : Auto Fail [Not Full Auto]";

	alarm_msg = "1. Automatic reading is not possible.\n";

	l_act.RemoveAll();
	l_act.Add("RETRY");
	l_act.Add("ABORT");
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_EXFAIL;

	alarm_title  = title;
	alarm_title += "RF Reader :  Ex-Fail";

	alarm_msg  = "1. read of write initiated from the terminal respectively other.\n";
	alarm_msg += "  actions cannot be carried out.\n";

	l_act.RemoveAll();
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_EXFAIL_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader :  Ex-Fail [Full Auto]";

	alarm_msg  = "1. read of write initiated from the terminal respectively other.\n";
	alarm_msg += "  actions cannot be carried out.\n";

	l_act.RemoveAll();
	l_act.Add("CHECK");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_EXFAIL_NOT_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader :  Ex-Fail [Not Full Auto]";

	alarm_msg  = "1. read of write initiated from the terminal respectively other.\n";
	alarm_msg += "  actions cannot be carried out.\n";

	l_act.RemoveAll();
	l_act.Add("RETRY");
	l_act.Add("ABORT");
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_WRITEFAIL;

	alarm_title  = title;
	alarm_title += "RF Reader :  Write-Fail";

	alarm_msg  = "1. data transfer to the tag not possible.\n";

	l_act.RemoveAll();
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_WRITEFAIL_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader :  Write-Fail [Full Auto]";

	alarm_msg  = "1. data transfer to the tag not possible.\n";

	l_act.RemoveAll();
	l_act.Add("CHECK");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_WRITEFAIL_NOT_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader :  Write-Fail [Not Full Auto]";

	alarm_msg  = "1. data transfer to the tag not possible.\n";

	l_act.RemoveAll();
	l_act.Add("RETRY");
	l_act.Add("ABORT");
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_NOTAG;

	alarm_title  = title;
	alarm_title += "RF Reader : NO Tag";

	alarm_msg  = "1. NO Tag or antenna installed.\n";

	l_act.RemoveAll();
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_NOTAG_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : NO Tag [Full Auto]";

	alarm_msg  = "1. NO Tag or antenna installed.\n";

	l_act.RemoveAll();
	l_act.Add("CHECK");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_NOTAG_NOT_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : NO Tag [Not Full Auto]";

	alarm_msg  = "1. NO Tag or antenna installed.\n";

	l_act.RemoveAll();
	l_act.Add("RETRY");
	l_act.Add("ABORT");
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_INVALID1;

	alarm_title  = title;
	alarm_title += "RF Reader : Invalid1";

	alarm_msg  = "1. Invalid paramter or command.\n";

	l_act.RemoveAll();
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_INVALID1_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : Invalid1 [Full Auto]";

	alarm_msg  = "1. Invalid paramter or command.\n";

	l_act.RemoveAll();
	l_act.Add("CHECK");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_INVALID1_NOT_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : Invalid1 [Not Full Auto]";

	alarm_msg  = "1. Invalid paramter or command.\n";

	l_act.RemoveAll();
	l_act.Add("RETRY");
	l_act.Add("ABORT");
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_UNKNOWN;

	alarm_title  = title;
	alarm_title += "RF Reader : Unknown";

	alarm_msg  = "1. Unknown failure.\n";

	l_act.RemoveAll();
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_UNKNOWN_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : Unknown [Full Auto]";

	alarm_msg  = "1. Unknown failure.\n";

	l_act.RemoveAll();
	l_act.Add("CHECK");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_UNKNOWN_NOT_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : Unknown [Not Full Auto]";

	alarm_msg  = "1. Unknown failure.\n";

	l_act.RemoveAll();
	l_act.Add("RETRY");
	l_act.Add("ABORT");
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_UNCONFIG;

	alarm_title  = title;
	alarm_title += "RF Reader : Unconfig";

	alarm_msg  = "1. The device is not configured.\n";

	l_act.RemoveAll();
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_UNCONFIG_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : Unconfig [Full Auto]";

	alarm_msg  = "1. The device is not configured.\n";

	l_act.RemoveAll();
	l_act.Add("CHECK");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_UNCONFIG_NOT_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : Unconfig [Not Full Auto]";

	alarm_msg  = "1. The device is not configured.\n";

	l_act.RemoveAll();
	l_act.Add("RETRY");
	l_act.Add("ABORT");
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_CHECK;

	alarm_title  = title;
	alarm_title += "RF Reader : Check";

	alarm_msg  = "1. Parity or and checksum failure.\n";

	l_act.RemoveAll();
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_CHECK_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : Check [Full Auto]";

	alarm_msg  = "1. Parity or and checksum failure.\n";

	l_act.RemoveAll();
	l_act.Add("CHECK");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_CHECK_NOT_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : Check [Not Full Auto]";

	alarm_msg  = "1. Parity or and checksum failure.\n";

	l_act.RemoveAll();
	l_act.Add("RETRY");
	l_act.Add("ABORT");
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_VOIDACKNE;

	alarm_title  = title;
	alarm_title += "RF Reader : Void Ackn";

	alarm_msg  = "1. No Valid Acknowledge.\n";

	l_act.RemoveAll();
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_VOIDACKNE_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : Void Ackn [Full Auto]";

	alarm_msg  = "1. No Valid Acknowledge.\n";

	l_act.RemoveAll();
	l_act.Add("CHECK");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_VOIDACKNE_NOT_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : Void Ackn [Not Full Auto]";

	alarm_msg  = "1. No Valid Acknowledge.\n";

	l_act.RemoveAll();
	l_act.Add("RETRY");
	l_act.Add("ABORT");
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_LOCKED;

	alarm_title  = title;
	alarm_title += "RF Reader : Locked";

	alarm_msg  = "1. Locked Page cannot be written.\n";

	l_act.RemoveAll();
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_LOCKED_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : Locked [Full Auto]";

	alarm_msg  = "1. Locked Page cannot be written.\n";

	l_act.RemoveAll();
	l_act.Add("CHECK");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_LOCKED_NOT_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : Locked [Not Full Auto]";

	alarm_msg  = "1. Locked Page cannot be written.\n";

	l_act.RemoveAll();
	l_act.Add("RETRY");
	l_act.Add("ABORT");
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_MSGLEN;

	alarm_title  = title;
	alarm_title += "RF Reader : Msg Len";

	alarm_msg  = "1. Message too long.\n";

	l_act.RemoveAll();
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_MSGLEN_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : Msg Len [Full Auto]";

	alarm_msg  = "1. Message too long.\n";

	l_act.RemoveAll();
	l_act.Add("CHECK");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_MSGLEN_NOT_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : Msg Len [Not Full Auto]";

	alarm_msg  = "1. Message too long.\n";

	l_act.RemoveAll();
	l_act.Add("RETRY");
	l_act.Add("ABORT");
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_INVALID2;

	alarm_title  = title;
	alarm_title += "RF Reader : Invalid2";

	alarm_msg  = "1. Invalid Parameter or Command.\n";

	l_act.RemoveAll();
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_INVALID2_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : Invalid2 [Full Auto]";

	alarm_msg  = "1. Invalid Parameter or Command.\n";

	l_act.RemoveAll();
	l_act.Add("CHECK");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_INVALID2_NOT_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : Invalid2 [Not Full Auto]";

	alarm_msg  = "1. Invalid Parameter or Command.\n";

	l_act.RemoveAll();
	l_act.Add("RETRY");
	l_act.Add("ABORT");
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_NOACKN;

	alarm_title  = title;
	alarm_title += "RF Reader : No Ackn";

	alarm_msg  = "1. The Message which has to be confirmed has been sent maximally.\n";
	alarm_msg += "   (RS232 maxrepeat) and has not been confirmed by the terminal.\n";
	alarm_msg += "   within the defined thme frame (see paramter 5).\n";

	l_act.RemoveAll();
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_NOACKN_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : No Ackn [Full Auto]";

	alarm_msg  = "1. The Message which has to be confirmed has been sent maximally.\n";
	alarm_msg += "   (RS232 maxrepeat) and has not been confirmed by the terminal.\n";
	alarm_msg += "   within the defined thme frame (see paramter 5).\n";

	l_act.RemoveAll();
	l_act.Add("CHECK");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__RF_NOACKN_NOT_FULL_AUTO;

	alarm_title  = title;
	alarm_title += "RF Reader : No Ackn [Not Full Auto]";

	alarm_msg  = "1. The Message which has to be confirmed has been sent maximally.\n";
	alarm_msg += "   (RS232 maxrepeat) and has not been confirmed by the terminal.\n";
	alarm_msg += "   within the defined thme frame (see paramter 5).\n";

	l_act.RemoveAll();
	l_act.Add("RETRY");
	l_act.Add("ABORT");
	l_act.Add("IGNORE");

	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	return 1;
}

int CObj__HERMOS_SERIAL::__DEFINE__VARIABLE_IO(p_io_variable)
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
int CObj__HERMOS_SERIAL::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString str_name;

	m_nCommState = OFFLINE;
	m_Rcv_Time  = 5000;

	iFlag_Log = 1;

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive_SIM = x_seq_info->Is__SIMULATION_MODE();
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
int CObj__HERMOS_SERIAL::__INITIALIZE__IO(p_io_para)
{
	// Set Driver Parameter ...
	int com_port  = -1;
	int nBaudRate = 19200;
	int nDataBit  =  8;
	int nStopBit  =  1;	
	int nParity   =  2;		// 0, 1, 2, 3, 4  :  No, Odd, Even, Mark, Space

	// ...
	{
		m_Term_Str[0] = CR;	
		m_Term_Str[1] = 0;

		sSTR__ERROR_VALUE = "NONE";
	}

	// ...
	{
		CString para_name;
		CString para_data;

		// 1.
		{
			para_name = "COM_PORT";	
			if(p_io_para->Get__PARAMETER_DATA(para_name, para_data) > 0)
			{
				com_port = atoi(para_data);
			}
		}
		// 2.
		{
			para_name = "BAUD_RATE";
			if(p_io_para->Get__PARAMETER_DATA(para_name, para_data) > 0)
			{
				nBaudRate = atoi(para_data);
			}
		}
		// 3. 
		{
			para_name = "DATA_BITS";
			if(p_io_para->Get__PARAMETER_DATA(para_name, para_data) > 0)
			{
				nDataBit = atoi(para_data);
			}
		}
		// 4.
		{
			para_name = "STOP_BITS";
			if(p_io_para->Get__PARAMETER_DATA(para_name, para_data) > 0)
			{
				nStopBit = atoi(para_data);
			}
		}
		// 5.
		{
			para_name = "PARITY";
			if(p_io_para->Get__PARAMETER_DATA(para_name, para_data) > 0)
			{
				nParity =  atoi(para_data);
			}
		}
		// 6.
		{
			para_name = "RETRY_COUNT";
			if(p_io_para->Get__PARAMETER_DATA(para_name, para_data) > 0)
			{
				m_nRetryCount = atoi(para_data);
			}
		}
		// 7.
		{
			para_name = "TIME_OUT";
			if(p_io_para->Get__PARAMETER_DATA(para_name, para_data) > 0)
			{
				m_nTimeout = atoi(para_data);
			}

			m_Rcv_Time = m_nTimeout;
		}
	}

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg  = "\n";
		log_msg += "Connect to Serial ... \n";

		log_bff.Format("  * Com_Port   : %1d \n", com_port);
		log_msg += log_bff;
		
		log_bff.Format("  * Baud_Rate  : %1d \n", nBaudRate);
		log_msg += log_bff;

		log_bff.Format("  * Data_Bit   : %1d \n", nDataBit);
		log_msg += log_bff;
	
		log_bff.Format("  * Parity_Bit : %1d \n", nParity);
		log_msg += log_bff;

		log_bff.Format("  * Stop_Bit   : %1d \n", nStopBit);
		log_msg += log_bff;
	
		log_bff.Format("  * Retry_Count  : %1d \n", m_nRetryCount);
		log_msg += log_bff;

		log_bff.Format("  * Recv_Timeout : %1d sec \n", m_nTimeout);
		log_msg += log_bff;
	
		Fnc__LOG(log_msg);
	}

	if(iActive_SIM > 0)
	{

	}
	else
	{
		if(mX_Serial->INIT__COMPORT(com_port, nBaudRate, nDataBit, nStopBit, nParity) < 0)
		{
			CString log_msg;

			log_msg.Format("Fail to do INIT__COMPORT: %d \n", com_port);
			Fnc__LOG(log_msg);
			return -1;
		}
	}

	// ...
	{
		CString log_msg;

		log_msg.Format("Initialize RS-232 Complete \n");
		Fnc__LOG(log_msg);
	}
	return 1;
}

//--------------------------------------------------------------------------------
int CObj__HERMOS_SERIAL::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
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

		else									
		{

		}
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

int CObj__HERMOS_SERIAL::__CALL__MONITORING(id, p_variable, p_alarm)
{
	switch(id)
	{
		case MON_ID__IO_MONITOR:
			Mon__IO_MONITOR(p_variable,p_alarm);
			break;
	}

	return 1;
}
