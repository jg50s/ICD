// Dlg__Ref_Wafer_Sel.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"
#include "Dlg__Ref_Wafer_Sel.h"

#include "Macro_Function.h"
#include "Macro__Wafer_Tree.h"
#include "CLS__Wafer_Trace.h"


// CDlg__Ref_Wafer_Sel dialog

IMPLEMENT_DYNAMIC(CDlg__Ref_Wafer_Sel, CDialog)

CDlg__Ref_Wafer_Sel::CDlg__Ref_Wafer_Sel(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Ref_Wafer_Sel::IDD, pParent)
{

}

CDlg__Ref_Wafer_Sel::~CDlg__Ref_Wafer_Sel()
{
}

void CDlg__Ref_Wafer_Sel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST__RESULT_TABLE, mList__Result_Table);
	DDX_Control(pDX, IDOK, mBtn__Ref_Wfr_Sel);
	DDX_Control(pDX, IDC_BTN__REF_WFR_DEL, mBtn__Ref_Delete);
}


BEGIN_MESSAGE_MAP(CDlg__Ref_Wafer_Sel, CDialog)
	ON_WM_MEASUREITEM()

	ON_NOTIFY(NM_CLICK, IDC_LIST__RESULT_TABLE, &CDlg__Ref_Wafer_Sel::OnNMClickList__Ref_Result_Table)
	ON_BN_CLICKED(IDOK, &CDlg__Ref_Wafer_Sel::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN__REF_WFR_DEL, &CDlg__Ref_Wafer_Sel::OnBnClickedBtn__Ref_Wfr_Del)
END_MESSAGE_MAP()


// CDlg__Ref_Wafer_Sel message handlers

void CDlg__Ref_Wafer_Sel::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if(nIDCtl == IDC_LIST__RESULT_TABLE)
	{
		lpMeasureItemStruct->itemHeight = 21;
	}

	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

BOOL CDlg__Ref_Wafer_Sel::OnInitDialog()
{
	CDialog::OnInitDialog();

	// List : Result_Table ...
	{
		CReportCtrl* p_table = &mList__Result_Table;

		// ...
		{
			int list_view_stype;

			list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
			list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
			list_view_stype += LVS_EX_INFOTIP;
			// list_view_stype += LVS_EX_DOUBLEBUFFER;

			p_table->SetExtendedStyle(list_view_stype);
			p_table->ModifyStyle(LVS_OWNERDRAWFIXED, 0, 0);
		}

		p_table->SetNoSort(false);
		_Make__Result_Table(p_table);
	}

	_Refresh__Result_Table();
	return TRUE;  
}


void CDlg__Ref_Wafer_Sel
::_Refresh__Result_Table()
{
	iSel_Table_Index = -1;
	mBtn__Ref_Wfr_Sel.EnableWindow(FALSE);
	mBtn__Ref_Delete.EnableWindow(FALSE);

	_Update__Search_All();

	// ...
	CReportCtrl* p_table = &mList__Result_Table;

	_Add__Result_Table(p_table, &mLog_Ctrl);
}


// ...
#define _CFG__JRT_COL_SIZE						9
#define _JRT_COL__NUMBER						0
#define _JRT_COL__JOBID	    					1
#define _JRT_COL__LOTID   						2
#define _JRT_COL__PORTID						3
#define _JRT_COL__SLOTID						4
#define _JRT_COL__CSTID							5
#define _JRT_COL__DATE							6
#define _JRT_COL__TIME							7
#define _JRT_COL__PATH							8


void CDlg__Ref_Wafer_Sel
::_Make__Result_Table(CReportCtrl *p_table)
{
	CStringArray l__col_name;
	CUIntArray   l__col_width;

	// ...
	{
		l__col_name.RemoveAll();
		l__col_width.RemoveAll();

		int i_limit = _CFG__JRT_COL_SIZE;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(i == _JRT_COL__NUMBER)
			{
				l__col_name.Add("No.");
				l__col_width.Add(35);
			}
			else if(i == _JRT_COL__JOBID)
			{
				l__col_name.Add("JOB ID");
				l__col_width.Add(120);
			}
			else if(i == _JRT_COL__LOTID)
			{
				l__col_name.Add("LOT ID");
				l__col_width.Add(120);
			}
			else if(i == _JRT_COL__PORTID)
			{
				l__col_name.Add("PTN");
				l__col_width.Add(40);
			}
			else if(i == _JRT_COL__SLOTID)
			{
				l__col_name.Add("STN");
				l__col_width.Add(40);
			}
			else if(i == _JRT_COL__CSTID)
			{
				l__col_name.Add("CST ID");
				l__col_width.Add(120);
			}
			else if(i == _JRT_COL__DATE)
			{
				l__col_name.Add("Date");
				l__col_width.Add(80);
			}
			else if(i == _JRT_COL__TIME)
			{
				l__col_name.Add("Time");
				l__col_width.Add(80);
			}
			else if(i == _JRT_COL__PATH)
			{
				l__col_name.Add("Path");
				l__col_width.Add(0);
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

		for(int i=0; i<_CFG__JRT_COL_SIZE; i++)
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

void CDlg__Ref_Wafer_Sel
::_Add__Result_Table(CReportCtrl *p_table, CLS__Job_Log_Ctrl* p_log_ctrl)
{
	COLORREF t_color = RGB(0,0,255);
	COLORREF b_color = RGB(255,255,255);

	// ...
	{
		p_table->DeleteAllItems();
		p_table->SetRedraw(FALSE);
	}

	// ...
	int r_index = 0;

	int i_limit = p_log_ctrl->Get__Log_Size();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CLS__Job_Log_Info* p_info = p_log_ctrl->Get__Log_Info(i);

		CString str_data;
		int col;

		CString str_no;
		CString str_lpid;
		CString str_slot;
		CString str_cstid;
		CString str_jobid;
		CString str_lotid;
		CString str_date = p_info->sLog_Date;
		CString str_time;
		CString str_path;

		int k_limit = p_info->sList_PortID.GetSize();
		int k;

		for(k=0; k<k_limit; k++)
		{
			// ...
			{
				str_no.Format("%1d", r_index+1);
				str_lpid  = p_info->sList_PortID[k];
				str_slot  = p_info->sList_SlotID[k];
				str_jobid = p_info->sList_JobID[k];
				str_lotid = p_info->sList_LotID[k];
				str_cstid = p_info->sList_CstID[k];
				str_time  = p_info->sList_Time[k];
				str_path.Format("%s\\%s", p_info->sLog_Date,p_info->sList_Dir[k]);
			}

			// ...
			{
				p_table->InsertItem(r_index, str_no, t_color,b_color);

				//
				col = _JRT_COL__JOBID;
				str_data = str_jobid;
				p_table->SetItem(r_index,col, LVIF_TEXT,str_data,0,0,0,0);

				col = _JRT_COL__LOTID;
				str_data = str_lotid;
				p_table->SetItem(r_index,col, LVIF_TEXT,str_data,0,0,0,0);

				col = _JRT_COL__PORTID;
				str_data = str_lpid;
				p_table->SetItem(r_index,col, LVIF_TEXT,str_data,0,0,0,0);

				col = _JRT_COL__SLOTID;
				str_data = str_slot;
				p_table->SetItem(r_index,col, LVIF_TEXT,str_data,0,0,0,0);

				col = _JRT_COL__CSTID;
				str_data = str_cstid;
				p_table->SetItem(r_index,col, LVIF_TEXT,str_data,0,0,0,0);

				col = _JRT_COL__DATE;
				str_data = str_date;
				p_table->SetItem(r_index,col, LVIF_TEXT,str_data,0,0,0,0);

				col = _JRT_COL__TIME;
				str_data = str_time;
				p_table->SetItem(r_index,col, LVIF_TEXT,str_data,0,0,0,0);

				col = _JRT_COL__PATH;
				str_data = str_path;
				p_table->SetItem(r_index,col, LVIF_TEXT,str_data,0,0,0,0);
			}

			r_index++;
		}
	}

	p_table->SetRedraw(TRUE);
}

void CDlg__Ref_Wafer_Sel::
_Update__Search_All()
{
	CStringArray l__ref_dir;
	CStringArray l__ref_date;

	MACRO__Get_Dir_Date_List(sDir_Root, l__ref_dir,l__ref_date);

	mLog_Ctrl.Clear_ALL();

	// ...
	CString str_date;

	int i_limit = l__ref_dir.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		str_date = l__ref_dir[i];

		mLog_Ctrl.Load__Log_Date(str_date);

		// ...
		CString dir_sub;
		dir_sub.Format("%s\\%s", sDir_Root,str_date);

		CStringArray l_log;
		CStringArray l_time;

		MACRO__Get_Dir_Time_List(dir_sub, l_log,l_time);

		int k_limit = l_log.GetSize();
		int k;

		for(k=0; k<k_limit; k++)
		{
			CString str_log  = l_log[k];
			CString str_time = l_time[k];

			CStringArray l_para;					
			MACRO__Convert__LIST('+', str_log, l_para);

			// ...
			CString para_lpid;
			CString para_lotid;
			CString para_cstid;
			CString para_jobid;

			if(l_para.GetSize() > 1)		para_lpid  = l_para[1];
			if(l_para.GetSize() > 2)		para_lotid = l_para[2]; 
			if(l_para.GetSize() > 3)		para_jobid = l_para[3]; 
			if(l_para.GetSize() > 4)		para_cstid = l_para[4]; 

			// ...
			CString cmp_lpx;
			cmp_lpx.Format("P%s_", para_lpid);
			// ...
			CStringArray l_file_name;
			CStringArray l_file_date;
			CString file_ext = "wfr";

			CString dir_wfr;
			dir_wfr.Format("%s\\%s", dir_sub,str_log);

			MACRO__Get_File_List(dir_wfr,file_ext, l_file_name,l_file_date);

			int t_limit = l_file_name.GetSize();
			int t;

			for(t=0; t<t_limit; t++)
			{
				CString para_slotid = l_file_name[t];

				if(para_slotid.Find(cmp_lpx) != 0)			continue;
				para_slotid.Delete(0, cmp_lpx.GetLength());

				mLog_Ctrl.Load__Log_Info(para_lpid,para_slotid, para_cstid,para_jobid,para_lotid,str_log,str_time);
			}
		}
	}

	if(mLog_Ctrl.Get__Log_Size() > 0)		mBtn__Ref_Delete.EnableWindow(TRUE);
	else									mBtn__Ref_Delete.EnableWindow(FALSE);
}

void CDlg__Ref_Wafer_Sel::OnNMClickList__Ref_Result_Table(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int r_index = pNMItemActivate->iItem;
	if(r_index >= 0)
	{
		iSel_Table_Index = r_index;
		mBtn__Ref_Wfr_Sel.EnableWindow(TRUE);
	}

	*pResult = 0;
}

void CDlg__Ref_Wafer_Sel::OnBnClickedOk()
{
	if(iSel_Table_Index < 0)		return;

	CListCtrl* p_table = &mList__Result_Table;

	CString para_dir  = p_table->GetItemText(iSel_Table_Index, _JRT_COL__PATH);
	CString para_port = p_table->GetItemText(iSel_Table_Index, _JRT_COL__PORTID);
	CString para_slot = p_table->GetItemText(iSel_Table_Index, _JRT_COL__SLOTID);

	sPara__Dir_Log  = para_dir;
	sPara__Wfr_Port = para_port;
	sPara__Wfr_Slot = para_slot;

	OnOK();
}

void CDlg__Ref_Wafer_Sel::OnBnClickedBtn__Ref_Wfr_Del()
{
	if(iSel_Table_Index < 0)		return;

	CListCtrl* p_table = &mList__Result_Table;

	CString para_dir  = p_table->GetItemText(iSel_Table_Index, _JRT_COL__PATH);
	CString para_port = p_table->GetItemText(iSel_Table_Index, _JRT_COL__PORTID);
	CString para_slot = p_table->GetItemText(iSel_Table_Index, _JRT_COL__SLOTID);

	CString wfr_file;
	wfr_file.Format("P%s_%s.wfr", para_port,para_slot);

	CString wfr_path;
	wfr_path.Format("%s\\%s\\%s", sDir_Root,para_dir,wfr_file);

	//
	CLS__Wafer_Info wfr_info;
	MACRO__Update__Wafer_Info(wfr_path, &wfr_info);

	CStringArray l_md_info;
	CStringArray l_tack;
	CStringArray l_rcp;
	CStringArray l_log_info;

	wfr_info.Get__PROCESS_LOG(l_md_info,l_tack,l_rcp,l_log_info);

	int i_limit = l_md_info.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString md_name  = l_md_info[i];
		CString log_info = l_log_info[i];

		CString log_file = MACRO__Get_File_Name(log_info);
		CString dir_md;

		// PMx ...
		if(dir_md.GetLength() < 1)
		{
			int md_id = MACRO__Get_PMx_ID(md_name);
			if(md_id > 0)		dir_md.Format("PM%1d", md_id);
		}
		// LLx ...
		if(dir_md.GetLength() < 1)
		{
			int md_id = MACRO__Get_LLx_ID(md_name);
			if(md_id > 0)		dir_md.Format("LL%1d", md_id);
		}

		if(dir_md.GetLength() < 1)
		{
			continue;
		}

		// ...
		{
			CString log_path;
			CString dir_log;

			dir_log.Format("%s\\%s\\%s\\", sDir_Root,para_dir,dir_md);

			// .d
			log_path.Format("%s%s.d", dir_log,log_file);
			DeleteFile(log_path);
			
			// .rcp_inf
			log_path.Format("%s%s.rcp_inf", dir_log,log_file);
			DeleteFile(log_path);

			// .rcp_log
			log_path.Format("%s%s.rcp_log", dir_log,log_file);
			DeleteFile(log_path);

			// .step
			log_path.Format("%s%s.step", dir_log,log_file);
			DeleteFile(log_path);
		}

		// Directory Delete ...
		{
			CString dir_del;
			dir_del.Format("%s\\%s\\%s\\", sDir_Root,para_dir,dir_md);

			RemoveDirectory(dir_del);
		}

		DeleteFile(wfr_path);
	}

	// Delete - para_dir ...
	{
		CString dir_log;
		dir_log.Format("%s\\", para_dir);

		CStringArray l_para;
		MACRO__Convert__LIST('\\', dir_log, l_para);

		int i_limit = l_para.GetSize();
		int i;

		for(i=i_limit-1; i>=0; i--)
		{
			CString dir_del = sDir_Root;

			for(int t=0; t<=i; t++)
			{
				CString str_para = l_para[t];

				dir_del += "\\";
				dir_del += str_para;
			}

			RemoveDirectory(dir_del);
		}
	}

	_Refresh__Result_Table();
	return;
}
