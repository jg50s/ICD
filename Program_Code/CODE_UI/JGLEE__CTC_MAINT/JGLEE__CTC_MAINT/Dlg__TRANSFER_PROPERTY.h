#pragma once

#include "Interface_Code.h"


// CDlg__TRANSFER_PROPERTY dialog

class CDlg__TRANSFER_PROPERTY : public CDialog
{
	DECLARE_DYNAMIC(CDlg__TRANSFER_PROPERTY)

public:
	CDlg__TRANSFER_PROPERTY(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__TRANSFER_PROPERTY();

// Dialog Data
	enum { IDD = IDD_DLG__TRANSFER_PROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtn_STN_SRC();
	afx_msg void OnBnClickedBtn_STN_TRG();
	afx_msg void OnBnClickedBtn_CYCLE();
	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

private:
	CString mSTR_STN_SRC;
	CString mSTR_STN_TRG;
	CString mSTR_CYCLE;
	CString mSTR_ACT_NAME;

public:
	GObj__Resource_Info *pGObj_Res;

	CString sPARA__STN_SRC;
	CString sPARA__STN_TRG;
	CString sPARA__ACT_NAME;
	CString sPARA__CYCLE;
};
