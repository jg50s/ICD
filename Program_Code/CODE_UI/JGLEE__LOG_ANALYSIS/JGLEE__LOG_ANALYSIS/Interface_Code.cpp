#include "StdAfx.h"

#include "CObj__Job_History.h"
#include "CObj__PMx_Table.h"
#include "CObj__Wafer_Trace.h"
#include "CObj__Report_Table.h"


//--------------------------------------------------------------------------------------
extern "C" __declspec(dllexport) 
GObj__Interface_Ctrl* Create_GObj(const CString& str_gobj)
{
	CString cls_name = str_gobj;
	CString gobj_name;

	// ...
	{
		gobj_name = "JOB.HISTORY";
		if(cls_name.CompareNoCase(gobj_name) == 0)
			return (new CObj__Job_History);

		gobj_name = "WAFER.TRACE";
		if(cls_name.CompareNoCase(gobj_name) == 0)
			return (new CObj__Wafer_Trace);

		gobj_name = "PMx.TABLE";
		if(cls_name.CompareNoCase(gobj_name) == 0)
			return (new CObj__PMx_Table);

		gobj_name = "REPORT.TABLE";
		if(cls_name.CompareNoCase(gobj_name) == 0)
			return (new CObj__Report_Table);
	}

	return NULL;
}
