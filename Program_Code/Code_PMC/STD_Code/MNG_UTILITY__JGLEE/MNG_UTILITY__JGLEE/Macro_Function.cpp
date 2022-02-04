#include "StdAfx.h"



// ...
int Macro__Check_1Point(const CString& str_data,int& check_percent)
{
	CString key_word = "%_1Point";
	CString str_bff  = str_data;

	int db_index = str_bff.Find(key_word,0);
	if(db_index < 0)		return -1;

	int key_len = key_word.GetLength();
	str_bff.Delete(db_index,key_len-db_index);

	check_percent = atoi(str_bff);
	return 1;
}

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

void Macro__Get_Date(CString& date, CString& time)
{
	CTime t = CTime::GetCurrentTime();

	date.Format("%00004d/%002d/%002d",
				t.GetYear(),
				t.GetMonth(),
				t.GetDay());

	time.Format("%002d:%002d:%002d",
				t.GetHour(),
				t.GetMinute(),
				t.GetSecond());
}

int  Macro__Convert_String_To_Array(const CString& str_data,
									CStringArray&  l_data)
{
	l_data.RemoveAll();

	// ...
	CString str_bff;
	char ch;

	int limit = str_data.GetLength();
	int i;

	for(i=0;i<limit;i++)
	{
		ch = str_data.GetAt(i);

		if(ch == ',')
		{
			l_data.Add(str_bff);
			str_bff = "";
		}
		else
		{
			str_bff += ch;
		}		
	}

	return 1;
}
int  Macro__Convert_String_To_String(const CString& str_data,
									 CString& data1,
									 CString& data2)
{
	int data_count = 0;

	data1 = "";
	data2 = "";

	// ...
	CString str_bff;
	char ch;

	int limit = str_data.GetLength();
	int i;

	for(i=0;i<limit;i++)
	{
		ch = str_data.GetAt(i);

		if(ch == '/')
		{
			data_count++;

			if(data_count == 1)
			{
				data1 = str_bff;
			}
			else if(data_count == 2)
			{
				data2 = str_bff;
			}

			str_bff = "";
		}
		else
		{
			str_bff += ch;
		}		
	}

	// ...
	{
		data_count++;

		if(data_count == 1)
		{
			data1 = str_bff;
		}
		else if(data_count == 2)
		{
			data2 = str_bff;
		}
	}

	return 1;
}
