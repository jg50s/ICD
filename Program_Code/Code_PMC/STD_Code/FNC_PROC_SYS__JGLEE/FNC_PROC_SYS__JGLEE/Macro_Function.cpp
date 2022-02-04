#include "StdAfx.h"


// ...
int Macro__Get_DateTime(CString &date,CString &time)
{
	CTime t = CTime::GetCurrentTime();

	date.Format("%00004d_%002d_%002d", t.GetYear(),t.GetMonth(),t.GetDay());
	time.Format("%002d%002d%002d", t.GetHour(),t.GetMinute(),t.GetSecond());

	return 1;
}

int  Macro__Get_Step_Data(const int step_id,const CString& in_data,CString& step_data)
{
	CString bff_data = in_data;
	CString key_word = ",";
	int db_count = 0;

	while(1)
	{
		int db_index = bff_data.Find(key_word);
		if(db_index < 0)		return -1;

		bff_data.Delete(0,db_index+1);
		db_count++;

		if(db_count == step_id)			
		{
			step_data.Format("%.3f", atof(bff_data));
			return 1;
		}
	}

	return -1;
}
