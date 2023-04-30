// Dlg__Route_ALx.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__RECIPE_CTC.h"
#include "Dlg__Route_ALx.h"

#include "Dlg__Route_Mode_Select.h"


// CDlg__Route_ALx dialog

IMPLEMENT_DYNAMIC(CDlg__Route_ALx, CDialog)

CDlg__Route_ALx::CDlg__Route_ALx(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Route_ALx::IDD, pParent)
{

}

CDlg__Route_ALx::~CDlg__Route_ALx()
{
}

void CDlg__Route_ALx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT__ANGLE,   mData_Angle);

	DDX_Text(pDX, IDC_EDIT__SLOT_02, mData_Slot02);
	DDX_Text(pDX, IDC_EDIT__SLOT_01, mData_Slot01);

	DDX_Control(pDX, IDC_BTN__SLOT_02, mCtrl_Slot02);
	DDX_Control(pDX, IDC_BTN__SLOT_01, mCtrl_Slot01);

	DDX_Control(pDX, IDC_BTN__ANGLE, mCtrl_Angle);
}


BEGIN_MESSAGE_MAP(CDlg__Route_ALx, CDialog)
	ON_BN_CLICKED(IDC_BTN__ANGLE,   &CDlg__Route_ALx::OnBnClickedBtn__PARA_ANGLE)
	ON_BN_CLICKED(IDC_BTN__SLOT_02, &CDlg__Route_ALx::OnBnClickedBtn__PARA_SLOT02)
	ON_BN_CLICKED(IDC_BTN__SLOT_01, &CDlg__Route_ALx::OnBnClickedBtn__PARA_SLOT01)

	ON_BN_CLICKED(IDOK, &CDlg__Route_ALx::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg__Route_ALx message handlers

BOOL CDlg__Route_ALx::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	CString str_title;

	str_title.Format("%s Option ...", sPARA_ALx);
	SetWindowText(str_title);

	// 1. 
	{
		if(bACTIVE__CTRL_CFG)
		{
			mCtrl_Angle.EnableWindow(FALSE);
			mData_Angle = "CONFIG";
		}
		else
		{
			mCtrl_Angle.EnableWindow(TRUE);
			mData_Angle = sPARA_ANGLE;
		}
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

		//
		if(bACTIVE__SLOT_FIXED)
		{
			mCtrl_Slot01.EnableWindow(FALSE);
			mCtrl_Slot02.EnableWindow(FALSE);
		}
		else
		{
			mCtrl_Slot01.EnableWindow(bACTIVE_SLOT01);
			mCtrl_Slot02.EnableWindow(bACTIVE_SLOT02);
		}

		if(!bACTIVE_SLOT01)			mData_Slot01 = "DISABLE";
		if(!bACTIVE_SLOT02)			mData_Slot02 = "DISABLE";
	}

	UpdateData(FALSE);
	return TRUE;  
}

void CDlg__Route_ALx::OnBnClickedBtn__PARA_ANGLE()
{
	CDlg__Route_Mode_Select dlg;

	dlg.sPARA__INFO = "Align Angle Mode";

	dlg.sPARA__SEL_DATA = mData_Angle;

	dlg.sList__ITEM_DATA.Add("CONFIG");
	dlg.sList__ITEM_DATA.Add("DISABLE");
	dlg.sList__ITEM_DATA.Add("LLx");
	dlg.sList__ITEM_DATA.Add("PMx");

	if(dlg.DoModal() == IDOK)
	{
		mData_Angle = dlg.sPARA__SEL_DATA;
	}
	UpdateData(FALSE);
}
void CDlg__Route_ALx::OnBnClickedBtn__PARA_SLOT02()
{
	CDlg__Route_Mode_Select dlg;

	dlg.sPARA__INFO = "Align Slot(2) Use";

	dlg.sPARA__SEL_DATA = mData_Slot02;

	dlg.sList__ITEM_DATA.Add("ENABLE");
	dlg.sList__ITEM_DATA.Add("DISABLE");

	if(dlg.DoModal() == IDOK)
	{
		mData_Slot02 = dlg.sPARA__SEL_DATA;
	}
	UpdateData(FALSE);
}
void CDlg__Route_ALx::OnBnClickedBtn__PARA_SLOT01()
{
	CDlg__Route_Mode_Select dlg;

	dlg.sPARA__INFO = "Align Slot(1) Use";

	dlg.sPARA__SEL_DATA = mData_Slot01;

	dlg.sList__ITEM_DATA.Add("ENABLE");
	dlg.sList__ITEM_DATA.Add("DISABLE");

	if(dlg.DoModal() == IDOK)
	{
		mData_Slot01 = dlg.sPARA__SEL_DATA;
	}
	UpdateData(FALSE);
}

void CDlg__Route_ALx::OnBnClickedOk()
{
	UpdateData(TRUE);

	// ...
	{
		sPARA_ANGLE = mData_Angle;

		//
		sPARA_SLOT = "";
		
		if(mData_Slot01.CompareNoCase("ENABLE") == 0)		sPARA_SLOT += "1";
		else												sPARA_SLOT += "0";
		
		if(mData_Slot02.CompareNoCase("ENABLE") == 0)		sPARA_SLOT += "1";
		else												sPARA_SLOT += "0";
	}

	OnOK();
}
