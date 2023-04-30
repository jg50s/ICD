#include "StdAfx.h"

#include "CObj__Route_EDIT.h"
#include "CObj__Route_STD.h"

#include "CObj__Compare_CFG.h"
#include "CObj__Compare_STD.h"

#include "CObj__PMx_Recipe_Select.h"


//--------------------------------------------------------------------------------------
extern "C" __declspec(dllexport) 
GObj__Interface_Ctrl* Create_GObj(const CString& str_gobj)
{
	CString cls_name = str_gobj;
	CString gobj_name;

	// ...
	{
		gobj_name = "ROUTE.EDIT";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__Route_EDIT);
		}
	}
	// ...
	{
		gobj_name = "ROUTE.STD";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__Route_STD);
		}
	}

	// ...
	{
		gobj_name = "COMPARE.CFG";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__Compare_CFG);
		}
	}
	// ...
	{
		gobj_name = "COMPARE.STD";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__Compare_STD);
		}
	}

	// ...
	{
		gobj_name = "PMx_RECIPE.SELECT";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__PMx_Recipe_Select);
		}
	}

	return NULL;
}
