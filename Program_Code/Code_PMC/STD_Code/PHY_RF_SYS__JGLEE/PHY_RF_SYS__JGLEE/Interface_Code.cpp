#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__ESC_IO.h"
#include "CObj__ESC_OBJ.h"

#include "CObj__HE_PRESSURE.h"
#include "CObj__HE_VLV.h"
#include "CObj__RF_STD.h"



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
#define CLS__ESC_IO								"ESC.IO"
#define CLS__ESC_OBJ							"ESC.OBJ"

#define CLS__HE_PRESSURE						"HE.PRESSURE"
#define CLS__HE_VLV								"HE.VLV"
#define CLS__RF_STD								"RF.STD"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__ESC_IO)
ADD__OBJ_CLS(CLS__ESC_OBJ)

ADD__OBJ_CLS(CLS__HE_PRESSURE)
ADD__OBJ_CLS(CLS__HE_VLV)
ADD__OBJ_CLS(CLS__RF_STD)

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__ESC_IO)						return (new CObj__ESC_IO);
IF__OBJ_CLS(CLS__ESC_OBJ)						return (new CObj__ESC_OBJ);

IF__OBJ_CLS(CLS__HE_PRESSURE)					return (new CObj__HE_PRESSURE);
IF__OBJ_CLS(CLS__HE_VLV)						return (new CObj__HE_VLV);
IF__OBJ_CLS(CLS__RF_STD)						return (new CObj__RF_STD);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK
