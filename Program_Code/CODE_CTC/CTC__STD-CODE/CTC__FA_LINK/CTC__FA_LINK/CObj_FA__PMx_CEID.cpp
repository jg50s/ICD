#include "StdAfx.h"
#include "CObj_FA__PMx_CEID.h"


//-------------------------------------------------------------------------
CObj_FA__PMx_CEID::CObj_FA__PMx_CEID()
{

}
CObj_FA__PMx_CEID::~CObj_FA__PMx_CEID()
{

}

//-------------------------------------------------------------------------
int CObj_FA__PMx_CEID::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	return 1;
}
int CObj_FA__PMx_CEID::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  MON_ID__REPORT_CEID					1


int CObj_FA__PMx_CEID::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CString def_name;
	CString def_vata;
	int i;

	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&mERROR__DEF_VAR);

	// ...
	{
		def_name = "PM_SIZE";
		p_variable->Get__DEF_CONST_DATA(def_name,def_vata);

		iPMx_SIZE = atoi(def_vata);
		if(iPMx_SIZE > CFG_PM_LIMIT)		iPMx_SIZE = CFG_PM_LIMIT;
		if(iPMx_SIZE < 0)					iPMx_SIZE = 0;

		for(i=0;i<iPMx_SIZE;i++)
		{
			def_name.Format("OBJ__PM%1d",i+1);
			p_variable->Get__DEF_CONST_DATA(def_name,def_vata);

			sPMx_OBJ_NAME[i] = def_vata;
		}
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3,MON_ID__REPORT_CEID);
	}
	return 1;
}

int CObj_FA__PMx_CEID::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	return 1;
}

int CObj_FA__PMx_CEID::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{

	return 1;
}

//-------------------------------------------------------------------------
int CObj_FA__PMx_CEID::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	p_ext_obj_create->Link__DEF_VARIABLE__ERROR_FEEDBACK(&mERROR__DEF_VAR);

	// ...
	CString obj_name;
	CString var_name;
	int i;

	for(i=0;i<iPMx_SIZE;i++)
	{
		obj_name = sPMx_OBJ_NAME[i];

		var_name = "CFG.PMC.USE";
		LINK__EXT_VAR_DIGITAL_CTRL(xEXT_CH__PMx_CFG_USE[i],     obj_name,var_name);

		var_name = "OBJ.STATUS";
		LINK__EXT_VAR_DIGITAL_CTRL(xEXT_CH__PMx_OBJ_STATUS[i],  obj_name,var_name);

		var_name = "SLIT.VLV.STS";
		LINK__EXT_VAR_DIGITAL_CTRL(xEXT_CH__PMx_DOOR_STS[i],    obj_name,var_name);

		var_name = "LIFT.PIN.STS";
		LINK__EXT_VAR_STRING_CTRL( xEXT_CH__PMx_LIFT_PIN_STS[i],obj_name,var_name);
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj_FA__PMx_CEID::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	return flag;
}

int CObj_FA__PMx_CEID::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__REPORT_CEID:
			Mon__REPORT_CEID(p_variable);
			break;
	}
	return 1;
}
