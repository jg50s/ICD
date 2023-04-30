// Dlg__PMx_Selection.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__RECIPE_CTC.h"
#include "Dlg__PMx_Selection.h"


// CDlg__PMx_Selection dialog

IMPLEMENT_DYNAMIC(CDlg__PMx_Selection, CDialog)

CDlg__PMx_Selection::CDlg__PMx_Selection(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__PMx_Selection::IDD, pParent)
{

}

CDlg__PMx_Selection::~CDlg__PMx_Selection()
{
}

void CDlg__PMx_Selection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN__PM1_TITLE, mCtrl__PM1_Tittle);
	DDX_Control(pDX, IDC_BTN__PM2_TITLE, mCtrl__PM2_Tittle);
	DDX_Control(pDX, IDC_BTN__PM3_TITLE, mCtrl__PM3_Tittle);
	DDX_Control(pDX, IDC_BTN__PM4_TITLE, mCtrl__PM4_Tittle);
	DDX_Control(pDX, IDC_BTN__PM5_TITLE, mCtrl__PM5_Tittle);
	DDX_Control(pDX, IDC_BTN__PM6_TITLE, mCtrl__PM6_Tittle);

	DDX_Control(pDX, IDC_BTN__PM1_NAME, mCtrl__PM1_Name);
	DDX_Control(pDX, IDC_BTN__PM2_NAME, mCtrl__PM2_Name);
	DDX_Control(pDX, IDC_BTN__PM3_NAME, mCtrl__PM3_Name);
	DDX_Control(pDX, IDC_BTN__PM4_NAME, mCtrl__PM4_Name);
	DDX_Control(pDX, IDC_BTN__PM5_NAME, mCtrl__PM5_Name);
	DDX_Control(pDX, IDC_BTN__PM6_NAME, mCtrl__PM6_Name);
}


BEGIN_MESSAGE_MAP(CDlg__PMx_Selection, CDialog)
	ON_BN_CLICKED(IDC_BTN__PM1_TITLE, &CDlg__PMx_Selection::OnBnClickedBtn_PM1)
	ON_BN_CLICKED(IDC_BTN__PM2_TITLE, &CDlg__PMx_Selection::OnBnClickedBtn_PM2)
	ON_BN_CLICKED(IDC_BTN__PM3_TITLE, &CDlg__PMx_Selection::OnBnClickedBtn_PM3)
	ON_BN_CLICKED(IDC_BTN__PM4_TITLE, &CDlg__PMx_Selection::OnBnClickedBtn_PM4)
	ON_BN_CLICKED(IDC_BTN__PM5_TITLE, &CDlg__PMx_Selection::OnBnClickedBtn_PM5)
	ON_BN_CLICKED(IDC_BTN__PM6_TITLE, &CDlg__PMx_Selection::OnBnClickedBtn_PM6)
	ON_BN_CLICKED(IDCANCEL, &CDlg__PMx_Selection::OnBnClickedCancel)

END_MESSAGE_MAP()


// CDlg__PMx_Selection message handlers

BOOL CDlg__PMx_Selection::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		int i_limit = iPara__PMx_Size;
		int i;

		for(i=0; i<i_limit; i++)
		{
			CButton *p_btn = NULL;

				 if(i == 0)		p_btn = &mCtrl__PM1_Name;
			else if(i == 1)		p_btn = &mCtrl__PM2_Name;
			else if(i == 2)		p_btn = &mCtrl__PM3_Name;
			else if(i == 3)		p_btn = &mCtrl__PM4_Name;
			else if(i == 4)		p_btn = &mCtrl__PM5_Name;
			else if(i == 5)		p_btn = &mCtrl__PM6_Name;
			else				continue;

			if(p_btn != NULL)
			{
				p_btn->SetWindowText(sPara__PMx_Name[i]);
			}
		}

		for( ; i<6; i++)
		{
			if(i == 0)
			{
				mCtrl__PM1_Tittle.EnableWindow(FALSE);
				mCtrl__PM1_Name.EnableWindow(FALSE);
				continue;
			}
			if(i == 1)
			{
				mCtrl__PM2_Tittle.EnableWindow(FALSE);
				mCtrl__PM2_Name.EnableWindow(FALSE);
				continue;
			}
			if(i == 2)
			{
				mCtrl__PM3_Tittle.EnableWindow(FALSE);
				mCtrl__PM3_Name.EnableWindow(FALSE);
				continue;
			}
			if(i == 3)
			{
				mCtrl__PM4_Tittle.EnableWindow(FALSE);
				mCtrl__PM4_Name.EnableWindow(FALSE);
				continue;
			}
			if(i == 4)
			{
				mCtrl__PM5_Tittle.EnableWindow(FALSE);
				mCtrl__PM5_Name.EnableWindow(FALSE);
				continue;
			}
			if(i == 5)
			{
				mCtrl__PM6_Tittle.EnableWindow(FALSE);
				mCtrl__PM6_Name.EnableWindow(FALSE);
				continue;
			}
		}
	}

	return TRUE;  
}

void CDlg__PMx_Selection::OnBnClickedBtn_PM1()
{
	Set__PMx_SEL(1);
}
void CDlg__PMx_Selection::OnBnClickedBtn_PM2()
{
	Set__PMx_SEL(2);
}
void CDlg__PMx_Selection::OnBnClickedBtn_PM3()
{
	Set__PMx_SEL(3);
}
void CDlg__PMx_Selection::OnBnClickedBtn_PM4()
{
	Set__PMx_SEL(4);
}
void CDlg__PMx_Selection::OnBnClickedBtn_PM5()
{
	Set__PMx_SEL(5);
}
void CDlg__PMx_Selection::OnBnClickedBtn_PM6()
{
	Set__PMx_SEL(6);
}
void CDlg__PMx_Selection::Set__PMx_SEL(const int pm_id)
{
	iPara__PMx_SEL = pm_id;
	sPara__PMx_SEL = sPara__PMx_Name[pm_id - 1];

	OnOK();
}

void CDlg__PMx_Selection::OnBnClickedCancel()
{
	OnCancel();
}
