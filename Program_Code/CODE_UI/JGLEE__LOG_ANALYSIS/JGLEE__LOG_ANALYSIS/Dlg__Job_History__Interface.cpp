#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Job_History.h"

#include "CObj__Job_History__KEY_DEF.h"


// ...
int CDlg__Job_History
::Set_Parameter(const int module_id)
{
	GObj__Parameter_Ctrl *p_para = pGObj_Res->pGOBJ_PARA_CTRL;

	CString dir_root;

	// ...
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;
		int eqp_id = module_id;

		x_sys_ctrl->Get__SEQ_DIR_ROOT(eqp_id, dir_root);
	}

	// Dir_Wafer ...
	{
		sDir_Root  = dir_root;
		sDir_Root += "\\EQP_LOG\\Wafer_Data";
	}
	// Dir_Ref_Wafer ...
	{
		sDir_Ref_Wfr  = dir_root;
		sDir_Ref_Wfr += "\\EQP_LOG\\Ref_Wafer";
	}
	// Dir_Ref_LotID ...
	{
		sDir_Ref_Lot  = dir_root;
		sDir_Ref_Lot += "\\EQP_LOG\\Ref_LotID";
	}
	// 

	_Init_Parameter();
	return 1;
}

void CDlg__Job_History
::_Init_Parameter()
{
	CString para_data;

	// ...
	{
		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_LPx_MAX, para_data);
		iLPx_SIZE = atoi(para_data);
		if(iLPx_SIZE > 5)		iLPx_SIZE = 5;
		if(iLPx_SIZE < 1)		iLPx_SIZE = 1;

		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_AXIS_MAX, para_data);
		double data__axis_full_range = atof(para_data);
		dRes__Axis_Range = data__axis_full_range / 5.0;
		if(dRes__Axis_Range < 0.1)			dRes__Axis_Range = 1.0;

		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_ERR_RANGE, para_data);
		dData__Error_Range = atof(para_data);
		double range_half = data__axis_full_range / 2.0;
		if(dData__Error_Range > range_half)			dData__Error_Range = range_half;
	}

	// ...
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;
		CString dir_inf;

		x_sys_ctrl->Get__GUI_DIR_EXE(dir_inf);
		dir_inf += "\\INCLUDE_FILE\\";

		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_RCP_PARA_PM1, para_data);
		sPara__Rcp_Inf_PM1  = dir_inf;
		sPara__Rcp_Inf_PM1 += para_data;

		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_RCP_PARA_PM2, para_data);
		sPara__Rcp_Inf_PM2  = dir_inf;
		sPara__Rcp_Inf_PM2 += para_data;

		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_RCP_PARA_PM3, para_data);
		sPara__Rcp_Inf_PM3  = dir_inf;
		sPara__Rcp_Inf_PM3 += para_data;

		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_RCP_PARA_PM4, para_data);
		sPara__Rcp_Inf_PM4  = dir_inf;
		sPara__Rcp_Inf_PM4 += para_data;

		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_RCP_PARA_PM5, para_data);
		sPara__Rcp_Inf_PM5  = dir_inf;
		sPara__Rcp_Inf_PM5 += para_data;

		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_RCP_PARA_PM6, para_data);
		sPara__Rcp_Inf_PM6  = dir_inf;
		sPara__Rcp_Inf_PM6 += para_data;

		//
		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_RCP_PARA_LL1, para_data);
		sPara__Rcp_Inf_LL1  = dir_inf;
		sPara__Rcp_Inf_LL1 += para_data;

		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_RCP_PARA_LL2, para_data);
		sPara__Rcp_Inf_LL2  = dir_inf;
		sPara__Rcp_Inf_LL2 += para_data;
	}
}

int CDlg__Job_History
::Set_MoveWindow(const POINT& p_st, const POINT& p_et)
{
	if(!bActive_Init)
	{
		bActive_Init = true;

		/*
		// ...
		int x_offset;
		int y_offset;

		// Dlg ...
		{
			RECT win_rc;

			GetWindowRect(&win_rc);
			mRC_DLG__WIN = win_rc;

			x_offset = win_rc.left;
			y_offset = win_rc.top;
		}

		// Button ...
		{
			CButton *p_btn;
			RECT *p_rc;

			int i_limit = 15;
			int i;

			for(i=0; i<i_limit; i++)
			{
				if(i == 0)
				{
					p_btn = &mBtn__Node_History;
					p_rc  = &mRC_BTN__NODE_HISTORY;
				}
				else if(i == 1)
				{
					p_btn = &mBtn__Node_All_Open;
					p_rc  = &mRC_BTN__NODE_ALL_OPEN;
				}
				else if(i == 2)
				{
					p_btn = &mBtn__Node_All_Close;
					p_rc  = &mRC_BTN__NODE_ALL_CLOSE;
				}
				else if(i == 3)
				{
					p_btn = &mCheck__Node_History;
					p_rc  = &mRC_CHK__NODE_HISTORY;
				}
				else if(i == 4)
				{
					p_btn = &mCheck__Node_Open;
					p_rc  = &mRC_CHK__NODE_ALL_OPEN;
				}
				else if(i == 5)
				{
					p_btn = &mCheck__Node_Close;
					p_rc  = &mRC_CHK__NODE_ALL_CLOSE;
				}
				else if(i == 6)
				{
					p_btn = &mBtn__Wfr_Refresh;
					p_rc  = &mRC_BTN__WFR_REFREASH;
				}
				else if(i == 7)
				{
					p_btn = &mBtn__DA_Chart;
					p_rc  = &mRC_BTN__DA_CHART;
				}
				else if(i == 8)
				{
					p_btn = &mBtn__Tack_Time;
					p_rc  = &mRC_BTN__TACK_TIME;
				}
				else if(i == 9)
				{
					p_btn = &mBtn__Wfr_Sel;
					p_rc  = &mRC_BTN__WFR_SEL;
				}
				else if(i == 10)
				{
					p_btn = &mCheck__Search_Move;
					p_rc  = &mRC_CHK__SEARCH_MOVE;
				}
				else if(i == 11)
				{
					p_btn = &mCheck__Search_Proc;
					p_rc  = &mRC_CHK__SEARCH_PROC;
				}
				else
				{
					continue;
				}

				p_btn->GetWindowRect(p_rc);
				p_rc->left   -= x_offset;
				p_rc->top    -= y_offset;
				p_rc->right  -= x_offset;
				p_rc->bottom -= y_offset;
			}
		}

		// Static ...
		{
			CStatic *p_btn;
			RECT *p_rc;

			int i_limit = 10;
			int i;

			for(i=0; i<i_limit; i++)
			{
				if(i == 0)
				{
					p_btn = &mGroup__Item;
					p_rc  = &mRC_GROUP__ITEM;
				}
				else if(i == 1)
				{
					p_btn = &mText__WfrID;
					p_rc  = &mRC_TEXT__WFRID;
				}
				else if(i == 2)
				{
					p_btn = &mText__LotID;
					p_rc  = &mRC_TEXT__LOTID;
				}
				else
				{
					continue;
				}

				p_btn->GetWindowRect(p_rc);
				p_rc->left   -= x_offset;
				p_rc->top    -= y_offset;
				p_rc->right  -= x_offset;
				p_rc->bottom -= y_offset;		
			}
		}

		// Edit ...
		{
			CEdit *p_btn;
			RECT *p_rc;

			int i_limit = 10;
			int i;

			for(i=0; i<i_limit; i++)
			{
				if(i == 0)
				{
					p_btn = &mEdit__Wfr_Path;
					p_rc  = &mRC_EDIT__WFR_PATH;
				}
				else if(i == 1)
				{
					p_btn = &mEdit__WfrID;
					p_rc  = &mRC_EDIT__WFRID;
				}
				else if(i == 2)
				{
					p_btn = &mEdit__LotID;
					p_rc  = &mRC_EDIT__LOTID;
				}
				else
				{
					continue;
				}

				p_btn->GetWindowRect(p_rc);
				p_rc->left   -= x_offset;
				p_rc->top    -= y_offset;
				p_rc->right  -= x_offset;
				p_rc->bottom -= y_offset;	
			}
		}

		// Tree ...
		{
			RECT t_rc;
			mTree_Wafer.GetWindowRect(&t_rc);

			t_rc.left   -= x_offset;
			t_rc.top    -= y_offset;
			t_rc.right  -= x_offset;
			t_rc.bottom -= y_offset;

			mRC_TREE__WAFER = t_rc;
		}
	}

	// ...
	{
		RECT win_rc = mRC_DLG__WIN;

		double win_ws = win_rc.right - win_rc.left;
		double win_hs = win_rc.bottom - win_rc.top;

		double cur_ws = p_et.x - p_st.x;
		double cur_hs = p_et.y - p_st.y;

		if(win_ws < 1)			win_ws = 1;
		if(win_hs < 1)			win_hs = 1;

		double w_ratio = cur_ws / win_ws;
		double h_ratio = cur_hs / win_hs;

		// Button ...
		{
			CButton *p_btn;
			RECT b_rc;

			int i_limit = 15;
			int i;

			for(i=0; i<i_limit; i++)
			{
				if(i == 0)
				{
					p_btn = &mBtn__Node_History;;
					b_rc  = mRC_BTN__NODE_HISTORY;
				}
				else if(i == 1)
				{
					p_btn = &mBtn__Node_All_Open;
					b_rc  = mRC_BTN__NODE_ALL_OPEN;
				}
				else if(i == 2)
				{
					p_btn = &mBtn__Node_All_Close;
					b_rc  = mRC_BTN__NODE_ALL_CLOSE;
				}
				else if(i == 3)
				{
					p_btn = &mCheck__Node_History;
					b_rc  = mRC_CHK__NODE_HISTORY;
				}
				else if(i == 4)
				{
					p_btn = &mCheck__Node_Open;
					b_rc  = mRC_CHK__NODE_ALL_OPEN;
				}
				else if(i == 5)
				{
					p_btn = &mCheck__Node_Close;
					b_rc  = mRC_CHK__NODE_ALL_CLOSE;
				}
				else if(i == 6)
				{
					p_btn = &mBtn__Wfr_Refresh;
					b_rc  = mRC_BTN__WFR_REFREASH;
				}
				else if(i == 7)
				{
					p_btn = &mBtn__DA_Chart;
					b_rc  = mRC_BTN__DA_CHART;
				}
				else if(i == 8)
				{
					p_btn = &mBtn__Tack_Time;
					b_rc  = mRC_BTN__TACK_TIME;
				}
				else if(i == 9)
				{
					p_btn = &mBtn__Wfr_Sel;
					b_rc  = mRC_BTN__WFR_SEL;
				}
				else if(i == 10)
				{
					p_btn = &mCheck__Search_Move;
					b_rc  = mRC_CHK__SEARCH_MOVE;
				}
				else if(i == 11)
				{
					p_btn = &mCheck__Search_Proc;
					b_rc  = mRC_CHK__SEARCH_PROC;
				}
				else
				{
					continue;
				}

				// ...
				b_rc.left   *= w_ratio;
				b_rc.right  *= w_ratio;
				b_rc.top    *= h_ratio;
				b_rc.bottom *= h_ratio;

				p_btn->MoveWindow(&b_rc);
			}
		}

		// Static ...
		{
			CStatic *p_btn;
			RECT b_rc;

			int i_limit = 10;
			int i;

			for(i=0; i<i_limit; i++)
			{
				if(i == 0)
				{
					p_btn = &mGroup__Item;
					b_rc  = mRC_GROUP__ITEM;
				}
				else if(i == 1)
				{
					p_btn = &mText__WfrID;
					b_rc  = mRC_TEXT__WFRID;
				}
				else if(i == 2)
				{
					p_btn = &mText__LotID;
					b_rc  = mRC_TEXT__LOTID;
				}
				else
				{
					continue;
				}

				// ...
				b_rc.left   *= w_ratio;
				b_rc.right  *= w_ratio;
				b_rc.top    *= h_ratio;
				b_rc.bottom *= h_ratio;

				p_btn->MoveWindow(&b_rc);
			}
		}

		// Edit ...
		{
			CEdit *p_btn;
			RECT b_rc;

			int i_limit = 10;
			int i;

			for(i=0; i<i_limit; i++)
			{
				if(i == 0)
				{
					p_btn = &mEdit__Wfr_Path;
					b_rc  = mRC_EDIT__WFR_PATH;
				}
				else if(i == 1)
				{
					p_btn = &mEdit__WfrID;
					b_rc  = mRC_EDIT__WFRID;
				}
				else if(i == 2)
				{
					p_btn = &mEdit__LotID;
					b_rc  = mRC_EDIT__LOTID;
				}
				else
				{
					continue;
				}

				// ...
				b_rc.left   *= w_ratio;
				b_rc.right  *= w_ratio;
				b_rc.top    *= h_ratio;
				b_rc.bottom *= h_ratio;

				p_btn->MoveWindow(&b_rc);
			}
		}

		// Tree ...
		{
			CTreeCtrl* p_table = &mTree_Wafer;
			RECT t_rc = mRC_TREE__WAFER;

			t_rc.left   *= w_ratio;
			t_rc.right  *= w_ratio;
			t_rc.top    *= h_ratio;
			t_rc.bottom *= h_ratio;

			p_table->MoveWindow(&t_rc);
		}
		*/
	}

	// ...
	{
		int sx = p_st.x;
		int sy = p_st.y;
		int wx = p_et.x - p_st.x;
		int wy = p_et.y - p_st.y;

		MoveWindow(sx,sy,wx,wy,true);
		ShowWindow(SW_SHOW);
	}
	return 1;
}
int CDlg__Job_History
::Redraw_Page()
{
	Invalidate(TRUE);
	return 1;
}
