#pragma once
#include "afxcmn.h"


// CDlg__MDx_Info dialog

class CDlg__MDx_Info : public CDialog
{
	DECLARE_DYNAMIC(CDlg__MDx_Info)

public:
	CDlg__MDx_Info(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__MDx_Info();

// Dialog Data
	enum { IDD = IDD_DLG__MDx_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	DECLARE_MESSAGE_MAP()

	// ...
	CListCtrl mCtrl__Info_Table;

	void Make__Info_List(CListCtrl *p_table);
	void Add__Info_List(CListCtrl *p_table, 
						const CStringArray& l_cfg_name);
	//

public:
	CStringArray sList__MDx_Info;
};
