#include "StdAfx.h"

#include "CObj__PROCESS_STD.h"


// ...
#define  DEF__PROCESS_STD				"PROCESS.STD"


// ...
#define  IF__OBJ(OBJ_NAME)							\
if(str_gobj.CompareNoCase(OBJ_NAME) == 0)			


// ...
extern "C" __declspec(dllexport) 
GObj__Interface_Ctrl* Create_GObj(const CString& str_gobj)
{
	IF__OBJ(DEF__PROCESS_STD)			return (new CObj__PROCESS_STD);

	return NULL;
}
