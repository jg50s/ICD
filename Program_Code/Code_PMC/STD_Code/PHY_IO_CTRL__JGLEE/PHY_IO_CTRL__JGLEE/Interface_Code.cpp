#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__CHM_IO.h"

#include "CObj__INTERLOCK_GAS_BOX.h"
#include "CObj__INTERLOCK_IO.h"

#include "CObj__LIFT_PIN_IO.h"
#include "CObj__PM_SLOT_IO.h"
#include "CObj__RF_IO.h"
#include "CObj__SHUTTER_IO.h"



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
#define CLS__CHM_IO									"CHM.IO"

#define CLS__INTERLOCK_GAS_BOX						"INTERLOCK.GAS_BOX"
#define CLS__INTERLOCK_IO							"INTERLOCK.IO"

#define CLS__LIFT_PIN_IO							"LIFT_PIN.IO"
#define CLS__PM_SLOT_IO								"PM_SLOT.IO"
#define CLS__RF_IO									"RF.IO"
#define CLS__SHUTTER_IO								"SHUTTER.IO"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__CHM_IO);

ADD__OBJ_CLS(CLS__INTERLOCK_GAS_BOX);
ADD__OBJ_CLS(CLS__INTERLOCK_IO);

ADD__OBJ_CLS(CLS__LIFT_PIN_IO);
ADD__OBJ_CLS(CLS__PM_SLOT_IO);
ADD__OBJ_CLS(CLS__RF_IO);
ADD__OBJ_CLS(CLS__SHUTTER_IO);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__CHM_IO)							return (new CObj__CHM_IO);

IF__OBJ_CLS(CLS__INTERLOCK_GAS_BOX)					return (new CObj__INTERLOCK_GAS_BOX);
IF__OBJ_CLS(CLS__INTERLOCK_IO)						return (new CObj__INTERLOCK_IO);

IF__OBJ_CLS(CLS__LIFT_PIN_IO)						return (new CObj__LIFT_PIN_IO);
IF__OBJ_CLS(CLS__PM_SLOT_IO)						return (new CObj__PM_SLOT_IO);
IF__OBJ_CLS(CLS__RF_IO)								return (new CObj__RF_IO);
IF__OBJ_CLS(CLS__SHUTTER_IO)						return (new CObj__SHUTTER_IO);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK

