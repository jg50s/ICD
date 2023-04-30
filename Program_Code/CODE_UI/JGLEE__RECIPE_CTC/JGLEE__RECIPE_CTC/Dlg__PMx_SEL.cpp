// CDlg__PMx_SEL.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__RECIPE_CTC.h"
#include "Dlg__PMx_SEL.h"

#include "Macro_Function.h"


// CDlg__PMx_SEL dialog

IMPLEMENT_DYNAMIC(CDlg__PMx_SEL, CDialog)

CDlg__PMx_SEL::CDlg__PMx_SEL(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__PMx_SEL::IDD, pParent)
{
	bActive__PMx_SEL  = false;
	bActive__CFG_TYPE = false;
}

CDlg__PMx_SEL::~CDlg__PMx_SEL()
{
}

void CDlg__PMx_SEL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN__PMx_TITLE_1, mBtn__MDx_01);
	DDX_Control(pDX, IDC_BTN__PMx_TITLE_2, mBtn__MDx_02);
	DDX_Control(pDX, IDC_BTN__PMx_TITLE_3, mBtn__MDx_03);
	DDX_Control(pDX, IDC_BTN__PMx_TITLE_4, mBtn__MDx_04);
	DDX_Control(pDX, IDC_BTN__PMx_TITLE_5, mBtn__MDx_05);
	DDX_Control(pDX, IDC_BTN__PMx_TITLE_6, mBtn__MDx_06);
}


BEGIN_MESSAGE_MAP(CDlg__PMx_SEL, CDialog)
	ON_BN_CLICKED(IDC_BTN__PMx_TITLE_1, &CDlg__PMx_SEL::OnBnClickedBtn__MDx_01)
	ON_BN_CLICKED(IDC_BTN__PMx_TITLE_2, &CDlg__PMx_SEL::OnBnClickedBtn__MDx_02)
	ON_BN_CLICKED(IDC_BTN__PMx_TITLE_3, &CDlg__PMx_SEL::OnBnClickedBtn__MDx_03)
	ON_BN_CLICKED(IDC_BTN__PMx_TITLE_4, &CDlg__PMx_SEL::OnBnClickedBtn__MDx_04)
	ON_BN_CLICKED(IDC_BTN__PMx_TITLE_5, &CDlg__PMx_SEL::OnBnClickedBtn__MDx_05)
	ON_BN_CLICKED(IDC_BTN__PMx_TITLE_6, &CDlg__PMx_SEL::OnBnClickedBtn__MDx_06)
	ON_BN_CLICKED(IDCANCEL, &CDlg__PMx_SEL::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlg__PMx_SEL message handlers

BOOL CDlg__PMx_SEL::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		SetWindowText(sPara__Win_Title);
	}

	// ...
	{
		CButton *p_btn;
		CStringArray* pl_md;
		CStringArray* pl_title;

		if(bActive__CFG_TYPE)
		{
			pl_md = &sList__CFG_TYPE;
		}
		else
		{
			pl_md = &sList__PMx_ID;
			pl_title = &sList__PMx_TITLE;
		}

		//
		int i_limit = pl_md->GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CString md_name;

			if(bActive__CFG_TYPE)
			{
				md_name = pl_md->GetAt(i);
			}
			else
			{
				CString md_id = pl_md->GetAt(i);

				md_name.Format("PM%s", md_id);

				int md_index = atoi(md_id) - 1;
				if((md_index >= 0) && (md_index < pl_title->GetSize()))
				{	
					CString md_title = pl_title->GetAt(md_index);
					md_name.Format("PM%s  (%s)", md_id,md_title);
				}
			}

				 if(i == 0)			p_btn = &mBtn__MDx_01;
			else if(i == 1)			p_btn = &mBtn__MDx_02;
			else if(i == 2)			p_btn = &mBtn__MDx_03;
			else if(i == 3)			p_btn = &mBtn__MDx_04;
			else if(i == 4)			p_btn = &mBtn__MDx_05;
			else if(i == 5)			p_btn = &mBtn__MDx_06;
			else					continue;

			p_btn->SetWindowText(md_name);
			p_btn->EnableWindow(TRUE);
		}

		for( ; i<6; i++)
		{
				 if(i == 0)			p_btn = &mBtn__MDx_01;
			else if(i == 1)			p_btn = &mBtn__MDx_02;
			else if(i == 2)			p_btn = &mBtn__MDx_03;
			else if(i == 3)			p_btn = &mBtn__MDx_04;
			else if(i == 4)			p_btn = &mBtn__MDx_05;
			else if(i == 5)			p_btn = &mBtn__MDx_06;
			else					continue;

			p_btn->EnableWindow(FALSE);
		}
	}

	return TRUE;  
}

void CDlg__PMx_SEL::OnBnClickedBtn__MDx_01()
{
	_Click__MDx(&mBtn__MDx_01);
}
void CDlg__PMx_SEL::OnBnClickedBtn__MDx_02()
{
	_Click__MDx(&mBtn__MDx_02);
}
void CDlg__PMx_SEL::OnBnClickedBtn__MDx_03()
{
	_Click__MDx(&mBtn__MDx_03);
}
void CDlg__PMx_SEL::OnBnClickedBtn__MDx_04()
{
	_Click__MDx(&mBtn__MDx_04);
}
void CDlg__PMx_SEL::OnBnClickedBtn__MDx_05()
{
	_Click__MDx(&mBtn__MDx_05);
}
void CDlg__PMx_SEL::OnBnClickedBtn__MDx_06()
{
	_Click__MDx(&mBtn__MDx_06);
}
void CDlg__PMx_SEL::_Click__MDx(CButton* p_btn)
{
	CString str_data;
	p_btn->GetWindowText(str_data);

	if(bActive__CFG_TYPE)
	{
		sPara__CFG_TYPE_SEL = str_data;
	}
	else
	{
		iPara__PMx_SEL = MACRO__Get__PMC_ID(str_data);

		int pm_index = iPara__PMx_SEL - 1;
		if((pm_index >= 0) && (pm_index < sList__PMx_TITLE.GetSize()))
			sPara__PMx_TITLE = sList__PMx_TITLE[pm_index];
		else
			sPara__PMx_TITLE = "";
	}

	OnOK();
}

void CDlg__PMx_SEL::OnBnClickedCancel()
{
	OnCancel();
}
