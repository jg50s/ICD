#pragma once

#include "Interface_Code.h"

#include "CCommon_System.h"
#include "Ccommon_Error.h"


class CObj__PMC_STD : public __IOBJ__STD_TYPE
{
private:
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	//-------------------------------------------------------------------------
	CString sObject_Name;

	SCX__USER_LOG_CTRL xLOG_CTRL;
	int m_nPM_LIMIT;


	//-------------------------------------------------------------------------
	// INTERNAL PROPERTY

	CX__VAR_ANALOG_CTRL  aCH__PARA_PMC_ID;

	//-------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	CII_EXT_OBJECT__CTRL *pPM_VLV__OBJ_CTRL;
	CX__VAR_ANALOG_CTRL  aEXT_CH__PARA_PMC_ID;


	//------------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable,
					CII_OBJECT__ALARM* p_alarm);

	CString sMODE__MAINT;
	int  Call__MAINT(CII_OBJECT__VARIABLE* p_variable,
				    CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__SV_CLOSE;
	int  Call__SV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
						CII_OBJECT__ALARM* p_alarm,
						const int pmc_id);

	CString sMODE__INIT_SV_CLOSE;
	int  Call__INIT_SV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
							 CII_OBJECT__ALARM* p_alarm,
							 const int pmc_id);

	CString sMODE__SV_OPEN;
	int  Call__SV_OPEN(CII_OBJECT__VARIABLE* p_variable,
					   CII_OBJECT__ALARM* p_alarm,
					   const int pmc_id);
	//------------------------------------------------------------------------------

public:
	CObj__PMC_STD();
	~CObj__PMC_STD();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
