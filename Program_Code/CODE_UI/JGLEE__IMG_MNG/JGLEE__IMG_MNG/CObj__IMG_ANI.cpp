#include "stdafx.h"

#include "CObj__IMG_ANI.h"


//---------------------------------------------------------
#define  pKEY__DATA_IMG_SIZE			"DATA.IMG_SIZE"
#define  pKEY__DATA_PATH_X				"DATA.PATH_%1d"

#define  pKEY__DATA_DISPLAY_MODE		"DATA.DISPLAY_MODE"
#define  pKEY__DATA_FIXED_IMG			"DATA.FIXED_IMG"

#define  pKEY__TEST_IMG_ID				"TEST.IMG_ID"


//---------------------------------------------------------
CObj__IMG_ANI::CObj__IMG_ANI()
{

}
CObj__IMG_ANI::~CObj__IMG_ANI()
{

}

//---------------------------------------------------------
void CObj__IMG_ANI::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	p_obj_para_def->Register_Command(pKEY__DATA_IMG_SIZE,  "ListBox", "1 2 3 4 5 6 7 8 9 10", "1");

	// IMG_X ...
	{
		CString key_name;

		int i_limit = 10;
		int i;

		for(i=0; i<i_limit; i++)
		{
			int id = i + 1;

			key_name.Format(pKEY__DATA_PATH_X, id);
			p_obj_para_def->Register_Command(key_name);
		}
	}

	p_obj_para_def->Register_Command(pKEY__DATA_DISPLAY_MODE, "ListBox", "NO YES", "NO");
	p_obj_para_def->Register_Command(pKEY__DATA_FIXED_IMG, "");

	p_obj_para_def->Register_Command(pKEY__TEST_IMG_ID,  "ListBox", "1 2 3 4 5 6 7 8 9 10", "1");
}
void CObj__IMG_ANI::Set_Parameter(const int& module_id,
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

	// ...
	CString key_name;
	CString def_data;

	// ...
	CString dir_root;
	int ref_type = RES_TYPE__GUI_ROOT;
	pGObj_Res->pGOBJ_PARA_CTRL->Get_Obj_Dir(ref_type, dir_root);

	CString dir_sub;
	dir_sub.Format("%s%s", dir_root,"\\SCREEN_RES\\RESOURCE\\");

	// ...
	{
		key_name = pKEY__DATA_IMG_SIZE;
		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(key_name, def_data);
		iIMG_SIZE = atoi(def_data);
		if(iIMG_SIZE > 10)		iIMG_SIZE = 10;
	}

	// ...
	{
		key_name = pKEY__DATA_DISPLAY_MODE;
		p_obj_res->pGOBJ_PARA_CTRL->Get_Constant_Data(key_name, def_data);

		if(def_data.CompareNoCase("YES") == 0)			bActive_Display_Mode = true;
		else											bActive_Display_Mode = false;
	}

	if(bActive_Display_Mode)
	{
		mRes__IMG_CTRL.Delete__ALL_IMG();

		int i_limit = iIMG_SIZE;
		int i;

		for(i=0; i<i_limit; i++)
		{
			int id = i + 1;

			CString img_state;
			CString img_dir;

			// 1. STATE ...
			{
				img_state.Format("%1d", id);
			}
			// 2. PATH
			{
				key_name.Format(pKEY__DATA_PATH_X, id);
				p_obj_res->pGOBJ_PARA_CTRL->Get_Constant_Data(key_name, def_data);

				img_dir.Format("%s\\%s", dir_sub,def_data);
			}

			mRes__IMG_CTRL.Load__IMG_FILE(img_state,img_dir);
		}
	}
	else
	{
		CString img_dir;

		key_name = pKEY__DATA_FIXED_IMG;
		p_obj_res->pGOBJ_PARA_CTRL->Get_Constant_Data(key_name, def_data);

		img_dir.Format("%s\\%s", dir_sub,def_data);

		mRes__IMG_CTRL.Load__IMG_FILE("fixed", img_dir);
	}

	bActive_Timer = false;
	iIMG_ID = 0;
}

void CObj__IMG_ANI::Show_GObj(const HWND& hwnd)
{
	Draw__Img(true);
}
void CObj__IMG_ANI::Hide_GObj()
{

}

//---------------------------------------------------------
void CObj__IMG_ANI::WM_Paint(const HWND& hwnd)
{

}
void CObj__IMG_ANI::WM_Timer(const HWND& hwnd)
{
	if(bActive_Display_Mode)
	{
		if(bActive_Timer)
		{
			int cur_tick = GetTickCount();
			int diff_tick = cur_tick - iTimer_Ref_Tick;

			iTimer_Count++;

			if(diff_tick >= 5000)
			{
				int timer_count = iTimer_Count;

				iTimer_Ref_Tick = GetTickCount();
				iTimer_Count = 0;

				printf(" * timer count <- [%.3f] \n", timer_count / (diff_tick / 1000.0));
			}
		}
		else
		{
			bActive_Timer = true;

			iTimer_Count = 0;
			iTimer_Ref_Tick = GetTickCount();
		}
	}

	Draw__Img();
}

void CObj__IMG_ANI::WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{
	Draw__Img();
}
void CObj__IMG_ANI::WM_LButtonUp(const HWND& hwnd)
{

}

void CObj__IMG_ANI::WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__IMG_ANI::WM_RButtonUp(const HWND& hwnd)
{

}

void CObj__IMG_ANI::WM_Notify(UINT message,const WPARAM wparam,LPARAM lparam)
{

}

//---------------------------------------------------------
void CObj__IMG_ANI::Draw__Img(const bool draw_mode)
{
	HDC hdc_cur  = pGObj_Res->hDC;
	HDC hdc_back = pGObj_Res->hDC_BACK;
	HDC hdc_mem  = pGObj_Res->hDC_MEM;

	// ...
	CString ch_data;

	if(bActive_Display_Mode)
	{
		if(iREAL_MODE < 0)
		{
			pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__TEST_IMG_ID, ch_data);
		}
		else
		{
			int img_id = ++iIMG_ID;
			if(iIMG_ID >= iIMG_SIZE)	iIMG_ID = 0;
			if(iIMG_ID >= 10)			iIMG_ID = 0;

			ch_data.Format("%1d", img_id);
		}
	}
	else 
	{
		ch_data = "fixed";
	}

	if(!draw_mode)
	{
		if(mRes__IMG_CTRL.Check__CUR_IMG_STATE(ch_data) > 0)
		{
			return;
		}
	}

	if(mRes__IMG_CTRL.Draw__IMG(ch_data, hdc_cur,hdc_back,hdc_mem, pSt,pEt, -1) < 0)
	{
		if(iREAL_MODE < 0)		
			Draw__Area_Line();
	}
}
void CObj__IMG_ANI::Draw__Area_Line()
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
