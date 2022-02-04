#include "StdAfx.h"
#include "CObj__CHM_FNC.h"
#include "CObj__CHM_FNC__DEF.h"
#include "CObj__CHM_FNC__ALID.h"

#include "Macro_Function.h"


// ...
int CObj__CHM_FNC
::Call__VAC_VLV__ALL_CLOSE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int r_flag = 1;

	if(bActive__PHY_VAC_VLV)
	{
		if(pOBJ_CTRL__PHY_VAC_VLV->Call__OBJECT(CMMD_VAC__ALL_CLOSE) < 0)		r_flag = -11;
	}

	if(bActive__VAT_OBJ)
	{
		if(pOBJ_CTRL__VAT->Call__OBJECT(_APC_CMMD__CLOSE) < 0)					r_flag = -21;
	}

	return r_flag;
}

int CObj__CHM_FNC
::Call__VAC_VLV__SR_OPEN(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int r_flag = 1;

	if(bActive__OBJ_CTRL__TURBO_PUMP)
	{
		if(bActive__VAT_OBJ)
		{
			if(pOBJ_CTRL__VAT->Call__OBJECT(_APC_CMMD__CLOSE) < 0)			r_flag = -11;
		}
	}
	else 
	{
		if(bActive__VAT_OBJ)
		{
			if(pOBJ_CTRL__VAT->Call__OBJECT(_APC_CMMD__OPEN) < 0)			r_flag = -11;
		}
	}

	if(bActive__PHY_VAC_VLV)
	{
		if(pOBJ_CTRL__PHY_VAC_VLV->Call__OBJECT(CMMD_VAC__SR_OPEN) < 0)		r_flag = -21;
	}

	return r_flag;
}
int CObj__CHM_FNC
::Call__VAC_VLV__FR_OPEN(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int r_flag = 1;

	if(bActive__OBJ_CTRL__TURBO_PUMP)
	{
		if(bActive__VAT_OBJ)
		{
			if(pOBJ_CTRL__VAT->Call__OBJECT(_APC_CMMD__CLOSE) < 0)			r_flag = -11;
		}
	}
	else 
	{
		if(bActive__VAT_OBJ)
		{
			if(pOBJ_CTRL__VAT->Call__OBJECT(_APC_CMMD__OPEN) < 0)			r_flag = -11;
		}
	}

	if(bActive__PHY_VAC_VLV)
	{
		if(pOBJ_CTRL__PHY_VAC_VLV->Call__OBJECT(CMMD_VAC__FR_OPEN) < 0)		r_flag = -21;
	}

	return r_flag;
}

int CObj__CHM_FNC
::Call__VAC_VLV__EXHAUST_OPEN(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	if(bActive__PHY_VAC_VLV)
	{
		return pOBJ_CTRL__PHY_VAC_VLV->Call__OBJECT(CMMD__EXHAUST_OPEN);
	}

	return -11;
}
int CObj__CHM_FNC
::Call__VAC_VLV__EXHAUST_CLOSE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	if(bActive__PHY_VAC_VLV)
	{
		return pOBJ_CTRL__PHY_VAC_VLV->Call__OBJECT(CMMD__EXHAUST_CLOSE);
	}

	return -11;
}

int CObj__CHM_FNC
::Call__VAC_VLV__APC_CLOSE()
{
	if(bActive__VAT_OBJ)
	{
		return pOBJ_CTRL__VAT->Call__OBJECT(_APC_CMMD__CLOSE);
	}
	return -1;
}
int CObj__CHM_FNC
::Call__VAC_VLV__APC_OPEN()
{
	if(bActive__VAT_OBJ)
	{
		return pOBJ_CTRL__VAT->Call__OBJECT(_APC_CMMD__OPEN);
	}
	return -1;
}
int CObj__CHM_FNC
::Call__VAC_VLV__APC_POSITION(const double set_pos)
{
	if(bActive__VAT_OBJ)
	{
		aEXT_CH__VAT_PARA_POSITION->Set__VALUE(set_pos);

		return pOBJ_CTRL__VAT->Call__OBJECT(_APC_CMMD__POSITION);
	}
	return -1;
}

int CObj__CHM_FNC
::Call__VAC_VLV__APC_BALLAST_CTRL(const bool active_xfer)
{
	if(bActive__VAT_OBJ)
	{
		if(active_xfer)			return pOBJ_CTRL__VAT->Call__OBJECT(_APC_CMMD__BALLAST_TRANSFER);
		else					return pOBJ_CTRL__VAT->Call__OBJECT(_APC_CMMD__BALLAST_CHAMBER);
	}
	return -1;
}
int CObj__CHM_FNC
::Run__VAC_VLV__APC_BALLAST_CTRL(const bool active_xfer)
{
	if(bActive__VAT_OBJ)
	{
		if(active_xfer)			return pOBJ_CTRL__VAT->Run__OBJECT(_APC_CMMD__BALLAST_TRANSFER);
		else					return pOBJ_CTRL__VAT->Run__OBJECT(_APC_CMMD__BALLAST_CHAMBER);
	}
	return -1;
}
