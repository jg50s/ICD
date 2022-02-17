#include "StdAfx.h"
#include "CObj__GAS_VLV_PHY.h"


// ...
int CObj__GAS_VLV_PHY
::Call__ALL_CLOSE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int i;

	// GAS_LINE.PURGE ...
	{
		for(i=0; i<iSIZE__GAS_LINE__VLV_PURGE; i++)
		{
			dEXT_CH__GAS_LINE__VLV_PURGE[i]->Set__DATA(STR__CLOSE);
		}
	}
	// CHM_LINE.PURGE ...
	{
		for(i=0; i<iSIZE__CHM_LINE__VLV_PURGE; i++)
		{
			dEXT_CH__CHM_LINE__VLV_PURGE[i]->Set__DATA(STR__CLOSE);
		}
	}
	// MFC.PURGE ...
	{
		for(i=0; i<iSIZE__MFC__VLV_PURGE; i++)
		{
			dEXT_CH__MFC__VLV_PURGE[i]->Set__DATA(STR__CLOSE);
		}
	}

	// SOFT.VENT ...
	{
		for(i=0; i<iSIZE__SOFT_VENT__VLV_CLOSE; i++)
		{
			dEXT_CH__SOFT_VENT__VLV_CLOSE[i]->Set__DATA(STR__CLOSE);
		}
	}
	// FAST.VENT ...
	{
		for(i=0; i<iSIZE__FAST_VENT__VLV_CLOSE; i++)
		{
			dEXT_CH__FAST_VENT__VLV_CLOSE[i]->Set__DATA(STR__CLOSE);
		}
	}

	// CHM.PURGE ...
	{
		for(i=0; i<iSIZE__TOP_CHM__VLV_PURGE; i++)
		{
			dEXT_CH__TOP_CHM__VLV_PURGE[i]->Set__DATA(STR__CLOSE);
		}
	}
	// CHM.PROC ..
	{
		for(i=0; i<iSIZE__TOP_CHM__VLV_PROC; i++)
		{
			dEXT_CH__TOP_CHM__VLV_PROC[i]->Set__DATA(STR__CLOSE);
		}
	}

	return 1;
}

int CObj__GAS_VLV_PHY
::Call__SV_OPEN(CII_OBJECT__VARIABLE *p_variable,
				CII_OBJECT__ALARM *p_alarm)
{
	int i_limit;
	int i;

	i_limit = iSIZE__MFC__VLV_PURGE;
	for(i=0; i<i_limit; i++)
	{
		dEXT_CH__MFC__VLV_PURGE[i]->Set__DATA(STR__CLOSE);
	}

	i_limit = iSIZE__SOFT_VENT__VLV_CLOSE;
	for(i=0; i<i_limit; i++)
	{
		dEXT_CH__SOFT_VENT__VLV_CLOSE[i]->Set__DATA(STR__CLOSE);
	}

	i_limit = iSIZE__SOFT_VENT__VLV_OPEN;
	for(i=0; i<i_limit; i++)
	{
		dEXT_CH__SOFT_VENT__VLV_OPEN[i]->Set__DATA(STR__OPEN);
	}

	return 1;
}
int CObj__GAS_VLV_PHY
::Call__SV_CLOSE(CII_OBJECT__VARIABLE *p_variable,
				 CII_OBJECT__ALARM *p_alarm)
{
	int i_limit;
	int i;

	i_limit = iSIZE__MFC__VLV_PURGE;
	for(i=0; i<i_limit; i++)
	{
		dEXT_CH__MFC__VLV_PURGE[i]->Set__DATA(STR__CLOSE);
	}

	i_limit = iSIZE__SOFT_VENT__VLV_CLOSE;
	for(i=0; i<i_limit; i++)
	{
		dEXT_CH__SOFT_VENT__VLV_CLOSE[i]->Set__DATA(STR__CLOSE);
	}

	i_limit = iSIZE__SOFT_VENT__VLV_OPEN;
	for(i=0; i<i_limit; i++)
	{
		dEXT_CH__SOFT_VENT__VLV_OPEN[i]->Set__DATA(STR__CLOSE);
	}

	return 1;
}

int CObj__GAS_VLV_PHY
::Call__FV_OPEN(CII_OBJECT__VARIABLE *p_variable,
				CII_OBJECT__ALARM *p_alarm)
{
	int i_limit;
	int i;

	i_limit = iSIZE__MFC__VLV_PURGE;
	for(i=0; i<i_limit; i++)
	{
		dEXT_CH__MFC__VLV_PURGE[i]->Set__DATA(STR__CLOSE);
	}

	i_limit = iSIZE__FAST_VENT__VLV_CLOSE;
	for(i=0; i<i_limit; i++)
	{
		dEXT_CH__FAST_VENT__VLV_CLOSE[i]->Set__DATA(STR__CLOSE);
	}

	i_limit = iSIZE__FAST_VENT__VLV_OPEN;
	for(i=0; i<i_limit; i++)
	{
		dEXT_CH__FAST_VENT__VLV_OPEN[i]->Set__DATA(STR__OPEN);
	}

	return 1;
}
int CObj__GAS_VLV_PHY
::Call__FV_CLOSE(CII_OBJECT__VARIABLE *p_variable,
				 CII_OBJECT__ALARM *p_alarm)
{
	int i_limit;
	int i;

	i_limit = iSIZE__MFC__VLV_PURGE;
	for(i=0; i<i_limit; i++)
	{
		dEXT_CH__MFC__VLV_PURGE[i]->Set__DATA(STR__CLOSE);
	}

	i_limit = iSIZE__FAST_VENT__VLV_CLOSE;
	for(i=0; i<i_limit; i++)
	{
		dEXT_CH__FAST_VENT__VLV_CLOSE[i]->Set__DATA(STR__CLOSE);
	}

	i_limit = iSIZE__FAST_VENT__VLV_OPEN;
	for(i=0; i<i_limit; i++)
	{
		dEXT_CH__FAST_VENT__VLV_OPEN[i]->Set__DATA(STR__CLOSE);
	}

	return 1;
}


// ...
int CObj__GAS_VLV_PHY
::Call__GAS_LINE_PURGE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int i;

	for(i=0; i<iSIZE__GAS_LINE__VLV_PURGE; i++)
	{
		dEXT_CH__GAS_LINE__VLV_PURGE[i]->Set__DATA(STR__OPEN);
	}
	return 1;
}
int CObj__GAS_VLV_PHY
::Call__CHM_LINE_PURGE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	int i;

	for(i=0; i<iSIZE__CHM_LINE__VLV_PURGE; i++)
	{
		dEXT_CH__CHM_LINE__VLV_PURGE[i]->Set__DATA(STR__OPEN);
	}
	return 1;
}
int CObj__GAS_VLV_PHY
::Call__LINE_PURGE_WITH_N2(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	int i;

	for(i=0; i<iSIZE__CHM_LINE__VLV_PURGE; i++)
	{
		dEXT_CH__CHM_LINE__VLV_PURGE[i]->Set__DATA(STR__OPEN);
	}
	for(i=0; i<iSIZE__MFC__VLV_PURGE; i++)
	{
		dEXT_CH__MFC__VLV_PURGE[i]->Set__DATA(STR__OPEN);
	}

	return 1;
}
int CObj__GAS_VLV_PHY
::Call__CLOSE_N2_PURGE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	int i;

	for(i=0; i<iSIZE__GAS_LINE__VLV_PURGE; i++)
	{
		dEXT_CH__GAS_LINE__VLV_PURGE[i]->Set__DATA(STR__CLOSE);
	}
	for(i=0; i<iSIZE__CHM_LINE__VLV_PURGE; i++)
	{
		dEXT_CH__CHM_LINE__VLV_PURGE[i]->Set__DATA(STR__CLOSE);
	}
	for(i=0; i<iSIZE__MFC__VLV_PURGE; i++)
	{
		dEXT_CH__MFC__VLV_PURGE[i]->Set__DATA(STR__CLOSE);
	}

	return 1;
}

int CObj__GAS_VLV_PHY
::Call__PROC_OPEN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	int i;
	
	for(i=0; i<iSIZE__TOP_CHM__VLV_PROC; i++)
	{
		dEXT_CH__TOP_CHM__VLV_PROC[i]->Set__DATA(STR__OPEN);
	}

	return 1;
}
