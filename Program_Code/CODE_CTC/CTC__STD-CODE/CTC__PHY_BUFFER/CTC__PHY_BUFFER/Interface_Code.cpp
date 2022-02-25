#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj_Phy__BUFFER_MNG.h"
#include "CObj_Phy__BUFFER_STD.h"



//----------------------------------------------------------
DECLARE_START__DLL_STD_OBJ__GET_VERSION

#ifdef _DEBUG
debug_mode =  1;
#else
debug_mode = -1;			
#endif

DECLARE_END__DLL_STD_OBJ__GET_VERSION
//----------------------------------------------------------


//----------------------------------------------------------
#define CLS__BUFFER_MNG					"BUFFER.MNG"
#define CLS__BUFFER_STD					"BUFFER.STD"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__BUFFER_MNG);
ADD__OBJ_CLS(CLS__BUFFER_STD);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__BUFFER_MNG)			return (new CObj_Phy__BUFFER_MNG);
IF__OBJ_CLS(CLS__BUFFER_STD)			return (new CObj_Phy__BUFFER_STD);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK
