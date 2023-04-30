#include "stdafx.h"
#include "Dlg__Compare_CFG.h"

#include "CObj__Compare_CFG__KEY_DEF.h"
#include "Macro_Function.h"


// ...
#define _CMMD_STR__PM_ID				"#PM.ID"
#define _CMMD_STR__PAGE					"#PAGE"
#define _CMMD_STR__CFG_ITEM				"#CFG_ITEM"

#define _CMMD_SIZE						3
#define _CMMD_ID__PM_ID					0
#define _CMMD_ID__PAGE					1
#define _CMMD_ID__CFG_ITEM				2


int CDlg__Compare_CFG::
_Upload__Inf_File(const CString& path_inf)
{
	mCls__Page_Info.Clear();

	// ...
	CStringArray l__pm_id;
	
	CString para__page_name;
	CStringArray l__ch_name;
	CStringArray l__ch_title;

	// ...
	CString file_data;

	if(MACRO__Get_File_Data(path_inf, file_data) < 0)
	{
		return -1;
	}

	CStringArray l_line;
	MACRO__Get_Line_List_From_File_Data(file_data, l_line);

	// ...
	int i_limit = l_line.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_line = l_line[i];

		// ...
		CString key_name;

		int k_limit = _CMMD_SIZE;
		int k;

		for(k=0; k<k_limit; k++)
		{
			     if(k == _CMMD_ID__PM_ID)			key_name = _CMMD_STR__PM_ID;
			else if(k == _CMMD_ID__PAGE)			key_name = _CMMD_STR__PAGE;
			else if(k == _CMMD_ID__CFG_ITEM)		key_name = _CMMD_STR__CFG_ITEM;
			else									continue;

			int s_index = str_line.Find(key_name);
			if(s_index < 0)							continue;

			str_line.Delete(0, key_name.GetLength()+s_index);

			// ...
			CStringArray l_para;
			MACRO__Convert__LIST(' ', str_line, l_para);

			if(k == _CMMD_ID__PM_ID)
			{
				/*
				printf(" * [%s] <- ", key_name);

				int t_limit = l_para.GetSize();
				for(int t=0; t<t_limit; t++)
				{
					printf("[%s] ", l_para[t]);
				}
				printf("\n");
				*/

				mCls__Page_Info.Load__PM_ID(l_para);
			}
			else if(k == _CMMD_ID__PAGE)
			{
				CString page_name = MACRO__Trim_Left_String(str_line);
				page_name = MACRO__Trim_Right_String(page_name);	

				// printf(" * [%s] <- [%s] \n", key_name,page_name);

				if(para__page_name.GetLength() > 0)
				{
					mCls__Page_Info.Load__PAGE_INFO(para__page_name, l__ch_name,l__ch_title);
				}

				para__page_name = page_name;
				l__ch_name.RemoveAll();
				l__ch_title.RemoveAll();
			}
			else if(k == _CMMD_ID__CFG_ITEM)
			{
				CString str_channel;
				CString str_title;

				if(l_para.GetSize() > 0)		str_channel = l_para[0];
				if(l_para.GetSize() > 1)		str_title   = l_para[1];

				str_title = MACRO__Trim_Left_String(str_title);
				str_title = MACRO__Trim_Right_String(str_title);

				// printf(" * [%s] <- [%s] [%s] \n", key_name,str_channel,str_title);

				l__ch_name.Add(str_channel);
				l__ch_title.Add(str_title);
			}

			break;
		}
	}

	if(para__page_name.GetLength() > 0)
	{
		mCls__Page_Info.Load__PAGE_INFO(para__page_name, l__ch_name,l__ch_title);
	}

	/*
	// ...
	{
		// ...
		{
			CStringArray l__pm_id;
			mCls__Page_Info.Get__PM_ID(l__pm_id);

			int i_limit = l__pm_id.GetSize();
			printf(" ** pm_id : ", i_limit);

			for(int i=0; i<i_limit; i++)
			{
				printf("[%s] ", l__pm_id[i]);
			}
			printf("\n");
		}

		// ...
		{
			CStringArray l_page;
			mCls__Page_Info.Get__PAGE_LIST(l_page);

			int i_limit = l_page.GetSize();
			for(int i=0; i<i_limit; i++)
			{
				CString page_name = l_page[i];
				mCls__Page_Info.Get__PAGE_INFO(page_name, l__ch_name,l__ch_title);

				// ...
				int t_limit = l__ch_name.GetSize();

				printf(" ** page_name <- [%s] [%1d] \n", page_name,t_limit);

				for(int t=0; t<t_limit; t++)
				{
					printf("  ** %02d) [%s] [%s] \n", t+1,l__ch_name[t],l__ch_title[t]);
				}
			}
			printf("\n");
		}
	}
	*/
	return 1;
}
int CDlg__Compare_CFG::
_Upload__Inf_Cfg_File(const bool active_ref,
					  const int pm_id, 
					  CStringArray& l_cfg_name)
{
	if(active_ref)
	{
		mBtn__Ref_Cfg_Page.SetWindowText("");
		mBtn__Copy_Ref_To_Chk.EnableWindow(FALSE);
	}
	else
	{
		mBtn__Chk_Cfg_Page.SetWindowText("");
		mBtn__Copy_Chk_To_Ref.EnableWindow(FALSE);
	}

	// ...
	l_cfg_name.RemoveAll();

	// ...
	CGX__SYSTEM_CTRL x_sys_ctrl;

	CString dir_root;
	CString path_cfg;
	CString dir_cfg;

	int eqp_id = pm_id + 1;
	x_sys_ctrl->Get__SEQ_DIR_ROOT(eqp_id, dir_root);

	dir_cfg.Format("%s%s",    dir_root, "\\EQP_PAGE\\CONFIG");
	path_cfg.Format("%s\\%s", dir_cfg,  "CONFIG_PAGE.inf");

	// ...
	CString file_data;
	if(MACRO__Get_File_Data(path_cfg, file_data) < 0)
	{
		return -1;
	}

	CStringArray l_line;
	MACRO__Get_Line_List_From_File_Data(file_data, l_line);

	int k_limit = l_line.GetSize();
	for(int k=0; k<k_limit; k++)
	{
		l_cfg_name.Add(l_line[k]);
	}
	return 1;
}
int CDlg__Compare_CFG::
_Upload__Cfg_File(const CString& file_cfg,
				  CStringArray& l_channel,
				  CStringArray& l_data)
{
	// ...
	{
		l_channel.RemoveAll();
		l_data.RemoveAll();
	}

	// ...
	CString file_data;

	if(MACRO__Get_File_Data(file_cfg, file_data) < 0)
	{
		printf(" * CDlg__Compare_CFG::_Upload__Cfg_File() ... \n");
		printf(" ** file_cfg <- [%s] \n", file_cfg);
		return -1;
	}

	CStringArray l_line;
	MACRO__Get_Line_List_From_File_Data(file_data, l_line);

	// ...
	bool active_cfg = false;
	int ch_count = 0;

	int i_limit = l_line.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_line = l_line[i];

		if(!active_cfg)
		{
			if(str_line.Find("#CONFIG#") >= 0)		active_cfg = true;

			continue;
		}

		// ...
		CStringArray l_para;
		MACRO__Convert__LIST(',', str_line, l_para);

		CString para_channel;
		CString para_data;

		if(l_para.GetSize() > 0)		para_channel = l_para[0];
		if(l_para.GetSize() > 1)		para_data    = l_para[1];

		int s_index = para_channel.Find("+", 0);
		if(s_index < 0)			continue;

		l_channel.Add(para_channel);
		l_data.Add(para_data);
	}

	return 1;
}
