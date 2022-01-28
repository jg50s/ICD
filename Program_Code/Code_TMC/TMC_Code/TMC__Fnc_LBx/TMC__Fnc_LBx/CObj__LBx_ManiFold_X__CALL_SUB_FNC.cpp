#include "StdAfx.h"
#include "CObj__LBx_ManiFold_X.h"
#include "CObj__LBx_ManiFold_X__DEF.h"


// ...
int  CObj__LBx_ManiFold_X
::Check__OBJECT_BUSY(const CString& obj_sts)
{
	if(obj_sts.CompareNoCase(STR__AVAILABLE) == 0)		return -1;
	if(obj_sts.CompareNoCase(STR__ABORTED) == 0)		return -1;
	if(obj_sts.CompareNoCase(STR__IDLE) == 0)			return -1;

	return 1;
}

// ...
bool CObj__LBx_ManiFold_X::Is__ALL_DV_OPEN()
{
	bool active__all_open = true;

	for(int i=0; i<iLBx_SLOT_SIZE; i++)
	{
		if(dEXT_CH__DOOR_VLV_STATUS_X[i]->Check__DATA(STR__OPEN) > 0)
			continue;

		active__all_open = false;
		break;
	}

	return active__all_open;
}
bool CObj__LBx_ManiFold_X::Is__ANY_DV_OPEN()
{
	bool active__any_open = false;

	for(int i=0; i<iLBx_SLOT_SIZE; i++)
	{
		if(dEXT_CH__DOOR_VLV_STATUS_X[i]->Check__DATA(STR__OPEN) < 0)
			continue;

		active__any_open = true;
		break;
	}

	return active__any_open;
}
bool CObj__LBx_ManiFold_X::Is__SLOT_DV_OPEN()
{
	int para_id = (int)	aCH__PARA_SLOT_ID->Get__VALUE();
	int p_index = para_id - 1;

	if(p_index <  0)					return false;
	if(p_index >= iLBx_SLOT_SIZE)		return false;

	//
	if(dEXT_CH__DOOR_VLV_STATUS_X[p_index]->Check__DATA(STR__OPEN) < 0)		return false;

	return true;
}

bool CObj__LBx_ManiFold_X::Is__ALL_SV_OPEN()
{
	bool active__all_open = true;

	for(int i=0; i<iLBx_SLOT_SIZE; i++)
	{
		if(dEXT_CH__VAC_VLV_STATUS_X[i]->Check__DATA(STR__OPEN) > 0)
			continue;

		active__all_open = false;
		break;
	}

	return active__all_open;
}
bool CObj__LBx_ManiFold_X::Is__ALL_SV_CLOSE()
{
	bool active__all_close = true;

	for(int i=0; i<iLBx_SLOT_SIZE; i++)
	{
		if(dEXT_CH__VAC_VLV_STATUS_X[i]->Check__DATA(STR__CLOSE) > 0)
			continue;

		active__all_close = false;
		break;
	}

	return active__all_close;
}
bool CObj__LBx_ManiFold_X::Is__ANY_SV_OPEN()
{
	bool active__any_open = false;

	for(int i=0; i<iLBx_SLOT_SIZE; i++)
	{
		if(dEXT_CH__VAC_VLV_STATUS_X[i]->Check__DATA(STR__OPEN) < 0)
			continue;

		active__any_open = true;
		break;
	}

	return active__any_open;
}
bool CObj__LBx_ManiFold_X::Is__SLOT_SV_OPEN()
{
	int para_id = (int)	aCH__PARA_SLOT_ID->Get__VALUE();
	int p_index = para_id - 1;

	if(p_index <  0)					return false;
	if(p_index >= iLBx_SLOT_SIZE)		return false;

	//
	if(dEXT_CH__VAC_VLV_STATUS_X[p_index]->Check__DATA(STR__OPEN)  < 0)		return false;

	return true;
}
