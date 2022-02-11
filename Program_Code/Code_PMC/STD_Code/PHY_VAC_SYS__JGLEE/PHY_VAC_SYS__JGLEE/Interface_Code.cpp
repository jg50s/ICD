#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__VAC_VLV_PHY.h"

#include "CObj__TMP_IO.h"
#include "CObj__PMP_IO.h"

#include "CObj__VAT_IO.h"



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
#define CLS__VAC_VLV_PHY					"VAC_VLV.PHY"

#define CLS__TMP_IO							"TMP.IO"
#define CLS__PMP_IO							"PMP.IO"

#define CLS__VAT_IO							"VAT.IO"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__VAC_VLV_PHY);

ADD__OBJ_CLS(CLS__TMP_IO);
ADD__OBJ_CLS(CLS__PMP_IO);

ADD__OBJ_CLS(CLS__VAT_IO);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__VAC_VLV_PHY)				return (new CObj__VAC_VLV_PHY);

IF__OBJ_CLS(CLS__TMP_IO)					return (new CObj__TMP_IO);
IF__OBJ_CLS(CLS__PMP_IO)					return (new CObj__PMP_IO);

IF__OBJ_CLS(CLS__VAT_IO)					return (new CObj__VAT_IO);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK

