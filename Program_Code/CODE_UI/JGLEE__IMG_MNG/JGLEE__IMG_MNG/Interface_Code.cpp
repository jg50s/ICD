#include "StdAfx.h"
#include "Interface_Header.h"

#include "CObj__IMG_ANI.h"
#include "CObj__IMG_LINK.h"
#include "CObj__IMG_RES.h"


// ...
#define  DEF__IMG_ANI								"IMG.ANI"
#define  DEF__IMG_LINK								"IMG.LINK"
#define  DEF__IMG_RES								"IMG.RES"


#define  IF__OBJ(OBJ_NAME)							\
if(str_gobj.CompareNoCase(OBJ_NAME) == 0)			


// ...
extern "C" __declspec(dllexport) 
GObj__Interface_Ctrl* Create_GObj(const CString& str_gobj)
{
	IF__OBJ(DEF__IMG_ANI)						return (new CObj__IMG_ANI);
	IF__OBJ(DEF__IMG_LINK)						return (new CObj__IMG_LINK);
	IF__OBJ(DEF__IMG_RES)						return (new CObj__IMG_RES);

	return NULL;
}
