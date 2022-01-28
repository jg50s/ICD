#include "StdAfx.h"
#include "CObj__PMC_STD.h"
#include "CObj__PMC_STD__DEF.h"
#include "CObj__PMC_STD__ALID.h"


// ...
int  CObj__PMC_STD
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,
			 CII_OBJECT__ALARM* p_alarm)
{
	return 1;
}
int  CObj__PMC_STD
::Call__MAINT(CII_OBJECT__VARIABLE* p_variable,
			  CII_OBJECT__ALARM* p_alarm)
{
	return 1;
}

int  CObj__PMC_STD
::Call__SV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
			     CII_OBJECT__ALARM* p_alarm,
			     const int pmc_id)
{
	return pPM_VLV__OBJ_CTRL->Call__OBJECT("PMC_SV_CLOSE");
}

int  CObj__PMC_STD
::Call__INIT_SV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
					  CII_OBJECT__ALARM* p_alarm,
					  const int pmc_id)
{
	return pPM_VLV__OBJ_CTRL->Call__OBJECT("PMC_INIT_SV_CLOSE");
}

int  CObj__PMC_STD
::Call__SV_OPEN(CII_OBJECT__VARIABLE* p_variable,
			    CII_OBJECT__ALARM* p_alarm,
			    const int pmc_id)
{
	return pPM_VLV__OBJ_CTRL->Call__OBJECT("PMC_SV_OPEN");
}
