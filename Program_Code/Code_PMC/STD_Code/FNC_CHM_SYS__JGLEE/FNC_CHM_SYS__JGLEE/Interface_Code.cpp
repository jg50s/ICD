#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__PMC_INF.h"
#include "CObj__ACTIVE_HANDOFF_INF.h"

#include "CObj__PMC_OPR.h"

#include "CObj__SYSTEM_STD.h"
#include "CObj__CHM_FNC.h"
#include "CObj__TRANSFER_FNC.h"


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
#define CLS__PMC_INF						"PMC.INF"
#define CLS__ACTIVE_HANDOFF_INF				"ACTIVE_HANDOFF.INF"

#define CLS__PMC_OPR						"PMC.OPR"

#define CLS__SYSTEM_STD						"SYSTEM.STD"
#define CLS__CHM_FNC						"CHM.FNC"
#define CLS__TRANSFER_FNC					"TRANSFER.FNC"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__PMC_INF);
ADD__OBJ_CLS(CLS__ACTIVE_HANDOFF_INF);

ADD__OBJ_CLS(CLS__PMC_OPR);

ADD__OBJ_CLS(CLS__SYSTEM_STD);
ADD__OBJ_CLS(CLS__CHM_FNC);
ADD__OBJ_CLS(CLS__TRANSFER_FNC);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__PMC_INF)					return (new CObj__PMC_INF);
IF__OBJ_CLS(CLS__ACTIVE_HANDOFF_INF)		return (new CObj__ACTIVE_HANDOFF_INF);

IF__OBJ_CLS(CLS__PMC_OPR)					return (new CObj__PMC_OPR);

IF__OBJ_CLS(CLS__SYSTEM_STD)				return (new CObj__SYSTEM_STD);
IF__OBJ_CLS(CLS__CHM_FNC)					return (new CObj__CHM_FNC);
IF__OBJ_CLS(CLS__TRANSFER_FNC)				return (new CObj__TRANSFER_FNC);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK

