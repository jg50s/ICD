// Dlg__DA_Log_STD.cpp : implementation file
//

#include "stdafx.h"
#include "math.h"

#include "JGLEE__LOG_TMC.h"
#include "Dlg__DA_Log_STD.h"

#include "CObj__DA_Log_STD.h"
#include "Macro_Function.h"

#include "CObj__DA_Log_STD__KEY_DEF.h"

#define  _DEF__PI						3.141592


// CDlg__DA_Log_STD dialog

IMPLEMENT_DYNAMIC(CDlg__DA_Log_STD, CDialog)

CDlg__DA_Log_STD::CDlg__DA_Log_STD(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__DA_Log_STD::IDD, pParent)
{
	mStr__Search_LotID  = _T("");
	mStr__Search_PPID   = _T("");
	mStr__Search_PortID = _T("");
	mStr__Search_SlotID = _T("");

	mStr__Error_Range = _T("");
	dData__Error_Range = 0.0;
}

CDlg__DA_Log_STD::~CDlg__DA_Log_STD()
{
}

void CDlg__DA_Log_STD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST__LOG_DATE, mCtrl__Log_Date);
	DDX_Control(pDX, IDC_LIST__LOG_FILE, mCtrl__Log_File);
	DDX_Control(pDX, IDC_LIST__LOG_RESULT, mCtrl__Log_Result);
	DDX_Control(pDX, IDC__DA_CHART, mDA_Chart);

	DDX_Text(pDX, IDC__SEARCH_LOTID,  mStr__Search_LotID);
	DDX_Text(pDX, IDC__SEARCH_PPID,   mStr__Search_PPID);
	DDX_Text(pDX, IDC__SEARCH_PORTID, mStr__Search_PortID);
	DDX_Text(pDX, IDC__SEARCH_SLOTID, mStr__Search_SlotID);

	DDX_Control(pDX, IDC__SEARCH_PM1, mCheck__Search_PM1);
	DDX_Control(pDX, IDC__SEARCH_PM2, mCheck__Search_PM2);
	DDX_Control(pDX, IDC__SEARCH_PM3, mCheck__Search_PM3);
	DDX_Control(pDX, IDC__SEARCH_PM4, mCheck__Search_PM4);
	DDX_Control(pDX, IDC__SEARCH_PM5, mCheck__Search_PM5);
	DDX_Control(pDX, IDC__SEARCH_PM6, mCheck__Search_PM6);

	DDX_Control(pDX, IDC__SEARCH_LL1, mCheck__Search_LL1);
	DDX_Control(pDX, IDC__SEARCH_LL2, mCheck__Search_LL2);
	DDX_Control(pDX, IDC__SEARCH_LL3, mCheck__Search_LL3);
	DDX_Control(pDX, IDC__SEARCH_LL4, mCheck__Search_LL4);
	DDX_Control(pDX, IDC_CHECK__ERROR_RANGE, mCheck__Error_Range);
	DDX_Text(pDX, IDC_EDIT__SOFT_ERROR, mStr__Error_Range);
	DDX_Control(pDX, IDC_SPIN1, mCtrl__Err_Ramge);
	DDX_Control(pDX, IDC__ONLY_ALARM, mCheck__Only_Alarm);
}


BEGIN_MESSAGE_MAP(CDlg__DA_Log_STD, CDialog)
	ON_BN_CLICKED(IDC_BTN__UPLOAD_LOG, &CDlg__DA_Log_STD::OnBnClickedBtn__Upload_Log)
	ON_BN_CLICKED(IDC_BTN__WFR_SEARCH, &CDlg__DA_Log_STD::OnBnClickedBtn__Wafer_Search)
	ON_BN_CLICKED(IDC_BTN__WFR_REFRESH, &CDlg__DA_Log_STD::OnBnClickedBtn__DA_Refresh)
	ON_BN_CLICKED(IDC_BTN__RESULT_REFRESH, &CDlg__DA_Log_STD::OnBnClickedBtn__Result_Refresh)

	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CDlg__DA_Log_STD::OnDeltaposSpin__Err_Range)

	ON_NOTIFY(NM_CLICK, IDC_LIST__LOG_DATE, &CDlg__DA_Log_STD::OnNMClickList__Log_Date)
	ON_NOTIFY(NM_CLICK, IDC_LIST__LOG_FILE, &CDlg__DA_Log_STD::OnNMClickList__Log_File)
	ON_NOTIFY(NM_CLICK, IDC_LIST__LOG_RESULT, &CDlg__DA_Log_STD::OnNMClickList__DA_Item)

	ON_WM_PAINT()

	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST__LOG_DATE, &CDlg__DA_Log_STD::OnLvnColumnclickList__Log_Date)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST__LOG_FILE, &CDlg__DA_Log_STD::OnLvnColumnclickList__Log_File)

END_MESSAGE_MAP()


// CDlg__DA_Log_STD message handlers

BOOL CDlg__DA_Log_STD::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	CListCtrl *p_table;

	CImageList *p_img = &mImg_Log;
	int list_view_stype;

	// ...
	{
		CBitmap cBit;
		cBit.LoadBitmap(IDB_DIGITAL_LIST_IMG);

		p_img->Create(1,20, ILC_COLOR4,1,1);
		p_img->Add(&cBit, RGB(0,0,0));	

		list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
		list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
		list_view_stype += LVS_EX_INFOTIP;
	}

	// ...
	int i_limit = 3;
	int i;

	for(i=0; i<i_limit; i++)
	{
		     if(i == 0)		p_table = &mCtrl__Log_Date;			// Log-Dir 
		else if(i == 1)		p_table = &mCtrl__Log_File;			// Log-File
		else if(i == 2)		p_table = &mCtrl__Log_Result;		// Log-Result
		else				continue;

		// ...
		{
			p_table->SetImageList(p_img, LVSIL_SMALL);
			p_table->SetExtendedStyle(list_view_stype);
		}

			 if(i == 0)				_Make__Table_Dir_List(p_table);
		else if(i == 1)				_Make__Table_LotID_List(p_table);
		else if(i == 2)				_Make__Result_List(p_table);
	}

	// ...
	{
		CButton* p_bttn;

		for(i=0; i<_CFG__PMx_SIZE; i++)
		{
				 if(i == 0)		p_bttn = &mCheck__Search_PM1;
			else if(i == 1)		p_bttn = &mCheck__Search_PM2;
			else if(i == 2)		p_bttn = &mCheck__Search_PM3;
			else if(i == 3)		p_bttn = &mCheck__Search_PM4;
			else if(i == 4)		p_bttn = &mCheck__Search_PM5;
			else if(i == 5)		p_bttn = &mCheck__Search_PM6;
			else				continue;

			pCheck__Search_PMx[i] = p_bttn;
		}

		for(i=0; i<_CFG__LLx_SIZE; i++)
		{
				 if(i == 0)		p_bttn = &mCheck__Search_LL1;
			else if(i == 1)		p_bttn = &mCheck__Search_LL2;
			else if(i == 2)		p_bttn = &mCheck__Search_LL3;
			else if(i == 3)		p_bttn = &mCheck__Search_LL4;
			else				continue;

			pCheck__Search_LLx[i] = p_bttn;
		}
	}

	// ...
	{
		for(i=0; i<_CFG__PMx_SIZE; i++)
		{
			bCheck__PMx[i] = true;

			if(bCheck__PMx[i])		pCheck__Search_PMx[i]->SetCheck(1);
			else					pCheck__Search_PMx[i]->SetCheck(0);
		}
		for(i=0; i<_CFG__LLx_SIZE; i++)
		{
			bCheck__LLx[i] = true;

			if(bCheck__LLx[i])		pCheck__Search_LLx[i]->SetCheck(1);
			else					pCheck__Search_LLx[i]->SetCheck(0);
		}
	}

	// ...
	{
		iSearch__PortID = 0;
		iSearch__SlotID = 0;
	}

	// ...
	{
		mCheck__Error_Range.SetCheck(1);

		mStr__Error_Range.Format("%.1f", dData__Error_Range);
	}

	UpdateData(FALSE);
	return TRUE; 
}

void CDlg__DA_Log_STD::OnDeltaposSpin__Err_Range(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if(pNMUpDown->iDelta < 0)
	{
		dData__Error_Range += 0.1;
		if(dData__Error_Range > 10.0)
			dData__Error_Range = 10.0;

		mStr__Error_Range.Format("%.1f", dData__Error_Range);
	}
	else
	{
		dData__Error_Range -= 0.1;
		if(dData__Error_Range < -10.0)
			dData__Error_Range = -10.0;

		mStr__Error_Range.Format("%.1f", dData__Error_Range);
	}

	*pResult = 0;

	_Draw__DA_Chart();
	UpdateData(FALSE);
}

void CDlg__DA_Log_STD::OnPaint()
{
	CPaintDC dc(this); 

	_Draw__DA_Chart();
}
void CDlg__DA_Log_STD::_Draw__DA_Chart(const int db_index)
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
	if(sel_index < 0)		sel_index = mCtrl__Log_Result.GetSelectionMark();

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
			dData__Error_Range = atof(mStr__Error_Range);
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

		COLORREF pt_color;
		CPen *p_old_pen = NULL;
		//pt_color = RGB(255,100,0);
		//CPen pen_xxx(PS_SOLID, 1, pt_color);
		//p_old_pen = p_dc->SelectObject(&pen_xxx);
		//CPen *p_old_pen = p_dc->SelectObject(&pen_xxx);
		
		CBrush brush_xxx;
		brush_xxx.CreateSolidBrush( RGB(255,128,0) );  

		// ...
		{
			CStringArray l_off_01;
			CStringArray l_off_02;
			CStringArray l_Arm_Type;
			CStringArray l_Arm_Action;

			mDB__OFFSET_PT.Get__INFO(l_off_01, l_off_02);
			mDB__OFFSET_PT.Get__INFO_ARM(l_Arm_Type, l_Arm_Action);//KMS

			// ...
			int p_x1;
			int p_y1;
			int p_x2;
			int p_y2;

			// ...
			int i_limit = l_off_01.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				
				
					
					if(l_Arm_Type[i] == "A")
					{
						if(l_Arm_Action[i] == "PICK") pt_color = RGB(0,176,240); // Target Porint Circle Brush
						else pt_color = RGB(255,0,0); // Target Porint Circle Brush
					}
					else // ARM-B
					{
						if(l_Arm_Action[i]  == "PICK") pt_color = RGB(112,48,160); // Target Porint Circle Brush
						else pt_color = RGB(146,208,80); // Target Porint Circle Brush
					}
					
					//pt_color = RGB(100,0,255);
					CPen pen_xxx(PS_SOLID, 1, pt_color);
					p_old_pen = p_dc->SelectObject(&pen_xxx);
				
				
				//...
				if(bActive__R_T_OFFSET)
				{
					double r_mm  = atof(l_off_01[i]);
					double t_deg = atof(l_off_02[i]);

					_Get__XY_Of_RT(r_mm,t_deg, p_x1,p_y1, p_x2,p_y2);   
				}
				else
				{
					double x_pos = atof(l_off_01[i]);
					double y_pos = atof(l_off_02[i]);

					_Get__XY_Of_XY(x_pos,y_pos, p_x1,p_y1, p_x2,p_y2);   
				}

				if(i != sel_index)
				{
					p_dc->Ellipse(p_x1,p_y1, p_x2,p_y2);
				}
			}

			if(sel_index >= 0)
			{
				i = sel_index;

				if(bActive__R_T_OFFSET)
				{
					double r_mm  = atof(l_off_01[i]);
					double t_deg = atof(l_off_02[i]);

					_Get__XY_Of_RT(r_mm,t_deg, p_x1,p_y1, p_x2,p_y2);
				}
				else
				{
					double x_pos = atof(l_off_01[i]);
					double y_pos = atof(l_off_02[i]);

					_Get__XY_Of_XY(x_pos,y_pos, p_x1,p_y1, p_x2,p_y2);   
				}

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
int  CDlg__DA_Log_STD::_Get__XY_Of_RT(const double para_radius, 
									  const double para_degree,
									  int& p_x1,int& p_y1,
									  int& p_x2,int& p_y2)
{
	double theta_deg = para_degree * _DEF__PI / 180.0;

	double v_x = para_radius * cos(theta_deg);
	double v_y = para_radius * sin(theta_deg);

	p_x1 = iRes__Center_X + ((v_x / (5.0 * dRes__Axis_Range)) * dRes__Center_R) - iRes__Point_R_Size;
	p_y1 = iRes__Center_Y - ((v_y / (5.0 * dRes__Axis_Range)) * dRes__Center_R) - iRes__Point_R_Size;
	p_x2 = p_x1 + (2 * iRes__Point_R_Size);
	p_y2 = p_y1 + (2 * iRes__Point_R_Size);

	return 1;
}
int  CDlg__DA_Log_STD::_Get__XY_Of_XY(const double x_offset, 
									  const double y_offset,
									  int& p_x1,int& p_y1,
									  int& p_x2,int& p_y2)
{
	double v_x = x_offset;
	double v_y = y_offset;

	p_x1 = iRes__Center_X + ((v_x / (5.0 * dRes__Axis_Range)) * dRes__Center_R) - iRes__Point_R_Size;
	p_y1 = iRes__Center_Y - ((v_y / (5.0 * dRes__Axis_Range)) * dRes__Center_R) - iRes__Point_R_Size;
	p_x2 = p_x1 + (2 * iRes__Point_R_Size);
	p_y2 = p_y1 + (2 * iRes__Point_R_Size);

	return 1;
}

void CDlg__DA_Log_STD::OnBnClickedBtn__Upload_Log()
{
	CString dir_root = sDir_Root;

	// ...
	{
		mCtrl__Log_Date.DeleteAllItems();
		mCtrl__Log_File.DeleteAllItems();
	    mCtrl__Log_Result.DeleteAllItems();

		mDB_LOTID.Clear__LOTID();
	}

	// ...	
	{
		CStringArray l_dir_name;
		CStringArray l_dir_date;

		CString dir_log;
		CString file_ext = "log";

		MACRO__Get_Dir_Date_List(dir_root, l_dir_name,l_dir_date);

		// ...
		CListCtrl *p_table = &mCtrl__Log_Date;
		bSortDirect_LogDate = false;
		Sort__Log_Table(p_table, 2, bSortDirect_LogDate, l_dir_name,l_dir_date);
		
		sList__Log_Date__Name.Copy(l_dir_name);
		sList__Log_Date__Date.Copy(l_dir_date);

		if(l_dir_name.GetCount() > 0)
		{
			int row = 0;

			p_table->SetHotItem(row);
			p_table->SetItemState(row, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED); 
		}

		// ...
		int i_limit = l_dir_name.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			dir_log.Format("%s\\%s", dir_root,l_dir_name[i]);
			
			if(i != 0)		continue;;

			_Update__Log_Date(dir_log, file_ext);
		}		
	}

	// ...
}
void CDlg__DA_Log_STD::
_Update__Log_Date(const CString& dir_log,
				  const CString& file_ext)
{
	// ...
	{
		mCtrl__Log_File.DeleteAllItems();
		mCtrl__Log_Result.DeleteAllItems();

		mDB_LOTID.Clear__LOTID();
		mDB__OFFSET_PT.Clear__INFO();
	}

	// ...
	CStringArray l_file_name;
	CStringArray l_file_date;

	MACRO__Get_File_List(dir_log,file_ext, l_file_name,l_file_date);

	// ...
	int k_limit = l_file_name.GetSize();
	int k;

	for(k=0; k<k_limit; k++)
	{
		CString str_line = l_file_name[k];

		CStringArray l_para;
		MACRO__Convert__LIST('+', str_line, l_para);		

		bool active__prc_file = false;
		CString str_file_header = "";
		CString str_lotid  = "";
		CString str_portid = "";

		int t_limit = l_para.GetSize();
		int t;

		for(t=0; t<t_limit; t++)
		{
			CString str_para = l_para[t];

			if(t == 0)
			{
				if(bActive__LOG_PROC)
				{
					if(str_para.CompareNoCase("PRC") == 0)
					{
						active__prc_file = true;

						str_file_header = "PRC";
					}
				}
				else
				{
					if((str_para.Find("PM") == 0)
					|| (str_para.Find("LL") == 0))
					{
						active__prc_file = true;

						int s_index = str_para.Find("+", 0);
						if(s_index >= 0)		str_para.Delete(s_index, str_para.GetLength() - s_index);

						str_file_header = str_para;
					}
				}
			}
			else if(t == 1)		str_portid = str_para;
			else if(t == 2)		str_lotid  = str_para;
		}

		if(active__prc_file)
		{
			mDB_LOTID.Load__LOTID(str_lotid, str_portid, str_file_header);
		}
	}

	// ...
	{
		CStringArray l_lotid;
		CStringArray l_portid;
		CStringArray l_log_header;

		mDB_LOTID.Get__LOTID(l_lotid, l_portid, l_log_header);

		// ...
		CListCtrl *p_table = &mCtrl__Log_File;
		bSortDirect_LogFile = true;
		
		Sort__Log_Table(p_table, 4, 1, bSortDirect_LogFile, l_portid,l_lotid,l_log_header);

		sList__Log_File__PortID.Copy(l_portid);
		sList__Log_File__LotID.Copy(l_lotid);
		sList__Log_File__Header.Copy(l_log_header);

		if(l_portid.GetCount() > 0)
		{
			int row = 0;

			p_table->SetHotItem(row);
			p_table->SetItemState(row, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED); 

			_Fnc__Log_View(row);
			_Draw__DA_Chart();
		}
	}
}

void CDlg__DA_Log_STD::OnBnClickedBtn__Wafer_Search()
{
	CDlg__DA_Wafer_Search dlg;
	int i;

	// ...
	{
		dlg.sPara__LotID = sSearch__LotID;
		dlg.sPara__PPID  = sSearch__PPID;

		dlg.iPara__PortID = iSearch__PortID;
		dlg.iPara__SlotID = iSearch__SlotID;

		for(i=0; i<_CFG__PMx_SIZE; i++)
			dlg.bPara__Check_PMx[i] = bCheck__PMx[i];

		for(i=0; i<_CFG__LLx_SIZE; i++)
			dlg.bPara__Check_LLx[i] = bCheck__LLx[i];
	}

	if(dlg.DoModal() == IDOK)
	{
		UpdateData(TRUE);

		// ...
		{
			sSearch__LotID = dlg.sPara__LotID;
			sSearch__PPID  = dlg.sPara__PPID;

			iSearch__PortID = dlg.iPara__PortID;
			iSearch__SlotID = dlg.iPara__SlotID;
	
			for(i=0; i<_CFG__PMx_SIZE; i++)
				bCheck__PMx[i] = dlg.bPara__Check_PMx[i];
	
			for(i=0; i<_CFG__LLx_SIZE; i++)
				bCheck__LLx[i] = dlg.bPara__Check_LLx[i];
		}

		// ...
		{
			mStr__Search_LotID = sSearch__LotID;
			mStr__Search_PPID  = sSearch__PPID;

			mStr__Search_PortID.Format("%1d", iSearch__PortID);
			mStr__Search_SlotID.Format("%1d", iSearch__SlotID);

			for(i=0; i<_CFG__PMx_SIZE; i++)
			{
				if(bCheck__PMx[i])		pCheck__Search_PMx[i]->SetCheck(1);
				else					pCheck__Search_PMx[i]->SetCheck(0);
			}
			for(i=0; i<_CFG__LLx_SIZE; i++)
			{
				if(bCheck__LLx[i])		pCheck__Search_LLx[i]->SetCheck(1);
				else					pCheck__Search_LLx[i]->SetCheck(0);
			}
		}

		_Fnc__Log_View();
		_Draw__DA_Chart();

		UpdateData(FALSE);
	}
}
void CDlg__DA_Log_STD::OnBnClickedBtn__DA_Refresh()
{
	UpdateData(TRUE);

	_Draw__DA_Chart();
}
void CDlg__DA_Log_STD::OnBnClickedBtn__Result_Refresh()
{
	UpdateData(TRUE);

	_Fnc__Log_View();
	_Draw__DA_Chart();
}

void CDlg__DA_Log_STD::OnNMClickList__Log_Date(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// ...
	{
		CString dir_root = sDir_Root;
		CString file_ext = "log";

		int r_index = pNMItemActivate->iItem;
		int c_index = 1;

		CString dir_name = mCtrl__Log_Date.GetItemText(r_index,c_index);
		CString dir_log;

		dir_log.Format("%s\\%s", dir_root,dir_name);
		printf("dir_log <- [%s] \n", dir_log);
		
		_Update__Log_Date(dir_log, file_ext);
		_Draw__DA_Chart();
	}
	*pResult = 0;
}
void CDlg__DA_Log_STD::OnNMClickList__Log_File(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// ...
	{
		int r_index = pNMItemActivate->iItem;

		_Fnc__Log_View(r_index);
		_Draw__DA_Chart();
	}
	*pResult = 0;
}
void CDlg__DA_Log_STD::OnNMClickList__DA_Item(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// ...
	{
		int r_index = pNMItemActivate->iItem;

		_Draw__DA_Chart(r_index);
	}
	*pResult = 0;
}

// ...
int CDlg__DA_Log_STD
::Set_Parameter(const int module_id)
{
	GObj__Parameter_Ctrl *p_para = pGObj_Res->pGOBJ_PARA_CTRL;

	CString para_data;
	CString dir_root;

	// ...
	{
		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_LOG_TYPE, para_data);

		if(para_data.CompareNoCase("PROCESS") == 0)		bActive__LOG_PROC = true;
		else											bActive__LOG_PROC = false;
	}

	// ...
	{
		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_OFFSET_TYPE, para_data);

		if(para_data.CompareNoCase("R_T") == 0)			bActive__R_T_OFFSET = true;
		else											bActive__R_T_OFFSET = false;
	}

	if(iREAL_MODE < 0)
	{
		CString log_msg;

		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__TEST_DIR_ROOT, dir_root);
		dir_root += "\\EQP_LOG\\DA_Data";

		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__TEST_AXIS_MAX, para_data);
		double data__axis_full_range = atof(para_data);
		dRes__Axis_Range = data__axis_full_range / 5.0;
		if(dRes__Axis_Range < 0.1)			dRes__Axis_Range = 1.0;

		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__TEST_ERR_RANGE, para_data);
		dData__Error_Range = atof(para_data);
		double range_half = data__axis_full_range / 2.0;
		if(dData__Error_Range > range_half)			dData__Error_Range = range_half;
		mStr__Error_Range.Format("%.1f", dData__Error_Range);
	}
	else
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;
		int eqp_id = module_id;
		
		x_sys_ctrl->Get__SEQ_DIR_ROOT(eqp_id, dir_root);
		dir_root += "\\EQP_LOG\\DA_Data";
	}

	sDir_Root = dir_root;

	return 1;
}

int CDlg__DA_Log_STD
::Set_MoveWindow(const POINT& p_st, const POINT& p_et)
{
	if(iREAL_MODE > 0)
	{
		CString key_name;
		CString ch_data;

		key_name = pKEY__CH_AXIS_MAX;
		pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Data(key_name, ch_data);
		dRes__Axis_Range = atof(ch_data) / 5.0;

		key_name = pKEY__CH_ERR_RANGE;
		pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Data(key_name, ch_data);
		dData__Error_Range = atof(ch_data);
		mStr__Error_Range.Format("%.1f", dData__Error_Range);

		UpdateData(FALSE);
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
int CDlg__DA_Log_STD
::Redraw_Page()
{
	Invalidate(TRUE);
	return 1;
}


// ...
void CDlg__DA_Log_STD::
OnLvnColumnclickList__Log_Date(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if(pNMLV->iItem == -1)
	{
		CListCtrl* p_table = &mCtrl__Log_Date;
		int col_id = pNMLV->iSubItem;

		Sort__Log_Table(p_table, col_id, bSortDirect_LogDate, sList__Log_Date__Name,sList__Log_Date__Date);
	}

	*pResult = 0;
}
void CDlg__DA_Log_STD::
OnLvnColumnclickList__Log_File(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if(pNMLV->iItem == -1)
	{
		CListCtrl* p_table = &mCtrl__Log_File;
		int col_id = pNMLV->iSubItem;
		int col_size = 4;

		Sort__Log_Table(p_table, col_size, col_id, bSortDirect_LogFile, sList__Log_File__PortID,sList__Log_File__LotID,sList__Log_File__Header);
	}

	*pResult = 0;
}

int  CDlg__DA_Log_STD::
Sort__Log_Table(CListCtrl* p_table,
				const int col_id, 
				bool& sort_order,
				CStringArray& l_file,
				CStringArray& l_date)
{
	CStringArray l_header;

	int db_size = l_date.GetSize();
	l_header.SetSize(db_size);

	return Sort__Log_Table(p_table, 3, col_id, sort_order, l_file,l_date,l_header);
}
int  CDlg__DA_Log_STD::
Sort__Log_Table(CListCtrl* p_table,
				const int col_size, 
				const int col_id, 
				bool& sort_order,
				CStringArray& l_file,
				CStringArray& l_date,
				CStringArray& l_header)
{
	if(col_id < 1)			return -1;
	if(col_id > 2)			return -2;

	// ...
	int i_limit = l_file.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString cmp_name   = l_file[i];
		CString cmp_date   = l_date[i];
		CString cmp_header = l_header[i];

		for(int k=i+1; k<i_limit; k++)
		{
			CString cur_name   = l_file[k];
			CString cur_date   = l_date[k];
			CString cur_header = l_header[k];

			// ...
			bool active_order = false;

			if(col_id == 1)
			{
				if(sort_order)		
				{
					if(cmp_name.CompareNoCase(cur_name) > 0)		active_order = true;
				}
				else
				{
					if(cmp_name.CompareNoCase(cur_name) < 0)		active_order = true;
				}
			}
			else if(col_id == 2)
			{
				if(sort_order)		
				{
					if(cmp_date.CompareNoCase(cur_date) > 0)		active_order = true;
				}
				else
				{
					if(cmp_date.CompareNoCase(cur_date) < 0)		active_order = true;
				}
			}

			if(active_order)
			{
				l_file[i]   = cur_name;
				l_date[i]   = cur_date;
				l_header[i] = cur_header;

				l_file[k]   = cmp_name;
				l_date[k]   = cmp_date;
				l_header[k] = cmp_header;

				cmp_name   = cur_name;
				cmp_date   = cur_date;
				cmp_header = cur_header;
			}
		}
	}

	_Add__Table_List(p_table, col_size, l_file,l_date,l_header);

	sort_order = !sort_order;
	return 1;
}
