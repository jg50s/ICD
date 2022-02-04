#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__MFC_FLOW_CHECK.h"
#include "CObj__RF_CONDUCT.h"
#include "CObj__APC_POS_CONDUCT.h"
#include "CObj__FRC_CHECK.h"
#include "CObj__GAUGE_CHECK.h"
#include "CObj__DGF_CHECK.h"

#include "CObj__AUTO_PM.h"


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
#define CLS__MFC_FLOW_CHECK						"MFC.FLOW.CHECK"
#define CLS__RF_CONDUCT							"RF.CONDUCT"
#define CLS__APC_POS_CONDUCT					"APC.POS.CONDUCT"
#define CLS__FRC_CHECK							"FRC.CHECK"
#define CLS__GAUGE_CHECK						"GAUGE.CHECK"
#define CLS__DGF_CHECK							"DGF.CHECK"

#define CLS__AUTO_PM							"AUTO.PM"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__MFC_FLOW_CHECK)
ADD__OBJ_CLS(CLS__RF_CONDUCT)
ADD__OBJ_CLS(CLS__APC_POS_CONDUCT)
ADD__OBJ_CLS(CLS__FRC_CHECK)
ADD__OBJ_CLS(CLS__GAUGE_CHECK)
ADD__OBJ_CLS(CLS__DGF_CHECK)

ADD__OBJ_CLS(CLS__AUTO_PM)

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__MFC_FLOW_CHECK)				return (new CObj__MFC_FLOW_CHECK);
IF__OBJ_CLS(CLS__RF_CONDUCT)					return (new CObj__RF_CONDUCT);
IF__OBJ_CLS(CLS__APC_POS_CONDUCT)				return (new CObj__APC_POS_CONDUCT);
IF__OBJ_CLS(CLS__FRC_CHECK)						return (new CObj__FRC_CHECK);
IF__OBJ_CLS(CLS__GAUGE_CHECK)					return (new CObj__GAUGE_CHECK);
IF__OBJ_CLS(CLS__DGF_CHECK)						return (new CObj__DGF_CHECK);

IF__OBJ_CLS(CLS__AUTO_PM)						return (new CObj__AUTO_PM);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK

