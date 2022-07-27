#include "StdAfx.h"
#include "CObj__PMP_IO.h"


#define CMMD__INIT				"INIT"


// ...
int CObj__PMP_IO
::Call__INIT(CII_OBJECT__VARIABLE *p_variable)
{
	if(iPUMP__CTRL_TYPE = _PMP_CTRL_TYPE__OBJECT)
	{
		return pOBJ_CTRL__PUMP->Call__OBJECT(CMMD__INIT);
	}
	
	if(iPUMP__CTRL_TYPE = _PMP_CTRL_TYPE__IO)
	{
		return dEXT_CH__DO_PUMP_SET->Set__DATA(STR__ON);
	}
	return 1;
}

int CObj__PMP_IO
::Call__PUMP_ON(CII_OBJECT__VARIABLE *p_variable)
{
	if(iPUMP__CTRL_TYPE = _PMP_CTRL_TYPE__OBJECT)
	{
		return pOBJ_CTRL__PUMP->Call__OBJECT(sPUMP_MODE__ON);
	}
	
	if(iPUMP__CTRL_TYPE = _PMP_CTRL_TYPE__IO)
	{
		return dEXT_CH__DO_PUMP_SET->Set__DATA(STR__ON);
	}
	return 1;
}
int CObj__PMP_IO
::Call__PUMP_OFF(CII_OBJECT__VARIABLE *p_variable)
{
	if(iPUMP__CTRL_TYPE = _PMP_CTRL_TYPE__OBJECT)
	{
		return pOBJ_CTRL__PUMP->Call__OBJECT(sPUMP_MODE__OFF);
	}
	
	if(iPUMP__CTRL_TYPE = _PMP_CTRL_TYPE__IO)
	{
		return dEXT_CH__DO_PUMP_SET->Set__DATA(STR__ON);
	}
	return 1;
}
