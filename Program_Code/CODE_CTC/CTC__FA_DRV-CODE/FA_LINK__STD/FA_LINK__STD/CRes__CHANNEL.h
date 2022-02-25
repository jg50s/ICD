#pragma once

#include "Interface_Code.h"

#define _CFG__LPx_SIZE						5


class CRes__CHANNEL
{
private:
	bool bActive__INIT_CHANNEL;

public:
	SCX__STRING_CHANNEL sCH__CMS_UPDATE_FLAG__LPx[_CFG__LPx_SIZE];

public:
	CRes__CHANNEL();
	~CRes__CHANNEL();

	// ...
	void Init__CHANNEL();

	void Set__CMS_Update_Flag_Of_LPx(const int lp_id);
};
