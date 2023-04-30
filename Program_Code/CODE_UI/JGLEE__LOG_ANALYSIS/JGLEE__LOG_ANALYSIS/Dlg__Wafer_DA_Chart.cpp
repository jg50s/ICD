// Dlg__Wafer_DA_Chart.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"
#include "Dlg__Wafer_DA_Chart.h"

#include "Macro__Wafer_Tree.h"


#define  _DEF__PI						3.141592


// CDlg__Wafer_DA_Chart dialog

IMPLEMENT_DYNAMIC(CDlg__Wafer_DA_Chart, CDialog)

CDlg__Wafer_DA_Chart::CDlg__Wafer_DA_Chart(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Wafer_DA_Chart::IDD, pParent)
	, mStr__Error_Range(_T(""))
{
	bActive__Multi_Slot = false;
}

CDlg__Wafer_DA_Chart::~CDlg__Wafer_DA_Chart()
{
}

void CDlg__Wafer_DA_Chart::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST__SLOT_INFO,  mList__Slot_Info);
	DDX_Control(pDX, IDC_LIST__WAFER_INFO, mCtrl__Wafer_Info);
	DDX_Control(pDX, IDC_STATIC__DA_CHART, mDA_Chart);

	DDX_Control(pDX, IDC_CHECK__ERROR_RANGE, mCheck__Error_Range);
	DDX_Text(pDX, IDC_EDIT__ERROR_RANGE, mStr__Error_Range);
	DDX_Control(pDX, IDC_SPIN__ERRIR_RANGE, mCtrl__Error_Range);
	DDX_Control(pDX, IDC_BTN__LOTID_DATA, mBtn__LotID_Data);
	DDX_Control(pDX, IDC_BTN__PORTID_DATA, mBtn__PortID_Data);
	DDX_Control(pDX, IDC_BTN__SLOTID_DATA, mBtn__SlotID_Data);

	DDX_Control(pDX, IDC_CHECK__PM1, mCheck_PM1);
	DDX_Control(pDX, IDC_CHECK__PM2, mCheck_PM2);
	DDX_Control(pDX, IDC_CHECK__PM3, mCheck_PM3);
	DDX_Control(pDX, IDC_CHECK__PM4, mCheck_PM4);
	DDX_Control(pDX, IDC_CHECK__PM5, mCheck_PM5);
	DDX_Control(pDX, IDC_CHECK__PM6, mCheck_PM6);

	DDX_Control(pDX, IDC_CHECK__LL1, mCheck_LL1);
	DDX_Control(pDX, IDC_CHECK__LL2, mCheck_LL2);
	DDX_Control(pDX, IDC_CHECK__LL3, mCheck_LL3);
	DDX_Control(pDX, IDC_CHECK__LL4, mCheck_LL4);

	DDX_Control(pDX, IDC_CHECK__ONLY_ALARM, mCheck__Only_Alarm);
	DDX_Control(pDX, IDC_BTN__SLOT_ALL,   mBtn__Slot_All);
	DDX_Control(pDX, IDC_BTN__SLOT_CLEAR, mBtn__Slot_Clear);
}


BEGIN_MESSAGE_MAP(CDlg__Wafer_DA_Chart, CDialog)
	ON_WM_PAINT()

	ON_BN_CLICKED(IDC_BTN__SLOT_ALL,   &CDlg__Wafer_DA_Chart::OnBnClickedBtn__Slot_All)
	ON_BN_CLICKED(IDC_BTN__SLOT_CLEAR, &CDlg__Wafer_DA_Chart::OnBnClickedBtn__Slot_Clear)

	ON_NOTIFY(NM_CLICK, IDC_LIST__WAFER_INFO, &CDlg__Wafer_DA_Chart::OnNMClickList__Wafer_Select)

	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN__ERRIR_RANGE, &CDlg__Wafer_DA_Chart::OnDeltaposSpin__Error_Range)
	ON_BN_CLICKED(IDC_CHECK__ERROR_RANGE, &CDlg__Wafer_DA_Chart::OnBnClickedCheck__Error_Range)

	ON_BN_CLICKED(IDC_BTN__CHECK_ALL,   &CDlg__Wafer_DA_Chart::OnBnClickedBtn__Check_All)
	ON_BN_CLICKED(IDC_BTN__CHECK_CLEAR, &CDlg__Wafer_DA_Chart::OnBnClickedBtn__Check_Clear)
	ON_BN_CLICKED(IDC_BTN__CHECK_PMx,   &CDlg__Wafer_DA_Chart::OnBnClickedBtn__Check_PMx)
	ON_BN_CLICKED(IDC_BTN__CHECK_LLx,   &CDlg__Wafer_DA_Chart::OnBnClickedBtn__Check_LLx)

	ON_NOTIFY(NM_CLICK, IDC_LIST__SLOT_INFO, &CDlg__Wafer_DA_Chart::OnNMClickList__Slot_Info)
	ON_BN_CLICKED(IDC_BTN__RESULT_REFRESH, &CDlg__Wafer_DA_Chart::OnBnClickedBtn__Result_Refresh)
END_MESSAGE_MAP()


// CDlg__Wafer_DA_Chart message handlers

BOOL CDlg__Wafer_DA_Chart::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		_Make__Slot_List();

		if(bActive__Multi_Slot)
		{
			_Add__Slot_List(sList__Slot_ID);

			mList__Slot_Info.EnableWindow(TRUE);
			mBtn__Slot_All.EnableWindow(TRUE);
			mBtn__Slot_Clear.EnableWindow(TRUE);
		}
		else
		{
			sList__Slot_ID.Add(sPara__SlotID);

			_Add__Slot_List(sList__Slot_ID);

			mList__Slot_Info.EnableWindow(FALSE);
			mBtn__Slot_All.EnableWindow(FALSE);
			mBtn__Slot_Clear.EnableWindow(FALSE);
		}
	}

	// ...
	{
		CListCtrl *p_table = &mCtrl__Wafer_Info;
		CImageList *p_img = &mImg__Wafer_Info;

		_Make__Wafer_List(p_table, p_img);
	}

	// ...
	{
		dRes__Axis_Range = 1.0;
		dRes__Axis_Max = dRes__Axis_Range * 5.0;

		dData__Error_Range = 1.6;
		mStr__Error_Range.Format("%.1f", dData__Error_Range);

		mCheck__Error_Range.SetCheck(1);
	}

	// ...
	{
		mBtn__LotID_Data.SetWindowText(sPara__LotID);
		mBtn__PortID_Data.SetWindowText(sPara__PortOD);
		mBtn__SlotID_Data.SetWindowText(sPara__SlotID);
	}

	// ...
	{
		OnBnClickedBtn__Slot_All();
		OnBnClickedBtn__Check_All();

		mCheck__Only_Alarm.SetCheck(0);
	}

	// ...
	{
		_Clear__Wafer_List();
		_Add__Wafer_List(sPara__SlotID, sList__MODULE,sList__R_OFFSET,sList__T_OFFSET);
	}

	UpdateData(FALSE);
	return TRUE;
}

void CDlg__Wafer_DA_Chart::OnPaint()
{
	CPaintDC dc(this); 

	_Draw__DA_Chart(-1);
}

void CDlg__Wafer_DA_Chart::
_Draw__DA_Chart(const int db_index)
{
	double axis_range = dRes__Axis_Range;

	// ...
	RECT rc_client;
	RECT rc_circle;
	int  center_x;
	int  center_y;
	int  center_r;

	CDC *p_dc = mDA_Chart.GetWindowDC();

	int sel_index = db_index;
	if(sel_index < 0)		sel_index = mCtrl__Wafer_Info.GetSelectionMark();

	// ...
	{
		RECT rc_win;
		mDA_Chart.GetClientRect(&rc_win);

		int ws = 2;
		rc_win.left += ws;
		rc_win.top  += ws;
		rc_win.right  -= ws;
		rc_win.bottom -= ws;

		rc_client.left   = rc_win.left;
		rc_client.top    = rc_win.top;
		rc_client.right  = rc_win.right;
		rc_client.bottom = rc_win.bottom - 15;

		center_x = (rc_client.right + rc_client.left) / 2;
		center_y = (rc_client.bottom + rc_client.top) / 2;

		p_dc->Rectangle(&rc_win);
	}
	// Circle ...
	{
		int e_m = 6;
		int s_w = (rc_client.right - rc_client.left - e_m) / 2;
		int s_h = (rc_client.bottom - rc_client.top - e_m) / 2;

		if(s_w > s_h)		s_w = s_h;
		center_r = s_w;

		rc_circle.left   = center_x - center_r;
		rc_circle.top    = center_y - center_r;
		rc_circle.right  = center_x + center_r;
		rc_circle.bottom = center_y + center_r;

		p_dc->Ellipse(&rc_circle);
	}

	// Error Range ...
	if(mCheck__Error_Range.GetCheck() > 0)
	{
		COLORREF pt_color = RGB(255,100,100);

		CPen *p_old_pen = NULL;
		CPen pen_xxx(PS_SOLID, 1, pt_color);
		p_old_pen = p_dc->SelectObject(&pen_xxx);

		// ...
		{
			int err_r = (dData__Error_Range / (axis_range * 5.0)) * center_r;

			RECT rc_err;
			rc_err.left   = center_x - err_r;
			rc_err.top    = center_y - err_r;
			rc_err.right  = center_x + err_r;
			rc_err.bottom = center_y + err_r;

			p_dc->Ellipse(&rc_err);
		}

		p_dc->SelectObject(p_old_pen);
	}

	// X & T Axis ...
	{
		// X Axis ...
		{
			int p_x1 = rc_client.left;
			int p_y1 = center_y;

			int p_x2 = rc_client.right;
			int p_y2 = center_y;

			p_dc->MoveTo(p_x1,p_y1);
			p_dc->LineTo(p_x2,p_y2);
		}
		// Y Axis ...
		{
			int p_x1 = center_x;
			int p_y1 = rc_client.top;

			int p_x2 = center_x;
			int p_y2 = rc_client.bottom;

			p_dc->MoveTo(p_x1,p_y1);
			p_dc->LineTo(p_x2,p_y2);
		}
	}
	// X Text ...
	{
		CString t_str;

		int t_y = center_y + 5;

		int i_limit = 5;
		int i;

		for(i=0; i<=i_limit; i++)
		{
			int x_pos = (i_limit - i);
			int t_x = (x_pos * center_r) / i_limit;

			// ...
			{
				t_str.Format("%.1f", x_pos * axis_range);
				p_dc->TextOut(center_x + t_x, t_y, t_str);
			}
			if(x_pos > 0)
			{
				t_str.Format("%.1f", -x_pos * axis_range);
				p_dc->TextOut(center_x - t_x, t_y, t_str);
			}
		}
	}
	// Y Text ...
	{
		CString t_str;

		int t_x = center_x + 5;

		int i_limit = 5;
		int i;

		for(i=0; i<=i_limit; i++)
		{
			int y_pos = (i_limit - i);
			int t_y = (y_pos * center_r) / i_limit;

			if(y_pos > 0)
			{
				t_str.Format("%.1f", -y_pos * axis_range);
				p_dc->TextOut(t_x, center_y + t_y, t_str);

				t_str.Format("%.1f", y_pos * axis_range);
				p_dc->TextOut(t_x, center_y - t_y, t_str);
			}
		}
	}
	// Unit Text ...
	{
		CString t_str = "mm";

		int t_x = center_x + center_r - 20;
		int t_y = center_y + center_y - 5;

		p_dc->TextOut(t_x,t_y, t_str);
	}

	// ...
	{
		iRes__Center_X = center_x;
		iRes__Center_Y = center_y;
		dRes__Center_R = center_r;
		iRes__Point_R_Size = 4;
	}

	// RT Point ...
	{
		COLORREF pt_color = RGB(0,0,255);

		CPen pen_xxx(PS_SOLID, 1, pt_color);
		CPen *p_old_pen = p_dc->SelectObject(&pen_xxx);

		CBrush brush_xxx;
		brush_xxx.CreateSolidBrush( RGB(255,128,0) );  

		// ...
		{
			CStringArray l_off_r;
			CStringArray l_off_t;

			int p_x1;
			int p_y1;
			int p_x2;
			int p_y2;

			_Get__RT_Offset_Of_Wafer_List(l_off_r,l_off_t);

			int i_limit = l_off_r.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				double r_deg = atof(l_off_r[i]);
				double t_mm  = atof(l_off_t[i]);

				_Get__XY_Of_RT(r_deg,t_mm, p_x1,p_y1, p_x2,p_y2);

				if(i != sel_index)
				{
					p_dc->Ellipse(p_x1,p_y1, p_x2,p_y2);
				}
			}

			if(sel_index >= 0)
			{
				i = sel_index;

				double r_deg = atof(l_off_r[i]);
				double t_mm  = atof(l_off_t[i]);

				_Get__XY_Of_RT(r_deg,t_mm, p_x1,p_y1, p_x2,p_y2);

				// ...
				{
					CBrush* p_old_brush = p_dc->SelectObject(&brush_xxx);

					p_dc->Rectangle(p_x1,p_y1, p_x2,p_y2);

					p_dc->SelectObject(p_old_brush);
				}
			}
		}

		p_dc->SelectObject(p_old_pen);
	}
}
int  CDlg__Wafer_DA_Chart
::_Get__XY_Of_RT(const double para_r_deg, 
				 const double t_mm,
				 int& p_x1,int& p_y1,
				 int& p_x2,int& p_y2)
{
	double r_deg = para_r_deg * _DEF__PI / 180.0;

	double v_x = t_mm * cos(r_deg);
	double v_y = t_mm * sin(r_deg);

	p_x1 = iRes__Center_X + ((v_x / (5.0 * dRes__Axis_Range)) * dRes__Center_R) - iRes__Point_R_Size;
	p_y1 = iRes__Center_Y - ((v_y / (5.0 * dRes__Axis_Range)) * dRes__Center_R) - iRes__Point_R_Size;
	p_x2 = p_x1 + (2 * iRes__Point_R_Size);
	p_y2 = p_y1 + (2 * iRes__Point_R_Size);

	return 1;
}

void CDlg__Wafer_DA_Chart::OnDeltaposSpin__Error_Range(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	double ref_max = dRes__Axis_Max * 0.9;

	if(pNMUpDown->iDelta < 0)
	{
		dData__Error_Range += 0.1;
		if(dData__Error_Range >= ref_max)
			dData__Error_Range = ref_max;

		mStr__Error_Range.Format("%.1f", dData__Error_Range);
	}
	else
	{
		dData__Error_Range -= 0.1;
		if(dData__Error_Range <= 0.1)
			dData__Error_Range = 0.1;

		mStr__Error_Range.Format("%.1f", dData__Error_Range);
	}

	*pResult = 0;

	_Draw__DA_Chart(-1);
	UpdateData(FALSE);
}

void CDlg__Wafer_DA_Chart::OnNMClickList__Wafer_Select(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// ...
	{
		int r_index = pNMItemActivate->iItem;

		_Draw__DA_Chart(r_index);
	}

	*pResult = 0;
}

void CDlg__Wafer_DA_Chart::OnBnClickedCheck__Error_Range()
{
	_Draw__DA_Chart(-1);
}

void CDlg__Wafer_DA_Chart::OnBnClickedBtn__Check_All()
{
	mCheck_PM1.SetCheck(1);
	mCheck_PM2.SetCheck(1);
	mCheck_PM3.SetCheck(1);
	mCheck_PM4.SetCheck(1);
	mCheck_PM5.SetCheck(1);
	mCheck_PM6.SetCheck(1);

	mCheck_LL1.SetCheck(1);
	mCheck_LL2.SetCheck(1);
	mCheck_LL3.SetCheck(1);
	mCheck_LL4.SetCheck(1);
}
void CDlg__Wafer_DA_Chart::OnBnClickedBtn__Check_Clear()
{
	mCheck_PM1.SetCheck(0);
	mCheck_PM2.SetCheck(0);
	mCheck_PM3.SetCheck(0);
	mCheck_PM4.SetCheck(0);
	mCheck_PM5.SetCheck(0);
	mCheck_PM6.SetCheck(0);

	mCheck_LL1.SetCheck(0);
	mCheck_LL2.SetCheck(0);
	mCheck_LL3.SetCheck(0);
	mCheck_LL4.SetCheck(0);
}
void CDlg__Wafer_DA_Chart::OnBnClickedBtn__Check_PMx()
{
	mCheck_PM1.SetCheck(1);
	mCheck_PM2.SetCheck(1);
	mCheck_PM3.SetCheck(1);
	mCheck_PM4.SetCheck(1);
	mCheck_PM5.SetCheck(1);
	mCheck_PM6.SetCheck(1);

	mCheck_LL1.SetCheck(0);
	mCheck_LL2.SetCheck(0);
	mCheck_LL3.SetCheck(0);
	mCheck_LL4.SetCheck(0);
}
void CDlg__Wafer_DA_Chart::OnBnClickedBtn__Check_LLx()
{
	mCheck_PM1.SetCheck(0);
	mCheck_PM2.SetCheck(0);
	mCheck_PM3.SetCheck(0);
	mCheck_PM4.SetCheck(0);
	mCheck_PM5.SetCheck(0);
	mCheck_PM6.SetCheck(0);

	mCheck_LL1.SetCheck(1);
	mCheck_LL2.SetCheck(1);
	mCheck_LL3.SetCheck(1);
	mCheck_LL4.SetCheck(1);
}

void CDlg__Wafer_DA_Chart::OnBnClickedBtn__Slot_All()
{
	int i_limit = mList__Slot_Info.GetItemCount();

	for(int i=0; i<i_limit; i++)
		mList__Slot_Info.SetCheck(i, 1);
}
void CDlg__Wafer_DA_Chart::OnBnClickedBtn__Slot_Clear()
{
	int i_limit = mList__Slot_Info.GetItemCount();

	for(int i=0; i<i_limit; i++)
		mList__Slot_Info.SetCheck(i, 0);
}

void CDlg__Wafer_DA_Chart::OnNMClickList__Slot_Info(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int r_index = pNMItemActivate->iItem;
	if(r_index >= 0)
	{
		CListCtrl *p_table = &mList__Slot_Info;

		if(p_table->GetCheck(r_index) > 0)			p_table->SetCheck(r_index, 0);
		else										p_table->SetCheck(r_index, 1);
	}

	*pResult = 0;
}
void CDlg__Wafer_DA_Chart::OnBnClickedBtn__Result_Refresh()
{
	if(bActive__Multi_Slot)
	{
		CListCtrl* p_slot_info = &mList__Slot_Info;

		CString str_portid = sPara__PortOD;

		int i_limit = p_slot_info->GetItemCount();
		int i;

		_Clear__Wafer_List();

		for(i=0; i<i_limit; i++)
		{
			if(p_slot_info->GetCheck(i) < 1)		continue;

			//
			CString str_slotid = _Get__ID_Of_Slot_List(i);

			CString wfr_path;
			wfr_path.Format("%s\\%s\\P%s_%s.wfr", sDir_Root,sDir_Sub,str_portid,str_slotid);

			CLS__Wafer_Info wfr_info;
			MACRO__Update__Wafer_Info(wfr_path, &wfr_info);

			CStringArray l_module;
			CStringArray l_r_offset;
			CStringArray l_t_offset;

			wfr_info.Get__WAFER_DA_INFO(l_module,l_r_offset,l_t_offset);

			_Add__Wafer_List(str_slotid, l_module,l_r_offset,l_t_offset);
		}
	}
	else
	{
		_Clear__Wafer_List();

		_Add__Wafer_List(sPara__SlotID, sList__MODULE,sList__R_OFFSET,sList__T_OFFSET);
	}

	_Draw__DA_Chart(-1);
}
