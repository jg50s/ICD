#include "StdAfx.h"
#include "Macro_FNC.h"


// ...
CString Macro__Change_1st_UnderBar(const CString& file_name)
{
	CString in_file = file_name;
	char ch;

	int limit = in_file.GetLength();
	int i;

	for(i=0;i<limit;i++)
	{
		ch = in_file.GetAt(i);

		if(ch == '\\')		break;
		if(ch != '_')		continue;

		in_file.SetAt(i,'\\'); 
		break;
	}

	return in_file;	
}
