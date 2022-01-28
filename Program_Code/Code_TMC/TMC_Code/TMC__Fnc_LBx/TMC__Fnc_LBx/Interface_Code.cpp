#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__LBx_OneManiFold.h"
#include "CObj__LBx_TEST.h"
#include "CObj__LBx_SLOT_TEST.h"
#include "CObj__LBx_TwoManiFold.h"
#include "CObj__LBx_ManiFold_X.h"
#include "CObj__ManiFold_TEST.h"


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
#define CLS__LBx_OneManiFold			"LBx.OneManiFold"
#define CLS__LBx_TEST					"LBx.TEST"
#define CLS__LBx_SLOT_TEST				"LBx_SLOT.TEST"
#define CLS__LBx_TwoManiFold			"LBx.TwoManiFold"
#define CLS__LBx_ManiFold_X			    "LBx.ManiFold_X"
#define CLS__ManiFold_TEST			    "ManiFold.TEST"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__LBx_OneManiFold);
ADD__OBJ_CLS(CLS__LBx_TEST);
ADD__OBJ_CLS(CLS__LBx_SLOT_TEST);
ADD__OBJ_CLS(CLS__LBx_TwoManiFold);
ADD__OBJ_CLS(CLS__LBx_ManiFold_X);
ADD__OBJ_CLS(CLS__ManiFold_TEST);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__LBx_OneManiFold)		return (new CObj__LBx_OneManiFold);
IF__OBJ_CLS(CLS__LBx_TEST)				return (new CObj__LBx_TEST);
IF__OBJ_CLS(CLS__LBx_SLOT_TEST)			return (new CObj__LBx_SLOT_TEST);
IF__OBJ_CLS(CLS__LBx_TwoManiFold)		return (new CObj__LBx_TwoManiFold);
IF__OBJ_CLS(CLS__LBx_ManiFold_X)		return (new CObj__LBx_ManiFold_X);
IF__OBJ_CLS(CLS__ManiFold_TEST)			return (new CObj__ManiFold_TEST);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK
