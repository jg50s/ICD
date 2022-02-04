#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__GAS_VLV_FNC.h"
#include "CObj__GAS_VLV_PHY.h"

#include "CObj__MFC_IO.h"
#include "CObj__PT_IO.h"

#include "CObj__DGF_FLEX.h"


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
#define CLS__GAS_VLV_FNC				"GAS_VLV.FNC"
#define CLS__GAS_VLV_PHY				"GAS_VLV.PHY"

#define CLS__MFC_IO						"MFC.IO"
#define CLS__PT_IO						"PT.IO"

#define CLS__DFG_FLEX					"DGF.FLEX"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__GAS_VLV_FNC);
ADD__OBJ_CLS(CLS__GAS_VLV_PHY);

ADD__OBJ_CLS(CLS__MFC_IO);
ADD__OBJ_CLS(CLS__PT_IO);

ADD__OBJ_CLS(CLS__DFG_FLEX);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__GAS_VLV_FNC)	   		return (new CObj__GAS_VLV_FNC);
IF__OBJ_CLS(CLS__GAS_VLV_PHY)	   		return (new CObj__GAS_VLV_PHY);

IF__OBJ_CLS(CLS__MFC_IO)		   		return (new CObj__MFC_IO);
IF__OBJ_CLS(CLS__PT_IO)			   		return (new CObj__PT_IO);

IF__OBJ_CLS(CLS__DFG_FLEX)		   		return (new CObj__DGF_FLEX);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK

