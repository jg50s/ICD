#include "StdAfx.h"
#include "Interface_Code.h"


// ...
CString Macro__Get_String_Without_KeyChar(const CString& src_word,
										  const CStringArray& l_keyword,
										  const CStringArray& l_keydata)
{
	CString str_word = src_word;

	int db_index;
	CString str_keyword;
	CString str_keydata;

	int limit = l_keyword.GetSize();
	int i;

	for(i=0;i<limit;i++)
	{
		str_keyword = l_keyword[i];
		str_keydata = l_keydata[i];

		while(1)
		{
			db_index = str_word.Find(str_keyword,0);
			if(db_index < 0)		break;

			str_word.Delete(db_index,str_keyword.GetLength());
			str_word.Insert(db_index,str_keydata);
		}
	}

	return str_word;
}

int Macro__Get_SeqID_From_String(const CString& str_name)
{
	int seq_id = 0;

	if(str_name.CompareNoCase("CTC") == 0)
	{
		seq_id = 0;
	}
	else
	{
		CString cmp_name;
		int i;

		for(i=0;i<11;i++)
		{
			cmp_name.Format("MODULE%1d",i);

			if(cmp_name.CompareNoCase(str_name) != 0)
			{
				continue;
			}

			seq_id = i+1;
			break;
		}
	}

	return seq_id;
}

int  Macro__Check_String(const CString& cmp_str,const CStringArray& l_str)
{
	int limit = l_str.GetSize();
	int i;

	for(i=0;i<limit;i++)
	{
		if(cmp_str.CompareNoCase(l_str[i]) == 0)
		{
			return 1;
		}
	}

	return -1;
}

int  MACRO__Get_Line_List_From_File_Data(const CString& file_data, 
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
int  MACRO__Get_File_Data(const CString& file_path, 
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

CString MACRO__Get_Alarm_Level(const int alm_level)
{
	if(alm_level == ALARM_LEVEL__LIGHT)				return "LIGHT";
	if(alm_level == ALARM_LEVEL__WARNING)			return "WARNING";

	return "HEAVY";
}
