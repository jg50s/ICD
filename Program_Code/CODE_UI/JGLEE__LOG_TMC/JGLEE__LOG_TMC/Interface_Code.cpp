#include "StdAfx.h"

#include "CObj__DA_Log_STD.h"


//--------------------------------------------------------------------------------------
extern "C" __declspec(dllexport) 
GObj__Interface_Ctrl* Create_GObj(const CString& str_gobj)
{
	CString cls_name = str_gobj;
	CString gobj_name;

	// ...
	{
		gobj_name = "DA_LOG.STD";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__DA_Log_STD);
		}
	}

	return NULL;
}
