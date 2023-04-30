#pragma once

#include "afxcmn.h"

#include "resource.h"
#include "Interface_Header.h"

#include "CLS__Item_Define.h"
#include "CCls__Utility.h"
#include "afxwin.h"


// CDlg__PMx_Table dialog

class CDlg__PMx_Table : public CDialog
{
	DECLARE_DYNAMIC(CDlg__PMx_Table)

public:
	CDlg__PMx_Table(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__PMx_Table();

// Dialog Data
	enum { IDD = IDD_DLG__PMx_TABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();

	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnBnClickedBtn__PM1();
	afx_msg void OnBnClickedBtn__PM2();
	afx_msg void OnBnClickedBtn__PM3();
	afx_msg void OnBnClickedBtn__PM4();
	afx_msg void OnBnClickedBtn__PM5();
	afx_msg void OnBnClickedBtn__PM6();

	afx_msg void OnBnClickedBtn__GOTO_MAINT();

	DECLARE_MESSAGE_MAP()

	// ...
	bool bActive_Init;

	CCls__ReSize mReSize;
	
	int iData__Col_Width__NO;
	int iData__Col_Width__NAME;
	int iData__Col_Width__DATA;
	int iData__Col_Width__CHANNEL;

	bool bActive_PMx[10];
	CString sPMx_NAME[10];

	// ...
	CListCtrl  mCtrl__PMx_Table;
	CImageList mImg__PMx_Table;

	void _Make__PMx_Table(CListCtrl *p_table);
	void _Add__PMx_Table(CListCtrl *p_table, const int pm_id);

	// ...
	CString sFile_Info;
	CString sDir_Info;

	CLS__Item_Define mCls_Def;
	CLS__PMx_Ctrl mCtrl_PMx;

	int iPMx_ID;
	CButton mBtn__PM1;
	CButton mBtn__PM2;
	CButton mBtn__PM3;
	CButton mBtn__PM4;
	CButton mBtn__PM5;
	CButton mBtn__PM6;
	CButton mBtn__PMx;

	CButton mBtn__Goto_Maint;

	// ...
	void _Update__File_Info(const CString& dir_inf, const CString& file_inf);
	
	void _Change__PMx(const int pm_id);
	void _Request__GOTO_MAINT_Of_PMx(const int pm_id);
	//


public:
	int iREAL_MODE;
	GObj__Resource_Info *pGObj_Res;

	// ...
	int Set_Parameter(const int module_id);

	int Set_MoveWindow(const POINT& p_st, const POINT& p_et);
	int Redraw_Page();
};
