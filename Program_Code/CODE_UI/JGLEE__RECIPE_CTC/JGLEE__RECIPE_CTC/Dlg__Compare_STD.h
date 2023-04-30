#pragma once

#include "Interface_Header.h"
#include "resource.h"
#include "afxcmn.h"

#include "Dlg__PMx_Selection.h"
#include "Dlg__Rcp_Type_Selection.h"
#include "afxwin.h"


// CDlg__Compare_STD dialog

class CStep_Info
{
public:
	CStep_Info()
	{
		sList__Channe_Type.RemoveAll();
		sList__Channe_Name.RemoveAll();
		sList__Channe_Data.RemoveAll();
		sList__Step_Name.RemoveAll();
	}
	~CStep_Info()
	{

	}

	int Add__Step_Info(const CString& ch_type,const CString& ch_name,const CString& ch_data)
	{
		sList__Channe_Type.Add(ch_type);
		sList__Channe_Name.Add(ch_name);
		sList__Channe_Data.Add(ch_data);
		sList__Step_Name.Add("");
		return 1;
	}

	// ...
	int iStep_ID;
	CStringArray sList__Channe_Type;
	CStringArray sList__Channe_Name;
	CStringArray sList__Channe_Data;
	CStringArray sList__Step_Name;
};
class CRcp_Info
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CPtrArray pList__Step_Info;
	CStep_Info *pLast_Step;

public:
	CRcp_Info()
	{
		InitializeCriticalSection(&mCS_LOCK);

		pLast_Step = NULL;
	}
	~CRcp_Info()
	{
		Clear__All();

		DeleteCriticalSection(&mCS_LOCK);
	}

	// ...
	void Clear__All()
	{
		EnterCriticalSection(&mCS_LOCK);

		CStep_Info *p_step;

		int i_limit = pList__Step_Info.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			p_step = (CStep_Info *) pList__Step_Info[i];
			delete p_step;
		}
		pList__Step_Info.RemoveAll();

		LeaveCriticalSection(&mCS_LOCK);
	}

	int Add__Step_ID(const int step_id)
	{
		EnterCriticalSection(&mCS_LOCK);

		CStep_Info *p_step = new CStep_Info;
		pList__Step_Info.Add(p_step);
		pLast_Step = p_step;

		p_step->iStep_ID = step_id;

		LeaveCriticalSection(&mCS_LOCK);
		return 1;
	}
	int Add__Step_Info(const CString& ch_type,const CString& ch_name,const CString& ch_data)
	{
		EnterCriticalSection(&mCS_LOCK);

		int flag = pLast_Step->Add__Step_Info(ch_type,ch_name,ch_data);

		LeaveCriticalSection(&mCS_LOCK);
		return flag;
	}

	// ...
	int Get__Step_Size()
	{
		EnterCriticalSection(&mCS_LOCK);

		int step_size = pList__Step_Info.GetSize();

		LeaveCriticalSection(&mCS_LOCK);
		return step_size;
	}

	CStep_Info* Get__Step_Info(const int step_index)
	{
		EnterCriticalSection(&mCS_LOCK);

		CStep_Info *p_step = NULL;

		if((step_index >= 0) && (step_index < pList__Step_Info.GetSize()))
		{
			p_step = (CStep_Info*) pList__Step_Info[step_index];
		}

		LeaveCriticalSection(&mCS_LOCK);
		return p_step;
	}
};

class CPara_Info
{
private:
	CRITICAL_SECTION mCS_LOCK;

public:
	CStringArray sList__Para_Channel;
	CStringArray sList__Para_Title;
	CStringArray sList__Para_Category;

	// ...
	CPara_Info()
	{
		InitializeCriticalSection(&mCS_LOCK);
	}
	~CPara_Info()
	{
		DeleteCriticalSection(&mCS_LOCK);
	}

	void Clear__All()
	{
		EnterCriticalSection(&mCS_LOCK);

		sList__Para_Channel.RemoveAll();
		sList__Para_Title.RemoveAll();
		sList__Para_Category.RemoveAll();

		LeaveCriticalSection(&mCS_LOCK);
	}

	void Add__New_Parameter()
	{
		EnterCriticalSection(&mCS_LOCK);

		sList__Para_Channel.Add("");
		sList__Para_Title.Add("");
		sList__Para_Category.Add("");

		LeaveCriticalSection(&mCS_LOCK);
	}
	void Load__Para_Channel(const CString& ch_name)
	{
		EnterCriticalSection(&mCS_LOCK);

		int db_index = sList__Para_Channel.GetSize() - 1;

		if(db_index >= 0)		
			sList__Para_Channel[db_index] = ch_name;

		LeaveCriticalSection(&mCS_LOCK);
	}
	void Load__Para_Titlel(const CString& title)
	{
		EnterCriticalSection(&mCS_LOCK);

		int db_index = sList__Para_Title.GetSize() - 1;

		if(db_index >= 0)		
			sList__Para_Title[db_index] = title;

		LeaveCriticalSection(&mCS_LOCK);
	}
	void Load__Para_Category(const CString& category)
	{
		EnterCriticalSection(&mCS_LOCK);

		int db_index = sList__Para_Category.GetSize() - 1;

		if(db_index >= 0)		
			sList__Para_Category[db_index] = category;

		LeaveCriticalSection(&mCS_LOCK);
	}

	CString Get__Para_Title(const CString& ch_name, CString& str_category)
	{
		EnterCriticalSection(&mCS_LOCK);

		CString str_title = "";
		str_category = "";

		int i_limit = sList__Para_Channel.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(ch_name.CompareNoCase(sList__Para_Channel[i]) != 0)
			{
				continue;
			}

			str_title    = sList__Para_Title[i];
			str_category = sList__Para_Category[i];
			break;
		}

		LeaveCriticalSection(&mCS_LOCK);
		return str_title;
	}
};

class CDlg__Compare_STD : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Compare_STD)

public:
	CDlg__Compare_STD(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Compare_STD();

// Dialog Data
	enum { IDD = IDD_DLG__COMPARE_STD };

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtn__Ref_PM_Ctrl();
	afx_msg void OnBnClickedBtn__Check_PM_Ctrl();

	afx_msg void OnBnClickedBtn__Ref_Rcp_Type_Ctrl();
	afx_msg void OnBnClickedBtn__Check_Rcp_Type_Ctrl();

	afx_msg void OnBnClickedBtn__Ref_PM_Update();
	afx_msg void OnBnClickedBtn__Check_PM_Update();

	afx_msg void OnNMClickList__Ref_File_Table(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList__Check_File_Table(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedBtn__Compare_Check();
	afx_msg void OnBnClickedBtn__Result_Save();
	afx_msg void OnBnClickedBtn__Parameter_View();

	afx_msg void OnBnClickedBtn__Copy_To_Ref_RCP();
	afx_msg void OnBnClickedBtn__Copy_To_Chk_RCP();
	afx_msg void OnBnClickedBtn__Copy_To_Other_PMx();

	afx_msg void OnLvnColumnclickList__Ref_File_Table(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickList__Check_File_Table(NMHDR *pNMHDR, LRESULT *pResult);

	// ...
	int  Sort__Route_File(CListCtrl* p_table,
						  const int col, 
						  bool& sort_order,
						  CStringArray& l_file,
						  CStringArray& l_date);

	bool bSortDirect_RefFile;
	bool bSortDirect_CheckFile;
	//

private:
	CTreeCtrl mTree__Result_Report;
	CImageList mImageList__Result_Report;

	// ...
	CListCtrl mCtrl__Ref_File_List;
	CImageList mImg__Ref_File_List;

	CStringArray sList__Ref_File_List__File;
	CStringArray sList__Ref_File_List__Date;

	// ...
	CListCtrl mCtrl__Check_File_List;
	CImageList mImg__Check_File_List;

	CStringArray sList__Check_File_List__File;
	CStringArray sList__Check_File_List__Date;

	// ...
	CButton mCtrl__Ref_PM_Data;
	CButton mCtrl__Check_PM_Data;

	CButton mCtrl__Ref_Rcp_Type_Data;
	CButton mCtrl__Check_Rcp_Type_Data;

	CButton mCtrl__Ref_PM_ID_Update;
	CButton mCtrl__Ref_Rcp_Type_Update;

	CButton mCtrl__Check_PM_ID_Update;
	CButton mCtrl__Check_Rcp_Type_Update;

	CButton mCtrl__Ref_Recipe_Name;
	CButton mCtrl__Check_Recipe_Name;

	CButton mCtrl__Result_Ref_PM;
	CButton mCtrl__Result_Ref_Rcp;

	CButton mCtrl__Result_Check_PM;
	CButton mCtrl__Result_Check_Rcp;

	CString mStr_Save_File_Path;
	CButton mCtrl__Result_Save;

	int iPM_SIZE;

	CRcp_Info  mRcp_Info__Ref;
	CRcp_Info  mRcp_Info__Check;
	CPara_Info mPara_Info;

	// ...
	BOOL Fnc_OnInitDialog();

	//
	void Make__File_List(CListCtrl *p_table);
	void Add__File_List(CListCtrl *p_table, const CStringArray& l_file_name,const CStringArray& l_file_date);

	void Get__Para_Of_PMx_Selection(CDlg__PMx_Selection* p_dlg);
	void Get__Para_Of_Rcp_Type_Selection(CDlg__Rcp_Type_Selection* p_dlg);

	int  Get__File_Info(const CString& file_path, CStringArray& l_line);
	int  Upload__Rcp_Info(const CString& file_path, CRcp_Info* p_rcp_info);
	int  Upload__Para_Info(const CString& file_path, CPara_Info* p_para_info);

	CString Get__Child_Node_List(CTreeCtrl *p_tree, HTREEITEM h_parent, const CString& str_tap);

	int  Copy__Source_File_To_Other_PMx();
	int  Copy__Source_File_To_Target_File(const int ref_to_chk_copy);
	int  Search__File_Name_Of_File_Table(CListCtrl* p_table, const CString& file_name);

public:
	int iREAL_MODE;
	GObj__Resource_Info *pGObj_Res;

	// ...
	int Set_Parameter(const int module_id);

	int Set_MoveWindow(const POINT& p_st, const POINT& p_et);
	int Redraw_Page();
};
