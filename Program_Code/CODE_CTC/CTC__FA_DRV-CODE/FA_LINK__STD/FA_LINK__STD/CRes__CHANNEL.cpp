#include "stdafx.h"
#include "CRes__CHANNEL.h"


CRes__CHANNEL mRes__CHANNEL;


// ...
CRes__CHANNEL::CRes__CHANNEL()
{
	bActive__INIT_CHANNEL = false;
}
CRes__CHANNEL::~CRes__CHANNEL()
{

}

void CRes__CHANNEL::Init__CHANNEL()
{
	if(bActive__INIT_CHANNEL)			return;
	bActive__INIT_CHANNEL = true;

	// ...
	CString obj_name;
	CString var_name;
	CString ch_name;

	int i_limit;
	int i;

	// ...
	obj_name = "FA_APP_CTRL";

	// LPx ...
	for(i=0; i<_CFG__LPx_SIZE; i++)
	{
		var_name.Format("CMS.UPDATE.FLAG.LP%1d", i+1);
		ch_name.Format("%s+%s", obj_name,var_name);

		sCH__CMS_UPDATE_FLAG__LPx[i]->Register__CHANNEL_NAME(ch_name);
	}
}

void CRes__CHANNEL::Set__CMS_Update_Flag_Of_LPx(const int lp_id)
{
	if(lp_id < 1)					return;
	if(lp_id > _CFG__LPx_SIZE)		return;

	sCH__CMS_UPDATE_FLAG__LPx[lp_id-1]->Set__DATA("YES");
}
