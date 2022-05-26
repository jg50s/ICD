#include "StdAfx.h"
#include "CObj__ADC1000.h"



//--------------------------------------------------------------------------------
CObj__ADC1000::CObj__ADC1000()
{
	m_nCommSts = OFFLINE;
}
CObj__ADC1000::~CObj__ADC1000()
{

}


//--------------------------------------------------------------------------------
int CObj__ADC1000::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;
	
	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,	"INIT");
		ADD__CTRL_VAR(sMODE__DARK,	"DARK");
	}
	return 1;
}
int CObj__ADC1000::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee";

	return 1;
}


// ...
#define MON_ID__SIGNAL								1
#define MON_ID__FILTER								2
#define MON_ID__DARK								3

int CObj__ADC1000::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString item_list;
	int i;

	// CFG : SYSTEM ...
	{
		str_name = "CFG.PART.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "YES NO", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_PART_USE, str_name);
	}

	//
	str_name = "APP.LOG.PARAM.LOG.START";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"STOP START","");
	LINK__VAR_DIGITAL_CTRL(dCH__APP_LOG_PARAM_START_STOP,str_name);

	str_name = "DRV.LOG.PARAM.LOG.START";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"STOP START","");
	LINK__VAR_DIGITAL_CTRL(dCH__DRV_LOG_PARAM_START_STOP,str_name);

	str_name = "JGLEE.LOG";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"STOP START","");
	LINK__VAR_DIGITAL_CTRL(dCH__JGLEE_LOG,str_name);

	str_name.Format("APP.OBJ.MSG");
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

	str_name.Format("CFG.BASIC.FUNCTION");
	item_list.Format("NONE USE");
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name, item_list, "");
	LINK__VAR_DIGITAL_CTRL(dCH__CFG_BASIC_FUNCTION, str_name);

	str_name.Format("CFG.BASIC.OPERAND1");
	item_list.Format("IB1 IB2 IB3 IB4 IB5 IB6 IB7 IB8");
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name, item_list, "");
	LINK__VAR_DIGITAL_CTRL(dCH__CFG_BASIC_OPERAND1, str_name);

	str_name.Format("CFG.BASIC.OPERAND2");
	item_list.Format("IB1 IB2 IB3 IB4 IB5 IB6 IB7 IB8");
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name, item_list, "");
	LINK__VAR_DIGITAL_CTRL(dCH__CFG_BASIC_OPERAND2, str_name);

	str_name.Format("CFG.BASIC.OPERATOR");
	item_list.Format("+ - * /");
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name, item_list, "");
	LINK__VAR_DIGITAL_CTRL(dCH__CFG_BASIC_OPERATOR, str_name);

	str_name = "OES.BROADBAND.SIGNAL.AVG";
	STD__ADD_ANALOG_WITH_OPTION(str_name, "", 3, -999999999, 999999999,-1, "L", "");
	LINK__VAR_ANALOG_CTRL(aCH__OES_BROADBAND_SIGNAL_AVG, str_name);

	for(i=0; i<MAX_SPECTRUM_COUNT; i++)
	{
		str_name.Format("CFG.IB%d.USE", i+1);
		item_list.Format("Yes No");
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, item_list, "");
		LINK__VAR_DIGITAL_CTRL(aCH__CFG_IB_USE[i], str_name);

		str_name.Format("CFG.IB%d.WIDTH", i+1);
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "Pixels", 0, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_WIDTH_IB[i], str_name);

		str_name.Format("CFG.IB%d.WAVELENGTH", i+1);
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "nm", 0, 200, 900, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_IB_WAVELENGTH[i], str_name);

		str_name.Format("CFG.IB%d.FIR.COUNT", i+1);
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "Count", 0, 0, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_FIR_COUNT[i], str_name);
		
		str_name.Format("CFG.IB%d.IIR.COEFFICIENT", i+1);
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "", 3, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_IIR_COEFFICIENT[i], str_name);

		str_name.Format("CFG.IB%d.Normalize.Time", i+1);
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_NORMAL_TIME[i], str_name);

		str_name.Format("SPEC.IB%d.FILTERED.DATA", i+1);
		STD__ADD_ANALOG_WITH_OPTION(str_name, "", 3, -999999999, 999999999,-1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__SPEC_FILTERED_DATA[i], str_name);

		str_name.Format("SPEC.IB%d.FILTER", i+1);
		item_list.Format("NONE FIR IIR Normalize FIRNormalize IIRNormalize");
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, item_list, "");
		LINK__VAR_DIGITAL_CTRL(dCH__SPEC_FILTER[i], str_name);
	}

	// ...
	str_name.Format("CFG.dOES.SUM.MODE");
	item_list.Format("ON OFF");
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name, item_list, "");
	LINK__VAR_DIGITAL_CTRL(dCH__OES_SUM_MODE, str_name);

	str_name.Format("CFG.dOES.MIN.MAX.DELETE");
	item_list.Format("OFF ON");
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name, item_list, "");
	LINK__VAR_DIGITAL_CTRL(dCH__OES_MIN_MAX_DELETE, str_name);

	str_name.Format("EPD.BIAS.VOLT.CAL.REQ");
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__EPD_BIAS_VOLT_CAL_REQ, str_name);
	
	str_name.Format("CFG.IB1.MULTI.SAMPLE");
	STD__ADD_ANALOG_WITH_X_OPTION(str_name, "Numbers", 0, 1, 16, "");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_MULTI_SAMPLE, str_name);

	str_name.Format("EPD.SIGNAL");
	STD__ADD_ANALOG_WITH_OPTION(str_name, "", 3, -999999999, 999999999,-1, "L", "");
	LINK__VAR_ANALOG_CTRL(aCH__EPD_SIGNAL, str_name);

	str_name.Format("CFG.CCD.GAIN");
	item_list.Format("0 1 2 3 4 5 6 7");
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name, item_list, "");
	LINK__VAR_DIGITAL_CTRL(dCH__CFG_CCD_GAIN, str_name);

	// ... OES Spectrometer CCD Setting Parameter
	str_name.Format("CFG.OES.MASTER.CCD.FIRST.COEFFICENT");
	STD__ADD_STRING_WITH_X_OPTION(str_name, "");
	LINK__VAR_STRING_CTRL(sCH__CFG_OES_MASTER_CCD_FIRST_COEFFICENT, str_name);

	str_name.Format("CFG.OES.MASTER.CCD.SECOND.COEFFICENT");
	STD__ADD_STRING_WITH_X_OPTION(str_name, "");
	LINK__VAR_STRING_CTRL(sCH__CFG_OES_MASTER_CCD_SECOND_COEFFICENT, str_name);

	str_name.Format("CFG.OES.MASTER.CCD.INTERCEPT");
	STD__ADD_STRING_WITH_X_OPTION(str_name, "");
	LINK__VAR_STRING_CTRL(sCH__CFG_OES_MASTER_CCD_INTERCEPT, str_name);

	str_name.Format("OES.SPECTROM.DATA");
	STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
	LINK__VAR_STRING_CTRL(sCH__OES_SPECTROM_DATA, str_name);

	str_name.Format("OES.SPECTROM.WAVELENGTH");
	STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
	LINK__VAR_STRING_CTRL(sCH__OES_SPECTROM_WAVELENGTH, str_name);

	str_name.Format("CFG.OES.SNAP.SHOP.GET.DATA.DELAY");
	STD__ADD_ANALOG_WITH_X_OPTION(str_name, "msec", 0, 10, 1000, "");
	LINK__VAR_ANALOG_CTRL(aCFG_OES_SNAP_SHOP_GET_DATA_DELAY, str_name);

	str_name.Format("OES.SNAP.SHOP.GRAPH.DISPLAY");
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__OES_SNAP_SHOP_GRAPH_DISPLAY, str_name);

	// ...
	{
		CString str_cmd;

		for(i=0; i<MAX_SPECTRUM_COUNT; i++)
		{
			str_cmd.Format("%d", i);
			str_name.Format("ai.Spectrum.%d", i+1);
			STD__ADD_ANALOG_WITH_OPTION(str_name, "count", 2, -9999999, 9999999,-1, "L", "");
			LINK__VAR_ANALOG_CTRL(aiCH__Spectrum[i], str_name);
		}

		str_name.Format("OES.LABEL.INFROM.INTERCEPT");
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");

		str_name.Format("OES.LABEL.INFROM.FIRST.COEFF");
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");

		str_name.Format("OES.LABEL.INFROM.SECOND.COEFF");
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");

		//... OES WAVELENGTH START VAL (0.00 ~ 1000.00)
		//... OES WAVELENGTH END   VAL
		// Gui Read Data
		str_name.Format("Gui.Cal.Value");
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__Gui_Cal_Value, str_name);

		str_name = "CFG.ZERO_CAL.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "YES NO", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_ZERO_CAL_USE, str_name);
	}

	// ...
	{
		str_name = "CFG.SNAP_SHOT.TIME_COUNT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 60, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_SNAP_SHOT_TIME_COUNT, str_name);

		str_name = "CUR.SNAP_SHOT.TIME_COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_SNAP_SHOT_TIME_COUNT, str_name);

		//
		str_name = "PARA.SNAP_SHOT.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "AUTO MANUAL", "");
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_SNAP_SHOT_MODE, str_name);

		str_name = "CUR.SNAP_SHOT.MODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_SNAP_SHOT_MODE, str_name);

		//
		str_name = "REQ.SNAP_SHOT.CHECK";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__REQ_SNAP_SHOT_CHECK, str_name);
		
		str_name = "ACTIVE.SNAP_SHOT.CHECK";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ACTIVE_SNAP_SHOT_CHECK, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__SIGNAL);
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__FILTER);
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__DARK);
	}
	return 1;
}

int CObj__ADC1000::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s : ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	// ...
	{
		alarm_id = ALID__OFFLINE_ALARM;

		alarm_title  = title;
		alarm_title += " - OES SYSTEM : OES Offline.";

		alarm_msg = "Check the Online !";
		
		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__INIT_CMD_ERROR_ALARM;

		alarm_title  = title;
		alarm_title += " - OES SYSTEM : Parameter Set Fail(First Coeff., Second Coeff, Intercept) .";

		alarm_msg = "Check the Parameter and OES !";
		
		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	return 1;
}

int CObj__ADC1000
::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	// ...
	CString str_name, item_list;
	CString str_match;
	CString str_cmd;
	int i = 0, j = 0;

	// Analog Channel ...
	// AI ...
	{
		str_name.Format("ai.Spectrum.Total.Get");
		IO__ADD_ANALOG_READ__MANUAL_EX(str_name, "count", 2, -9999999, 9999999, str_cmd, "", "");
		LINK__IO_VAR_ANALOG_CTRL(aiCH__Spectrum_Total, str_name);
	}
	// AO ...
	{
		str_name.Format("ao.BoxCar.Width.1");
		IO__ADD_ANALOG_WRITE__MANUAL_EX(str_name, "Pixels", 0, 0, 100, "", "", "");
		LINK__IO_VAR_ANALOG_CTRL(aoCH__BoxCar_Width, str_name);

		str_name.Format("ao.Scan.Average.1");
		IO__ADD_ANALOG_WRITE__MANUAL_EX(str_name, "times", 0, 1, 16, "", "", "");
		LINK__IO_VAR_ANALOG_CTRL(aoCH__Scan_Average, str_name);
	}
	
	// Digital Channel ...
	// DI ...
	{
		str_name.Format("di.Comm.Sts");
		item_list.Format("Offline Online");
		IO__ADD_DIGITAL_READ__MANUAL_EX(str_name, item_list, "", "", "");
		LINK__IO_VAR_DIGITAL_CTRL(diCH__COMM_STS, str_name);

		str_name.Format("di.Get.Dark");
		item_list.Format("Disable Enable");
		IO__ADD_DIGITAL_READ__MANUAL_EX(str_name, item_list, "", "", "");
		LINK__IO_VAR_DIGITAL_CTRL(diCH__Get_Dark, str_name);			
	}
	// DO ...
	{
		str_name.Format("do.CCD.Gain");
		item_list.Format("0 1 2 3 4 5 6 7");
		IO__ADD_DIGITAL_WRITE__MANUAL_EX(str_name, item_list, "", "", "");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__CCD_GAIN, str_name);

		str_name.Format("do.Set.Coefficient");
		item_list.Format("None Set");
		IO__ADD_DIGITAL_WRITE__MANUAL_EX(str_name, item_list, "", "", "");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__SET_COEFFICIENT, str_name);

		str_name.Format("do.Set.Drak");
		item_list.Format("Disable Enable");
		IO__ADD_DIGITAL_WRITE__MANUAL_EX(str_name, item_list, "", "", "");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__SET_Dark, str_name);
	}

	// String Channel ...
	// SI ...
	{
		str_name.Format("si.Get.Intercept");
		IO__ADD_STRING_READ__MANUAL_EX(str_name, "A", "", "");
		LINK__IO_VAR_STRING_CTRL(siCH__GET_INTERCEPT, str_name);

		str_name.Format("si.Get.First.Coefficient");
		IO__ADD_STRING_READ__MANUAL_EX(str_name, "A", "", "");
		LINK__IO_VAR_STRING_CTRL(siCH__GET_FIRST_COEFF, str_name);

		str_name.Format("si.Get.Second.Coefficient");
		IO__ADD_STRING_READ__MANUAL_EX(str_name, "A", "", "");
		LINK__IO_VAR_STRING_CTRL(siCH__GET_SECOND_COEFF, str_name);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__ADC1000
::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

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
	{
		SCX__SEQ_INFO x_seq_info;

		iACTIVE_SIM = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}

int CObj__ADC1000
::__INITIALIZE__IO(p_io_para)
{	
	// Set Driver Parameter ...
	int numberOfSpectrometers = wrapper.openAllSpectrometers();

	// ...
	CString log_msg;

	// ...
	{
		log_msg.Format("Detected Spectrometer Numbers: %d", numberOfSpectrometers);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	if(numberOfSpectrometers < 1)
	{
		// ...
		{
			log_msg.Format("OES Open Failed. ");
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		m_nOpenSts = FALSE;
		return -1;
	}

	// Online Error Clear ...
	{
		m_nOpenSts = TRUE;

		int usec = static_cast<int>(5.6 * 1000);
		wrapper.setIntegrationTime(0, usec);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__ADC1000
::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	CString log_msg;
	int flag = -1;

	// ...
	{
		log_msg.Format("Start ... :  [%s]", mode);
		
		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		IF__CTRL_MODE(sMODE__INIT)
		{
			flag = Call__INIT(p_variable, p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__DARK)
		{
			flag = Call__DARK(p_variable, p_alarm);
		}
		else
		{
			log_msg.Format("Invalid Function Mode (%s)", mode);
			xLOG_CTRL->WRITE__LOG(log_msg);

			flag = -1;
		}
	}
	
	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]", mode);
		
		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);		
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]", mode);
		
		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}

int CObj__ADC1000
::__CALL__MONITORING(id, p_variable, p_alarm)
{
		 if(id == MON_ID__SIGNAL)			MON__MAKE_EPD_SIGNAL_THREAD(p_variable, p_alarm);
	else if(id == MON_ID__FILTER)			MON__FILTER_THREAD(p_variable, p_alarm);
	else if(id == MON_ID__DARK)				MON__DARK_CTRL(p_variable, p_alarm);		  
	
	return 1;
}

int CObj__ADC1000
::__CLOSE__OBJECT()
{
	wrapper.closeAllSpectrometers();

	return 1;
}

