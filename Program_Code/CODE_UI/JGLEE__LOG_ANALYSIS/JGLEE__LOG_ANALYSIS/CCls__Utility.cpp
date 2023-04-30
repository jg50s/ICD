#include "stdafx.h"
#include "CCls__Utility.h"


// ...
#define _PART_TYPE__CListCtrl				11

// ...
CCls__ReSize::CCls__ReSize()
{
	pDLG = NULL;

	iDLG__X_Offset = 0;
	iDLG__Y_Offset = 0;
}
CCls__ReSize::~CCls__ReSize()
{

}

void CCls__ReSize::Link_Dlg(CDialog* p_dlg)
{
	pDLG = p_dlg;
	if(pDLG == NULL)			return;

	// ...
	RECT win_rc;
	pDLG->GetWindowRect(&win_rc);

	iDLG__X_Offset = win_rc.left;
	iDLG__Y_Offset = win_rc.top;

	dDLG__Width  = win_rc.right - win_rc.left;
	dDLG__Height = win_rc.bottom - win_rc.top;
}

int CCls__ReSize::_Check_ResID(const int res_id)
{
	int i_limit = iList__RES_ID.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(res_id == iList__RES_ID[i])			return i;
	}
	return -1;
}

void CCls__ReSize::Link_ResID(const int res_id)
{
	if(_Check_ResID(res_id) >= 0)			return;

	iList__RES_ID.Add(res_id);
	iList__RES_LLIMIT.Add(0);
	iList__RES_RLIMIT.Add(0);
	iList__RES_LSIDE_SPACE.Add(0);
	iList__RES_RSIDE_SPACE.Add(0);

	iList__POS_SX.Add(0);
	iList__POS_SY.Add(0);
	iList__POS_EX.Add(0);
	iList__POS_EY.Add(0);
}
void CCls__ReSize::Link_ResID__LLimit(const int res_id, const int llimit, const int left_space, const int right_space)
{
	if(_Check_ResID(res_id) >= 0)			return;

	iList__RES_ID.Add(res_id);
	iList__RES_LLIMIT.Add(llimit);
	iList__RES_RLIMIT.Add(0);
	iList__RES_LSIDE_SPACE.Add(left_space);
	iList__RES_RSIDE_SPACE.Add(right_space);

	iList__POS_SX.Add(0);
	iList__POS_SY.Add(0);
	iList__POS_EX.Add(0);
	iList__POS_EY.Add(0);
}
void CCls__ReSize::Link_ResID__RLimit(const int res_id, const int rlimit, const int left_space, const int right_space)
{
	if(_Check_ResID(res_id) >= 0)			return;

	iList__RES_ID.Add(res_id);
	iList__RES_LLIMIT.Add(0);
	iList__RES_RLIMIT.Add(rlimit);
	iList__RES_LSIDE_SPACE.Add(left_space);
	iList__RES_RSIDE_SPACE.Add(right_space);

	iList__POS_SX.Add(0);
	iList__POS_SY.Add(0);
	iList__POS_EX.Add(0);
	iList__POS_EY.Add(0);
}

int  CCls__ReSize::Get_ResID__LLimit(const int res_id)
{
	int i_index = _Check_ResID(res_id);
	if(i_index < 0)			return 0;

	return iList__RES_LLIMIT[i_index];
}
void CCls__ReSize::Change_ResID__LLimit(const int res_id, const int llimit, const int left_space, const int right_space)
{
	int i_index = _Check_ResID(res_id);
	if(i_index < 0)			return;

	iList__RES_LLIMIT[i_index] = llimit;
	iList__RES_RLIMIT[i_index] = 0;
	iList__RES_LSIDE_SPACE[i_index] = left_space;
	iList__RES_RSIDE_SPACE[i_index] = right_space;
}
void CCls__ReSize::Change_ResID__RLimit(const int res_id, const int rlimit, const int left_space, const int right_space)
{
	int i_index = _Check_ResID(res_id);
	if(i_index < 0)			return;

	iList__RES_LLIMIT[i_index] = 0;
	iList__RES_RLIMIT[i_index] = rlimit;
	iList__RES_LSIDE_SPACE[i_index] = left_space;
	iList__RES_RSIDE_SPACE[i_index] = right_space;
}

void CCls__ReSize::Init_Position()
{
	if(pDLG == NULL)			return;

	// ...
	int x_offset = iDLG__X_Offset;
	int y_offset = iDLG__Y_Offset;

	int i_limit = iList__RES_ID.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		int id = iList__RES_ID[i];

		RECT rc;
		pDLG->GetDlgItem(id)->GetWindowRect(&rc);

		iList__POS_SX[i] = rc.left   - x_offset;
		iList__POS_SY[i] = rc.top    - y_offset;
		iList__POS_EX[i] = rc.right  - x_offset;
		iList__POS_EY[i] = rc.bottom - y_offset;
	}
}
void CCls__ReSize::
Move_Position(const POINT p_st,const POINT p_et, const bool x_resize,const bool y_resize)
{
	if(pDLG == NULL)			return;

	// ...
	double win_ws = dDLG__Width;
	double win_hs = dDLG__Height;

	double cur_ws = p_et.x - p_st.x;
	double cur_hs = p_et.y - p_st.y;

	if(win_ws < 1)			win_ws = 1;
	if(win_hs < 1)			win_hs = 1;

	double w_ratio = cur_ws / win_ws;
	double h_ratio = cur_hs / win_hs;

	// ...
	int i_limit = iList__RES_ID.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		RECT rc;

		int llimit  = iList__RES_LLIMIT[i];
		int rlimit  = iList__RES_RLIMIT[i];
		int l_space = iList__RES_LSIDE_SPACE[i];
		int r_space = iList__RES_RSIDE_SPACE[i];

		// ...
		{
			rc.left   = iList__POS_SX[i];
			rc.right  = iList__POS_EX[i];
			
			rc.top    = iList__POS_SY[i];
			rc.bottom = iList__POS_EY[i];
		}
		
		if(llimit > 0)
		{
			int part_ws = rc.right - rc.left;
			int part_hs = rc.bottom - rc.top;

			rc.right = cur_ws - r_space;
			rc.left  = cur_ws - llimit + l_space;

			rc.top    *= h_ratio;
			rc.bottom *= h_ratio;
		}
		else
		{
			if(x_resize)
			{
				rc.left   *= w_ratio;
				rc.right  *= w_ratio;
			}

			if(y_resize)
			{
				rc.top    *= h_ratio;
				rc.bottom *= h_ratio;
			}
		}

		if(rlimit > 0)
		{
			int r_ws = cur_ws - rlimit;
				
			rc.left += l_space;
			rc.right = r_ws - r_space;
		}

		int id = iList__RES_ID[i];
		pDLG->GetDlgItem(id)->MoveWindow(&rc);
	}
}
