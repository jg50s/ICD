#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__PMx_EX.h"
#include "CObj_Mng__PMx_INFO.h"

#include "CObj_Mng__LPx_INFO.h"
#include "CObj_Mng__CTC_INFO.h"
#include "CObj_Mng__TMC_INFO.h"



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
#define CLS__PMx_EX					"PMx.EX"
#define CLS__PMx_INFO				"PMx.INFO"

#define CLS__LPx_INFO				"LPx.INFO"
#define CLS__CTC_INFO				"CTC.INFO"
#define CLS__TMC_INFO				"TMC.INFO"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__PMx_EX);
ADD__OBJ_CLS(CLS__PMx_INFO);

ADD__OBJ_CLS(CLS__LPx_INFO);
ADD__OBJ_CLS(CLS__CTC_INFO);
ADD__OBJ_CLS(CLS__TMC_INFO);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__PMx_EX)			return (new CObj__PMx_EX);
IF__OBJ_CLS(CLS__PMx_INFO)			return (new CObj_Mng__PMx_INFO);

IF__OBJ_CLS(CLS__LPx_INFO)			return (new CObj_Mng__LPx_INFO);
IF__OBJ_CLS(CLS__CTC_INFO)			return (new CObj_Mng__CTC_INFO);
IF__OBJ_CLS(CLS__TMC_INFO)			return (new CObj_Mng__TMC_INFO);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK
