#include "StdAfx.h"
#include "CObj__VAC_VLV_FNC.h"


// ...
int CObj__VAC_VLV_FNC::Call__ALL_CLOSE(CII_OBJECT__VARIABLE *p_variable)
{
	pOBJ_CTRL__APC_VLV->Call__OBJECT(APC_CMMD__CLOSE);

	pOBJ_CTRL__VAC_VLV->Call__OBJECT(PMP_CMMD__ALL_CLOSE);
	return 1;
}
int CObj__VAC_VLV_FNC::Call__FR_SR_CLOSE(CII_OBJECT__VARIABLE *p_variable)
{
	pOBJ_CTRL__VAC_VLV->Call__OBJECT(PMP_CMMD__ALL_CLOSE);
	return 1;
}

//
int CObj__VAC_VLV_FNC::Call__SR_OPEN(CII_OBJECT__VARIABLE *p_variable)
{
	pOBJ_CTRL__VAC_VLV->Call__OBJECT(PMP_CMMD__SR_OPEN);

	pOBJ_CTRL__APC_VLV->Call__OBJECT(APC_CMMD__OPEN);
	return 1;
}
int CObj__VAC_VLV_FNC::Call__SR_CLOSE(CII_OBJECT__VARIABLE *p_variable)
{
	pOBJ_CTRL__VAC_VLV->Call__OBJECT(PMP_CMMD__SR_CLOSE);
	return 1;
}

// 
int CObj__VAC_VLV_FNC::Call__FR_OPEN(CII_OBJECT__VARIABLE *p_variable, const int all_mode)
{
	pOBJ_CTRL__VAC_VLV->Call__OBJECT(PMP_CMMD__FR_OPEN);

	if(all_mode > 0)
	{
		pOBJ_CTRL__APC_VLV->Call__OBJECT(APC_CMMD__OPEN);
	}
	return 1;
}
int CObj__VAC_VLV_FNC::Call__FR_CLOSE(CII_OBJECT__VARIABLE *p_variable)
{
	pOBJ_CTRL__VAC_VLV->Call__OBJECT(PMP_CMMD__FR_CLOSE);
	return 1;
}

int CObj__VAC_VLV_FNC::Call__EXHAUST_OPEN(CII_OBJECT__VARIABLE *p_variable)
{
	pOBJ_CTRL__VAC_VLV->Call__OBJECT(PMP_CMMD__FR_CLOSE);
	pOBJ_CTRL__VAC_VLV->Call__OBJECT(PMP_CMMD__SR_CLOSE);

	pOBJ_CTRL__VAC_VLV->Call__OBJECT(PMP_CMMD__EXHAUST_OPEN);
	return 1;
}
int CObj__VAC_VLV_FNC::Call__EXHAUST_CLOSE(CII_OBJECT__VARIABLE *p_variable)
{
	pOBJ_CTRL__VAC_VLV->Call__OBJECT(PMP_CMMD__EXHAUST_CLOSE);
	return 1;
}

// ...
int CObj__VAC_VLV_FNC::Call__APC_OPEN(CII_OBJECT__VARIABLE *p_variable)
{
	pOBJ_CTRL__APC_VLV->Call__OBJECT(APC_CMMD__OPEN);
	return 1;
}
int CObj__VAC_VLV_FNC::Call__APC_CLOSE(CII_OBJECT__VARIABLE *p_variable)
{
	pOBJ_CTRL__APC_VLV->Call__OBJECT(APC_CMMD__CLOSE);
	return 1;
}
int CObj__VAC_VLV_FNC::Call__APC_POSITION(CII_OBJECT__VARIABLE *p_variable)
{
	double para__apc_pos = aCH__PARA_APC_POSITION->Get__VALUE();
	aEXT_CH__APC_VLV__PARA_POSITION->Set__VALUE(para__apc_pos);

	return pOBJ_CTRL__APC_VLV->Call__OBJECT(APC_CMMD__POSITION);
}

// ...
int CObj__VAC_VLV_FNC::Call__APC_BALLAST_CTRL(CII_OBJECT__VARIABLE *p_variable)
{
	CString	ch_data;

	dCH__APC_BALLAST_MODE->Get__DATA(ch_data);
	
	/*
	aEXT_CH__APC_VLV__PARA_POSITION->Set__DATA(str_data);
	pOBJ_CTRL__APC_VLV->Call__OBJECT(APC_CMMD__BALLAST_CTRL);
	*/
	return 1;
}

int CObj__VAC_VLV_FNC::Call__APC_BALLAST_POS(CII_OBJECT__VARIABLE *p_variable)
{
	CString	ch_data;

	sCH__PARA_XFER_BALLAST_WAIT_SKIP_FLAG->Get__DATA(ch_data);
	
	/*
	aEXT_CH__APC_VLV__PARA_POSITION->Set__DATA(str_data);
	pOBJ_CTRL__APC_VLV->Call__OBJECT(APC_CMMD__BALLAST_POS);
	*/
	return 1;
}
