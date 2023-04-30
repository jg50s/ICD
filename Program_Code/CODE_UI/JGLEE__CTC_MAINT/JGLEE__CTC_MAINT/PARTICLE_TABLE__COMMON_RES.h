#pragma once

#include "Interface_Code.h"
#include "PARTICLE_TABLE__COMMON_DEF.h"


class CPARTICLE_TABLE__COMMON_RES
{
public:
	GObj__Resource_Info *pGObj_Res;

	//
	CString sDATA__T_Color__IDLE;
	CString sDATA__B_Color__IDLE;

	COLORREF cPARA__T_Color__IDLE;
	COLORREF cPARA__B_Color__IDLE;

	//
	CString sDATA__T_Color__DISABLE;
	CString sDATA__B_Color__DISABLE;

	COLORREF cPARA__T_Color__DISABLE;
	COLORREF cPARA__B_Color__DISABLE;

	//
	CString sDATA__T_Color__RESERVE;
	CString sDATA__B_Color__RESERVE;

	COLORREF cPARA__T_Color__RESERVE;
	COLORREF cPARA__B_Color__RESERVE;

	//
	CString sDATA__T_Color__RUN;
	CString sDATA__B_Color__RUN;

	COLORREF cPARA__T_Color__RUN;
	COLORREF cPARA__B_Color__RUN;

	//
	CString sDATA__T_Color__END;
	CString sDATA__B_Color__END;

	COLORREF cPARA__T_Color__END;
	COLORREF cPARA__B_Color__END;

	//
	CString sDATA__T_Color__ABORT;
	CString sDATA__B_Color__ABORT;

	COLORREF cPARA__T_Color__ABORT;
	COLORREF cPARA__B_Color__ABORT;
	//

public:
	CPARTICLE_TABLE__COMMON_RES();

	//
	void Init__CTRL_STATE();

	int  Get__COLOR_OF_CTRL_STATE(const CString& str_state, COLORREF& t_color,COLORREF& b_color);
};
