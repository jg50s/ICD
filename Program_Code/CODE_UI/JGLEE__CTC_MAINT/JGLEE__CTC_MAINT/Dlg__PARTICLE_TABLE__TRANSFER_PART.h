#pragma once

#include "afxcmn.h"
#include "Interface_Code.h"

#include "CObj__PARTICLE_TABLE__DEF.h"
#include "CCls__REPORT_CTRL.h"


// CDlg__PARTICLE_TABLE__TRANSFER_PART dialog

class CDlg__PARTICLE_TABLE__TRANSFER_PART : public CDialog
{
	DECLARE_DYNAMIC(CDlg__PARTICLE_TABLE__TRANSFER_PART)

public:
	CDlg__PARTICLE_TABLE__TRANSFER_PART(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__PARTICLE_TABLE__TRANSFER_PART();

// Dialog Data
	enum { IDD = IDD_PARTICLE_TABLE__TRANSFER_PART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

private:
	void _Make__Table_Transfer(CReportCtrl* p_table);
	void _Add__Table_Transfer(CReportCtrl* p_table);
	void _Update__Table_Transfer(CReportCtrl* p_table);

	int  _Get__Act_Name(const int act_id, CString& act_name);

public:
	int iREAL_MODE;
	GObj__Resource_Info *pGObj_Res;

	bool bLLx__PIN_USE;
	int  iLLx__SLOT_SIZE;

	int iSTx__MD_SIZE;

	//
	CReportCtrl mTable_Transfer;

	void Update_Table();

	// ...
	bool bActive__Timer_Run;
	void WM_Timer(const HWND& hwnd);
};
