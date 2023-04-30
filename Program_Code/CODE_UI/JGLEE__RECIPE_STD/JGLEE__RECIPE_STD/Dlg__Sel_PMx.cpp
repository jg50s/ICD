// Dlg__Sel_PMx.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__RECIPE_STD.h"
#include "Dlg__Sel_PMx.h"


// CDlg__Sel_PMx dialog

IMPLEMENT_DYNAMIC(CDlg__Sel_PMx, CDialog)

CDlg__Sel_PMx::CDlg__Sel_PMx(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Sel_PMx::IDD, pParent)
{

}

CDlg__Sel_PMx::~CDlg__Sel_PMx()
{
}

void CDlg__Sel_PMx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN__SEL_PM1, mCtrl__PM1);
	DDX_Control(pDX, IDC_BTN__SEL_PM2, mCtrl__PM2);
	DDX_Control(pDX, IDC_BTN__SEL_PM3, mCtrl__PM3);
	DDX_Control(pDX, IDC_BTN__SEL_PM4, mCtrl__PM4);
	DDX_Control(pDX, IDC_BTN__SEL_PM5, mCtrl__PM5);
	DDX_Control(pDX, IDC_BTN__SEL_PM6, mCtrl__PM6);
}


BEGIN_MESSAGE_MAP(CDlg__Sel_PMx, CDialog)
	ON_BN_CLICKED(IDC_BTN__SEL_PM1, &CDlg__Sel_PMx::OnBnClickedBtn__SEL_PM1)
	ON_BN_CLICKED(IDC_BTN__SEL_PM2, &CDlg__Sel_PMx::OnBnClickedBtn__SEL_PM2)
	ON_BN_CLICKED(IDC_BTN__SEL_PM3, &CDlg__Sel_PMx::OnBnClickedBtn__SEL_PM3)
	ON_BN_CLICKED(IDC_BTN__SEL_PM4, &CDlg__Sel_PMx::OnBnClickedBtn__SEL_PM4)
	ON_BN_CLICKED(IDC_BTN__SEL_PM5, &CDlg__Sel_PMx::OnBnClickedBtn__SEL_PM5)
	ON_BN_CLICKED(IDC_BTN__SEL_PM6, &CDlg__Sel_PMx::OnBnClickedBtn__SEL_PM6)
END_MESSAGE_MAP()


// CDlg__Sel_PMx message handlers

BOOL CDlg__Sel_PMx::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		CButton* p_btn;

		int i_limit = _CFG_PMx__SIZE;
		int i;

		for(i=0; i<i_limit; i++)
		{
			int pm_id = i + 1;

			     if(i == 0)		p_btn = &mCtrl__PM1;
			else if(i == 1)		p_btn = &mCtrl__PM2;
			else if(i == 2)		p_btn = &mCtrl__PM3;
			else if(i == 3)		p_btn = &mCtrl__PM4;
			else if(i == 4)		p_btn = &mCtrl__PM5;
			else if(i == 5)		p_btn = &mCtrl__PM6;
			else				continue;

			if(pm_id == iPara__SEL_PMx)
			{
				p_btn->EnableWindow(FALSE);
			}
			else
			{
				if(bActive__PMx[i])			p_btn->EnableWindow(TRUE);
				else						p_btn->EnableWindow(FALSE);
			}
		}
	}
	return TRUE;
}

void CDlg__Sel_PMx::OnBnClickedBtn__SEL_PM1()
{
	_Fnc__SEL_PMx(1);
}
void CDlg__Sel_PMx::OnBnClickedBtn__SEL_PM2()
{
	_Fnc__SEL_PMx(2);
}
void CDlg__Sel_PMx::OnBnClickedBtn__SEL_PM3()
{
	_Fnc__SEL_PMx(3);
}
void CDlg__Sel_PMx::OnBnClickedBtn__SEL_PM4()
{
	_Fnc__SEL_PMx(4);
}
void CDlg__Sel_PMx::OnBnClickedBtn__SEL_PM5()
{
	_Fnc__SEL_PMx(5);
}
void CDlg__Sel_PMx::OnBnClickedBtn__SEL_PM6()
{
	_Fnc__SEL_PMx(6);
}

void CDlg__Sel_PMx::_Fnc__SEL_PMx(const int pm_id)
{
	iPara__SEL_PMx = pm_id;

	CDialog::OnOK();
}
