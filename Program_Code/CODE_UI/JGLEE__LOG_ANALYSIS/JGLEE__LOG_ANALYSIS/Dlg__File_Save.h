#pragma once
#include "afxwin.h"


// CDlg__File_Save dialog

class CDlg__File_Save : public CDialog
{
	DECLARE_DYNAMIC(CDlg__File_Save)

public:
	CDlg__File_Save(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__File_Save();

// Dialog Data
	enum { IDD = IDD_DLG__FILE_SAVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

	// ...
	CListBox mList__File_Output;

	CButton mCheck__Left_Align;
	CButton mCheck__Right_Align;

	int  _Upload__Hard_Drive();
	//

public:
	CString sPara__SEL_DIR;

	bool bActive__ALIGN_LEFT;
	bool bActive__ALIGN_RIGHT;
};
