// Dlg__PMx_Table.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"
#include "Dlg__PMx_Table.h"


// CDlg__PMx_Table dialog

IMPLEMENT_DYNAMIC(CDlg__PMx_Table, CDialog)

CDlg__PMx_Table::CDlg__PMx_Table(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__PMx_Table::IDD, pParent)
{

}

CDlg__PMx_Table::~CDlg__PMx_Table()
{
}

void CDlg__PMx_Table::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST__PMx_TABLE, mCtrl__PMx_Table);

	DDX_Control(pDX, IDC_BTN__PM1, mBtn__PM1);
	DDX_Control(pDX, IDC_BTN__PM2, mBtn__PM2);
	DDX_Control(pDX, IDC_BTN__PM3, mBtn__PM3);
	DDX_Control(pDX, IDC_BTN__PM4, mBtn__PM4);
	DDX_Control(pDX, IDC_BTN__PM5, mBtn__PM5);
	DDX_Control(pDX, IDC_BTN__PM6, mBtn__PM6);
	DDX_Control(pDX, IDC_BTN__PMx, mBtn__PMx);

	DDX_Control(pDX, IDC_BTN__GOTO_MAINT, mBtn__Goto_Maint);
}


BEGIN_MESSAGE_MAP(CDlg__PMx_Table, CDialog)
	ON_BN_CLICKED(IDC_BTN__PM1, &CDlg__PMx_Table::OnBnClickedBtn__PM1)
	ON_BN_CLICKED(IDC_BTN__PM2, &CDlg__PMx_Table::OnBnClickedBtn__PM2)
	ON_BN_CLICKED(IDC_BTN__PM3, &CDlg__PMx_Table::OnBnClickedBtn__PM3)
	ON_BN_CLICKED(IDC_BTN__PM4, &CDlg__PMx_Table::OnBnClickedBtn__PM4)
	ON_BN_CLICKED(IDC_BTN__PM5, &CDlg__PMx_Table::OnBnClickedBtn__PM5)
	ON_BN_CLICKED(IDC_BTN__PM6, &CDlg__PMx_Table::OnBnClickedBtn__PM6)

	ON_BN_CLICKED(IDC_BTN__GOTO_MAINT, &CDlg__PMx_Table::OnBnClickedBtn__GOTO_MAINT)

	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlg__PMx_Table message handlers

BOOL CDlg__PMx_Table::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		CListCtrl* p_table = &mCtrl__PMx_Table;
		CImageList *p_img  = &mImg__PMx_Table;

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

		_Make__PMx_Table(p_table);
		iPMx_ID = 0;
	}

	bActive_Init = false;

	if(iREAL_MODE > 0)
	{
		SetTimer(1, 500, NULL);
	}
	return TRUE; 
}

void CDlg__PMx_Table::OnBnClickedBtn__PM1()
{
	_Change__PMx(1);
}
void CDlg__PMx_Table::OnBnClickedBtn__PM2()
{
	_Change__PMx(2);
}
void CDlg__PMx_Table::OnBnClickedBtn__PM3()
{
	_Change__PMx(3);
}
void CDlg__PMx_Table::OnBnClickedBtn__PM4()
{
	_Change__PMx(4);
}
void CDlg__PMx_Table::OnBnClickedBtn__PM5()
{
	_Change__PMx(5);
}
void CDlg__PMx_Table::OnBnClickedBtn__PM6()
{
	_Change__PMx(6);
}
void CDlg__PMx_Table::_Change__PMx(const int pm_id)
{
	CListCtrl* p_table = &mCtrl__PMx_Table;
	CString str_data;

	_Add__PMx_Table(p_table, pm_id);

	iPMx_ID = pm_id;
	// str_data.Format("%1d", pm_id);
	str_data = sPMx_NAME[pm_id - 1];
	mBtn__PMx.SetWindowText(str_data);
	
	UpdateData(FALSE);
}


// ...
#define _CFG__TBL_COL_SIZE						4
#define _TBL_COL__NUMBER						0
#define _TBL_COL__NAME	    					1
#define _TBL_COL__DATA    						2
#define _TBL_COL__CHANNEL						3


void CDlg__PMx_Table
::_Make__PMx_Table(CListCtrl *p_table)
{
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
				l__col_width.Add(iData__Col_Width__NO);
			}
			else if(i == _TBL_COL__NAME)
			{
				l__col_name.Add("Name");
				l__col_width.Add(iData__Col_Width__NAME);
			}
			else if(i == _TBL_COL__DATA)
			{
				l__col_name.Add("Data");
				l__col_width.Add(iData__Col_Width__DATA);
			}
			else if(i == _TBL_COL__CHANNEL)
			{
				l__col_name.Add("Channel");
				l__col_width.Add(iData__Col_Width__CHANNEL);
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

		for(int i=0; i<_CFG__TBL_COL_SIZE; i++)
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

void CDlg__PMx_Table
::_Add__PMx_Table(CListCtrl *p_table,
				  const int pm_id)
{
	p_table->DeleteAllItems();
	p_table->SetRedraw(FALSE);

	// ...
	CStringArray l_channel;
	CStringArray l_title;

	mCtrl_PMx.Get__PMx_INFO(pm_id, l_channel,l_title);

	// ...
	CString str_item;
	int n_count = 1;

	int i_limit = l_channel.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		str_item = l_channel[i];

		if(str_item.CompareNoCase("&LINE") == 0)
		{
			p_table->InsertItem(i, "", 0);
			continue;
		}

		int k_limit = _CFG__TBL_COL_SIZE;
		int k;

		for(k=0; k<k_limit; k++)
		{
				 if(k == _TBL_COL__NUMBER)			str_item.Format("%1d", n_count);
			else if(k == _TBL_COL__NAME)			str_item = l_title[i];
			else if(k == _TBL_COL__DATA)			str_item = "";
			else if(k == _TBL_COL__CHANNEL)			str_item = l_channel[i];
			else									continue;

			if(k == _TBL_COL__NUMBER)		p_table->InsertItem(i, str_item, 0);
			else							p_table->SetItem(i,k, LVIF_TEXT,str_item,0,0,0,0);
		}

		n_count++;
	}

	p_table->SetRedraw(TRUE);
}

void CDlg__PMx_Table::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 1)
	{
		CStringArray l_data;

		// ...
		{
			CStringArray l_channel;

			CString ch_name;
			CString ch_data;

			mCtrl_PMx.Get__CHANNEL_INFO(iPMx_ID,l_channel);
			
			int i_limit = l_channel.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				ch_name = l_channel[i];
				ch_data = "";

				pGObj_Res->pGOBJ_PARA_CTRL->Get__Data_From_Ch_Name(ch_name,ch_data);

				l_data.Add(ch_data);
			}
		}

		// ...
		{
			CString pre_data;
			CString cur_data;

			CListCtrl *p_table = &mCtrl__PMx_Table;

			int t_count = p_table->GetItemCount();
			int c_index = _TBL_COL__DATA;

			int i_limit = l_data.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				pre_data = p_table->GetItemText(i,c_index);
				cur_data = l_data[i];
				
				if(pre_data == cur_data)		continue;
				if(i >= t_count)				continue;

				p_table->SetItemText(i,c_index, cur_data);
			}
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CDlg__PMx_Table::OnBnClickedBtn__GOTO_MAINT()
{
	int pm_id = iPMx_ID;
	if(pm_id < 1)			return;

	_Request__GOTO_MAINT_Of_PMx(pm_id);
}
