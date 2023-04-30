#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__PMx_Table.h"

#include "Macro_Function.h"


// ...
#define _CFG_CMMD_SIZE                 5

#define _CMMD_ID__PMx_ID               0
#define _CMMD_ID__DEFINE               1
#define _CMMD_ID__INCLUDE              2
#define _CMMD_ID__CHANNEL              3
#define _CMMD_ID__LINE_EMPTY		   4

#define _CMMD_STR__PMx_ID             "#PM.ID"
#define _CMMD_STR__DEFINE             "#DEFINE"
#define _CMMD_STR__INCLUDE            "#INCLUDE"
#define _CMMD_STR__CHANNEL            "#CHANNEL"
#define _CMMD_STR__LINE_EMPTY	      "#LINE.EMPTY"


void CDlg__PMx_Table::
_Update__File_Info(const CString& dir_inf,
				   const CString& file_inf)
{
	CString file_path;
	file_path.Format("%s\\%s", dir_inf,file_inf);

	// ...
	CString file_data;
	MACRO__Get_File_Data(file_path, file_data);

	CStringArray l_line;
	MACRO__Get_Line_List_From_File_Data(file_data, l_line);

	int i_limit = l_line.GetSize();
	int i;

	// Item Info ...
	{
		CString key_name;

		for(i=0; i<i_limit; i++)
		{
			CString str_line = l_line[i];

			// ...			
			int k_limit = _CFG_CMMD_SIZE;
			int k;

			for(k=0; k<k_limit; k++)
			{
					 if(k == _CMMD_ID__PMx_ID)				key_name = _CMMD_STR__PMx_ID;
				else if(k == _CMMD_ID__DEFINE)				key_name = _CMMD_STR__DEFINE;
				else if(k == _CMMD_ID__INCLUDE)				key_name = _CMMD_STR__INCLUDE;
				else if(k == _CMMD_ID__CHANNEL)				key_name = _CMMD_STR__CHANNEL;
				else if(k == _CMMD_ID__LINE_EMPTY)			key_name = _CMMD_STR__LINE_EMPTY;
				else										continue;

				int s_index = str_line.Find(key_name);
				if(s_index < 0)			continue;

				CString str_data = str_line;
				str_data.Delete(0, s_index+key_name.GetLength());

				CString str_para = MACRO__Get_String_With_No_Space(str_data);

				if(k == _CMMD_ID__PMx_ID)
				{
					int pm_id = atoi(str_para);

					mCtrl_PMx.Set__PMx_ID(pm_id);
					break;
				}
				if(k == _CMMD_ID__DEFINE)
				{
					CStringArray l_para;
					CString para_name;
					CString para_data;

					MACRO__Convert__LIST(' ', str_para, l_para, 2);

					if(l_para.GetSize() > 0)		para_name = l_para[0];
					if(l_para.GetSize() > 1)		para_data = l_para[1];

					para_data = MACRO__Get_String_With_No_Space(para_data);
					para_data = MACRO__Get_String_With_No_Char(para_data, '"');

					mCls_Def.Load__INFO(para_name, para_data);
					break;
				}
				if(k == _CMMD_ID__INCLUDE)
				{
					CString file_inf = MACRO__Get_String_With_No_Char(str_para, '"');
					
					// mCls_Def.Display__ALL_DATA();

					_Update__File_Info(dir_inf, file_inf);			
					break;
				}
				if(k == _CMMD_ID__CHANNEL)
				{
					CStringArray l_para;
					CString para_channel;
					CString para_title;

					MACRO__Convert__LIST(' ', str_para,l_para, 2);

					if(l_para.GetSize() > 0)		para_channel = l_para[0];
					if(l_para.GetSize() > 1)		para_title   = l_para[1];

					para_channel = mCls_Def.Check(para_channel);
					
					para_title = MACRO__Get_String_With_No_Space(para_title);
					para_title = MACRO__Get_String_With_No_Char(para_title, '"');
					if(para_title.GetLength() < 1)		para_title = para_channel;
					para_title = mCls_Def.Check(para_title);

					mCtrl_PMx.Load__INFO(para_channel, para_title);
					break;
				}
				if(k == _CMMD_ID__LINE_EMPTY)
				{
					mCtrl_PMx.Load__EMPTY_LINE();
					break;
				}

				break;
			}
		}

		// ...
	}

	// ...
}
