#include "StdAfx.h"
#include "CObj__MFC_IO.h"

#include "CCommon_Utility.h"


//----------------------------------------------------------------------------------------------------
int  CObj__MFC_IO::
Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

int  CObj__MFC_IO::
Call__OPEN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	double min_value;
	double max_value;
	int i_dec;

	aCH__MON_MFC_SET_FLOW->Get__MIN_MAX_DEC(min_value,max_value,i_dec);

	double set_flow = max_value;

	return Fnc__CONTROL(set_flow, 1, max_value);
}
int  CObj__MFC_IO::
Call__PURGE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	double min_value;
	double max_value;
	int i_dec;

	aCH__MON_MFC_SET_FLOW->Get__MIN_MAX_DEC(min_value,max_value,i_dec);

	double set_flow = max_value;

	return Fnc__CONTROL(set_flow, 1, max_value, true);
}
int  CObj__MFC_IO::
Call__CLOSE(CII_OBJECT__VARIABLE* p_variable,
			CII_OBJECT__ALARM* p_alarm)
{
	double min_value;
	double max_value;
	int i_dec;

	aCH__MON_MFC_SET_FLOW->Get__MIN_MAX_DEC(min_value,max_value,i_dec);

	double set_flow = 0.0;

	return Fnc__CONTROL(set_flow, -1, max_value);
}

int  CObj__MFC_IO
::Call__CONTROL(CII_OBJECT__VARIABLE* p_variable,
			    CII_OBJECT__ALARM*    p_alarm)
{
	double min_value;
	double max_value;
	int i_dec;
	
	aCH__PARA_SET_VALUE->Get__MIN_MAX_DEC(min_value,max_value,i_dec);
	double set_flow = aCH__PARA_SET_VALUE->Get__VALUE();

	return Fnc__CONTROL(set_flow, 1, max_value);
}
int  CObj__MFC_IO
::Fnc__CONTROL(const double set_flow, const int open_mode, const double cfg_max, const bool active__purge_vlv)
{
	int set_hexa = 0;

	if(active__purge_vlv)
	{
		dEXT_CH__IO_VLV_IN->Set__DATA(STR__CLOSE);
		dEXT_CH__IO_VLV_OUT->Set__DATA(STR__OPEN);

		if(bActive__VLV_PURGE)			dEXT_CH__IO_VLV_PURGE->Set__DATA(STR__OPEN);
		else							return -11;
	}
	else
	{
		if(bActive__VLV_PURGE)
		{
			dEXT_CH__IO_VLV_PURGE->Set__DATA(STR__CLOSE);
		}		

		if(open_mode > 0)
		{
			dEXT_CH__IO_VLV_OUT->Set__DATA(STR__OPEN);
			dEXT_CH__IO_VLV_IN->Set__DATA(STR__OPEN);
		}
		else
		{
			dEXT_CH__IO_VLV_IN->Set__DATA(STR__CLOSE);
			dEXT_CH__IO_VLV_OUT->Set__DATA(STR__CLOSE);
		}
	}

	Fnc__SET_FLOW(set_flow);
	return 1;
}

int  CObj__MFC_IO
::Call__RAMP_CTRL(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM*    p_alarm)
{
	double min_value;
	double max_value;
	int i_dec;

	aCH__PARA_SET_VALUE->Get__MIN_MAX_DEC(min_value,max_value,i_dec);
	double set_flow = aCH__PARA_SET_VALUE->Get__VALUE();

	return Fnc__RAMP_CTRL(p_variable, set_flow, 1, max_value);
}
int  CObj__MFC_IO
::Fnc__RAMP_CTRL(CII_OBJECT__VARIABLE* p_variable, const double set_flow, const int open_mode, const double cfg_max)
{
	int set_hexa = 0;

	if(bActive__VLV_PURGE)
	{
		dEXT_CH__IO_VLV_PURGE->Set__DATA(STR__CLOSE);
	}

	if(open_mode > 0)
	{
		dEXT_CH__IO_VLV_OUT->Set__DATA(STR__OPEN);
		dEXT_CH__IO_VLV_IN->Set__DATA(STR__OPEN);
	}
	else
	{
		dEXT_CH__IO_VLV_IN->Set__DATA(STR__CLOSE);
		dEXT_CH__IO_VLV_OUT->Set__DATA(STR__CLOSE);
	}

	// ...
	CString ch_data;

	// ...
	double para__ramp_sec = aCH__PARA_RAMP_SEC->Get__VALUE();

	if(para__ramp_sec > 0.1)
	{
		SCX__TIMER_CTRL x_timer_ctrl;

		double ref__loop_sec = 0.1;

		sEXT_CH__IO_MFC_SET->Get__DATA(ch_data);
		double ref_value = atof(ch_data);

		int loop_size = (int) para__ramp_sec / ref__loop_sec;
		double inc_set = (set_flow - ref_value) / loop_size;
		double set_value = ref_value;

		while(loop_size > 0)
		{
			loop_size--;
			x_timer_ctrl->POLL(ref__loop_sec);

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -1;
			}

			set_value += inc_set;
			Fnc__SET_FLOW(set_value);
		}
	}

	Fnc__SET_FLOW(set_flow);
	return 1;
}

int  CObj__MFC_IO
::Call__SET_FLOW(CII_OBJECT__VARIABLE* p_variable,
			     CII_OBJECT__ALARM*    p_alarm)
{
	double set_flow = aCH__PARA_SET_VALUE->Get__VALUE();

	return Fnc__SET_FLOW(set_flow);
}
int  CObj__MFC_IO
::Fnc__SET_FLOW(const double set_flow)
{
	double min_value;
	double max_value;
	int i_dec;

	aCH__PARA_SET_VALUE->Get__MIN_MAX_DEC(min_value,max_value,i_dec);

	// ...
	CString ch_data;

	ch_data.Format("%.2f", set_flow);
	aCH__MON_MFC_SET_FLOW->Set__DATA(ch_data);

	if(iActive__SIM_MODE > 0)
	{
		aCH__MON_MFC_READ_FLOW->Set__VALUE(set_flow);
	}

	if(iLINK_DATA__TYPE == _DATA_TYPE__HEXA)
	{
		int max_hexa = iLINK_DATA__MAX_FLOW;

		double set_ratio = set_flow / max_value;
		int set_hexa = (int)(max_hexa * set_ratio);

		if(set_hexa > 0x7fff)		set_hexa = 0x7fff;
		if(set_hexa < 0)			set_hexa = 0;

		ch_data.Format("%.1f", set_ratio*100.0);
		sCH__MON_MFC_SET_PERCENT->Set__DATA(ch_data);

		ch_data.Format("%1d", set_hexa);
		sEXT_CH__IO_MFC_SET->Set__DATA(ch_data);

		if(iActive__SIM_MODE > 0)
		{
			sEXT_CH__IO_MFC_READ->Set__DATA(ch_data);
		}
	}
	else
	{
		sEXT_CH__IO_MFC_SET->Set__DATA(ch_data);

		if(iActive__SIM_MODE > 0)
		{
			sEXT_CH__IO_MFC_READ->Set__DATA(ch_data);
		}

		// 
		double set_ratio = set_flow / max_value;
		ch_data.Format("%.1f", set_ratio*100.0);

		sCH__MON_MFC_SET_PERCENT->Set__DATA(ch_data);
	}

	return 1;
}

