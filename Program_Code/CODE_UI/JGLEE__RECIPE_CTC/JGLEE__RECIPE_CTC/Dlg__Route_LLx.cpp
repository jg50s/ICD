// Dlg__Route_LLx.cpp : implementation file
//

#include "stdafx.h"
#include "Interface_Header.h"

#include "JGLEE__RECIPE_CTC.h"
#include "CObj__Route_EDIT__KEY_DEF.h"

#include "Dlg__Route_LLx.h"
#include "Dlg__Route_Mode_Select.h"


// CDlg__Route_LLx dialog

IMPLEMENT_DYNAMIC(CDlg__Route_LLx, CDialog)

CDlg__Route_LLx::CDlg__Route_LLx(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Route_LLx::IDD, pParent)
	, mData_Mode(_T(""))
	, mData_Slot02(_T(""))
	, mData_Slot01(_T(""))
{

}

CDlg__Route_LLx::~CDlg__Route_LLx()
{
}

void CDlg__Route_LLx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT__MODE, mData_Mode);
	DDX_Text(pDX, IDC_EDIT__SLOT_02, mData_Slot02);
	DDX_Text(pDX, IDC_EDIT__SLOT_01, mData_Slot01);

	DDX_Text(pDX, IDC_EDIT__COOLING_SEC, mData__Cooling_Sec);
	DDX_Control(pDX, IDC_BTN__COOLING_SEC, mCtrl__Cooling_Sec);

	DDX_Control(pDX, IDC_BTN__SLOT_01, mCtrl__Slot_01);
	DDX_Control(pDX, IDC_BTN__SLOT_02, mCtrl__Slot_02);
}


BEGIN_MESSAGE_MAP(CDlg__Route_LLx, CDialog)
	ON_BN_CLICKED(IDC_BTN__MODE,    &CDlg__Route_LLx::OnBnClickedBtn__MODE)
	ON_BN_CLICKED(IDC_BTN__SLOT_01, &CDlg__Route_LLx::OnBnClickedBtn__SLOT01)
	ON_BN_CLICKED(IDC_BTN__SLOT_02, &CDlg__Route_LLx::OnBnClickedBtn__SLOT02)
	ON_BN_CLICKED(IDC_BTN__COOLING_SEC, &CDlg__Route_LLx::OnBnClickedBtn__COOLING_SEC)

	ON_BN_CLICKED(IDOK, &CDlg__Route_LLx::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg__Route_LLx message handlers

BOOL CDlg__Route_LLx::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	CString str_title;

	str_title.Format("%s Option ...", sPARA_LLx);
	SetWindowText(str_title);

	// 1. 
	{
		mData_Mode = sPARA_MODE;
	}
	// 2. 
	{
		mData_Slot01 = "DISABLE";
		mData_Slot02 = "DISABLE";

		int i_limit = sPARA_SLOT.GetLength();
		int i;

		for(i=0; i<i_limit; i++)
		{
			char ch_slot = sPARA_SLOT[i];

			if(ch_slot == '1')
			{
					 if(i == 0)		mData_Slot01 = "ENABLE";
				else if(i == 1)		mData_Slot02 = "ENABLE";
			}
			else
			{
					 if(i == 0)		mData_Slot01 = "DISABLE";
				else if(i == 1)		mData_Slot02 = "DISABLE";
			}
		}
	}

	if(bACTIVE__LLx_SLOT_FIXED)
	{
		mCtrl__Slot_01.EnableWindow(FALSE);
		mCtrl__Slot_02.EnableWindow(FALSE);
	}
	else
	{
		mCtrl__Slot_01.EnableWindow(TRUE);
		mCtrl__Slot_02.EnableWindow(TRUE);
	}

	if(bACTIVE__LLx_OUT_COOLING)
	{
		mCtrl__Cooling_Sec.EnableWindow(TRUE);
		mData__Cooling_Sec = sPARA__COOLING_SEC;
	}
	else
	{
		mCtrl__Cooling_Sec.EnableWindow(FALSE);
		mData__Cooling_Sec = "__";
	}

	UpdateData(FALSE);
	return TRUE;  
}

void CDlg__Route_LLx::OnBnClickedBtn__MODE()
{
	CDlg__Route_Mode_Select dlg;

	dlg.sPARA__INFO = "LLx Control Mode";

	dlg.sPARA__SEL_DATA = mData_Mode;
	
	if(iLLx_IN__ACTIVE > 0)
	{
		if(bACTIVE__LLx_MODE_ALL)		dlg.sList__ITEM_DATA.Add(STR__ALL);

		dlg.sList__ITEM_DATA.Add(STR__ONLY_INPUT);
	}
	else
	{
		if(bACTIVE__LLx_MODE_ALL)		dlg.sList__ITEM_DATA.Add(STR__ALL);

		dlg.sList__ITEM_DATA.Add(STR__ONLY_OUTPUT);
	}

	if(dlg.DoModal() == IDOK)
	{
		mData_Mode = dlg.sPARA__SEL_DATA;

		UpdateData(FALSE);
	}
}
void CDlg__Route_LLx::OnBnClickedBtn__SLOT01()
{
	CDlg__Route_Mode_Select dlg;

	dlg.sPARA__INFO = "LLx Slot(1) Use";

	dlg.sPARA__SEL_DATA = mData_Slot01;

	dlg.sList__ITEM_DATA.Add("ENABLE");
	dlg.sList__ITEM_DATA.Add("DISABLE");

	if(dlg.DoModal() == IDOK)
	{
		mData_Slot01 = dlg.sPARA__SEL_DATA;

		UpdateData(FALSE);
	}
}
void CDlg__Route_LLx::OnBnClickedBtn__SLOT02()
{
	CDlg__Route_Mode_Select dlg;

	dlg.sPARA__INFO = "LLx Slot(2) Use";

	dlg.sPARA__SEL_DATA = mData_Slot02;

	dlg.sList__ITEM_DATA.Add("ENABLE");
	dlg.sList__ITEM_DATA.Add("DISABLE");

	if(dlg.DoModal() == IDOK)
	{
		mData_Slot02 = dlg.sPARA__SEL_DATA;

		UpdateData(FALSE);
	}
}
void CDlg__Route_LLx::OnBnClickedBtn__COOLING_SEC()
{
	CGX__UTILITY_CTRL x_pad_ctrl;

	CString str_name   = "Cooling (sec)"; 
	CString min_value  = "0";
	CString max_value  = "9999"; 
	CString init_data  = mData__Cooling_Sec;
	CString str_result = init_data;

	if(x_pad_ctrl->Popup__ANALOG_PAD(str_name, min_value,max_value,init_data, str_result) > 0)
	{
		mData__Cooling_Sec = str_result;

		UpdateData(FALSE);
	}
}

void CDlg__Route_LLx::OnBnClickedOk()
{
	UpdateData(TRUE);

	// ...
	{
		sPARA_MODE = mData_Mode;

		//
		sPARA_SLOT = "";

		if(mData_Slot01.CompareNoCase("ENABLE") == 0)		sPARA_SLOT += "1";
		else												sPARA_SLOT += "0";

		if(mData_Slot02.CompareNoCase("ENABLE") == 0)		sPARA_SLOT += "1";
		else												sPARA_SLOT += "0";

		//
		sPARA__COOLING_SEC = mData__Cooling_Sec;
	}

	OnOK();
}

