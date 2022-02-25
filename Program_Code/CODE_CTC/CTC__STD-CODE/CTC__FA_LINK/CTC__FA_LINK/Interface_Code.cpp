#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj_FA__APP_CTRL.h"
/*
#include "CObj_FA__PMx_CEID.h"
#include "CObj_FA__E30_CTRL.h"
#include "CObj_FA__E40_CTRL.h"
#include "CObj_FA__E94_CTRL.h"
*/


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
#define CLS__APP_CTRL		"APP.CTRL"
/*
#define CLS__PMx_CEID		"PMx.CEID"
#define CLS__E30_CTRL		"E30.CTRL"
#define CLS__E40_CTRL		"E40.CTRL"
#define CLS__E94_CTRL		"E94.CTRL"
*/


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__APP_CTRL);
/*
ADD__OBJ_CLS(CLS__PMx_CEID);
ADD__OBJ_CLS(CLS__E30_CTRL);
ADD__OBJ_CLS(CLS__E40_CTRL);
ADD__OBJ_CLS(CLS__E94_CTRL);
*/

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__APP_CTRL)		return (new CObj_FA__APP_CTRL);
/*
IF__OBJ_CLS(CLS__PMx_CEID)		return (new CObj_FA__PMx_CEID);
IF__OBJ_CLS(CLS__E30_CTRL)		return (new CObj_FA__E30_CTRL);
IF__OBJ_CLS(CLS__E40_CTRL)		return (new CObj_FA__E40_CTRL);
IF__OBJ_CLS(CLS__E94_CTRL)		return (new CObj_FA__E94_CTRL);
*/

DECLARE_END__DLL_STD_OBJ__CREATE_LINK
