#include "stdafx.h"
#include "Dlg__Compare_CFG.h"

#include "CObj__Compare_CFG__KEY_DEF.h"
#include "Macro_Function.h"


// ...
#define _ERR_TYPE__DATA					1
#define _ERR_TYPE__REF_CHANNEL			2
#define _ERR_TYPE__CHK_CHANNEL			3


int CDlg__Compare_CFG::
_Fnc__Error_Check(CUIntArray&   l__err_type,
				  CStringArray& l__err_ref_ch,
				  CStringArray& l__err_ref_data,
				  CStringArray& l__err_chk_ch,
				  CStringArray& l__err_chk_data)
{
	CString page_name;

	mBtn__Ref_Cfg_Page.GetWindowText(page_name);
	mBtn__Chk_Cfg_Page.SetWindowText("???");

	// ...
	CListCtrl* p_table = &mCtrl__Chk_List;
	bool active_check = false;

	int i_limit = p_table->GetItemCount();
	for(int i=0; i<i_limit; i++)
	{
		CString str_name = p_table->GetItemText(i, 1);

		if(str_name.CompareNoCase(page_name) != 0)		
			continue;

		// ...
		p_table->SetSelectionMark(i);
		p_table->EnsureVisible(i, FALSE ); 
		p_table->SetItemState(i, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		p_table->SetFocus();

		mBtn__Chk_Cfg_Page.SetWindowText(page_name);
		mBtn__Copy_Chk_To_Ref.EnableWindow(TRUE);

		active_check = true;
		break;
	}

	if(!active_check)		
	{
		return -1;
	}

	// ...
	CString path_ref;
	CStringArray l__ref_ch;
	CStringArray l__ref_data;

	CString path_chk;
	CStringArray l__chk_ch;
	CStringArray l__chk_data;

	// Ref ...
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;
		CString str_data;

		mBtn__Ref_PM_ID_Data.GetWindowText(str_data);
		int pmc_id = MACRO__Get__PMC_ID(str_data);
		int eqp_id = pmc_id + 1;
		
		CString dir_cfg;
		x_sys_ctrl->Get__SEQ_DIR_CONFIG(eqp_id, dir_cfg);

		path_ref.Format("%s\\%s.cfg", dir_cfg,page_name);
	}
	// Check ...
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;
		CString str_data;

		mBtn__Chk_PM_ID_Data.GetWindowText(str_data);
		int pmc_id = MACRO__Get__PMC_ID(str_data);
		int eqp_id = pmc_id + 1;

		CString dir_cfg;
		x_sys_ctrl->Get__SEQ_DIR_CONFIG(eqp_id, dir_cfg);

		path_chk.Format("%s\\%s.cfg", dir_cfg,page_name);
	}

	// ...
	{
		_Upload__Cfg_File(path_ref, l__ref_ch,l__ref_data);
		_Upload__Cfg_File(path_chk, l__chk_ch,l__chk_data);
	}

	// Error Check ...
	{
		bool active__ref_channel = false;
		bool active__chk_channel = false;

		// Ref -> Check ...
		{
			int i_limit = l__ref_ch.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				CString ref_ch   = l__ref_ch[i];
				CString ref_data = l__ref_data[i];

				// ...
				bool active_channel = false;

				int k_limit = l__chk_ch.GetSize();
				int k;

				for(k=0; k<k_limit; k++)
				{
					if(ref_ch.CompareNoCase(l__chk_ch[k]) != 0)			continue;

					if(ref_data.CompareNoCase(l__chk_data[k]) != 0)
					{
						l__err_type.Add(_ERR_TYPE__DATA);

						l__err_ref_ch.Add(ref_ch);
						l__err_ref_data.Add(ref_data);

						l__err_chk_ch.Add("");
						l__err_chk_data.Add(l__chk_data[k]);
					}

					active_channel = true;
					break;
				}

				if(!active_channel)
				{
					active__ref_channel = true;
					l__err_type.Add(_ERR_TYPE__REF_CHANNEL);

					l__err_ref_ch.Add(ref_ch);
					l__err_ref_data.Add(ref_data);

					l__err_chk_ch.Add("");
					l__err_chk_data.Add("");
				}
			}
		}

		// Check -> Ref ...
		{
			int i_limit = l__chk_ch.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				CString chk_ch   = l__chk_ch[i];
				CString chk_data = l__chk_data[i];

				// ...
				bool active_channel = false;

				int k_limit = l__ref_ch.GetSize();
				int k;

				for(k=0; k<k_limit; k++)
				{
					if(chk_ch.CompareNoCase(l__ref_ch[k]) != 0)			continue;

					active_channel = true;
					break;
				}

				if(!active_channel)
				{
					active__chk_channel = true;
					l__err_type.Add(_ERR_TYPE__CHK_CHANNEL);

					l__err_ref_ch.Add("");
					l__err_ref_data.Add("");

					l__err_chk_ch.Add(chk_ch);
					l__err_chk_data.Add(chk_data);
				}
			}
		}

		// ...
		mBtn__Copy_Ref_To_Chk.EnableWindow(FALSE);
		mBtn__Copy_Chk_To_Ref.EnableWindow(FALSE);

		if((!active__ref_channel) 
		&& (!active__chk_channel))
		{
			if(l__err_type.GetSize() > 0)
			{
				mBtn__Copy_Ref_To_Chk.EnableWindow(TRUE);
				mBtn__Copy_Chk_To_Ref.EnableWindow(TRUE);
			}
		}
	}

	return 1;
}

int  CDlg__Compare_CFG::
_Fnc__Error_Report(const CUIntArray&  l__err_type,
				   const CStringArray& l__err_ref_ch,
				   const CStringArray& l__err_ref_data,
				   const CStringArray& l__err_chk_ch,
				   const CStringArray& l__err_chk_data)
{
	CTreeCtrl *p_tree = &mCtrl__Result_Tree;
	p_tree->DeleteAllItems();

	// ...
	CString ref_page_name;
	CString chk_page_name;

	mBtn__Ref_Cfg_Page.GetWindowText(ref_page_name);
	mBtn__Chk_Cfg_Page.GetWindowText(chk_page_name);

	CString ref_pm_sel;
	CString chk_pm_sel;

	mBtn__Ref_PM_Data_Sel.GetWindowText(ref_pm_sel);
	mBtn__Chk_PM_Data_Sel.GetWindowText(chk_pm_sel);

	// ...
	CString str_info;

	int i_limit = l__err_type.GetSize();

	//
	HTREEITEM h_result_report = p_tree->InsertItem("RESULT_REPORT", 1,1, TVI_ROOT, TVI_LAST);

	str_info.Format("Page : %s", ref_page_name);
	p_tree->InsertItem(str_info, 2,2, h_result_report, TVI_LAST);

	str_info.Format("Ref.PM%s", ref_pm_sel);
	p_tree->InsertItem(str_info, 2,2, h_result_report, TVI_LAST);

	str_info.Format("Chk.PM%s", chk_pm_sel);
	p_tree->InsertItem(str_info, 2,2, h_result_report, TVI_LAST);

	if(ref_page_name.CompareNoCase(chk_page_name) != 0)
	{
		str_info = "State : Error";
		p_tree->InsertItem(str_info, 2,2, h_result_report, TVI_LAST);

		str_info = "Config page does not exist !";
		p_tree->InsertItem(str_info, 2,2, h_result_report, TVI_LAST);

		p_tree->Expand(h_result_report, TVE_EXPAND);
		return -1;
	}

	if(i_limit > 0)			str_info = "State : Error";
	else					str_info = "State : OK";
	p_tree->InsertItem(str_info, 2,2, h_result_report, TVI_LAST);

	str_info.Format("Error : %1d", i_limit);
	p_tree->InsertItem(str_info, 2,2, h_result_report, TVI_LAST);

	//
	HTREEITEM h_error  = p_tree->InsertItem("ERROR_REPORT",  1,1, TVI_ROOT, TVI_LAST);

	for(int i=0; i<i_limit; i++)
	{
		str_info.Format("%1d", i+1);
		HTREEITEM h_info = p_tree->InsertItem(str_info, 2,2, h_error, TVI_LAST);

		// ...
		int data__err_type = l__err_type[i];

		CString str__ref_ch   = l__err_ref_ch[i];
		CString str__ref_data = l__err_ref_data[i];

		CString str__chk_ch   = l__err_chk_ch[i];
		CString str__chk_data = l__err_chk_data[i];

		// ...
		str_info.Format("Error_Type : %1d", data__err_type);
		HTREEITEM h_err_type = p_tree->InsertItem(str_info, 3,3, h_info, TVI_LAST);

		str_info = _Get__Error_Type(data__err_type);
		p_tree->InsertItem(str_info, 3,3, h_err_type, TVI_LAST);

		if(data__err_type == _ERR_TYPE__DATA)
		{
			str_info = "Channel";
			HTREEITEM h_ch_info = p_tree->InsertItem(str_info, 3,3, h_info, TVI_LAST);
			
			str_info = str__ref_ch;
			p_tree->InsertItem(str_info, 3,3, h_ch_info, TVI_LAST);

			//
			str_info = "Data";
			HTREEITEM h_data_info = p_tree->InsertItem(str_info, 3,3, h_info, TVI_LAST);

			str_info = str__ref_data;
			p_tree->InsertItem(str_info, 3,3, h_data_info, TVI_LAST);

			str_info = str__chk_data;
			p_tree->InsertItem(str_info, 3,3, h_data_info, TVI_LAST);

			continue;
		}
		if(data__err_type == _ERR_TYPE__REF_CHANNEL)
		{
			str_info = "Channel";
			HTREEITEM h_ch_info = p_tree->InsertItem(str_info, 3,3, h_info, TVI_LAST);

			str_info = str__ref_ch;
			p_tree->InsertItem(str_info, 3,3, h_ch_info, TVI_LAST);

			//
			str_info = "Data";
			HTREEITEM h_data_info = p_tree->InsertItem(str_info, 3,3, h_info, TVI_LAST);

			str_info = str__ref_data;
			p_tree->InsertItem(str_info, 3,3, h_data_info, TVI_LAST);

			continue;
		}
		if(data__err_type == _ERR_TYPE__CHK_CHANNEL)
		{
			str_info = "Channel";
			HTREEITEM h_ch_info = p_tree->InsertItem(str_info, 3,3, h_info, TVI_LAST);

			str_info = str__chk_ch;
			p_tree->InsertItem(str_info, 3,3, h_ch_info, TVI_LAST);

			//
			str_info = "Data";
			HTREEITEM h_data_info = p_tree->InsertItem(str_info, 3,3, h_info, TVI_LAST);

			str_info = str__chk_data;
			p_tree->InsertItem(str_info, 3,3, h_data_info, TVI_LAST);

			continue;
		}
	}

	p_tree->Expand(h_result_report, TVE_EXPAND);
	p_tree->Expand(h_error, TVE_EXPAND);
}

CString CDlg__Compare_CFG::
_Get__Error_Type(const int err_type)
{
	if(err_type == _ERR_TYPE__DATA)					return "Data Error";
	if(err_type == _ERR_TYPE__REF_CHANNEL)			return "Chk.Channel does not exist";
	if(err_type == _ERR_TYPE__CHK_CHANNEL)			return "Ref.Channel does not exist";

	return "Unknown";
}
