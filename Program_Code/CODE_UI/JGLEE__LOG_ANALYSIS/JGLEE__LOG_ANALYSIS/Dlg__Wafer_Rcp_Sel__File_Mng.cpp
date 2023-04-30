#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Wafer_Rcp_Sel.h"
#include "Macro_Function.h"


// ...
#define _CMMD__RCP_PARA__ITEM_XXX					1
#define _CMMD__RCP_PARA__ITEM_YES					2

#define _CMMD__RCP_PARA__CATEGORY_XXX				11
#define _CMMD__RCP_PARA__CATEGORY_TITLE				12
#define _CMMD__RCP_PARA__CATEGORY_CHILD				13

#define _CMMD__RCP_PARA__CHANNEL					21

#define _CMMD__RCP_PARA__TITLE						31
#define _CMMD__RCP_PARA__CH_TITLE					32


// ...
int  CDlg__Wafer_Rcp_Sel::
Upload__Para_Info(const CString& file_path, CPara_Info* p_para_info)
{
	p_para_info->Clear__All();

	// ...
	CStringArray l_line;

	if(MACRO__Get_File_Data(file_path, l_line) < 0)
	{
		CString err_msg;
		err_msg.Format("file \"%s\"를 찾을 수 없습니다.", file_path);
		
		MessageBox(err_msg, "", MB_ICONERROR);
		return -1;
	}

	// ...
	int active__para_item = -1;
	int active__category  = -1;
	CString para_category = "";
	CString para_title    = "";

	int i_limit = l_line.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_line = l_line[i];

		// ...
		int active__para_cmmd = -1;
		int para_count = 0;		

		CString word = "";
		char ch;

		int k_len = str_line.GetLength();
		int k;

		for(k=0; k<k_len; k++)
		{
			ch = str_line[k];

			if((ch == ' ')		// space
			|| (ch == '	')		// tap 
			|| (ch == '\r') 
			|| (ch == '\n'))
			{
				if(word.GetLength() < 1)
				{
					continue;
				}

				if(para_count == 0)
				{
					if(word.CompareNoCase("##ITEM") == 0)
					{
						active__para_item = _CMMD__RCP_PARA__ITEM_XXX;
						active__category  = -1;

						para_title = "";
					}
					else if(active__para_item == _CMMD__RCP_PARA__ITEM_YES)
					{
							 if(word.CompareNoCase("#CATEGORY") == 0)			active__para_cmmd = _CMMD__RCP_PARA__CATEGORY_XXX;
						else if(word.CompareNoCase("#CHANNEL")  == 0)			active__para_cmmd = _CMMD__RCP_PARA__CHANNEL;
						else if(word.CompareNoCase("#TITLE")    == 0)			active__para_cmmd = _CMMD__RCP_PARA__TITLE;
						else if(word.CompareNoCase("#CH_TITLE") == 0)			active__para_cmmd = _CMMD__RCP_PARA__CH_TITLE;
					}
				}
				else if(active__para_item == _CMMD__RCP_PARA__ITEM_XXX)
				{
					if(para_count == 1)
					{
						if(word.CompareNoCase("YES") == 0)
						{
							active__para_item = _CMMD__RCP_PARA__ITEM_YES;

							p_para_info->Add__New_Parameter();
						}
						else
						{
							active__para_item = -1;
						}
					}
				}
				else if(active__para_cmmd == _CMMD__RCP_PARA__CATEGORY_XXX)
				{
					if(para_count == 1)
					{
						if(word.CompareNoCase("YES") == 0)
						{
							active__para_cmmd = _CMMD__RCP_PARA__CATEGORY_TITLE;
							active__category  = 1;

							para_category = para_title;
						}
						else if(word.CompareNoCase("CHILD") == 0)
						{
							active__para_cmmd = _CMMD__RCP_PARA__CATEGORY_CHILD;
							active__category  = -1;

							p_para_info->Load__Para_Category(para_category);
						}
						else
						{
							active__para_cmmd = -1;
							active__category  = -1;
						}
					}
				}
				else if(active__para_cmmd == _CMMD__RCP_PARA__CHANNEL)
				{
					if(para_count == 1)
					{
						p_para_info->Load__Para_Channel(word);
					}
				}
				else if(active__para_cmmd == _CMMD__RCP_PARA__TITLE)
				{
					if(para_count == 1)
					{
						p_para_info->Load__Para_Titlel(word);

						para_title = word;						
						if(active__category > 0)		para_category = word;
					}
				}
				else if(active__para_cmmd == _CMMD__RCP_PARA__CH_TITLE)
				{
					if(para_count == 1)
					{
						p_para_info->Load__Para_Ch_Titlel(word);
					}
				}

				para_count++;
				word = "";
			}
			else
			{
				word += ch;
			}
		}
	}

	return 1;
}

int  CDlg__Wafer_Rcp_Sel::
Upload__Rcp_Info(const CString& file_path, CRcp_Info* p_rcp_info)
{
	p_rcp_info->Clear__All();

	// ...
	CStringArray l_line;

	if(MACRO__Get_File_Data(file_path, l_line) < 0)
	{
		CString err_msg;
		err_msg.Format("file \"%s\"를 찾을 수 없습니다.", file_path);

		MessageBox(err_msg, "", MB_ICONERROR);
		return -1;
	}

	// ...
	int i_limit = l_line.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_line = l_line[i];

		// printf(" # %1d) [%s] \n", i,str_line);

		CString word = "";
		char ch;

		int para_count = 0;
		CString para__ch_type;
		CString para__ch_name;
		CString para__ch_data;

		int active_step = -1;
		int active_para = -1;

		int k_len = str_line.GetLength();
		int k;

		for(k=0; k<k_len; k++)
		{
			ch = str_line[k];

			if((ch == ',') || (ch == ';'))
			{
				if(word.CompareNoCase("@") == 0)
				{
					if(para_count == 0)
					{
						active_step = 1;
					}
				}
				else if(word.CompareNoCase("&") == 0)
				{
					if(para_count == 0)
					{
						active_para = 1;
					}
				}
				else
				{
					if(active_step > 0)
					{
						if(para_count == 1)
						{
							int step_id = atoi(word);
							p_rcp_info->Add__Step_ID(step_id);

							// printf(" ** step_id : [%s] \n", word);
						}
					}
					else if(active_para > 0)
					{
							 if(para_count == 1)			para__ch_type = word;
						else if(para_count == 2)			para__ch_name = word;
						else if(para_count == 3)			para__ch_data = word;
					}
				}

				if(ch == ';')
				{
					if(active_para > 0)
					{
						p_rcp_info->Add__Step_Info(para__ch_type,para__ch_name,para__ch_data);
					}

					active_step = -1;
					active_para = -1;
					para_count = 0;
				}
				else
				{
					para_count++;
				}

				word = "";
			}
			else
			{
				word += ch;
			}
		}
	}

	return 1;
}

