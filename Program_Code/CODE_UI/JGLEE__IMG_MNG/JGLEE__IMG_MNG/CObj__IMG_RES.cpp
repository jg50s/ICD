#include "stdafx.h"

#include "CObj__IMG_RES.h"
#include "resource.h"


//---------------------------------------------------------
#define  pKEY__CH_IMG_STATE			"CH.IMG_STATE"
#define  pKEY__TEST_IMG_STATE		"TEST.IMG_STATE"


//---------------------------------------------------------
CObj__IMG_RES::CObj__IMG_RES()
{

}
CObj__IMG_RES::~CObj__IMG_RES()
{

}

//---------------------------------------------------------
void CObj__IMG_RES::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	p_obj_para_def->Register_Channel(pKEY__CH_IMG_STATE);
	p_obj_para_def->Register_Command(pKEY__TEST_IMG_STATE);
}
void CObj__IMG_RES::Set_Parameter(const int& module_id,
								   const POINT& st,
								   const POINT& et,
								   const HWND& hwnd,
								   GObj__Resource_Info *p_obj_res)
{
	// ...
	{
		iMODULE_ID = module_id;

		pSt = st;
		pEt = et;

		pGObj_Res  = p_obj_res;
		iREAL_MODE = pGObj_Res->pGOBJ_PARA_CTRL->Check__RealMode();
	}

	// Image Link ...
	{
		CString img_state;
		int img_res;

		mRes__IMG_CTRL.Delete__ALL_IMG();

		// 1.
		{
			img_state = "OFF";
			img_res   = IDB_PNG__BTTN_OFF;

			mRes__IMG_CTRL.Load__IMG_PNG(img_state,img_res);
		}
		// 2.
		{
			img_state = "ON";
			img_res   = IDB_PNG__BTTN_ON;

			mRes__IMG_CTRL.Load__IMG_PNG(img_state,img_res);
		}
	}
}

void CObj__IMG_RES::Show_GObj(const HWND& hwnd)
{
	Draw__Img(true);
}
void CObj__IMG_RES::Hide_GObj()
{

}

//---------------------------------------------------------
void CObj__IMG_RES::WM_Paint(const HWND& hwnd)
{

}
void CObj__IMG_RES::WM_Timer(const HWND& hwnd)
{
	Draw__Img();
}

void CObj__IMG_RES::WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{
	Draw__Img();
}
void CObj__IMG_RES::WM_LButtonUp(const HWND& hwnd)
{

}

void CObj__IMG_RES::WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__IMG_RES::WM_RButtonUp(const HWND& hwnd)
{

}

void CObj__IMG_RES::WM_Notify(UINT message,const WPARAM wparam,LPARAM lparam)
{

}

//---------------------------------------------------------
void CObj__IMG_RES::Draw__Img(const bool draw_mode)
{
	HDC hdc_front = pGObj_Res->hDC;
	HDC hdc_back  = pGObj_Res->hDC_BACK;
	HDC hdc_mem   = pGObj_Res->hDC_MEM;

	// ...
	CString ch_data;

	if(iREAL_MODE < 0)
	{
		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__TEST_IMG_STATE, ch_data);
	}
	else
	{
		pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Data(pKEY__CH_IMG_STATE, ch_data);		
	}

	if(!draw_mode)
	{
		if(mRes__IMG_CTRL.Check__CUR_IMG_STATE(ch_data) > 0)
			return;
	}

	if(mRes__IMG_CTRL.Draw__IMG(ch_data, hdc_front,hdc_back,hdc_mem, pSt,pEt, -1) < 0)
	{
		if(iREAL_MODE < 0)		
			Draw__Area_Line();
	}
}
void CObj__IMG_RES::Draw__Area_Line()
{
	HDC hdc      = pGObj_Res->hDC;
	HDC hdc_back = pGObj_Res->hDC_BACK;

	// ...
	COLORREF lcolor = RGB(0,0,0);
	int lw = 1;

	// ...
	POINT st;
	POINT et;
	POINT size;	

	st = pSt;
	et = pEt;

	size.x = pEt.x - pSt.x;
	size.y = pEt.y - pSt.y;

	// ...
	{
		SetPixel(hdc_back, st.x,st.y, lcolor);

		StretchBlt(hdc_back,
					st.x,st.y, size.x,lw,
					hdc_back, 
					st.x,st.y,1,1,
					SRCCOPY);	

		StretchBlt(hdc_back,
					st.x,st.y, lw,size.y,
					hdc_back, 
					st.x,st.y,1,1,
					SRCCOPY);	

		StretchBlt(hdc_back,
					st.x,et.y-lw, size.x,lw,
					hdc_back, 
					st.x,st.y,1,1,
					SRCCOPY);	

		StretchBlt(hdc_back,
					et.x-lw,st.y, lw,size.y,
					hdc_back, 
					st.x,st.y,1,1,
					SRCCOPY);	

		StretchBlt(hdc,
					st.x,st.y, 
					size.x,size.y,
					hdc_back, 
					st.x,st.y, 
					size.x,size.y,
					SRCCOPY);	
	}
}
