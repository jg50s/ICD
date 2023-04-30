#pragma once

#include "Interface_Header.h"
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"


class Cls__PAGE_CHANNE
{
public:
	CStringArray sList__CHANNEL;
	CStringArray sList__TITLE;
};
class Cls__PAGE_INFO
{
private:
	CStringArray sList__PM_ID;

	CStringArray sList__PAGE;
	CPtrArray pList__ADDR;

public:
	Cls__PAGE_INFO()
	{
		
	}
	~Cls__PAGE_INFO()
	{
		Clear();
	}

	void Clear()
	{
		int i_limit = pList__ADDR.GetSize();
		for(int i=0; i<i_limit; i++)
		{
			Cls__PAGE_CHANNE* p_channel = (Cls__PAGE_CHANNE*) pList__ADDR[i];
			delete p_channel;
		}

		pList__ADDR.RemoveAll();
		sList__PAGE.RemoveAll();

		sList__PM_ID.RemoveAll();
	}

	void Load__PM_ID(const CStringArray& l__pm_id)
	{
		sList__PM_ID.Copy(l__pm_id);
	}
	void Load__PAGE_INFO(const CString& page_name, const CStringArray& l_channel,const CStringArray& l_title)
	{
		int i_limit = sList__PAGE.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(page_name.CompareNoCase(sList__PAGE[i]) != 0)		
				continue;
			
			return;
		}

		// ...
		{
			sList__PAGE.Add(page_name);

			//
			Cls__PAGE_CHANNE* p_addr = new Cls__PAGE_CHANNE;
			pList__ADDR.Add(p_addr);

			p_addr->sList__CHANNEL.Copy(l_channel);
			p_addr->sList__TITLE.Copy(l_title);
		}
	}

	void Get__PM_ID(CStringArray& l__pm_id)
	{
		l__pm_id.Copy(sList__PM_ID);
	}
	void Get__PAGE_LIST(CStringArray& l_page)
	{
		l_page.Copy(sList__PAGE);
	}
	int Get__PAGE_INFO(const CString& page_name, CStringArray& l_channel,CStringArray& l_title)
	{
		l_channel.RemoveAll();
		l_title.RemoveAll();

		// ...
		int i_limit = sList__PAGE.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(page_name.CompareNoCase(sList__PAGE[i]) != 0)		
				continue;

			// ...
			{
				Cls__PAGE_CHANNE* p_addr = (Cls__PAGE_CHANNE*) pList__ADDR[i];

				l_channel.Copy(p_addr->sList__CHANNEL);
				l_title.Copy(p_addr->sList__TITLE);
			}
			return 1;
		}

		return -1;
	}
};


// CDlg__Compare_CFG dialog

class CDlg__Compare_CFG : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Compare_CFG)

public:
	CDlg__Compare_CFG(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Compare_CFG();

// Dialog Data
	enum { IDD = IDD_DLG__COMPARE_CFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	afx_msg void OnBnClickedBtn__Ref_PM_ID();
	afx_msg void OnBnClickedBtn__Ref_CFG_TYPE();
	afx_msg void OnBnClickedBtn__Ref_Update();
	afx_msg void OnNMClickList__Ref_Table(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedBtn__Chk_PM_ID();
	afx_msg void OnBnClickedBtn__Chk_Update();

	afx_msg void OnBnClickedBtn__Path_View();
	afx_msg void OnBnClickedBtn__Config_Compare();
	afx_msg void OnBnClickedBtn__Result_Save();

	afx_msg void OnBnClickedBtn__Copy_Ref_To_Chk();
	afx_msg void OnBnClickedBtn__Copy_Chk_To_Ref();

	DECLARE_MESSAGE_MAP()

	// ...
	int _Upload__Inf_File(const CString& path_inf);

	int _Upload__Inf_Cfg_File(const bool active_ref,
							  const int pm_id, 
							  CStringArray& l_cfg_name);
	int _Upload__Cfg_File(const CString& file_cfg,
						  CStringArray& l_channel,
						  CStringArray& l_data);

	// ...
	void _Get__PMx_Title_List(CStringArray& l_pm_title);

	// ...
	void Make__File_List(CListCtrl *p_table);
	void Add__File_List(CListCtrl *p_table, 
						const CStringArray& l_cfg_name);

	void _Click_Btn__Cfg_Update(const bool active_ref,
								const int pm_id, 
								CListCtrl* p_table);

	// ...
	int  _Fnc__Error_Check(CUIntArray&   l__err_type,
						   CStringArray& l__err_ref_ch,
						   CStringArray& l__err_ref_data,
						   CStringArray& l__err_chk_ch,
						   CStringArray& l__err_chk_data);

	int  _Fnc__Error_Report(const CUIntArray&  l__err_type,
							const CStringArray& l__err_ref_ch,
							const CStringArray& l__err_ref_data,
							const CStringArray& l__err_chk_ch,
							const CStringArray& l__err_chk_data);

	CString _Get__Error_Type(const int err_tyoe);

	// ...
	CString _Get__Child_Node_List(CTreeCtrl *p_tree, 
		                         HTREEITEM h_parent, 
								 const CString& str_upper_tap);

	// ...
	int _Copy__Source_File_To_Other_PMx(const CString& src_pm_id,
									    const CString& src_path,
									    const CString& trg_pm_id,
									    const CString& trg_path);

	// ...
	Cls__PAGE_INFO mCls__Page_Info;

	//
	CButton mBtn__Ref_PM_ID_Data;
	CButton mBtn__Ref_Cfg_Type_Data;
	CButton mBtn__Ref_Cfg_Page;

	CListCtrl mCtrl__Ref_List;
	
	CButton mBtn__Ref_PM_Data_Sel;
	CButton mBtn__Ref_Cfg_Type_Sel;

	CButton mBtn__Copy_Ref_To_Chk;

	//
	CButton mBtn__Chk_PM_ID_Data;
	CButton mBtn__Chk_Cfg_Page;

	CListCtrl mCtrl__Chk_List;

	CButton mBtn__Chk_PM_Data_Sel;

	CButton mBtn__Copy_Chk_To_Ref;

	//
	CTreeCtrl mCtrl__Result_Tree;
	CImageList mImg__Result_Tree;

	//
	CButton mBtn__Config_Compare;

	CButton mBtn__Result_Save;
	CString mStr_Save_File_Path;

	//
	int iPM_SIZE;
	//

public:
	int iREAL_MODE;
	GObj__Resource_Info *pGObj_Res;

	// ...
	int Set_Parameter(const int module_id);

	int Set_MoveWindow(const POINT& p_st, const POINT& p_et);
	int Redraw_Page();
};
