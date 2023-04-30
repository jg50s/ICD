#include "stdafx.h"
#include "PARTICLE_TABLE__COMMON_RES.h"


CPARTICLE_TABLE__COMMON_RES mRes_Common;


// ...
CPARTICLE_TABLE__COMMON_RES::CPARTICLE_TABLE__COMMON_RES()
{

}

void CPARTICLE_TABLE__COMMON_RES::Init__CTRL_STATE()
{
	CString t_color__idle = sDATA__T_Color__IDLE;
	CString b_color__idle = sDATA__B_Color__IDLE;

	CString t_color__disable = sDATA__T_Color__DISABLE;
	CString b_color__disable = sDATA__B_Color__DISABLE;

	CString t_color__reserve = sDATA__T_Color__RESERVE;
	CString b_color__reserve = sDATA__B_Color__RESERVE;

	CString t_color__run = sDATA__T_Color__RUN;
	CString b_color__run = sDATA__B_Color__RUN;

	CString t_color__end = sDATA__T_Color__END;
	CString b_color__end = sDATA__B_Color__END;

	CString t_color__abort = sDATA__T_Color__ABORT;
	CString b_color__abort = sDATA__B_Color__ABORT;

	// ...
	COLORREF rgb_t_color__idle;
	COLORREF rgb_b_color__idle;

	COLORREF rgb_t_color__disable;
	COLORREF rgb_b_color__disable;

	COLORREF rgb_t_color__reserve;
	COLORREF rgb_b_color__reserve;

	COLORREF rgb_t_color__run;
	COLORREF rgb_b_color__run;

	COLORREF rgb_t_color__end;
	COLORREF rgb_b_color__end;

	COLORREF rgb_t_color__abort;
	COLORREF rgb_b_color__abort;

	// ...
	{
		int r_color, g_color, b_color;

		rgb_t_color__idle = pGObj_Res->pGOBJ_PARA_CTRL->Get_RGB_Color(t_color__idle, r_color,g_color,b_color);
		rgb_b_color__idle = pGObj_Res->pGOBJ_PARA_CTRL->Get_RGB_Color(b_color__idle, r_color,g_color,b_color);

		rgb_t_color__disable = pGObj_Res->pGOBJ_PARA_CTRL->Get_RGB_Color(t_color__disable, r_color,g_color,b_color);
		rgb_b_color__disable = pGObj_Res->pGOBJ_PARA_CTRL->Get_RGB_Color(b_color__disable, r_color,g_color,b_color);

		rgb_t_color__reserve = pGObj_Res->pGOBJ_PARA_CTRL->Get_RGB_Color(t_color__reserve, r_color,g_color,b_color);
		rgb_b_color__reserve = pGObj_Res->pGOBJ_PARA_CTRL->Get_RGB_Color(b_color__reserve, r_color,g_color,b_color);

		rgb_t_color__run = pGObj_Res->pGOBJ_PARA_CTRL->Get_RGB_Color(t_color__run, r_color,g_color,b_color);
		rgb_b_color__run = pGObj_Res->pGOBJ_PARA_CTRL->Get_RGB_Color(b_color__run, r_color,g_color,b_color);

		rgb_t_color__end = pGObj_Res->pGOBJ_PARA_CTRL->Get_RGB_Color(t_color__end, r_color,g_color,b_color);
		rgb_b_color__end = pGObj_Res->pGOBJ_PARA_CTRL->Get_RGB_Color(b_color__end, r_color,g_color,b_color);

		rgb_t_color__abort = pGObj_Res->pGOBJ_PARA_CTRL->Get_RGB_Color(t_color__abort, r_color,g_color,b_color);
		rgb_b_color__abort = pGObj_Res->pGOBJ_PARA_CTRL->Get_RGB_Color(b_color__abort, r_color,g_color,b_color);
	}

	//
	cPARA__T_Color__IDLE = rgb_t_color__idle;
	cPARA__B_Color__IDLE = rgb_b_color__idle;

	cPARA__T_Color__DISABLE = rgb_t_color__disable;
	cPARA__B_Color__DISABLE = rgb_b_color__disable;

	cPARA__T_Color__RESERVE = rgb_t_color__reserve;
	cPARA__B_Color__RESERVE = rgb_b_color__reserve;

	cPARA__T_Color__RUN = rgb_t_color__run;
	cPARA__B_Color__RUN = rgb_b_color__run;

	cPARA__T_Color__END = rgb_t_color__end;
	cPARA__B_Color__END = rgb_b_color__end;

	cPARA__T_Color__ABORT = rgb_t_color__abort;
	cPARA__B_Color__ABORT = rgb_b_color__abort;
}

int CPARTICLE_TABLE__COMMON_RES
::Get__COLOR_OF_CTRL_STATE(const CString& str_state, COLORREF& t_color,COLORREF& b_color)
{
	if(str_state.CompareNoCase(_CTRL_STATE__DISABLE) == 0)
	{
		t_color = cPARA__T_Color__DISABLE;
		b_color = cPARA__B_Color__DISABLE;
	}
	else if(str_state.CompareNoCase(_CTRL_STATE__RESERVE) == 0)
	{
		t_color = cPARA__T_Color__RESERVE;
		b_color = cPARA__B_Color__RESERVE;
	}
	else if(str_state.CompareNoCase(_CTRL_STATE__RUN) == 0)
	{
		t_color = cPARA__T_Color__RUN;
		b_color = cPARA__B_Color__RUN;
	}
	else if(str_state.CompareNoCase(_CTRL_STATE__END) == 0)
	{
		t_color = cPARA__T_Color__END;
		b_color = cPARA__B_Color__END;
	}
	else if(str_state.CompareNoCase(_CTRL_STATE__ABORT) == 0)
	{
		t_color = cPARA__T_Color__ABORT;
		b_color = cPARA__B_Color__ABORT;
	}
	else
	{
		t_color = cPARA__T_Color__IDLE;
		b_color = cPARA__B_Color__IDLE;
	}
	
	return 1;
}
