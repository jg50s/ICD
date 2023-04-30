#pragma once

#include "resource.h"
#include "afxcmn.h"

#include "Interface_Code.h"

#include "CObj__PARTICLE_TABLE__DEF.h"
#include "Dlg__PARTICLE_TABLE__TRANSFER_PART.h"
#include "Dlg__PARTICLE_TABLE__PROCESS_PART.h"


// CDlg__PARTICLE_TABLE dialog

class CDlg__PARTICLE_TABLE : public CDialog
{
	DECLARE_DYNAMIC(CDlg__PARTICLE_TABLE)

public:
	CDlg__PARTICLE_TABLE(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__PARTICLE_TABLE();

// Dialog Data
	enum { IDD = IDD_DLG__PARTICLE_TABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

private:
	CTabCtrl m_mainTab;

	CWnd* m_pwndShow;
	int iMainTAB_ID;

	CDlg__PARTICLE_TABLE__TRANSFER_PART* pDlg_subTab__Transfer_Part;
	CDlg__PARTICLE_TABLE__PROCESS_PART*  pDlg_subTab__Process_Part;

	int iPMx__MD_SIZE;
	int iSTx__MD_SIZE;
	
	bool bLLx__PIN_USE;
	int  iLLx__SLOT_SIZE;

	bool bActive__Init_Page;

public:
	int iREAL_MODE;
	GObj__Resource_Info *pGObj_Res;

	// ...
	int Set_Parameter(const int module_id);

	int Set_MoveWindow(const POINT& p_st, const POINT& p_et);
	int Redraw_Page();

	// ...
	void WM_Timer(const HWND& hwnd);
};
