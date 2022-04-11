#include "StdAfx.h"
#include "CObj__PMC_OPR.h"

#include "CObj__PMC_OPR__ALID.h"
#include "CObj__PMC_OPR__DEF.h"


// ...
int CObj__PMC_OPR
::Call__PICK_READY(CII_OBJECT__VARIABLE *p_variable)
{
	if(Fnc__TRANSFER_READY(p_variable) < 0)
	{
		return -1;
	}

	if(bActive__OBJ_CTRL__CHAMBER)
	{
		return pOBJ_CTRL__CHAMBER->Call__OBJECT(sMODE__PICK_READY);
	}
	return 1;
}
int CObj__PMC_OPR
::Call__PICK_X_READY(CII_OBJECT__VARIABLE *p_variable)
{
	if(Fnc__TRANSFER_READY(p_variable) < 0)
	{
		return -1;
	}

	if(bActive__OBJ_CTRL__CHAMBER)
	{
		return pOBJ_CTRL__CHAMBER->Call__OBJECT(sMODE__PICK_X_READY);
	}
	return 1;
}

int CObj__PMC_OPR
::Call__PICK_COMPLETE(CII_OBJECT__VARIABLE *p_variable)
{
	if(Fnc__TRANSFER_COMPLETE(p_variable) < 0)
	{
		return -1;
	}

	if(bActive__OBJ_CTRL__CHAMBER)
	{
		return pOBJ_CTRL__CHAMBER->Call__OBJECT(sMODE__PICK_COMPLETE);
	}
	return 1;
}
int CObj__PMC_OPR
::Call__PICK_X_COMPLETE(CII_OBJECT__VARIABLE *p_variable)
{
	if(Fnc__TRANSFER_COMPLETE(p_variable) < 0)
	{
		return -1;
	}

	if(bActive__OBJ_CTRL__CHAMBER)
	{
		return pOBJ_CTRL__CHAMBER->Call__OBJECT(sMODE__PICK_X_COMPLETE);
	}
	return 1;
}

int CObj__PMC_OPR
::Call__PLACE_READY(CII_OBJECT__VARIABLE *p_variable)
{
	if(Fnc__TRANSFER_READY(p_variable) < 0)
	{
		return -1;
	}

	if(bActive__OBJ_CTRL__CHAMBER)
	{
		return pOBJ_CTRL__CHAMBER->Call__OBJECT(sMODE__PLACE_READY);
	}
	return 1;
}
int CObj__PMC_OPR
::Call__PLACE_X_READY(CII_OBJECT__VARIABLE *p_variable)
{
	if(Fnc__TRANSFER_READY(p_variable) < 0)
	{
		return -1;
	}

	if(bActive__OBJ_CTRL__CHAMBER)
	{
		return pOBJ_CTRL__CHAMBER->Call__OBJECT(sMODE__PLACE_X_READY);
	}
	return 1;
}

int CObj__PMC_OPR
::Call__PLACE_COMPLETE(CII_OBJECT__VARIABLE *p_variable)
{
	if(Fnc__TRANSFER_COMPLETE(p_variable) < 0)
	{
		return -1;
	}

	if(bActive__OBJ_CTRL__CHAMBER)
	{
		return pOBJ_CTRL__CHAMBER->Call__OBJECT(sMODE__PLACE_COMPLETE);
	}
	return 1;
}
int CObj__PMC_OPR
::Call__PLACE_X_COMPLETE(CII_OBJECT__VARIABLE *p_variable)
{
	if(Fnc__TRANSFER_COMPLETE(p_variable) < 0)
	{
		return -1;
	}

	if(bActive__OBJ_CTRL__CHAMBER)
	{
		return pOBJ_CTRL__CHAMBER->Call__OBJECT(sMODE__PLACE_X_COMPLETE);
	}
	return 1;
}

int CObj__PMC_OPR
::Fnc__TRANSFER_READY(CII_OBJECT__VARIABLE *p_variable)
{
	if(bActive__OBJ_CTRL__SHUTTER)
	{
		pOBJ_CTRL__SHUTTER->Run__OBJECT(sLINK_MODE__SHUTTER__OPEN);
	}
	if(bActive__OBJ_CTRL__LIFT_PIN)
	{
		pOBJ_CTRL__LIFT_PIN->Run__OBJECT(sLINK_MODE__LIFT_PIN__TRANSFER_READY);
	}

	if(bActive__OBJ_CTRL__SHUTTER)
	{
		if(pOBJ_CTRL__SHUTTER->When__OBJECT() < 0)			return -11;
	}
	if(bActive__OBJ_CTRL__LIFT_PIN)
	{
		if(pOBJ_CTRL__LIFT_PIN->When__OBJECT() < 0)			return -21;
	}

	if(bActive__OBJ_CTRL__PM_SLOT)
	{
		return pOBJ_CTRL__PM_SLOT->Call__OBJECT(sLINK_MODE__PM_SLOT__OPEN);
	}

	return 1;
}
int CObj__PMC_OPR
::Fnc__TRANSFER_COMPLETE(CII_OBJECT__VARIABLE *p_variable)
{
	if(bActive__OBJ_CTRL__SHUTTER)
	{
		pOBJ_CTRL__SHUTTER->Run__OBJECT(sLINK_MODE__SHUTTER__CLOSE);
	}
	if(bActive__OBJ_CTRL__LIFT_PIN)
	{
		pOBJ_CTRL__LIFT_PIN->Run__OBJECT(sLINK_MODE__LIFT_PIN__TRANSFER_COMPLETE);
	}

	if(bActive__OBJ_CTRL__PM_SLOT)
	{
		return pOBJ_CTRL__PM_SLOT->Call__OBJECT(sLINK_MODE__PM_SLOT__CLOSE);
	}
	return 1;
}


// ...
int CObj__PMC_OPR
::Call__SLOT_OPEN(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__SLOT_OPEN);
}
int CObj__PMC_OPR
::Call__SLOT_CLOSE(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__SLOT_CLOSE);
}

int CObj__PMC_OPR
::Call__PIN_UP(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PIN_UP);
}
int CObj__PMC_OPR
::Call__PIN_DOWN(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PIN_DOWN);
}
