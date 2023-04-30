#include "StdAfx.h"

#include "CObj__PARTICLE_TABLE.h"


//--------------------------------------------------------------------------------------
extern "C" __declspec(dllexport) 
GObj__Interface_Ctrl* Create_GObj(const CString& str_gobj)
{
	CString cls_name = str_gobj;
	CString gobj_name;

	// ...
	{
		gobj_name = "PARTICLE.TABLE";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__PARTICLE_TABLE);
		}
	}

	return NULL;
}
