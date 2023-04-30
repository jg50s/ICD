// Dlg__Wafer_Tack_Table.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"
#include "Dlg__Wafer_Tack_Table.h"


// CDlg__Wafer_Tack_Table dialog

IMPLEMENT_DYNAMIC(CDlg__Wafer_Tack_Table, CDialog)

CDlg__Wafer_Tack_Table::CDlg__Wafer_Tack_Table(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Wafer_Tack_Table::IDD, pParent)
{

}

CDlg__Wafer_Tack_Table::~CDlg__Wafer_Tack_Table()
{
}

void CDlg__Wafer_Tack_Table::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST__TACK_TIME, mCtrl__Tack_Time);
	DDX_Control(pDX, IDC_BTN__WFRID, mBtn_WfrID);
	DDX_Control(pDX, IDC_CHECK__SEARCH_MOVE, mCheck__Moving);
	DDX_Control(pDX, IDC_CHECK__SEARCH_PROC, mCheck__Process);
	DDX_Control(pDX, IDC_BTN__REFRESH, mCtrl__Refresh_Btn);
}


BEGIN_MESSAGE_MAP(CDlg__Wafer_Tack_Table, CDialog)
	ON_BN_CLICKED(IDC_CHECK__SEARCH_MOVE, &CDlg__Wafer_Tack_Table::OnBnClickedCheck_Move)
	ON_BN_CLICKED(IDC_CHECK__SEARCH_PROC, &CDlg__Wafer_Tack_Table::OnBnClickedCheck_Process)
	ON_BN_CLICKED(IDC_BTN__REFRESH, &CDlg__Wafer_Tack_Table::OnBnClickedBtn_Refresh)
END_MESSAGE_MAP()


// CDlg__Wafer_Tack_Table message handlers

BOOL CDlg__Wafer_Tack_Table::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		CListCtrl* p_table = &mCtrl__Tack_Time;
		CImageList* p_img = &mImg__Tack_Time;

		_Make__Tack_Time_List(p_table, p_img);
	}

	// ...
	{
		DS__Wafer_Info ds_wfr;
		pWfr_Info->Get__WFR_INFO(ds_wfr);

		CString str_wfrid;
		str_wfrid.Format("P%1d:%02d", ds_wfr.iPORTID,ds_wfr.iSLOTID);
		mBtn_WfrID.SetWindowText(str_wfrid);

		_Refresh__Tack_Time();
	}

	UpdateData(FALSE);
	return TRUE; 
}

void CDlg__Wafer_Tack_Table
::_Refresh__Tack_Time()
{
	mCtrl__Refresh_Btn.EnableWindow(FALSE);

	if(bPara__Active_Move)		mCheck__Moving.SetCheck(1);
	else						mCheck__Moving.SetCheck(0);

	if(bPara__Active_Proc)		mCheck__Process.SetCheck(1);
	else						mCheck__Process.SetCheck(0);

	pWfr_Info->Get__WAFER_TACK_INFO(bPara__Active_Move,
									bPara__Active_Proc,
									sList__MODULE,
									sList__ACTION,
									sList__RESULT,
									sList__TIME,
									sList__COMMENT);		

	// ...
	CListCtrl* p_table = &mCtrl__Tack_Time;

	_Add__Tack_Time_List(p_table);
}


// ...
#define _CFG__TBL_COL_SIZE						6
#define _TBL_COL__NUMBER						0
#define _TBL_COL__MODULE						1
#define _TBL_COL__ACTION						2
#define _TBL_COL__RESULT						3
#define _TBL_COL__TIME							4
#define _TBL_COL__COMMENT						5


void CDlg__Wafer_Tack_Table
::_Make__Tack_Time_List(CListCtrl *p_table,
						CImageList *p_img)
{
	// ...
	{
		CBitmap cBit;
		cBit.LoadBitmap(IDB_DIGITAL_LIST_IMG);

		p_img->Create(1,20, ILC_COLOR4,1,1);
		p_img->Add(&cBit, RGB(0,0,0));	

		p_table->SetImageList(p_img, LVSIL_SMALL);

		// ...
		int list_view_stype;

		list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
		list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
		list_view_stype += LVS_EX_INFOTIP;

		p_table->SetExtendedStyle(list_view_stype);
	}

	// ...
	CStringArray l__col_name;
	CUIntArray   l__col_width;

	// ...
	{
		l__col_name.RemoveAll();
		l__col_width.RemoveAll();

		int i_limit = _CFG__TBL_COL_SIZE;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(i == _TBL_COL__NUMBER)
			{
				l__col_name.Add("No.");
				l__col_width.Add(50);
			}
			else if(i == _TBL_COL__MODULE)
			{
				l__col_name.Add("Module");
				l__col_width.Add(100);
			}
			else if(i == _TBL_COL__ACTION)
			{
				l__col_name.Add("Action");
				l__col_width.Add(120);
			}
			else if(i == _TBL_COL__RESULT)
			{
				l__col_name.Add("Result");
				l__col_width.Add(120);
			}
			else if(i == _TBL_COL__TIME)
			{
				l__col_name.Add("Time (sec)");
				l__col_width.Add(120);
			}
			else if(i == _TBL_COL__COMMENT)
			{
				l__col_name.Add("Comment");
				l__col_width.Add(200);
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

		int i_limit = _CFG__TBL_COL_SIZE;
		int i;

		for(i=0; i<i_limit; i++)
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

			if(col_cx < 1)
			{
				col_cx = 10 + (col_name.GetLength() * 10);
			}

			p_table->InsertColumn(i, col_name, LVCFMT_CENTER, col_cx);
		}		
	}
}

void CDlg__Wafer_Tack_Table
::_Add__Tack_Time_List(CListCtrl *p_table)
{
	p_table->DeleteAllItems();
	p_table->SetRedraw(FALSE);

	// ...
	CString str_item;

	int i_limit = sList__MODULE.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		int k_limit = _CFG__TBL_COL_SIZE;
		int k;

		for(k=0; k<k_limit; k++)
		{
				 if(k == _TBL_COL__NUMBER)			str_item.Format("%1d", i+1);
			else if(k == _TBL_COL__MODULE)			str_item = sList__MODULE[i];
			else if(k == _TBL_COL__ACTION)			str_item = sList__ACTION[i];
			else if(k == _TBL_COL__RESULT)			str_item = sList__RESULT[i];
			else if(k == _TBL_COL__TIME)			str_item = sList__TIME[i];
			else if(k == _TBL_COL__COMMENT)			str_item = sList__COMMENT[i];
			else									continue;

			if(k == _TBL_COL__NUMBER)			p_table->InsertItem(i, str_item, 0);
			else								p_table->SetItem(i,k, LVIF_TEXT,str_item,0,0,0,0);
		}
	}

	p_table->SetRedraw(TRUE);
}

void CDlg__Wafer_Tack_Table::OnBnClickedCheck_Move()
{
	if(mCheck__Moving.GetCheck() > 0)		bPara__Active_Move = true;
	else									bPara__Active_Move = false;

	if(mCheck__Process.GetCheck() > 0)		bPara__Active_Proc = true;
	else									bPara__Active_Proc = false;

	mCtrl__Refresh_Btn.EnableWindow(TRUE);
}
void CDlg__Wafer_Tack_Table::OnBnClickedCheck_Process()
{
	if(mCheck__Moving.GetCheck() > 0)		bPara__Active_Move = true;
	else									bPara__Active_Move = false;

	if(mCheck__Process.GetCheck() > 0)		bPara__Active_Proc = true;
	else									bPara__Active_Proc = false;

	mCtrl__Refresh_Btn.EnableWindow(TRUE);
}

void CDlg__Wafer_Tack_Table::OnBnClickedBtn_Refresh()
{
	_Refresh__Tack_Time();
}
