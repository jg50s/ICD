#include "StdAfx.h"
#include "CObj__PMC_OPR.h"

#include "CObj__PMC_OPR__ALID.h"
#include "CObj__PMC_OPR__DEF.h"


// ...
int CObj__PMC_OPR
::Call__PICK_READY(CII_OBJECT__VARIABLE *p_variable)
{
	if(bActive__OBJ_CTRL__CHAMBER)
	{
		int r_flag = pOBJ_CTRL__CHAMBER->Call__OBJECT(sMODE__PICK_READY);
		if(r_flag < 0)		return -11;
	}

	if(Fnc__TRANSFER_READY(p_variable, true) < 0)
	{
		return -12;
	}
	return 1;
}
int CObj__PMC_OPR
::Call__PICK_X_READY(CII_OBJECT__VARIABLE *p_variable)
{
	if(bActive__OBJ_CTRL__CHAMBER)
	{
		int r_flag = pOBJ_CTRL__CHAMBER->Call__OBJECT(sMODE__PICK_X_READY);
		if(r_flag < 0)		return -11;
	}

	if(Fnc__TRANSFER_READY(p_variable, true) < 0)
	{
		return -12;
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
	if(bActive__OBJ_CTRL__CHAMBER)
	{
		int r_flag = pOBJ_CTRL__CHAMBER->Call__OBJECT(sMODE__PLACE_READY);
		if(r_flag < 0)		return -11;
	}

	if(Fnc__TRANSFER_READY(p_variable, false) < 0)
	{
		return -12;
	}
	return 1;
}
int CObj__PMC_OPR
::Call__PLACE_X_READY(CII_OBJECT__VARIABLE *p_variable)
{
	if(bActive__OBJ_CTRL__CHAMBER)
	{
		int r_flag = pOBJ_CTRL__CHAMBER->Call__OBJECT(sMODE__PLACE_X_READY);
		if(r_flag < 0)		return -11;
	}

	if(Fnc__TRANSFER_READY(p_variable, false) < 0)
	{
		return -12;
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
::Fnc__TRANSFER_READY(CII_OBJECT__VARIABLE *p_variable, const bool active__pick_ready)
{
	if(bActive__OBJ_CTRL__LIFT_PIN)
	{
		bool active__lift_pin_ctrl = true;

		CString para_data = sCH__PARA_MANUAL_MOVE_LIFT_PIN_SKIP->Get__STRING();
		if(para_data.Find(STR__YES) >= 0)		active__lift_pin_ctrl = false;		

		if(active__lift_pin_ctrl)
		{
			if(active__pick_ready)
			{
				if(bActive__LIFT_PIN__PICK_READY)
				{
					int r_flag = pOBJ_CTRL__LIFT_PIN->Call__OBJECT(sLINK_MODE__LIFT_PIN__PICK_READY);
					if(r_flag < 0)			return -101;
				}
			}
			else
			{
				if(bActive__LIFT_PIN__PLACE_READY)
				{
					int r_flag = pOBJ_CTRL__LIFT_PIN->Call__OBJECT(sLINK_MODE__LIFT_PIN__PLACE_READY);
					if(r_flag < 0)			return -102;
				}
			}
		}
	}

	if(bActive__OBJ_CTRL__SHUTTER)
	{
		int r_flag = pOBJ_CTRL__SHUTTER->Call__OBJECT(sLINK_MODE__SHUTTER__OPEN);
		if(r_flag < 0)			return -11;
	}

	if(bActive__OBJ_CTRL__PM_SLOT)
	{
		int r_flag = pOBJ_CTRL__PM_SLOT->Call__OBJECT(sLINK_MODE__PM_SLOT__OPEN);
		if(r_flag < 0)			return -21;
	}

	return 1;
}
int CObj__PMC_OPR
::Fnc__TRANSFER_COMPLETE(CII_OBJECT__VARIABLE *p_variable)
{
	bool active__pm_slot_ctrl = true;

	CString para_data = sCH__PARA_MANUAL_MOVE_SLOT_CLOSE_SKIP->Get__STRING();
	if(para_data.Find(STR__YES) >= 0)		active__pm_slot_ctrl = false;

	if(active__pm_slot_ctrl)
	{
		if(bActive__OBJ_CTRL__PM_SLOT)
		{
			int r_flag = pOBJ_CTRL__PM_SLOT->Call__OBJECT(sLINK_MODE__PM_SLOT__CLOSE);
			if(r_flag < 0)			return -11;
		}
		if(bActive__OBJ_CTRL__SHUTTER)
		{
			int r_flag = pOBJ_CTRL__SHUTTER->Call__OBJECT(sLINK_MODE__SHUTTER__CLOSE);
			if(r_flag < 0)			return -21;
		}

		if(bActive__OBJ_CTRL__LIFT_PIN)
		{
			bool active__lift_pin_ctrl = true;

			CString para_data = sCH__PARA_MANUAL_MOVE_LIFT_PIN_SKIP->Get__STRING();
			if(para_data.Find(STR__YES) >= 0)		active__lift_pin_ctrl = false;		

			if(active__lift_pin_ctrl)
			{
				int r_flag = pOBJ_CTRL__LIFT_PIN->Call__OBJECT(sLINK_MODE__LIFT_PIN__TRANSFER_COMPLETE);
				if(r_flag < 0)			return -31;
			}
		}
	}

	return 1;
}

// ...
int CObj__PMC_OPR
::Call__SLOT_OPEN(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	if(bActive__OBJ_CTRL__SHUTTER)
	{
		int r_flag = pOBJ_CTRL__SHUTTER->Call__OBJECT(sLINK_MODE__SHUTTER__OPEN);
		if(r_flag < 0)			return -11;
	}

	if(bActive__OBJ_CTRL__PM_SLOT)
	{
		int r_flag = pOBJ_CTRL__PM_SLOT->Call__OBJECT(sLINK_MODE__PM_SLOT__OPEN);
		if(r_flag < 0)			return -21;
	}

	return 1;
}
int CObj__PMC_OPR
::Call__SLOT_CLOSE(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	if(bActive__OBJ_CTRL__PM_SLOT)
	{
		int r_flag = pOBJ_CTRL__PM_SLOT->Call__OBJECT(sLINK_MODE__PM_SLOT__CLOSE);
		if(r_flag < 0)			return -11;
	}

	if(bActive__OBJ_CTRL__SHUTTER)
	{
		int r_flag = pOBJ_CTRL__SHUTTER->Call__OBJECT(sLINK_MODE__SHUTTER__CLOSE);
		if(r_flag < 0)			return -21;
	}

	return 1;
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
