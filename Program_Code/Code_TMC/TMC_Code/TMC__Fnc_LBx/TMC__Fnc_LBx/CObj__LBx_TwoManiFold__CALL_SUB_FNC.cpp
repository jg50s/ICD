#include "StdAfx.h"
#include "CObj__LBx_TwoManiFold.h"
#include "CObj__LBx_TwoManiFold__DEF.h"


// ...
int  CObj__LBx_TwoManiFold
::Check__OBJECT_BUSY(const CString& obj_sts)
{
	if(obj_sts.CompareNoCase(STR__AVAILABLE) == 0)		return -1;
	if(obj_sts.CompareNoCase(STR__ABORTED) == 0)		return -1;
	if(obj_sts.CompareNoCase(STR__IDLE) == 0)			return -1;

	return 1;
}
