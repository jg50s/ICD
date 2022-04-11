#include "StdAfx.h"
#include "CObj__TMC_CHM_STD.h"


//----------------------------------------------------------------------------------------------------
int  CObj__TMC_CHM_STD::Call__INIT(CII_OBJECT__VARIABLE* p_variable)
{
	return pTMC_CHM__OBJ_CTRL->Call__OBJECT("INIT");
}
int  CObj__TMC_CHM_STD::Call__MAINT(CII_OBJECT__VARIABLE* p_variable)
{
	return pTMC_CHM__OBJ_CTRL->Call__OBJECT("MAINT");
}

//
int  CObj__TMC_CHM_STD::Call__PUMP(CII_OBJECT__VARIABLE* p_variable)
{
	return pTMC_CHM__OBJ_CTRL->Call__OBJECT("PUMP");
}
int  CObj__TMC_CHM_STD::Call__VENT(CII_OBJECT__VARIABLE* p_variable)
{
	return pTMC_CHM__OBJ_CTRL->Call__OBJECT("VENT");
}

// ...
int  CObj__TMC_CHM_STD::Call__PMx_SV_OPEN(CII_OBJECT__VARIABLE* p_variable)
{
	CString ch_data = dCH__PARA_PMx_ID->Get__STRING();
	dEXT_CH__PARA_PMx_ID->Set__DATA(ch_data);

	return pTMC_CHM__OBJ_CTRL->Call__OBJECT("PMx.SV_OPEN");
}
int  CObj__TMC_CHM_STD::Call__PMx_SV_CLOSE(CII_OBJECT__VARIABLE* p_variable)
{
	CString ch_data = dCH__PARA_PMx_ID->Get__STRING();
	dEXT_CH__PARA_PMx_ID->Set__DATA(ch_data);

	return pTMC_CHM__OBJ_CTRL->Call__OBJECT("PMx.SV_CLOSE");
}
