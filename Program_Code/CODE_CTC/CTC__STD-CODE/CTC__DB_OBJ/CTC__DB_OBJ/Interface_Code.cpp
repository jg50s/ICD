#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__DB_CFG.h"
#include "CObj__DB_GUI.h"


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
#define CLS__DB_CFG							"DB.CFG"
#define CLS__DB_GUI							"DB.GUI"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__DB_CFG);
ADD__OBJ_CLS(CLS__DB_GUI);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__DB_CFG)				return (new CObj__DB_CFG);
IF__OBJ_CLS(CLS__DB_GUI)				return (new CObj__DB_GUI);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK
