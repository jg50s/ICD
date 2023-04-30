// Dlg__PARTICLE_TABLE__PROCESS_PART.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__CTC_MAINT.h"
#include "Dlg__PARTICLE_TABLE__PROCESS_PART.h"

#include "CObj__PARTICLE_TABLE__DEF.h"
#include "PARTICLE_TABLE__COMMON_DEF.h"
#include "Dlg__TRANSFER_PROPERTY.h"
#include "Dlg__PROCESS_PROPERTY.h"

#include "Macro_Function.h"

#include "PARTICLE_TABLE__COMMON_RES.h"
extern CPARTICLE_TABLE__COMMON_RES mRes_Common;


// CDlg__PARTICLE_TABLE__PROCESS_PART dialog

IMPLEMENT_DYNAMIC(CDlg__PARTICLE_TABLE__PROCESS_PART, CDialog)

CDlg__PARTICLE_TABLE__PROCESS_PART::CDlg__PARTICLE_TABLE__PROCESS_PART(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__PARTICLE_TABLE__PROCESS_PART::IDD, pParent)
{
	bActive__Timer_Run = false;
}

CDlg__PARTICLE_TABLE__PROCESS_PART::~CDlg__PARTICLE_TABLE__PROCESS_PART()
{
}

void CDlg__PARTICLE_TABLE__PROCESS_PART::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST__PROCESS_PART, mTable_Process);
}

BOOL CDlg__PARTICLE_TABLE__PROCESS_PART::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		CReportCtrl* p_table = &mTable_Process;

		_Make__Table_Process(p_table);
		_Add__Table_Process(p_table);
	}

	return TRUE;
}

void CDlg__PARTICLE_TABLE__PROCESS_PART::Update_Table()
{
	printf(" * CDlg__PARTICLE_TABLE__PROCESS_PART::Update_Table() ... \n");

	//
	CReportCtrl* p_table = &mTable_Process;

	_Update__Table_Process(p_table);
}


BEGIN_MESSAGE_MAP(CDlg__PARTICLE_TABLE__PROCESS_PART, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST__PROCESS_PART,  &CDlg__PARTICLE_TABLE__PROCESS_PART::OnNMClickList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST__PROCESS_PART, &CDlg__PARTICLE_TABLE__PROCESS_PART::OnNMDblclkList)
END_MESSAGE_MAP()


// CDlg__PARTICLE_TABLE__PROCESS_PART message handlers

// ...
#define _CFG__COL_SIZE						10
#define _COL__NUMBER						0
#define _COL__STN_SRC	   					1
#define _COL__STN_TRG		 				2
#define _COL__MD_NAME						3
#define _COL__ACT_ITEM						4
#define _COL__CFG_COUNT						5
#define _COL__CUR_COUNT						6
#define _COL__ACT_ID						7
#define _COL__CTRL_STATE					8
#define _COL__KEY_ID						9


void CDlg__PARTICLE_TABLE__PROCESS_PART::_Make__Table_Process(CReportCtrl* p_table)
{
	// ...
	{	
		int list_view_stype;

		list_view_stype  = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
		list_view_stype += LVS_EX_ONECLICKACTIVATE | LVS_EX_UNDERLINEHOT;
		list_view_stype += LVS_EX_INFOTIP;
		list_view_stype += LVS_EX_CHECKBOXES;

		p_table->SetExtendedStyle(list_view_stype);
	}

	// ...
	CStringArray l__col_name;
	CUIntArray   l__col_width;

	// ...
	{
		l__col_name.RemoveAll();
		l__col_width.RemoveAll();

		int i_limit = _CFG__COL_SIZE;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(i == _COL__NUMBER)
			{
				l__col_name.Add("No.");
				l__col_width.Add(60);
			}
			else if(i == _COL__STN_SRC)
			{
				l__col_name.Add("STN");
				l__col_width.Add(40);
			}
			else if(i == _COL__STN_TRG)
			{
				l__col_name.Add("STN");
				l__col_width.Add(40);
			}
			else if(i == _COL__MD_NAME)
			{
				l__col_name.Add("Module");
				l__col_width.Add(60);
			}
			else if(i == _COL__ACT_ITEM)
			{
				l__col_name.Add("Action Item ...");
				l__col_width.Add(260);
			}
			else if(i == _COL__CFG_COUNT)
			{
				l__col_name.Add("Cycle");
				l__col_width.Add(50);
			}
			else if(i == _COL__CUR_COUNT)
			{
				l__col_name.Add("Count");
				l__col_width.Add(50);
			}
			else if(i == _COL__ACT_ID)
			{
				l__col_name.Add("ID");
				l__col_width.Add(40);
			}
			else if(i == _COL__CTRL_STATE)
			{
				l__col_name.Add("State");
				l__col_width.Add(50);
			}
			else if(i == _COL__KEY_ID)
			{
				l__col_name.Add("KeyID");
				l__col_width.Add(100);
			}
			else
			{
				continue;
			}
		}
	}

	// ...
	{
		p_table->DeleteAllItems();

		for(int i=0; i<_CFG__COL_SIZE; i++)
		{
			p_table->DeleteColumn(0);
		}
	}

	// ...
	{
		CString col_name;
		int col_cx;

		int limit = l__col_name.GetSize();
		int i;

		for(i=0; i<limit; i++)
		{
			col_name = l__col_name[i];
			col_cx   = (int) l__col_width[i];

			p_table->InsertColumn(i, col_name, LVCFMT_CENTER, col_cx);
		}		
	}
}

void CDlg__PARTICLE_TABLE__PROCESS_PART::_Add__Table_Process(CReportCtrl* p_table)
{
	p_table->DeleteAllItems();
	p_table->SetRedraw(FALSE);

	// ...
	CStringArray l__md_name;
	CStringArray l__act_item;
	CUIntArray   l__act_id;
	CStringArray l__ctrl_state;
	CStringArray l__key_id;

	// PMx ...
	{
		CString md_nmae;
		CString act_item;
		int act_id;
		CString ctrl_state;
		CString key_id;

		for(int i=0; i<iPMx__MD_SIZE; i++)
		{
			key_id.Format("%1d", i+1);
			md_nmae.Format("PM%s", key_id);
			ctrl_state = _CTRL_STATE__IDLE;
			
			for(int k=0; k<_ACT__PROCESS_SIZE; k++)
			{
				if(k == _ACT_ID__MOVE_TO_PMx)
				{
					act_item = "Pick up from / Place to PM";
					act_id   = k;
				}
				else if(k == _ACT_ID__PMx_SLOT_VLV_OP_CL)
				{
					act_item = "Door Valve Open / Close";
					act_id   = k;
				}
				else if(k == _ACT_ID__PMx_PIN_UP_TO_DOWN)
				{
					act_item = "Pin Up /Down";
					act_id   = k;
				}
				else if(k == _ACT_ID__PMx_PROCESS)
				{
					act_item = "Process";
					act_id   = k;
				}
				else
				{
					continue;
				}

				//
				l__md_name.Add(md_nmae);
				l__act_item.Add(act_item);
				l__act_id.Add(act_id);
				l__ctrl_state.Add(ctrl_state);
				l__key_id.Add(key_id);
			}
		}
	}

	// ...
	int k_limit = l__act_item.GetSize();
	for(int k=0; k<k_limit; k++)
	{
		CString str_state = l__ctrl_state[k];
		
		COLORREF t_color;
		COLORREF b_color;

		mRes_Common.Get__COLOR_OF_CTRL_STATE(str_state, t_color,b_color);

		// ...
		int i_limit = _CFG__COL_SIZE;
		for(int i=0; i<i_limit; i++)
		{
			CString str_name;

			if(i == _COL__NUMBER)
			{
				str_name.Format("%1d", k+1);
			}
			else if(i == _COL__STN_SRC)
			{
				str_name = "__";
			}
			else if(i == _COL__STN_TRG)
			{
				str_name = "__";
			}
			else if(i == _COL__MD_NAME)
			{
				str_name = l__md_name[k];
			}
			else if(i == _COL__ACT_ITEM)
			{
				str_name = l__act_item[k];
			}
			else if(i == _COL__CFG_COUNT)
			{
				str_name = "__";
			}
			else if(i == _COL__CUR_COUNT)
			{
				str_name = "__";
			}
			else if(i == _COL__ACT_ID)
			{
				str_name.Format("%1d", l__act_id[k]);
			}
			else if(i == _COL__CTRL_STATE)
			{
				str_name = l__ctrl_state[k];
			}
			else if(i == _COL__KEY_ID)
			{
				str_name = l__key_id[k];
			}
			else 
			{
				continue;
			}

			if(i == 0)
			{
				p_table->InsertItem(k, str_name);
				p_table->SetCheck(k, FALSE);
			}
			else
			{
				p_table->SetItem(k,i, LVIF_TEXT, str_name, 0,0,0,0);
			}

			p_table->SetItemTextColor(k,i, t_color);
			p_table->SetItemBkColor(k,i, b_color);
		}
	}

	p_table->SetRedraw(TRUE);
}

int  CDlg__PARTICLE_TABLE__PROCESS_PART::_Get__Act_Name(const int act_id, CString& act_name)
{
		 if(act_id == _ACT_ID__MOVE_TO_PMx)				act_name = _ACT_PROC__MOVE_TO_PMx;
	else if(act_id == _ACT_ID__PMx_SLOT_VLV_OP_CL)		act_name = _ACT_PROC__PMx_SLOT_VLV_OP_CL;
	else if(act_id == _ACT_ID__PMx_PIN_UP_TO_DOWN)		act_name = _ACT_PROC__PMx_PIN_UP_TO_DOWN;
	else if(act_id == _ACT_ID__PMx_PROCESS)				act_name = _ACT_PROC__PMx_PROCESS;
	else												return -1;

	return 1;
}

void CDlg__PARTICLE_TABLE__PROCESS_PART::_Update__Table_Process(CReportCtrl* p_table)
{
	p_table->SetRedraw(FALSE);

	// ...
	GObj__Parameter_Ctrl* p_para_ctrl = pGObj_Res->pGOBJ_PARA_CTRL;

	COLORREF t_color;
	COLORREF b_color;

	int k_limit = p_table->GetItemCount();
	for(int k=0; k<k_limit; k++)
	{
		CString ch__ctrl_state;
		CString ch__check_run;
		CString ch__stn_src;
		CString ch__stn_trg;
		CString ch__cfg_count;
		CString ch__cur_count;
		CString ch__rcp_name;

		if(iREAL_MODE > 0)
		{
			CString cur__md_id  = p_table->GetItemText(k, _COL__MD_NAME);
			CString cur__key_id = p_table->GetItemText(k, _COL__KEY_ID);

			CString str__act_id = p_table->GetItemText(k, _COL__ACT_ID);
			int data__act_id = atoi(str__act_id);

			// ...
			CString act_name;

			if(_Get__Act_Name(data__act_id, act_name) > 0)
			{
				if(iREAL_MODE > 0)
				{
					CString key_name;

					//
					key_name.Format("%s%s%s", pKEY__CH_PROC_ACT_CHECK_X, act_name, cur__key_id);
					p_para_ctrl->Get_Channel_Data(key_name, ch__check_run);

					key_name.Format("%s%s%s", pKEY__CH_PROC_CTRL_STATE_X, act_name, cur__key_id);
					p_para_ctrl->Get_Channel_Data(key_name, ch__ctrl_state);

					//
					key_name.Format("%s%s%s", pKEY__CH_PROC_STN_SRC_X, act_name, cur__key_id);
					p_para_ctrl->Get_Channel_Data(key_name, ch__stn_src);

					key_name.Format("%s%s%s", pKEY__CH_PROC_STN_TRG_X, act_name, cur__key_id);
					p_para_ctrl->Get_Channel_Data(key_name, ch__stn_trg);

					key_name.Format("%s%s%s", pKEY__CH_PROC_CFG_COUNT_X, act_name, cur__key_id);
					p_para_ctrl->Get_Channel_Data(key_name, ch__cfg_count);

					key_name.Format("%s%s%s", pKEY__CH_PROC_CUR_COUNT_X, act_name, cur__key_id);
					p_para_ctrl->Get_Channel_Data(key_name, ch__cur_count);

					//
					if(data__act_id == _ACT_ID__PMx_PROCESS)
					{
						key_name.Format("%s%s", pKEY__CH_PROC_RECIPE_NAME_X, cur__key_id);
						p_para_ctrl->Get_Channel_Data(key_name, ch__rcp_name);
					}
				}
			}
		}
		else
		{
			// CHECK.RUN ...
			{
				int col_id = _COL__NUMBER;
				bool cur_state = p_table->GetCheck(k);

				if(cur_state)			ch__check_run = "YES";
				else					ch__check_run = "NO";	
			}
			// STN.SRC ...
			{
				int col_id = _COL__STN_SRC;
				ch__stn_src = p_table->GetItemText(k, col_id);
			}
			// STN.TRG ...
			{
				int col_id = _COL__STN_TRG;
				ch__stn_trg = p_table->GetItemText(k, col_id);
			}
			// CFG.COUNT ...
			{
				int col_id = _COL__CFG_COUNT;
				ch__cfg_count = p_table->GetItemText(k, col_id);
			}
			// CUR.COUNT ...
			{
				int col_id = _COL__CUR_COUNT;
				ch__cur_count = p_table->GetItemText(k, col_id);
			}
			// RECIPE.NAME ...
			{
				int col_id = _COL__ACT_ITEM;
				ch__rcp_name = p_table->GetItemText(k, col_id);
			}
			// CTRL.STATE ...
			{
				int col_id = _COL__CTRL_STATE;
				ch__ctrl_state = p_table->GetItemText(k, col_id);
			}
		}

		// CHECK.RUN ...
		{
			int col_id = _COL__NUMBER;
			bool cur_state = p_table->GetCheck(k);

			CString cur_data;
			if(cur_state)			cur_data = "YES";
			else					cur_data = "NO";	

			if(ch__check_run.CompareNoCase(cur_data) != 0)
			{
				if(ch__check_run.CompareNoCase("YES") == 0)			p_table->SetCheck(k, TRUE);
				else												p_table->SetCheck(k, FALSE);
			}
		}
		// STN.SRC ...
		{
			int col_id = _COL__STN_SRC;
			CString cur_data = p_table->GetItemText(k, col_id);

			if(ch__stn_src.CompareNoCase(cur_data) != 0)
				p_table->SetItem(k,col_id, LVIF_TEXT, ch__stn_src, 0,0,0,0);			
		}
		// STN.TRG ...
		{
			int col_id = _COL__STN_TRG;
			CString cur_data = p_table->GetItemText(k, col_id);

			if(ch__stn_trg.CompareNoCase(cur_data) != 0)
				p_table->SetItem(k,col_id, LVIF_TEXT, ch__stn_trg, 0,0,0,0);			
		}
		// CFG.COUNT ...
		{
			int col_id = _COL__CFG_COUNT;
			CString cur_data = p_table->GetItemText(k, col_id);

			if(ch__cfg_count.CompareNoCase(cur_data) != 0)
				p_table->SetItem(k,col_id, LVIF_TEXT, ch__cfg_count, 0,0,0,0);			
		}
		// CUR.COUNT ...
		{
			int col_id = _COL__CUR_COUNT;
			CString cur_data = p_table->GetItemText(k, col_id);

			if(ch__cur_count.CompareNoCase(cur_data) != 0)
				p_table->SetItem(k,col_id, LVIF_TEXT, ch__cur_count, 0,0,0,0);			
		}
		// RECIPE.NAME ...
		if(ch__rcp_name.GetLength() > 0)
		{
			int col_id = _COL__ACT_ITEM;
			CString cur_data = p_table->GetItemText(k, col_id);

			if(ch__rcp_name.CompareNoCase(cur_data) != 0)
				p_table->SetItem(k,col_id, LVIF_TEXT, ch__rcp_name, 0,0,0,0);			
		}
		// CTRL.STATE ...
		{
			int col_id = _COL__CTRL_STATE;
			CString cur_data = p_table->GetItemText(k, col_id);

			if(ch__ctrl_state.CompareNoCase(cur_data) != 0)
			{
				p_table->SetItem(k,col_id, LVIF_TEXT, ch__ctrl_state, 0,0,0,0);

				mRes_Common.Get__COLOR_OF_CTRL_STATE(ch__ctrl_state, t_color,b_color);

				// ...
				CString str_data;

				int i_limit = _CFG__COL_SIZE;
				for(int i=0; i<i_limit; i++)
				{
					str_data = p_table->GetItemText(k,i);
					p_table->SetItemText(k,i, str_data);

					p_table->SetItemTextColor(k,i, t_color, FALSE);
					p_table->SetItemBkColor(k,i, b_color, FALSE);
				}
			}
		}

		// ...
	}

	p_table->SetRedraw(TRUE);
}

void CDlg__PARTICLE_TABLE__PROCESS_PART::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int main_index = pNMItemActivate->iItem;
	int sub_index  = pNMItemActivate->iSubItem;

	if(main_index >= 0)
	{
		GObj__Parameter_Ctrl* p_para_ctrl = pGObj_Res->pGOBJ_PARA_CTRL;
		CReportCtrl* p_table = &mTable_Process;

		if(sub_index == 0)
		{
			CString str_check;

			bool cur_state = p_table->GetCheck(main_index);
			bool set_state = !cur_state;

			if(set_state)		str_check = "YES";
			else				str_check = "NO";

			if(iREAL_MODE > 0)
			{
				CString cur__md_id  = p_table->GetItemText(main_index, _COL__MD_NAME);
				CString cur__key_id = p_table->GetItemText(main_index, _COL__KEY_ID);

				CString str__act_id = p_table->GetItemText(main_index, _COL__ACT_ID);
				int data__act_id = atoi(str__act_id);

				// ...
				CString act_name;

				if(_Get__Act_Name(data__act_id, act_name) > 0)
				{
					CString key_name;

					key_name.Format("%s%s%s", pKEY__CH_PROC_ACT_CHECK_X, act_name, cur__key_id);
					p_para_ctrl->Set_Suffix_Feedback(key_name, str_check);
				}
			}
			else
			{
				p_table->SetCheck(main_index, set_state);
			}
		}
	}

	*pResult = 0;
}

void CDlg__PARTICLE_TABLE__PROCESS_PART::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int main_index = pNMItemActivate->iItem;
	int sub_index  = pNMItemActivate->iSubItem;

	if(main_index >= 0)
	{
		GObj__Parameter_Ctrl* p_para_ctrl = pGObj_Res->pGOBJ_PARA_CTRL;
		CReportCtrl* p_table = &mTable_Process;

		if(sub_index > 0)
		{
			CString str__md_name  = p_table->GetItemText(main_index, _COL__MD_NAME);
			CString str__stn_src  = p_table->GetItemText(main_index, _COL__STN_SRC);
			CString str__stn_trg  = p_table->GetItemText(main_index, _COL__STN_TRG);
			CString str__act_name = p_table->GetItemText(main_index, _COL__ACT_ITEM);
			CString str__cycle    = p_table->GetItemText(main_index, _COL__CFG_COUNT);
			CString str__key_id   = p_table->GetItemText(main_index, _COL__KEY_ID);

			CString str__act_id   = p_table->GetItemText(main_index, _COL__ACT_ID);
			int data__act_id = atoi(str__act_id);

			// ...
			CString act_name;

			if(_Get__Act_Name(data__act_id, act_name) > 0)
			{
				if(data__act_id == _ACT_ID__PMx_PROCESS)
				{
					CDlg__PROCESS_PROPERTY dlg;

					dlg.pGObj_Res = pGObj_Res;
					dlg.iPARA__PMx_ID = MACRO__Get__PMC_ID(str__md_name);

					dlg.sPARA__STN_SRC  = str__stn_src;
					dlg.sPARA__STN_TRG  = str__stn_trg;
					dlg.sPARA__CYCLE    = str__cycle;
					dlg.sPARA__ACT_NAME = str__act_name;

					if(dlg.DoModal() == IDOK)
					{
						str__stn_src = dlg.sPARA__STN_SRC;
						str__stn_trg = dlg.sPARA__STN_TRG;
						str__cycle   = dlg.sPARA__CYCLE;
						str__act_name.Format("Process \"%s\"", dlg.sPARA__PROCESS);

						if(iREAL_MODE > 0)
						{
							CString key_name;

							key_name.Format("%s%s%s", pKEY__CH_PROC_STN_SRC_X, act_name, str__key_id);
							p_para_ctrl->Set_Suffix_Feedback(key_name, str__stn_src);

							key_name.Format("%s%s%s", pKEY__CH_PROC_STN_TRG_X, act_name, str__key_id);
							p_para_ctrl->Set_Suffix_Feedback(key_name, str__stn_trg);

							key_name.Format("%s%s%s", pKEY__CH_PROC_CFG_COUNT_X, act_name, str__key_id);
							p_para_ctrl->Set_Suffix_Feedback(key_name, str__cycle);

							key_name.Format("%s%s", pKEY__CH_PROC_RECIPE_NAME_X, str__key_id);
							p_para_ctrl->Set_Suffix_Feedback(key_name, str__act_name);
						}
						else
						{
							p_table->SetItemText(main_index, _COL__STN_SRC,   str__stn_src);
							p_table->SetItemText(main_index, _COL__STN_TRG,   str__stn_trg);
							p_table->SetItemText(main_index, _COL__CFG_COUNT, str__cycle);
							p_table->SetItemText(main_index, _COL__ACT_ITEM,  str__act_name);
						}
					}
				}
				else
				{
					CDlg__TRANSFER_PROPERTY dlg;

					dlg.pGObj_Res = pGObj_Res;

					dlg.sPARA__STN_SRC  = str__stn_src;
					dlg.sPARA__STN_TRG  = str__stn_trg;
					dlg.sPARA__CYCLE    = str__cycle;
					dlg.sPARA__ACT_NAME = str__act_name;

					if(dlg.DoModal() == IDOK)
					{
						str__stn_src = dlg.sPARA__STN_SRC;
						str__stn_trg = dlg.sPARA__STN_TRG;
						str__cycle = dlg.sPARA__CYCLE;

						if(iREAL_MODE > 0)
						{
							CString key_name;

							key_name.Format("%s%s%s", pKEY__CH_PROC_STN_SRC_X, act_name, str__key_id);
							p_para_ctrl->Set_Suffix_Feedback(key_name, str__stn_src);

							key_name.Format("%s%s%s", pKEY__CH_PROC_STN_TRG_X, act_name, str__key_id);
							p_para_ctrl->Set_Suffix_Feedback(key_name, str__stn_trg);

							key_name.Format("%s%s%s", pKEY__CH_PROC_CFG_COUNT_X, act_name, str__key_id);
							p_para_ctrl->Set_Suffix_Feedback(key_name, str__cycle);
						}
						else
						{
							p_table->SetItemText(main_index, _COL__STN_SRC,   str__stn_src);
							p_table->SetItemText(main_index, _COL__STN_TRG,   str__stn_trg);
							p_table->SetItemText(main_index, _COL__CFG_COUNT, str__cycle);
						}
					}
				}
			}

			// ...
		}
	}

	*pResult = 0;
}


// ...
void CDlg__PARTICLE_TABLE__PROCESS_PART::WM_Timer(const HWND& hwnd)
{
	if(bActive__Timer_Run)		return;
	bActive__Timer_Run = true;

	// ...
	{
		CReportCtrl* p_table = &mTable_Process;

		_Update__Table_Process(p_table);
	}

	bActive__Timer_Run = false;
}
