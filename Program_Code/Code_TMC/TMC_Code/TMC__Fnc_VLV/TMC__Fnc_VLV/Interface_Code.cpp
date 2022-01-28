#include "StdAfx.h"

#include "Interface_Code.h"

#include "CObj__TMC_EX.h"
#include "CObj__TMC_ManiFold_X.h"
#include "CObj__TMC_STD.h"

#include "CObj__TwoManiFold_TM.h"
#include "CObj__OneManiFold_TM.h"

#include "CObj__PMC_STD.h"
#include "CObj__OneManiFold_STD.h"

#include "CObj__TwoManiFold_LL.h"
#include "CObj__OneManiFold_LL.h"


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
#define CLS__TMC_EX						"TMC.EX"
#define CLS__TMC_ManiFold_X				"TMC.ManiFold_X"
#define CLS__TMC_STD					"TMC.STD"

#define CLS__TwoManiFold_TM			    "TwoManiFold.TM"
#define CLS__OneManiFold_TM			    "OneManiFold.TM"

#define CLS__PMC_STD					"PMC.STD"
#define CLS__OneManiFold_STD			"OneManiFold.STD"

#define CLS__TwoManiFold_LL			    "TwoManiFold.LL"
#define CLS__OneManiFold_LL			    "OneManiFold.LL"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

	ADD__OBJ_CLS(CLS__TMC_EX);
	ADD__OBJ_CLS(CLS__TMC_ManiFold_X);
	ADD__OBJ_CLS(CLS__TMC_STD);

	ADD__OBJ_CLS(CLS__TwoManiFold_TM);
	ADD__OBJ_CLS(CLS__OneManiFold_TM);

	ADD__OBJ_CLS(CLS__PMC_STD);
	ADD__OBJ_CLS(CLS__OneManiFold_STD);

	ADD__OBJ_CLS(CLS__TwoManiFold_LL);
	ADD__OBJ_CLS(CLS__OneManiFold_LL);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

	IF__OBJ_CLS(CLS__TMC_EX)				return (new CObj__TMC_EX);
	IF__OBJ_CLS(CLS__TMC_ManiFold_X)		return (new CObj__TMC_ManiFold_X);
	IF__OBJ_CLS(CLS__TMC_STD)				return (new CObj__TMC_STD);

	IF__OBJ_CLS(CLS__TwoManiFold_TM)		return (new CObj__TwoManiFold_TM);
	IF__OBJ_CLS(CLS__OneManiFold_TM)		return (new CObj__OneManiFold_TM);

	IF__OBJ_CLS(CLS__PMC_STD)				return (new CObj__PMC_STD);
	IF__OBJ_CLS(CLS__OneManiFold_STD)		return (new CObj__OneManiFold_STD);

	IF__OBJ_CLS(CLS__TwoManiFold_LL)		return (new CObj__TwoManiFold_LL);
	IF__OBJ_CLS(CLS__OneManiFold_LL)		return (new CObj__OneManiFold_LL);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK
