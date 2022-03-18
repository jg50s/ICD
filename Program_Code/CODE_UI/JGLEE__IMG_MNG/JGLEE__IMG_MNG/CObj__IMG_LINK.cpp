#include "stdafx.h"

#include "CObj__IMG_LINK.h"


//---------------------------------------------------------
#define  pKEY__CH_IMG_STATE			"CH.IMG_STATE"

#define  pKEY__DATA_STATE_X			"DATA.STATE_%1d"
#define  pKEY__DATA_PATH_X			"DATA.PATH_%1d"

#define  pKEY__TEST_IMG_STATE		"TEST.IMG_STATE"


//---------------------------------------------------------
CObj__IMG_LINK::CObj__IMG_LINK()
{

}
CObj__IMG_LINK::~CObj__IMG_LINK()
{

}

//---------------------------------------------------------
void CObj__IMG_LINK::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	p_obj_para_def->Register_Channel(pKEY__CH_IMG_STATE);

	// STATE_X ...
	{
		CString key_name;

		int i_limit = 10;
		int i;

		for(i=0; i<i_limit; i++)
		{
			key_name.Format(pKEY__DATA_STATE_X, i+1);
			p_obj_para_def->Register_Command(key_name);

			key_name.Format(pKEY__DATA_PATH_X, i+1);
			p_obj_para_def->Register_Command(key_name);
		}
	}

	//
	p_obj_para_def->Register_Command(pKEY__TEST_IMG_STATE);
}
void CObj__IMG_LINK::Set_Parameter(const int& module_id,
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
	{
		CString key_name;
		CString def_data;

		CString dir_root;
		int ref_type = RES_TYPE__GUI_ROOT;
		pGObj_Res->pGOBJ_PARA_CTRL->Get_Obj_Dir(ref_type, dir_root);

		CString dir_sub;
		dir_sub.Format("%s%s", dir_root,"\\SCREEN_RES\\RESOURCE\\");

		// ...
		mRes__IMG_CTRL.Delete__ALL_IMG();

		int i_limit = 10;
		int i;

		for(i=0; i<i_limit; i++)
		{
			int id = i + 1;
			
			CString img_state;
			CString img_dir;

			// 1.
			{
				key_name.Format(pKEY__DATA_STATE_X, id);
				p_obj_res->pGOBJ_PARA_CTRL->Get_Constant_Data(key_name, def_data);

				img_state = def_data;
				// printf("%1d) [State] <- [%s] \n", id,img_state);
			}
			// 2.
			{
				key_name.Format(pKEY__DATA_PATH_X, id);
				p_obj_res->pGOBJ_PARA_CTRL->Get_Constant_Data(key_name, def_data);
				
				img_dir.Format("%s\\%s", dir_sub,def_data);
				// printf("%1d) [Path] <- [%s] \n", id,img_dir);
			}

			mRes__IMG_CTRL.Load__IMG_FILE(img_state,img_dir);
		}
	}
}

void CObj__IMG_LINK::Show_GObj(const HWND& hwnd)
{
	Draw__Img(true);
}
void CObj__IMG_LINK::Hide_GObj()
{

}

//---------------------------------------------------------
void CObj__IMG_LINK::WM_Paint(const HWND& hwnd)
{

}
void CObj__IMG_LINK::WM_Timer(const HWND& hwnd)
{
	Draw__Img();
}

void CObj__IMG_LINK::WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{
	Draw__Img();
}
void CObj__IMG_LINK::WM_LButtonUp(const HWND& hwnd)
{
	
}

void CObj__IMG_LINK::WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{
	
}
void CObj__IMG_LINK::WM_RButtonUp(const HWND& hwnd)
{
	
}

void CObj__IMG_LINK::WM_Notify(UINT message,const WPARAM wparam,LPARAM lparam)
{

}

//---------------------------------------------------------
void CObj__IMG_LINK::Draw__Img(const bool draw_mode)
{
	HDC hdc_cur  = pGObj_Res->hDC;
	HDC hdc_back = pGObj_Res->hDC_BACK;
	HDC hdc_mem  = pGObj_Res->hDC_MEM;

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

	if(mRes__IMG_CTRL.Draw__IMG(ch_data, hdc_cur,hdc_back,hdc_mem, pSt,pEt, -1) < 0)
	{
		if(iREAL_MODE < 0)		
			Draw__Area_Line();
	}
}
void CObj__IMG_LINK::Draw__Area_Line()
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
