#include "StdAfx.h"

#include "CObj__DB_INF.h"
#include "CObj__DB_SYS.h"
#include "CObj__DB_GUI.h"
#include "CObj__DB_ETCHER.h"



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
#define CLS__DB_INF					"DB.INF"
#define CLS__DB_SYS					"DB.SYS"
#define CLS__DB_GUI					"DB.GUI"
#define CLS__DB_ETCHER				"DB.ETCHER"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__DB_INF);
ADD__OBJ_CLS(CLS__DB_SYS);
ADD__OBJ_CLS(CLS__DB_GUI);
ADD__OBJ_CLS(CLS__DB_ETCHER);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__DB_INF)					return (new CObj__DB_INF);
IF__OBJ_CLS(CLS__DB_SYS)					return (new CObj__DB_SYS);
IF__OBJ_CLS(CLS__DB_GUI)					return (new CObj__DB_GUI);
IF__OBJ_CLS(CLS__DB_ETCHER)					return (new CObj__DB_ETCHER);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK
