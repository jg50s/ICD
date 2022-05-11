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
	double cfg_max  = aCH__CFG_MFC_MAX_VALUE->Get__VALUE();
	double set_flow = aCH__MON_MFC_SET_FLOW->Get__VALUE();

	return Fnc__CONTROL(set_flow, 1, cfg_max);
}
int  CObj__MFC_IO::
Call__CLOSE(CII_OBJECT__VARIABLE* p_variable,
			CII_OBJECT__ALARM* p_alarm)
{
	double cfg_max  = aCH__CFG_MFC_MAX_VALUE->Get__VALUE();
	double set_flow = 0.0;

	return Fnc__CONTROL(set_flow, -1, cfg_max);
}

int  CObj__MFC_IO::
Call__PURGE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	int i;

	if(iSIZE__VLV_IN < 1)
	{
		return -1;
	}

	for(i=0; i<iSIZE__VLV_PURGE_IN; i++)
	{
		dEXT_CH__IO_VLV_PURGE_IN_X[i]->Set__DATA(STR__OPEN);
	}
	
	for(i=0; i<iSIZE__VLV_IN; i++)
	{
		dEXT_CH__IO_VLV_IN_X[i]->Set__DATA(STR__CLOSE);
	}

	for(i=0; i<iSIZE__VLV_OUT_ALL; i++)
	{
		dEXT_CH__IO_VLV_OUT_ALL_X[i]->Set__DATA(STR__CLOSE);
	}
	for(i=0; i<iSIZE__VLV_OUT_CENTER; i++)
	{
		dEXT_CH__IO_VLV_OUT_CENTER_X[i]->Set__DATA(STR__CLOSE);
	}
	for(i=0; i<iSIZE__VLV_OUT_EDGE; i++)
	{
		dEXT_CH__IO_VLV_OUT_EDGE_X[i]->Set__DATA(STR__CLOSE);
	}

	for(i=0; i<iSIZE__VLV_PURGE_OUT; i++)
	{
		dEXT_CH__IO_VLV_PURGE_OUT_X[i]->Set__DATA(STR__OPEN);
	}

	//
	double cfg_max = aCH__CFG_MFC_MAX_VALUE->Get__VALUE();

	return Fnc__SET_FLOW(cfg_max);
}
int  CObj__MFC_IO::
Call__GAS_LINE_PURGE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	int i;

	if(iSIZE__VLV_IN < 1)
	{
		return -1;
	}

	for(i=0; i<iSIZE__VLV_IN; i++)
	{
		dEXT_CH__IO_VLV_IN_X[i]->Set__DATA(STR__CLOSE);
	}

	for(i=0; i<iSIZE__VLV_OUT_ALL; i++)
	{
		dEXT_CH__IO_VLV_OUT_ALL_X[i]->Set__DATA(STR__CLOSE);
	}
	for(i=0; i<iSIZE__VLV_OUT_CENTER; i++)
	{
		dEXT_CH__IO_VLV_OUT_CENTER_X[i]->Set__DATA(STR__CLOSE);
	}
	for(i=0; i<iSIZE__VLV_OUT_EDGE; i++)
	{
		dEXT_CH__IO_VLV_OUT_EDGE_X[i]->Set__DATA(STR__CLOSE);
	}

	for(i=0; i<iSIZE__VLV_PURGE_OUT; i++)
	{
		dEXT_CH__IO_VLV_PURGE_OUT_X[i]->Set__DATA(STR__CLOSE);
	}

	for(i=0; i<iSIZE__VLV_PURGE_IN; i++)
	{
		dEXT_CH__IO_VLV_PURGE_IN_X[i]->Set__DATA(STR__OPEN);
	}

	//
	return Fnc__SET_FLOW(0.0);
}
int  CObj__MFC_IO::
Call__CHM_LINE_PURGE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	int i;

	for(i=0; i<iSIZE__VLV_PURGE_IN; i++)
	{
		dEXT_CH__IO_VLV_PURGE_IN_X[i]->Set__DATA(STR__CLOSE);
	}

	for(i=0; i<iSIZE__VLV_IN; i++)
	{
		dEXT_CH__IO_VLV_IN_X[i]->Set__DATA(STR__CLOSE);
	}
	
	for(i=0; i<iSIZE__VLV_OUT_ALL; i++)
	{
		dEXT_CH__IO_VLV_OUT_ALL_X[i]->Set__DATA(STR__CLOSE);
	}
	for(i=0; i<iSIZE__VLV_OUT_CENTER; i++)
	{
		dEXT_CH__IO_VLV_OUT_CENTER_X[i]->Set__DATA(STR__CLOSE);
	}
	for(i=0; i<iSIZE__VLV_OUT_EDGE; i++)
	{
		dEXT_CH__IO_VLV_OUT_EDGE_X[i]->Set__DATA(STR__CLOSE);
	}

	for(i=0; i<iSIZE__VLV_PURGE_OUT; i++)
	{
		dEXT_CH__IO_VLV_PURGE_OUT_X[i]->Set__DATA(STR__OPEN);
	}

	//
	return Fnc__SET_FLOW(0.0);
}

int  CObj__MFC_IO::Call__CONTROL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	double cfg_max  = aCH__CFG_MFC_MAX_VALUE->Get__VALUE();
	double set_flow = aCH__PARA_SET_VALUE->Get__VALUE();

	return Fnc__CONTROL(set_flow, 1, cfg_max);
}
int  CObj__MFC_IO
::Fnc__CONTROL(const double set_flow, const int open_mode, const double cfg_max)
{
	int i;

	for(i=0; i<iSIZE__VLV_PURGE_IN; i++)
	{
		dEXT_CH__IO_VLV_PURGE_IN_X[i]->Set__DATA(STR__CLOSE);
	}
	for(i=0; i<iSIZE__VLV_PURGE_OUT; i++)
	{
		dEXT_CH__IO_VLV_PURGE_OUT_X[i]->Set__DATA(STR__CLOSE);
	}

	if(open_mode > 0)
	{
		bool active__flow_center = false;
		bool active__flow_edge   = false;

		CString cfg__flow_mode = dCH__CFG_FLOW_MODE->Get__STRING();

			 if(cfg__flow_mode.CompareNoCase("CENTER") == 0)		active__flow_center = true;
		else if(cfg__flow_mode.CompareNoCase("EDGE")   == 0)		active__flow_edge   = true;
		else
		{
			active__flow_center = true;
			active__flow_edge   = true;
		}

		// Out.All ...
		{
			for(i=0; i<iSIZE__VLV_OUT_ALL; i++)
				dEXT_CH__IO_VLV_OUT_ALL_X[i]->Set__DATA(STR__OPEN);
		}
		// Out.Center ...
		if(active__flow_center)
		{
			for(i=0; i<iSIZE__VLV_OUT_CENTER; i++)
				dEXT_CH__IO_VLV_OUT_CENTER_X[i]->Set__DATA(STR__OPEN);
		}
		else
		{
			for(i=0; i<iSIZE__VLV_OUT_CENTER; i++)
				dEXT_CH__IO_VLV_OUT_CENTER_X[i]->Set__DATA(STR__CLOSE);
		}
		// Out.Edge ...
		if(active__flow_edge)
		{
			for(i=0; i<iSIZE__VLV_OUT_EDGE; i++)
				dEXT_CH__IO_VLV_OUT_EDGE_X[i]->Set__DATA(STR__OPEN);
		}
		else
		{
			for(i=0; i<iSIZE__VLV_OUT_EDGE; i++)
				dEXT_CH__IO_VLV_OUT_EDGE_X[i]->Set__DATA(STR__CLOSE);
		}
		
		for(i=0; i<iSIZE__VLV_IN; i++)
		{
			dEXT_CH__IO_VLV_IN_X[i]->Set__DATA(STR__OPEN);
		}
	}
	else
	{
		for(i=0; i<iSIZE__VLV_IN; i++)
		{
			dEXT_CH__IO_VLV_IN_X[i]->Set__DATA(STR__CLOSE);
		}
		
		for(i=0; i<iSIZE__VLV_OUT_ALL; i++)
		{
			dEXT_CH__IO_VLV_OUT_ALL_X[i]->Set__DATA(STR__CLOSE);
		}
		for(i=0; i<iSIZE__VLV_OUT_CENTER; i++)
		{
			dEXT_CH__IO_VLV_OUT_CENTER_X[i]->Set__DATA(STR__CLOSE);
		}
		for(i=0; i<iSIZE__VLV_OUT_EDGE; i++)
		{
			dEXT_CH__IO_VLV_OUT_EDGE_X[i]->Set__DATA(STR__CLOSE);
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
	double para__ramp_sec = aCH__PARA_RAMP_SEC->Get__VALUE();

	if(para__ramp_sec > 0.1)
	{
		double ref__loop_sec = 0.1;
		double ref_value;

		if(iLINK_DATA__TYPE == _DATA_TYPE__HEXA)
		{
			CString ch_data = sEXT_CH__IO_MFC_SET_HEXA->Get__STRING();
			ref_value = atof(ch_data);
		}
		else
		{
			ref_value = aEXT_CH__IO_MFC_SET_DEC->Get__VALUE();
		}

		int loop_size = (int) para__ramp_sec / ref__loop_sec;
		double inc_set = (set_flow - ref_value) / loop_size;
		double set_value = ref_value;

		Fnc__SET_FLOW(0.0);

		// ...
		SCX__TIMER_CTRL x_timer_ctrl;

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
		sEXT_CH__IO_MFC_SET_HEXA->Set__DATA(ch_data);

		if(iActive__SIM_MODE > 0)
		{
			sEXT_CH__IO_MFC_READ_HEXA->Set__DATA(ch_data);
		}
	}
	else
	{
		aEXT_CH__IO_MFC_SET_DEC->Set__DATA(ch_data);

		if(iActive__SIM_MODE > 0)
		{
			aEXT_CH__IO_MFC_READ_DEC->Set__DATA(ch_data);
		}

		// 
		double set_ratio = set_flow / max_value;
		ch_data.Format("%.1f", set_ratio*100.0);

		sCH__MON_MFC_SET_PERCENT->Set__DATA(ch_data);
	}

	return 1;
}

