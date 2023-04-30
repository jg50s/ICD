#pragma once

#include "Interface_Header.h"
#include "resource.h"
#include "afxcmn.h"


// CDlg__Report_Table dialog

class CDlg__Report_Table : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Report_Table)

public:
	CDlg__Report_Table(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Report_Table();

// Dialog Data
	enum { IDD = IDD_DLG__REPORT_TABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

	// ...
	CListCtrl mList__Report_Table;
	CImageList mImg__Report_Table;

	bool bActive__Init_Table;

	// ...
	int iData__Table_Row_Max;
	int iData__Col_Width_Index;
	int iData__Col_Width_Msg;

	void _Make__Report_Table(CListCtrl *p_table);
	void _Add__Report_Table(CListCtrl *p_table,	CStringArray& l_data);
	//

public:
	int iREAL_MODE;
	GObj__Resource_Info *pGObj_Res;

	// ...
	int Set_Parameter(const int module_id);

	int Set_MoveWindow(const POINT& p_st, const POINT& p_et);
	int Redraw_Page();
};
