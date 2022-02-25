#include "StdAfx.h"


// ...
int  Macro__Split_String(const CString& str_cmmd,
						 CStringArray& l_str,
						 const char ch_key)
{
	// ...
	{
		l_str.RemoveAll();
	}

	// ...
	CString word;
	char ch;

	int i_limit = str_cmmd.GetLength();
	int i;

	for(i=0; i<i_limit; i++)
	{
		ch = str_cmmd.GetAt(i);

		if(ch != ch_key)
		{
			word += ch;
			continue;
		}

		// ...
		{
			l_str.Add(word);
			word = "";
		}
	}

	if(word.GetLength() > 0)
	{
		l_str.Add(word);
	}
	return 1;
}

int  Macro__Get_PmID_From_String(const CString& str_pm)
{
	CString cmp_pm;

	int limit = 4;
	int i;

	for(i=0; i<limit; i++)
	{
		cmp_pm.Format("PM%1d", i+1);

		if(cmp_pm.CompareNoCase(str_pm) == 0)		
		{
			return (i+1);
		}
	}
	return -1;
}

int  Macro__Get_PmID_And_StepID_And_ParaName(const CString& str_cmmd,
											 int& pm_id,
											 int& step_id,
											 CString& para_name)
{
	CStringArray l_str;
	char ch_key = ',';

	Macro__Split_String(str_cmmd, l_str,ch_key);

	if(l_str.GetSize() != 3)
	{
		return -1;	
	}

	// ...
	{
		pm_id     = Macro__Get_PmID_From_String(l_str[0]);
		step_id   = atoi(l_str[1]); 
		para_name = l_str[2];
	}
	return 1;
}

int  Macro__Check_ID(const int id,const CUIntArray& l_id)
{
	int limit = l_id.GetSize();
	int i;

	for(i=0; i<limit; i++)
	{
		if(id == (int) l_id[i])
		{
			return 1;
		}
	}
	return -1;
}
