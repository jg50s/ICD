#pragma once
#include "afxwin.h"


// CDlg__Ref_Wafer_Mng dialog

class CDlg__Ref_Wafer_Mng : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Ref_Wafer_Mng)

public:
	CDlg__Ref_Wafer_Mng(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Ref_Wafer_Mng();

// Dialog Data
	enum { IDD = IDD_DLG__REF_WAFER_MNG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	// ...
	CButton mBtn__DIR_INFO_DATA;
	CButton mBtn__JOBID_DATA;
	CButton mBtn__CSTID_DATA;
	CButton mBtn__LOTID_DATA;
	CButton mBtn__START_TIME_DATA;
	CButton mBtn__PORTID_DATA;
	CButton mBtn__SLOTID_DATA;
	//

public:
	CString sPara__DIR_INFO_DATA;
	CString sPara__JOBID_DATA;
	CString sPara__CSTID_DATA;
	CString sPara__LOTID_DATA;
	CString sPara__START_TIME_DATA;
	CString sPara__PORTID_DATA;
	CString sPara__SLOTID_DATA;
};
