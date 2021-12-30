#pragma once

#include "Interface_Header.h"
#include "CCommon_Error.h"
#include "CCommon_DEF.h"


// ...
#define ALID__ESCCON_OFFLINE_ALARM					11
#define ALID__ESC_RAMPUP_TIMEOVER_ALARM				12
#define ALID__ESC_RAMPDN_TIMEOVER_ALARM				13
#define ALID__ESC_CURRENT_RANGE_ABORT				14
#define ALID__ESC_DATA_TYPE_ERROR					-104	//�Ķ������ ������ Ÿ���� �߸� �Ǿ����ϴ�.
#define ALID__ESC_PARAMETER_NOT_ALLOWED				-108	//��ɾ �ʿ��� �Ķ���� ���� ���� �Ķ���Ͱ� ���ŵǾ����ϴ�.
#define ALID__ESC_MISSING_PARAMETER					-109	//��ɾ �ʿ��� �Ķ���� ���� ���� �Ķ���Ͱ� ���ŵǾ����ϴ�.
#define ALID__ESC_UNDEFINED_HEADER					-113	//��ȿ���� ���� ����� ���ŵǾ����ϴ�.
#define ALID__ESC_DATA_OUT_OF_RANGE					-222	//������  �Ķ������ ���ġ�� �ʰ��߽��ϴ�.
#define ALID__ESC_TOO_MANY_ERRORS					-350	//10�� �̻��� ������ �߻��Ͽ� Error Buffer�� ����á���ϴ�. Error Clear�� �ʿ��մϴ�.
#define ALID__ESC_QUERY_INTERRUPED					-410	//����� ���ŵǾ����� ��� ���ۿ� ���� ����� �����Ͱ� ��� �ֽ��ϴ�. - ���� �����ʹ� �ս� �˴ϴ�.
#define ALID__ESC_QUERY_UNTERMINATED				-420	//�����͸� �е��� �����Ǿ�����, ��¹��ۿ� �����͸� �����ϴ� ����� ���ŵ��� �ʾҽ��ϴ�.
#define ALID__ESC_QUERY_DEADLOCKED					-430	//��� ���ۿ� ���� �ʹ� ���� �����͸� �ۼ��ϴ� ����� ���ŵǾ�����, �Է� ���� ���� ���� á���ϴ�. ����� ��������� ��� �����Ͱ� �սŵ˴ϴ�.
#define ALID__ESC_QUERY_UNTERMINATED_AFTER_indefinite	-440	//*IDN? ����� ��� ���ڿ��� ������ ���� ������� ����ؾ� �մϴ�.
#define ALID__ESC_COMMAND_NOT_ALLOWED_IN_REMOTE		-515	//Remote ���¿����� ���� ������ ����� ���� �߽��ϴ�.
#define ALID__ESC_OUTPUT_BUFFER_OVERFLOW			-522	//��� ���ۿ� �����Ͱ� ���� á���ϴ�.
#define ALID__ESC_OUTPUT_ENABLE						-561	//��� �߿� ����� ���� �߽��ϴ�.

//...
#define end_str						LF
//

//...
#define MODE__ON					"ON"
#define MODE__OFF					"OFF"
#define MODE__REMOTE				"REMOTE"
#define MODE__LOCAL					"LOCAL"
//

//...
#define STS__ON						"1"
#define STS__OFF					"0"
//

//...
#define CHAR__SEPARATE_SEMICOLON		';'
#define CHAR__SEPARATE_COMMA			','
//

// ...
#define CMD__LIAISE					";:"				// ���� ����� �׷����� �̾��ִ� ���� - Set) OUTP ON;:OUTP?<LF> -> ���� 1<LF> : Output On������ ���ÿ� Output ���¸� Read�� �� �ִ�.
#define CMD__OUTPUT					"OUTP "				// HV OUTPUT ON/OFF ���� - Set) OUTP ON<LF> -> HV On
#define CMD__TOGGLE					"TOGG "
#define CMD__OUTPUT_STATE_READ		"OUTP?"				// HV On/Off ���� Read
#define CMD__TOGGLE_STATE_READ		"TOGG?"				// Toggle On/Off ���� Read
#define CMD__LOCAL					"SYST:LOC"
#define CMD__REMOTE					"SYST:REM"
#define CMD__ONLY_VOLT_CHANGE		"VOLT "				// HV On�߿� Volt�� ������ ���, (�ؼ��� ������ �� ����) - Set) VOLT(space)2500,-2500<LF> -> Ch1 2500V, Ch2 -2500V
#define CMD__SETVOLT_READ			"VOLT? (@1,2)"		// ���� �����Ǿ� �ִ� Volt�� Read
#define CMD__VOLT_READ				"MEAS:VOLT? (@1,2)" // ���� ��µǴ� Volt�� Read - ���� : V+0200;V-200<LF>   ->  Ch1 200V, Ch2 -200V
#define CMD__CURR_READ				"MEAS:CURR? (@1,2)"	// ���� ��µǴ� Curr�� Read - ���� : A+1000;A+1000<LF>  ->  Ch1 1mA,  Ch2 1mA
#define CMD__VOLT_SET				"CONF:VOLT "		// 
#define CMD__CURRLIMIT_SET			"CONF:CURR "		// CurrentLimit ����  - Set) CONF:CURR(space)0.001,0.001<LF> -> Ch1 1mA. Ch2 1mA
#define CMD__CURRLIMIT_READ			"CONF:CURR? (@1,2)"	// ���� �����Ǿ� �ִ� Curr Limit�� Read  - ���� : A+1000;A+1000<LF> -> Ch1 1mA, Ch2 1mA
#define CMD__RAMPUP_SET				"CONF:RAMP UP,"		// RampUp Time ����   - Set) CONF:RAMP(space)UP,300<LF>   -> RampUp Time 0.3sec //Ch1, Ch2 ���� ����
#define CMD__RAMPDN_SET				"CONF:RAMP DOWN,"	// RampDown Time ���� - Set) CONF:RAMP(space)DOWN,500<LF> -> RampUp Time 0.5sec	//Ch1, Ch2 ���� ����
#define CMD__RAMPUP_READ			"CONF:RAMP? UP"		// ���� �����Ǿ� �ִ� RampUp Time Read   - ���� : 300<LF>	//Ch1, Ch2 ���� ����
#define CMD__RAMPDN_READ			"CONF:RAMP? DOWN"	// ���� �����Ǿ� �ִ� RampDown Time Read - ���� : 300<LF>	//Ch1, Ch2 ���� ����
#define CMD__STATE_READ				"STAT?"				// ���� : V+0000;V+0000;A+0000;A+0000;0;0;1<LF> -> Ch1����;Ch2����;Ch1����;Ch2����;OUTPUT����;TOGGLE����;REMOTE���� 
#define CMD__AUTO_TOGG				"AT "				// Auto Toggle ��� ���� ���� - AT(space)1<LF> -> 1 : ���, 0 : �̻��
#define CMD__AUTO_TOGG_READ			"AT?"				// ���� : 1<LF> �Ǵ� 0<LF> -> 1 : �����, 0 : �̻����
#define CMD__AUTO_TOGG_CNT			"AT:COUNT "			// Auto Toggle Count���� - Set) AT:COUNT(space)2<LF> -> Auto Toggle 2ȸ ����
#define CMD__AUTO_TOGG_CNT_READ		"AT:COUNT?"			// ���� �����Ǿ� �ִ� Auto Toggle Count Read - ���� : 2<LF> -> 2ȸ ����
#define CMD__AUTO_TOGG_VOLT			"AT:VOLT "			// Auto Toggle ���� Volt ���� - Set) AT:VOLT(space)2500<LF> -> 2.5kV�� ����
#define CMD__AUTO_TOGG_VOLT_READ	"AT:VOLT?"			// ���� �����Ǿ� �ִ� Auto Toggle Volt Read - ���� : 2500<LF>
#define CMD__ERROR_READ				"SYST:ERR?"			// ���� Error ���� Read
#define CMD__VERSION_READ			"SYST:VERS?"		// ���� System Ver. Read
#define CMD__BEEPER					"SYST:BEEP"			// Controller���� Boozer �︲
#define CMD__ERR_RESET				"*CLS"				// Error Reset
#define CMD__POWER_RESET			"*RST"				// Power Supply Reset
#define CMD__IDENTITY				"*IDN?"				// ���� : ������,�𵨸�,�ø����ȣ,�߿������<LF> ZEFATEK,DXM2.5K-DR,1808271001,5.1


class CObj_Phy__ESC_ZEFA : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	//.....
	//CCommon_Error__USER_FNC mERROR__USER_FNC;

	// ...
	SCX__SEQ_INFO	xI_SEQ;
	SCX__SERIAL		mX_Serial;

	CString sPROTOCOL_INFO;

	char m_Term_Str[3];
	int	 m_nCommState;
	int	 m_Rcv_Time;
	int	 m_RetryCnt;
	CString  m_Command;

	unsigned char m_CRC_Table1[256];
	unsigned char m_CRC_Table2[256];

	int  iResolution_type;
	int	 mon_flag;

	//.....
	//void Fnc__Initial_CRC_ETC();
	//void Fnc__Get_CRC(unsigned char *String,unsigned char Size,unsigned char *C0,unsigned char *C1);
	//


	//-------------------------------------------------------------------------
	SCX__USER_LOG_CTRL xI__APP_LOG_CTRL;
	SCX__USER_LOG_CTRL xI__DRV_LOG_CTRL;

	int iFLAG__DRV_FLAG;

	int  Recv_Data_Multi(const CString& real_data, CStringArray& value, const char Sepa_Str, int total_len);
	int  Recv_Data_Single(const CString& real_data, CString *value);
	void Write__APP_LOG(const CString& log_msg);
	void Write__DRV_LOG(const CString& log_msg);
	//

	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// VIRTUAL CHANNEL
	//.....
	CX__VAR_ANALOG_CTRL  aCH__VOLT_SET_CH1;
	CX__VAR_ANALOG_CTRL  aCH__VOLT_SET_CH2;
	CX__VAR_ANALOG_CTRL  aCH__CURRLIMIT_SET_CH1;
	CX__VAR_ANALOG_CTRL  aCH__CURRLIMIT_SET_CH2;
	CX__VAR_ANALOG_CTRL  aCH__RAMPUP_SET;
	CX__VAR_ANALOG_CTRL  aCH__RAMPDN_SET;
	CX__VAR_ANALOG_CTRL  aCH__AUTO_TOGGLE_CNT;
	CX__VAR_ANALOG_CTRL  aCH__AUTO_TOGGLE_VOLT;
	CX__VAR_ANALOG_CTRL  aCH__VOLT_READ_CH1;			// ���� ��� ���а�
	CX__VAR_ANALOG_CTRL  aCH__VOLT_READ_CH2;			// ���� ��� ���а�
	CX__VAR_ANALOG_CTRL  aCH__CURR_READ_CH1;			// ���� ��� ������
	CX__VAR_ANALOG_CTRL  aCH__CURR_READ_CH2;			// ���� ��� ������
	CX__VAR_ANALOG_CTRL  aCH__CURRLIMIT_READ_CH1;		// ���� CH1 �������Ѱ�
	CX__VAR_ANALOG_CTRL  aCH__CURRLIMIT_READ_CH2;		// ���� CH2 �������Ѱ�
	CX__VAR_ANALOG_CTRL  aCH__RAMPUP_READ;				// ���� CH1 Rampup ������
	CX__VAR_ANALOG_CTRL  aCH__RAMPDN_READ;				// ���� CH1 Rampdown ������
	CX__VAR_ANALOG_CTRL  aCH__AUTO_TOGGLE_CNT_READ;		
	CX__VAR_ANALOG_CTRL  aCH__AUTO_TOGGLE_VOLT_READ;
	//

	//.....
	//CX__VAR_DIGITAL_CTRL dCH__LOCAL_REMOTE;				// Local Remote
	CX__VAR_DIGITAL_CTRL  dCH__TOGGLE;					// Toggle On Off
	CX__VAR_DIGITAL_CTRL  dCH__OUTPUT;					// Output On Off
	CX__VAR_DIGITAL_CTRL  dCH__AUTO_TOGGLE;
	CX__VAR_DIGITAL_CTRL  dCH__ERROR_RESET;
	CX__VAR_DIGITAL_CTRL  dCH__POWER_SUPPLY_RESET;
	CX__VAR_DIGITAL_CTRL  dCH__COMM_STS;
	//

	//.....
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;
	CX__VAR_STRING_CTRL  sCH__COMM_STS;
	CX__VAR_STRING_CTRL  sCH__SETVOLT_READ_CH1;			// ���� ���м�����
	CX__VAR_STRING_CTRL  sCH__SETVOLT_READ_CH2;			// ���� ���м�����
	CX__VAR_STRING_CTRL  sCH__SETCURR_READ_CH1;			// ���� �������Ѽ�����
	CX__VAR_STRING_CTRL  sCH__SETCURR_READ_CH2;			// ���� �������Ѽ�����
	CX__VAR_STRING_CTRL  sCH__SETRAMPUP_READ;			// ���� RAMPUP������
	CX__VAR_STRING_CTRL  sCH__SETRAMPDN_READ;			// ���� RAMPDN������

	CX__VAR_STRING_CTRL  sCH__OUTPUT_STATUS;			// ���� Output ���� : 0: Off, 1: On
	CX__VAR_STRING_CTRL  sCH__TOGGLE_STATUS;			// ���� Toggle ���� : 0: Off, 1: On
	CX__VAR_STRING_CTRL  sCH__REMOTE_STATUS;			// ���� Remote ���� : 0: Off, 1: On
	CX__VAR_STRING_CTRL  sCH__AUTO_TOGGLE_READ;			// 0: Off, 1: On
	CX__VAR_STRING_CTRL  sCH__ERROR;

	CX__VAR_STRING_CTRL  sCH__STATE_READ;				// State Read : Ch1����; Ch2����; Ch1����; Ch2����; Output����; Toggle����; Remote����
	CX__VAR_STRING_CTRL  sCH__ERROR_READ;				// 
	//

	// CFG CHANNEL  -----------------------------------
	//...
	CX__VAR_ANALOG_CTRL  aCH__CFG_RAMPUP_TIME;
	CX__VAR_ANALOG_CTRL  aCH__CFG_RAMPDN_TIME;
	CX__VAR_ANALOG_CTRL  aCH__CFG_CURRLIMIT_CH1;
	CX__VAR_ANALOG_CTRL  aCH__CFG_CURRLIMIT_CH2;
	CX__VAR_ANALOG_CTRL  aCH__CFG_AUTO_TOGGLE_CNT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_AUTO_TOGGLE_VOLT;
	CX__VAR_DIGITAL_CTRL dCH__CFG_TOGGLE_USE;
	CX__VAR_DIGITAL_CTRL dCH__CFG_AUTO_TOGGLE_USE;
	CX__VAR_DIGITAL_CTRL dCH__CFG_NEED_REPLY;
	//

	// IO CHANNEL  -----------------------------------
	// AO
	CX__VAR_ANALOG_CTRL	aoCH__VOLT_SET_CH1;
	CX__VAR_ANALOG_CTRL	aoCH__VOLT_SET_CH2;

	// AI
	CX__VAR_ANALOG_CTRL  aiCH__SETVOLT_READ;	// ���� ���а�
	CX__VAR_ANALOG_CTRL  aiCH__CURRLIMIT_READ;	// ���� ������
	CX__VAR_ANALOG_CTRL  aiCH__RAMPUP_READ;
	CX__VAR_ANALOG_CTRL  aiCH__RAMPDN_READ;

	//DO
	CX__VAR_DIGITAL_CTRL doCH__OUTPUT;			// HV Off On
	CX__VAR_DIGITAL_CTRL doCH__TOGGLE;			// Toggle Off On
	CX__VAR_DIGITAL_CTRL doCH__LOCAL_REMOTE;	// Local Remote
	//CX__VAR_DIGITAL_CTRL doCH__STATE_READ;		// State Read - ch1VOLT;ch2VOLT;ch1CURR;ch2CURR;OUTPUT;TOGGLE;REMOTE

	// DI
	

	// SO
	CX__VAR_STRING_CTRL  sCH__VOLT_SET_ALL;				// Ch1, Ch2 Volt set value
	CX__VAR_STRING_CTRL  soCH__VOLT_SET_CH1;
	CX__VAR_STRING_CTRL  soCH__VOLT_SET_CH2;
	CX__VAR_STRING_CTRL  soCH__CURRLIMIT_SET;
	CX__VAR_STRING_CTRL  soCH__CURRLIMIT_SET_CH1;
	CX__VAR_STRING_CTRL  soCH__CURRLIMIT_SET_CH2;
	CX__VAR_STRING_CTRL  soCH__RAMPUP_SET;
	CX__VAR_STRING_CTRL  soCH__RAMPDN_SET;
	CX__VAR_STRING_CTRL  soCH__AUTO_TOGGLE_CNT;
	CX__VAR_STRING_CTRL  soCH__AUTO_TOGGLE_VOLT;
	CX__VAR_STRING_CTRL  soCH__STATE_READ;		// Status Read : Ch1����; Ch2����; Ch1����; Ch2����; Output����; Toggle����; Remote����
	CX__VAR_STRING_CTRL  soCH__ERROR_READ;

	// SI
	



	//-------------------------------------------------------------------------
	CString sMODE__LOCAL;
	int  Call__LOCAL(CII_OBJECT__VARIABLE*		p_variable,
					 CII_OBJECT__ALARM*			p_alarm);

	CString sMODE__REMOTE;
	int  Call__REMOTE(CII_OBJECT__VARIABLE*		p_variable,
				 	  CII_OBJECT__ALARM*		p_alarm);

	CString sMODE__TOGGLE_ON;
	CString sMODE__TOGGLE_OFF;
	int  Call__TOGGLE(CII_OBJECT__VARIABLE*		p_variable,
					  CII_OBJECT__ALARM*		p_alarm,
					  CString					mode);

	CString sMODE__ON;
	int  Call__ON(CII_OBJECT__VARIABLE*			p_variable,
				  CII_OBJECT__ALARM*			p_alarm);

	CString sMODE__OFF;
	int  Call__OFF(CII_OBJECT__VARIABLE*		p_variable,
				   CII_OBJECT__ALARM*			p_alarm);

	CString sMODE__AUTO_TOGGLE;
	int  Call__AUTO_TOGGLE(CII_OBJECT__VARIABLE*	p_variable,
						   CII_OBJECT__ALARM*		p_alarm,
						   CString					mode);

	CString sMODE__VOLT_SET;
	int  Call__VOLT_SET(CII_OBJECT__VARIABLE*		p_variable,
						CII_OBJECT__ALARM*			p_alarm);

	//CString sMODE__VOLT_READ;
	//int  Call__VOLT_READ(CII_OBJECT__VARIABLE*		p_variable,
	//					 CII_OBJECT__ALARM*			p_alarm);

	CString sMODE__SETVOLT_READ;
	int  Call__SETVOLT_READ(CII_OBJECT__VARIABLE*	p_variable,
							CII_OBJECT__ALARM*		p_alarm);

	CString sMODE__CURRLIMIT_SET;
	int  Call__CURRLIMIT_SET(CII_OBJECT__VARIABLE*	p_variable,
							 CII_OBJECT__ALARM*		p_alarm);

	CString sMODE__CURRLIMIT_READ;
	int  Call__CURRLIMIT_READ(CII_OBJECT__VARIABLE*	p_variable,
							  CII_OBJECT__ALARM*	p_alarm);

	//CString sMODE__CURRENT_READ;
	//int  Call__CURR_READ(CII_OBJECT__VARIABLE*		p_variable,
	//					 CII_OBJECT__ALARM*			p_alarm);

	CString sMODE__RAMPUP_SET;
	int  Call__RAMPUP_SET(CII_OBJECT__VARIABLE*		p_variable,
						  CII_OBJECT__ALARM*		p_alarm);

	CString sMODE__RAMPDN_SET;
	int  Call__RAMPDN_SET(CII_OBJECT__VARIABLE*		p_variable,
						  CII_OBJECT__ALARM*		p_alarm);

	CString sMODE__RAMPUP_READ;
	int  Call__RAMPUP_READ(CII_OBJECT__VARIABLE*	p_variable,
						   CII_OBJECT__ALARM*		p_alarm);

	CString sMODE__RAMPDN_READ;
	int  Call__RAMPDN_READ(CII_OBJECT__VARIABLE*	p_variable,
						   CII_OBJECT__ALARM*		p_alarm);

	CString sMODE__ERROR_READ;
	int  Call__ERROR_READ(CII_OBJECT__VARIABLE*		p_variable,
						  CII_OBJECT__ALARM*		p_alarm);

	CString sMODE__VERSION_READ;
	int  Call__VERSION_READ(CII_OBJECT__VARIABLE*	p_variable,
							CII_OBJECT__ALARM*		p_alarm);

	CString sMODE__ERROR_RESET;
	int  Call__ERROR_RESET(CII_OBJECT__VARIABLE*	p_variable,
						   CII_OBJECT__ALARM*		p_alarm);

	CString sMODE__POWER_RESET;
	int  Call__POWER_RESET(CII_OBJECT__VARIABLE*	p_variable,
						   CII_OBJECT__ALARM*		p_alarm);

	CString sMODE__STATE_READ;
	int  Call__STATE_READ(CII_OBJECT__VARIABLE*		p_variable,
						  CII_OBJECT__ALARM*		p_alarm);

	CString sMODE__PROC_SEQ;
	int  FNC__PROC_SEQ(CII_OBJECT__VARIABLE*		p_variable,
					   CII_OBJECT__ALARM*			p_alarm);

	CString sMODE__INITIAL;
	int  FNC__INITIAL(CII_OBJECT__VARIABLE*			p_variable,
					  CII_OBJECT__ALARM*			p_alarm);

	CString sMODE__PROC_READY;
	int  FNC__PROC_READY(CII_OBJECT__VARIABLE*			p_variable,
						   CII_OBJECT__ALARM*			p_alarm);

	int FNC__ON_SEQ(CII_OBJECT__VARIABLE*	p_variable,
					 CII_OBJECT__ALARM*	p_alarm);
	//
	
	//...
	int Command_Send(CString send_cmd);
	int Command_Recv(CString send_cmd, CString *recv_cmd);
	//

	// ...
	void Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	void Mon__MONITOR_1(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	void Mon__MONITOR_2(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	//

	// ...
	void Fnc__Do_Abort(CII_OBJECT__ALARM* p_alarm);
	int  Fnc__Is_Online(CII_OBJECT__ALARM* p_alarm);

	int  Seq__Ramp_Up_Down(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const int zero_ctrl);
	//


public:
	CObj_Phy__ESC_ZEFA();
	~CObj_Phy__ESC_ZEFA();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj, l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__VARIABLE_IO(p_rs232_variable);

	int __DEFINE__ALARM(p_alarm);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);
	int __INITIALIZE__IO(p_io_para);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm);
	int __CALL__MONITORING(id, p_variable, p_alarm);

	//-------------------------------------------------------------------------
	int __Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data);
	int __Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index);
	int __Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data);

	int __Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data);
	int __Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index);
	int __Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data);
};

