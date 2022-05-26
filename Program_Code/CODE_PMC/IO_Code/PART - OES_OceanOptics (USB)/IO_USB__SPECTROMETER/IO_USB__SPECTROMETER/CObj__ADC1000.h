#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__ADC1000__ALID.h"
#include "CObj__ADC1000__DEF.h"


#define HIGHRESTIMESTAMP_H
#define SPECTROMETERCHANNEL_H

#include <ArrayTypes.h>      // located in %OMNIDRIVER_HOME%\include
#include <Wrapper.h>


class CObj__ADC1000: public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------	
	CString	sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;	

	SCX__USER_LOG_CTRL xLOG_CTRL;
	
	int iACTIVE_SIM;

	// Spectrometer Ctrl class
	Wrapper wrapper;
	DoubleArray m_SpectrumArrary;
	DoubleArray m_WaveLength;

	// CFG : SYSTEM ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_PART_USE;

	//
	CX__VAR_DIGITAL_CTRL dCH__APP_LOG_PARAM_START_STOP;
	CX__VAR_DIGITAL_CTRL dCH__DRV_LOG_PARAM_START_STOP;
	CX__VAR_DIGITAL_CTRL dCH__JGLEE_LOG;

	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;
	CX__VAR_DIGITAL_CTRL dCH__CFG_BASIC_FUNCTION;
	CX__VAR_DIGITAL_CTRL dCH__CFG_BASIC_OPERAND1;
	CX__VAR_DIGITAL_CTRL dCH__CFG_BASIC_OPERAND2;
	CX__VAR_DIGITAL_CTRL dCH__CFG_BASIC_OPERATOR;

	CX__VAR_STRING_CTRL  sCH__EPD_BIAS_VOLT_CAL_REQ;

	CX__VAR_DIGITAL_CTRL aCH__CFG_IB_USE[MAX_SPECTRUM_COUNT];
	CX__VAR_ANALOG_CTRL  aCH__CFG_FIR_COUNT[MAX_SPECTRUM_COUNT];
	CX__VAR_ANALOG_CTRL  aCH__CFG_IIR_COEFFICIENT[MAX_SPECTRUM_COUNT];
	CX__VAR_ANALOG_CTRL  aCH__CFG_NORMAL_TIME[MAX_SPECTRUM_COUNT];
	CX__VAR_ANALOG_CTRL  aCH__CFG_IB_WAVELENGTH[MAX_SPECTRUM_COUNT];	//

	CX__VAR_ANALOG_CTRL  aCH__CFG_WIDTH_IB[MAX_SPECTRUM_COUNT];			// OES는 한개만 적용된다.

	CX__VAR_DIGITAL_CTRL dCH__OES_SUM_MODE;
	CX__VAR_DIGITAL_CTRL dCH__OES_MIN_MAX_DELETE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_MULTI_SAMPLE;

	CX__VAR_ANALOG_CTRL  aCH__OES_BROADBAND_SIGNAL_AVG;
	CX__VAR_ANALOG_CTRL  aCH__SPEC_FILTERED_DATA[MAX_SPECTRUM_COUNT];
	CX__VAR_DIGITAL_CTRL dCH__SPEC_FILTER[MAX_SPECTRUM_COUNT];
	CX__VAR_ANALOG_CTRL  aCH__EPD_SIGNAL;
	CX__VAR_DIGITAL_CTRL dCH__CFG_CCD_GAIN;

	// ... OES Spectrometer CCD Setting Parameter (Not Link)
	CX__VAR_STRING_CTRL  sCH__CFG_OES_MASTER_CCD_FIRST_COEFFICENT;
	CX__VAR_STRING_CTRL  sCH__CFG_OES_MASTER_CCD_SECOND_COEFFICENT;
	CX__VAR_STRING_CTRL  sCH__CFG_OES_MASTER_CCD_INTERCEPT;

	CX__VAR_STRING_CTRL  sCH__OES_SPECTROM_DATA;
	CX__VAR_STRING_CTRL  sCH__OES_SPECTROM_WAVELENGTH;
	CX__VAR_STRING_CTRL  sCH__OES_SNAP_SHOP_GRAPH_DISPLAY;
	CX__VAR_ANALOG_CTRL  aCFG_OES_SNAP_SHOP_GET_DATA_DELAY;
	CX__VAR_STRING_CTRL  sCH__Gui_Cal_Value;
	CX__VAR_DIGITAL_CTRL dCH__CFG_ZERO_CAL_USE;

	// ...
	CX__VAR_ANALOG_CTRL  aCH__CFG_SNAP_SHOT_TIME_COUNT;
	CX__VAR_STRING_CTRL  sCH__CUR_SNAP_SHOT_TIME_COUNT;

	CX__VAR_DIGITAL_CTRL dCH__PARA_SNAP_SHOT_MODE;	
	CX__VAR_STRING_CTRL  sCH__CUR_SNAP_SHOT_MODE;	

	CX__VAR_STRING_CTRL  sCH__REQ_SNAP_SHOT_CHECK;	
	CX__VAR_STRING_CTRL  sCH__ACTIVE_SNAP_SHOT_CHECK;	
	//

	//-------------------------------------------------------------------------	
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__DARK;
	int Call__DARK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	//-------------------------------------------------------------------------	
	int MON__MAKE_EPD_SIGNAL_THREAD(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int MON__FILTER_THREAD(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	int Fnc__SNAP_SHOT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	int MON__DARK_CTRL(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	//

	// ...
	enum { OFFLINE, ONLINE };
	int m_nOpenSts;
	int m_nCommSts;
	int m_nTimeout;
	int m_nRetryCount;

	CX__VAR_ANALOG_CTRL aoCH__BoxCar_Width;
	CX__VAR_ANALOG_CTRL aoCH__Scan_Average;
	CX__VAR_ANALOG_CTRL aiCH__Spectrum[MAX_SPECTRUM_COUNT];
	CX__VAR_ANALOG_CTRL aiCH__Spectrum_Total;

	CX__VAR_DIGITAL_CTRL doCH__CCD_GAIN;
	CX__VAR_DIGITAL_CTRL doCH__SET_COEFFICIENT;
	CX__VAR_DIGITAL_CTRL doCH__SET_Dark;
	CX__VAR_DIGITAL_CTRL diCH__COMM_STS;
	CX__VAR_DIGITAL_CTRL diCH__Get_Dark;

	CX__VAR_STRING_CTRL siCH__GET_INTERCEPT;
	CX__VAR_STRING_CTRL siCH__GET_FIRST_COEFF;
	CX__VAR_STRING_CTRL siCH__GET_SECOND_COEFF;

	// ...
	int GetSpecSignalIndex(CString str_name);

	int CheckOnline(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	int Alarm__CHECK_RETRY_ABORT(CII_OBJECT__ALARM* p_alarm, CString msg, const int alarm_id);
	int Alarm__CHECK__POST(CII_OBJECT__ALARM *p_alarm, const int alarm_id);

	int Check_OES_Open();
	//


public:
	CObj__ADC1000();
	~CObj__ADC1000();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);	
	int __DEFINE__ALARM(p_alarm);

	int __DEFINE__VARIABLE_IO(p_io_variable);

	//-------------------------------------------------------------------------	
	int __INITIALIZE__OBJECT(p_variable, p_ext_obj_create);
	int __INITIALIZE__IO(p_io_para);

	//-------------------------------------------------------------------------	
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);

	int __CLOSE__OBJECT();

	//-------------------------------------------------------------------------
	int __Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data);
	int __Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index);
	int __Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data);

	int __Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data);
	int __Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index);
	int __Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data);
};
