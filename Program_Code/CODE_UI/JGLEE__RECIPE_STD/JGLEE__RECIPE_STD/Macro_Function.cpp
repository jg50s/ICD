#include "stdafx.h"


// ...
int  MACRO__Get_Dir_Time_List(const CString& dir_root,
							  CStringArray&  l_dir_name,
							  CStringArray&  l_dir_time)
{
	// ...
	{
		l_dir_name.RemoveAll();
		l_dir_time.RemoveAll();
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

							f_time.Format("%002d%002d%002d",
										  st.wHour,
										  st.wMinute,
										  st.wSecond);
						}

						l_dir_time.Add(f_time);
					}
				}

				hresult = FindNextFile(hsrch,&wfd);
			}
		}

		FindClose(hsrch);
	}

	return 1;
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

void MACRO__Convert__LIST(const char parc, 
						  const CString& string,
						  CStringArray& data_list,
						  const int array_max)
{
	CString word;
	char ch;

	int n_count = 1;

	int limit = string.GetLength();
	int i;

	for(i=0; i<=limit; i++)
	{
		if(i < limit)	ch = string.GetAt(i);
		else			ch = parc;  

		if((n_count >= array_max)
		&& (array_max > 0))
		{
			if(i < limit)		word += ch;				
		}
		else
		{
			if(ch == parc)   
			{
				if(word.GetLength() > 0)
				{
					n_count++;
					data_list.Add(word);	
				}

				word = "";
			}
			else
			{
				word += ch;
			}
		}
	}

	if(word.GetLength() > 0)
		data_list.Add(word);
}

int MACRO__Get_Line_List_From_File_Data(const CString& file_data, 
										CStringArray& l_line)
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
int MACRO__Get_File_Data(const CString& file_path, 
						 CString& file_data)
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
int MACRO__Get_File_Data(const CString& file_path, 
						 CStringArray& l_line)
{
	l_line.RemoveAll();

	FILE *f_in = fopen(file_path, "r");
	if(f_in == NULL)			return -1;

	// ...
	char str_line[1024];
	int  line_count = 0;

	while(fgets(str_line, 1000, f_in) != NULL)
	{
		line_count++;
		if(line_count > 6000)		break;

		l_line.Add(str_line);
	}

	fclose(f_in);	
	return 1;
}
int MACRO__Get_Data_List_Of_File(const CString& file_path, 
								 CStringArray& l_line,
								 const CString& keyword_01,
								 const CString& keyword_02)
{
	l_line.RemoveAll();

	// ...
	FILE *f_in = fopen(file_path, "r");
	if(f_in == NULL)			return -1;

	// ...
	int i_max = 0;
	int i_len;

	i_max = keyword_01.GetLength();
	i_len = keyword_02.GetLength();
	if(i_len > i_max)		i_max = i_len;

	// ...
	char str_line[1024];
	CString str_data;

	// while(fgets(str_line, 1000, f_in) != NULL)
	while(fgets(str_line, 20, f_in) != NULL)
	{
		str_line[20] = 0;

		str_data = "";
		for(int i=0; i<i_max; i++)		str_data += str_line[i];

		if((str_data.Find(keyword_01) >= 0)
		|| (str_data.Find(keyword_02) >= 0))
		{
			l_line.Add(str_line);
		}
	}

	fclose(f_in);	
	return 1;
}

CString MACRO__Get_Current_Date()
{
	SYSTEMTIME file__sys_time;
	GetLocalTime(&file__sys_time);

	CString str_date;
	str_date.Format("%04d_%02d_%02d",		
					file__sys_time.wYear,
					file__sys_time.wMonth,
					file__sys_time.wDay);

	return str_date;
}
CString MACRO__Get_Current_Time()
{
	SYSTEMTIME file__sys_time;
	GetLocalTime(&file__sys_time);

	CString str_time;
	str_time.Format("%02d:%02d:%02d.%03d",		
					file__sys_time.wHour,
					file__sys_time.wMinute,
					file__sys_time.wSecond,
					file__sys_time.wMilliseconds);

	return str_time;
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

CString MACRO__Get_String_With_No_Char(const CString& str_org,
									   const char ch_check)
{
	CString str_data;
	char ch;

	// ...
	{
		bool active_data = false;

		int i_limit = str_org.GetLength();

		for(int i=0; i<i_limit; i++)
		{
			ch = (char) str_org.GetAt(i);

			if(!active_data)
			{
				if(ch == ch_check)		continue;

				active_data = true;
			}

			str_data += ch;
		}
	}

	// ...
	{
		int n_count = 0;

		int i_limit = str_data.GetLength();

		for(int i=i_limit-1; i>=0; i--)
		{
			ch = (char) str_data.GetAt(i);

			if(ch != ch_check)
			{
				break;
			}

			n_count++;
		}

		if(n_count > 0)
		{
			int i_len = str_data.GetLength();
			str_data.Delete(i_len-n_count, n_count);
		}
	}

	return str_data;
}
CString MACRO__Get_String_With_No_Space(const CString& str_org)
{
	return MACRO__Get_String_With_No_Char(str_org, ' ');
}

int MACRO__Make_File_Data(const CString& file_path, 
						  const CString& file_data,
						  const bool open_mode)
{
	CFile file_ctrl;

	int file_mode = CFile::modeWrite | CFile::modeCreate;
	if(open_mode)	file_mode |= CFile::modeNoTruncate;

	if(file_ctrl.Open(file_path, file_mode)) 
	{	
		file_ctrl.SeekToEnd();
		file_ctrl.Write(file_data, file_data.GetLength());
		file_ctrl.Close();
		return 1;
	}
	return -1;
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

int MACRO__Search_Index_Of_StringArray(const CStringArray& l_str, const CString& str_name)
{
	int i_limit = l_str.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(str_name.CompareNoCase(l_str[i]) == 0)
			return i;
	}
	return -1;
}

int MACRO__Get_PMx_ID(const CString& str_md)
{
	CString str_pm;
	int pm_id;

	int i_limit = 10;
	int i;

	for(i=0; i<i_limit; i++)
	{
		pm_id = i + 1;
		str_pm.Format("PM%1d", pm_id);
		
		if(str_md.Find(str_pm) >= 0)
			return pm_id;
	}
	return -1;
}
int MACRO__Get_LLx_ID(const CString& str_md)
{
	CString str_ll;
	int ll_id;

	int i_limit = 4;
	int i;

	for(i=0; i<i_limit; i++)
	{
		ll_id = i + 1;
		str_ll.Format("LL%1d", ll_id);

		if(str_md.Find(str_ll) >= 0)
			return ll_id;
	}
	return -1;
}

CString MACRO__Get_Dir_Path(const CString& file_path)
{
	int i_limit = file_path.GetLength();
	int i;

	for(i=i_limit; i>=0; i--)
	{
		if(file_path[i] != '\\')		continue;

		CString dir_path = file_path;
		dir_path.Delete(i, i_limit-i);
		return dir_path;
	}
	return "";
}
CString MACRO__Get_File_Name(const CString& file_path)
{
	int i_limit = file_path.GetLength();
	int i;

	for(i=i_limit; i>=0; i--)
	{
		if(file_path[i] != '\\')		continue;

		CString file_name = file_path;
		file_name.Delete(0, i+1);
		return file_name;
	}
	return "";
}

void MACRO__Cal_Tack_Time(const CStringArray& l_start_time,
						  const CStringArray& l_end_time,
						  CStringArray& l_tack_time)
{
	l_tack_time.RemoveAll();

	int i_limit = l_start_time.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_start = l_start_time[i];
		CString str_end   = l_end_time[i];

		double s_sec = 0;
		double e_sec = 0;

		// Start Sec ...
		{
			CStringArray l_para;
			MACRO__Convert__LIST(':', str_start, l_para, -1);

			if(l_para.GetSize() > 0)			s_sec += atof(l_para[0]) * 60 * 60;
			if(l_para.GetSize() > 1)			s_sec += atof(l_para[1]) * 60;
			if(l_para.GetSize() > 2)			s_sec += atof(l_para[2]);
		}
		// End Sec ...
		{
			CStringArray l_para;
			MACRO__Convert__LIST(':', str_end, l_para, -1);

			if(l_para.GetSize() > 0)			e_sec += atof(l_para[0]) * 60 * 60;
			if(l_para.GetSize() > 1)			e_sec += atof(l_para[1]) * 60;
			if(l_para.GetSize() > 2)			e_sec += atof(l_para[2]);
		}

		double t_sec = e_sec - s_sec;

		CString str_tack;
		str_tack.Format("%.3f", t_sec);

		l_tack_time.Add(str_tack);
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

int MACRO__Check_Stringarray(const CString str_data, const CStringArray& l_data)
{
	int i_limit = l_data.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(str_data.CompareNoCase(l_data[i]) == 0)
			return 1;
	}
	return -1;
}
int MACRO__Get_Count_Of_Stringarray(const CString str_data, const CStringArray& l_data)
{
	int md_count = 0;

	int i_limit = l_data.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(str_data.CompareNoCase(l_data[i]) != 0)
			continue;
			
		md_count++;
	}
	return md_count;
}

void MACRO__Convert__MIN_MAX(const CString& str_min_max, CString& a_min,CString& a_max)
{
	CString word1;
	CString word2;

	int  para = 0;
	
	int  i_limit = str_min_max.GetLength();
	int  i;

	for(i=0; i<i_limit; i++)
	{
		char ch = str_min_max.GetAt(i);

		if(ch == ',')
		{
			para++;
		}
		else if((ch != '(') && (ch != ')'))
		{
			     if(para == 0)		word1 += ch;
			else if(para == 1)		word2 += ch;
		}
	}

	a_min = word1;
	a_max = word2;
}
