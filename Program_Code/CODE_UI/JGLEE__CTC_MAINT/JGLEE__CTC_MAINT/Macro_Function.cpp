#include "StdAfx.h"
#include "Macro_Function.h"


int  MACRO__Get__PMC_ID(const CString& pmx_name)
{
	CString str_name;

	int i_limit = 10;
	int i;

	for(i=0; i<i_limit; i++)
	{
		int id = i + 1;

		str_name.Format("PM%1d", id);
		if(pmx_name.Find(str_name) == 0)	
			return id;
	}
	return -1;
}
int  MACRO__Get__LLx_ID(const CString& llx_name)
{
	CString str_name;

	int i_limit = 4;
	int i;

	for(i=0; i<i_limit; i++)
	{
		int id = i + 1;

		str_name.Format("LL%1d", id);
		if(str_name.CompareNoCase(llx_name) == 0)	
			return id;
	}
	return -1;
}

void MACRO__Convert__MIN_MAX(const CString& min_max_str,
							 CString& min_data,
							 CString& max_data)
{
	CString word1;
	CString word2;
	
	char ch;
	int  i;
	int  para = 0;
	int  limit = min_max_str.GetLength();

	for(i=0;i<limit;i++)
	{
		ch = min_max_str.GetAt(i);
		
		if(ch == ',')
		{
			para++;
		}
		else if((ch != '(')&&(ch != ')'))
		{
				 if(para == 0)	 word1 += ch;
			else if(para == 1)	 word2 += ch;
		}
	}

	min_data = word1;
	max_data = word2;
}

void MACRO__Convert__LIST(const char parc, const CString& string,
						  CStringArray& data_list)
{
	CString word;
	char ch;

	bool active_comment = false;

	int  limit = string.GetLength();
	int  i;
	
	for(i=0;i<=limit;i++)
	{
		if(i < limit)	ch = string.GetAt(i);
		else			ch = parc;   

		if(ch == '\"')
		{
			if(active_comment)			active_comment = false;
			else						active_comment = true;

			continue;
		}
		else if(active_comment)
		{
			word += ch;
		}
		else 
		{
			if(ch == parc)    
			{
				if(word.GetLength() > 0)
					data_list.Add(word);	

				word = "";
			}
			else
			{
				word += ch;
			}
		}
	}
}

CString MACRO__Get_Quotation_String(const CString& string)
{
	CString word;

	bool active_comment = false;
	int i_limit = string.GetLength();

	for(int i=0; i<i_limit; i++)
	{
		char ch = string.GetAt(i);

		if(ch == '\"')
		{
			if(active_comment)			active_comment = false;
			else						active_comment = true;

			continue;
		}
		else if(active_comment)
		{
			word += ch;
		}
	}
	
	if(active_comment)		return "";
	return word;
}

int  MACRO__Check_Driver_Type(const CString& drv_name)
{
	if(drv_name.GetLength() < 1)
	{
		return -1;
	}
	
	char str__path[10];	
	wsprintf(str__path, "%c:\\", drv_name.GetAt(0));
	
	UINT drv_type = GetDriveType(str__path);
	
	switch(drv_type)
	{
		case DRIVE_REMOVABLE:
		case DRIVE_FIXED:
		case DRIVE_REMOTE:
		case DRIVE_RAMDISK:
			return 1;
			
		default:
			return -1;
	}

	return -1;
}

int  MACRO__Get_Dir_Date_List(const CString& dir_root,
							  CStringArray&  l_dir_name,
							  CStringArray&  l_dir_date)
{
	// ...
	{
		l_dir_name.RemoveAll();
		l_dir_date.RemoveAll();
	}

	// ...
	CString dir_search;

	dir_search  = dir_root;
	dir_search += "\\";
	dir_search += "*.*";

	// ...
	{
		WIN32_FIND_DATA wfd;
		SYSTEMTIME st_file;
		SYSTEMTIME st;
		CString f_time;
		HANDLE hsrch;
		BOOL   hresult;

		strcpy(wfd.cFileName,"");

		hresult = TRUE;
		hsrch = FindFirstFile(dir_search,&wfd);

		if((hsrch != NULL)&&(strlen(wfd.cFileName) > 0))
		{
			while(hresult)
			{
				if(wfd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
				{
					if((strcmp(wfd.cFileName,".")  != 0)
					&& (strcmp(wfd.cFileName,"..") != 0))
					{
						l_dir_name.Add(wfd.cFileName);

						// ...
						{
							FileTimeToSystemTime(&wfd.ftCreationTime,&st_file);
							SystemTimeToTzSpecificLocalTime(NULL,&st_file,&st);   

							f_time.Format("%00004d%002d%002d %002d%002d%002d",
											st.wYear,
											st.wMonth,
											st.wDay,
											st.wHour,
											st.wMinute,
											st.wSecond);
						}

						l_dir_date.Add(f_time);
					}
				}

				hresult = FindNextFile(hsrch,&wfd);
			}
		}

		FindClose(hsrch);
	}

	return 1;
}
int  MACRO__Get_File_List(const CString& dir_root,
						  const CString& file_ext,
						  CStringArray&  l_file_name,
						  CStringArray&  l_file_date)
{
	// ...
	{
		l_file_name.RemoveAll();
		l_file_date.RemoveAll();
	}

	// ...
	CString dir_search;

	dir_search  = dir_root;
	dir_search += "\\";
	dir_search += "*.";
	dir_search += file_ext;

	// ...
	{
		l_file_name.RemoveAll();

		// ...
		CFileFind rfile_find;
		CTime f_time;
		CString str_time;

		if(rfile_find.FindFile(dir_search,0) != 0)
		{
			while(rfile_find.FindNextFile() != 0)
			{
				rfile_find.GetLastWriteTime(f_time);
				str_time.Format("%00004d%002d%002d %002d%002d%002d",
								f_time.GetYear(),
								f_time.GetMonth(),
								f_time.GetDay(),
								f_time.GetHour(),
								f_time.GetMinute(),
								f_time.GetSecond());

				l_file_name.Add(rfile_find.GetFileTitle());
				l_file_date.Add(str_time);
			}

			// ...
			{
				rfile_find.GetLastWriteTime(f_time);
				str_time.Format("%00004d%002d%002d %002d%002d%002d",
								f_time.GetYear(),
								f_time.GetMonth(),
								f_time.GetDay(),
								f_time.GetHour(),
								f_time.GetMinute(),
								f_time.GetSecond());

				l_file_name.Add(rfile_find.GetFileTitle());
				l_file_date.Add(str_time);
			}

			rfile_find.Close();
		}
	}

	return 1;
}

CString MACRO__Get_Date_Time()
{
	CTime f_time = CTime::GetCurrentTime();

	CString str_time;
	str_time.Format("%00004d%002d%002d_%002d%002d%002d",
					f_time.GetYear(),
					f_time.GetMonth(),
					f_time.GetDay(),
					f_time.GetHour(),
					f_time.GetMinute(),
					f_time.GetSecond());

	return str_time;
}

int MACRO__Get_File_Data(const CString& file_path, CString& file_data)
{
	CFile file_ctrl;

	if(file_ctrl.Open(file_path, CFile::modeRead)) 
	{	
		int len = file_ctrl.GetLength();
		char *str_data = new char[len + 1];
		str_data[len] = 0;

		file_ctrl.Read(str_data, len);
		file_ctrl.Close();

		file_data.Format("%s", str_data);

		delete [] str_data;
		return 1;
	}
	return -1;
}
int MACRO__Get_Line_List_From_File_Data(const CString& file_data, CStringArray& l_line)
{
	l_line.RemoveAll();

	// ...
	CString word;
	char ch;

	int i_len = file_data.GetLength();
	int i;

	for(i=0; i<i_len; i++)
	{
		ch = file_data[i];

		if((ch == '\r') || (ch == '\n'))
		{
			if(word.GetLength() > 0)
			{
				l_line.Add(word);
			}

			word = "";
		}
		else
		{
			word += ch;
		}
	}
	return 1;
}

int MACRO__Save_File_Data(const CString& file_path, const CString& file_data)
{
	CFile file_ctrl;

	if(file_ctrl.Open(file_path, CFile::modeCreate| CFile::modeWrite | CFile::typeText))
	{
		file_ctrl.Write(file_data, file_data.GetLength()*sizeof(TCHAR));
		file_ctrl.Close();
		return 1;
	}
	return -1;
}
int MACRO__Delete_File(const CString& file_path)
{
	if(DeleteFile(file_path))
	{
		printf(" * [OK] File_Delete : [%s] \n", file_path);
		return 1;
	}

	printf(" * [ERROR] File_Delete : [%s] \n", file_path);
	return -1;
}

void MACRO__Expand_All_Tree(CTreeCtrl* p_tree)
{
	HTREEITEM h_item = p_tree->GetFirstVisibleItem();

	while(h_item != NULL)
	{
		p_tree->Expand(h_item, TVE_EXPAND);
		h_item = p_tree->GetNextItem(h_item, TVGN_NEXTVISIBLE);
	}
}
void MACRO__Expand_Tree(CTreeCtrl* p_tree, 
						HTREEITEM h_node, 
						const int child_size)
{
	if(h_node == NULL)		return;

	int cur_size = child_size - 1;
	if(cur_size < 0)		return;

	p_tree->Expand(h_node, TVE_EXPAND);
	HTREEITEM h_item = h_node;

	while(h_item != NULL)
	{
		HTREEITEM h_child = p_tree->GetNextItem(h_item, TVGN_CHILD);
		MACRO__Expand_Tree(p_tree, h_child, cur_size);

		h_item = p_tree->GetNextSiblingItem(h_item);
		p_tree->Expand(h_item, TVE_EXPAND);
	}
}

void MACRO__Contract_All_Tree(CTreeCtrl* p_tree)
{
	HTREEITEM h_item = p_tree->GetRootItem();

	while(h_item != NULL)
	{
		p_tree->Expand(h_item, TVE_COLLAPSE);

		HTREEITEM h_child = p_tree->GetNextItem(h_item, TVGN_CHILD);
		MACRO__Contract_Tree(p_tree, h_child);

		h_item = p_tree->GetNextItem(h_item, TVGN_NEXT);
	}
}
void MACRO__Contract_Tree(CTreeCtrl* p_tree, HTREEITEM h_node)
{
	HTREEITEM h_item = h_node;

	while(h_item != NULL)
	{
		p_tree->Expand(h_item, TVE_COLLAPSE);

		HTREEITEM h_child = p_tree->GetNextItem(h_item, TVGN_CHILD);
		MACRO__Contract_Tree(p_tree, h_child);

		h_item = p_tree->GetNextItem(h_item, TVGN_NEXT);
	}
}

CString MACRO__Get_ITEM_DATA(const CString item_data, const char ch_sep)
{
	CString para_data = "";
	int check_active = -1;

	int i_limit = item_data.GetLength();
	int i;

	for(i=0; i<i_limit; i++)
	{
		char ch_data = item_data[i];

		if(check_active < 0)
		{
			if(ch_data == ch_sep)
				check_active = 1;

			continue;
		}
		else
		{
			if(para_data.GetLength() < 1)
			{
				if(ch_data == ' ')		continue;
			}

			para_data += ch_data;
		}
	}

	return para_data;
}

int MACRO__Check_Route_File_Edit_Type(const CString& file_data)
{
	CString	word;
	char ch;

	int line_count = 0;

	int i_size = file_data.GetLength();
	int i;

	for(i=0; i<i_size; i++)
	{
		ch = file_data.GetAt(i);

		if((ch == '^')
		|| (ch == ',')
		|| (ch == ';')
		|| (ch == '(')
		|| (ch == ')')
		|| (ch == '\r')
		|| (ch == '\n')
		|| (ch == EOF))
		{
			if(word.CompareNoCase("#ROUTE_EDIT#") == 0)
			{
				return 1;
			}

			if(ch == '\n')
			{
				line_count++;

				if(line_count > 1)		return -1;
			}

			word = "";	
		}
		else
		{
			word += ch;
		}
	}

	return -11;
}

CString MACRO__Trim_Left_String(const CString& str_org)
{
	CString str_data = str_org;

	int i_len = str_org.GetLength();
	int i;

	for(i=0; i<i_len; i++)
	{
		char ch = str_org.GetAt(i);		

		if(ch == ' ')		continue;
		if(ch == '	')		continue;
		if(ch == '"')		continue;

		break;
	}

	if(i > 0)
		str_data.Delete(0, i);

	return str_data;
}
CString MACRO__Trim_Right_String(const CString& str_org)
{
	CString str_data = str_org;
	int n_count = 0;

	int i_len = str_org.GetLength();
	int i;

	for(i=i_len-1; i>=0; i--)
	{
		char ch = str_org.GetAt(i);

		if((ch == ' ')
			|| (ch == '	')
			|| (ch == '"'))
		{
			n_count++;
			continue;;
		}

		break;
	}

	if(n_count > 0)
		str_data.Delete(i_len-n_count, n_count);

	return str_data;
}

CString MACRO__Convert_No_Number_To_Removal(const CString& str_data)
{
	CString str_bff = "";

	int i_len = str_data.GetLength();
	int i;

	for(i=0; i<i_len; i++)
	{
		char ch = str_data.GetAt(i);

		if((ch < '0') || (ch > '9'))		continue;
		else								str_bff += ch;
	}
	return str_bff;
}

void MACRO__Change_Order(CStringArray& l_date,
						 const bool order_type__descending,
						 const bool active__number_check)
{
	int i_limit = l_date.GetSize();
	int i;

	/*
	// Before ...
	{
		printf("MACRO__Change_Order() : Before ... \n");

		for(i=0; i<i_limit; i++)
			printf(" * %1d) [%s] \n", i+1, l_date[i]);
	}
	*/

	for(i=0; i<i_limit; i++)
	{
		CString cur_date = l_date[i];

		int cur_value = -1;
		if(active__number_check)
		{
			CString str_value = MACRO__Convert_No_Number_To_Removal(cur_date);
			cur_value = atoi(str_value);
			
			// printf(" ** Convert : [%s] -> [%s] \n", cur_date,str_value);
		}

		for(int k=i+1; k<i_limit; k++)
		{
			CString cmp_date = l_date[k];
			int cmp_value = -1;
			
			if(active__number_check)
			{
				CString str_value = MACRO__Convert_No_Number_To_Removal(cmp_date);
				cmp_value = atoi(str_value);

				if(order_type__descending)
				{
					if(cur_value >= cmp_value)
						continue;
				}
				else
				{
					if(cur_value <= cmp_value)
						continue;
				}
			}
			else
			{
				if(order_type__descending)
				{
					if(cur_date.CompareNoCase(cmp_date) >= 0)
						continue;
				}
				else
				{
					if(cur_date.CompareNoCase(cmp_date) <= 0)
						continue;
				}
			}

			l_date[i] = cmp_date;
			l_date[k] = cur_date;
			
			cur_date  = cmp_date;
			cur_value = cmp_value;
		}
	}

	/*
	// After ...
	{
		printf("MACRO__Change_Order() : After ... \n");

		for(i=0; i<i_limit; i++)
			printf(" * %1d) [%s] \n", i+1, l_date[i]);
	}
	*/
}
