#pragma once

#include "Interface_Header.h"
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"


// CDlg__PMx_Recipe_Select dialog

class CDlg__PMx_Recipe_Select : public CDialog
{
	DECLARE_DYNAMIC(CDlg__PMx_Recipe_Select)

public:
	CDlg__PMx_Recipe_Select(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__PMx_Recipe_Select();

// Dialog Data
	enum { IDD = IDD_DLG__PMx_RECIPE_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtn__PMx_Recipe();

	afx_msg void OnNMClickTree__PMx_Recipe(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkTree__PMx_Recipe(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTree__PMx_Recipe(NMHDR *pNMHDR, LRESULT *pResult);

private:
	bool bActive__PRE_ISE;
	bool bActive__POST_ISE;

	int iPM_SIZE;
	int iLL_SIZE;
	CButton mCtrl__SEL_PMx_ID;

	CTreeCtrl mTree__PMx_Recipe;
	CImageList mImageList__PMx_Recipe;

	// ...
	HTREEITEM Get__Node_Of_MDx(const CString& pm_name);

	int  Get__Recipe_Of_MDx(const CString& pm_name, CString& rcp_pre, CString& rcp_main, CString& rcp_post);
	int  Set__Recipe_Of_MDx(const CString& pm_name, 
						    const CString& rcp_pre, const CString& rcp_main, const CString& rcp_post, 
							const bool active_pm,
							const bool active_ll);

	int  Change__PMx_Recipe();
	int  Update__PMx_Recipe_Channel();

	void Init__Tree_Table_Of_PMx_Recipe();

public:
	int iREAL_MODE;
	GObj__Resource_Info *pGObj_Res;

	// ...
	int Set_Parameter(const int module_id);

	int Set_MoveWindow(const POINT& p_st, const POINT& p_et);
	int Redraw_Page();

	int Call_Timer();
};
