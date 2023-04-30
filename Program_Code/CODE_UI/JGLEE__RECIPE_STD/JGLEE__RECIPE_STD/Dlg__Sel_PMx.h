#pragma once

#include "CInfo__Rcp_Common.h"
#include "afxwin.h"


// CDlg__Sel_PMx dialog

class CDlg__Sel_PMx : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Sel_PMx)

public:
	CDlg__Sel_PMx(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Sel_PMx();

// Dialog Data
	enum { IDD = IDD_DLG__SELECT_PMx };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtn__SEL_PM1();
	afx_msg void OnBnClickedBtn__SEL_PM2();
	afx_msg void OnBnClickedBtn__SEL_PM3();
	afx_msg void OnBnClickedBtn__SEL_PM4();
	afx_msg void OnBnClickedBtn__SEL_PM5();
	afx_msg void OnBnClickedBtn__SEL_PM6();

	DECLARE_MESSAGE_MAP()

private:
	// ...
	CButton mCtrl__PM1;
	CButton mCtrl__PM2;
	CButton mCtrl__PM3;
	CButton mCtrl__PM4;
	CButton mCtrl__PM5;
	CButton mCtrl__PM6;

	void _Fnc__SEL_PMx(const int pm_id);
	//

public:
	int iPara__SEL_PMx;

	bool bActive__PMx[_CFG_PMx__SIZE];
};
