#include "StdAfx.h"
#include "CObj_FA__APP_CTRL.h"


#include "CMacro_FA.h"
extern CMacro_FA mFA_Link;


// ...
int CObj_FA__APP_CTRL::__CLOSE__OBJECT()
{
	mFA_Link.SEPARATE();
	return 1;
}
