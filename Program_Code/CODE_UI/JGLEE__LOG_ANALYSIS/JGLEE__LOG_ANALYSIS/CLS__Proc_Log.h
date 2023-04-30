#pragma once

#include "Interface_Header.h"


class CProc_Log__Y_Data
{
public:
	CString sChannel_Name;

	CStringArray sList__Data_Y;

public:
	CProc_Log__Y_Data()
	{

	}
	~CProc_Log__Y_Data()
	{

	}

	void Load__Y_Data(const CString& y_data)
	{
		sList__Data_Y.Add(y_data);
	}

	void Get__Y_Data(CStringArray& l_y_data)
	{
		l_y_data.Copy(sList__Data_Y);
	}
	int Get__Y_Data()
	{
		return sList__Data_Y.GetSize();
	}
};
class CProc_Log__XY_Data
{
private:
	CStringArray sList__X_Data;
	CPtrArray pList__Y_Data;

	CProc_Log__Y_Data* _Get__Addr_Of_Channel_Name(const CString& ch_name)
	{
		int i_limit = pList__Y_Data.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CProc_Log__Y_Data *p_y = (CProc_Log__Y_Data*) pList__Y_Data[i];

			if(ch_name.CompareNoCase(p_y->sChannel_Name) != 0)
				continue;

			return p_y;
		}
		return NULL;
	}

public:
	CProc_Log__XY_Data()
	{

	}
	~CProc_Log__XY_Data()
	{
		Clear();
	}

	void Clear()
	{
		int i_limit = pList__Y_Data.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CProc_Log__Y_Data *p_y = (CProc_Log__Y_Data *) pList__Y_Data[i];
			delete p_y;
		}
		pList__Y_Data.RemoveAll();
	}

	void Load__XY_Data(const double x_data, 
					   const CStringArray& l__ch_name,
					   const CStringArray& l__y_data)
	{
		int db_index = sList__X_Data.GetSize();

		// ...
		CString str_x;
		str_x.Format("%.3f", x_data);

		sList__X_Data.Add(str_x);

		//
		int i_limit = l__ch_name.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CString ch_name = l__ch_name[i];
			CString y_data  = l__y_data[i];

			CProc_Log__Y_Data* p_y = _Get__Addr_Of_Channel_Name(ch_name);
			if(p_y == NULL)		
			{
				if(db_index > 0)			continue;

				p_y = new CProc_Log__Y_Data;
				pList__Y_Data.Add(p_y);				

				p_y->sChannel_Name = ch_name;
			}

			p_y->Load__Y_Data(y_data);
		}

		/*
		if(db_index == 0)
		{
			i_limit = pList__Y_Data.GetSize();

			printf(" * Channel List <- [%1d] ... \n", i_limit);

			for(i=0; i<i_limit; i++)
			{
				CProc_Log__Y_Data* p_y = (CProc_Log__Y_Data*) pList__Y_Data[i];

				printf(" ** %02d)  [%s] \n", i+1,p_y->sChannel_Name);
			}
		}
		*/
	}

	int Get__X_Size()
	{
		return sList__X_Data.GetSize();
	}
	int Get__X_Data(CStringArray& l_x_data)
	{
		l_x_data.Copy(sList__X_Data);
		return 1;
	}
	int Get__X_Data(const int db_size, double* p_x_stamp)
	{
		int i_limit = sList__X_Data.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(i < db_size)			p_x_stamp[i] = atof(sList__X_Data[i]);
			else					return 1;
		}
		return 1;
	}

	int Get__All_Y_Data(const CString& ch_name, 
					    CStringArray& l_y_data)
	{
		l_y_data.RemoveAll();

		CProc_Log__Y_Data *p_y = _Get__Addr_Of_Channel_Name(ch_name);
		if(p_y == NULL)			return -1;

		p_y->Get__Y_Data(l_y_data);
		return 1;
	}
	int Get__All_Y_Data(const CString& ch_name)
	{
		CProc_Log__Y_Data *p_y = _Get__Addr_Of_Channel_Name(ch_name);
		if(p_y == NULL)			return -1;

		return p_y->Get__Y_Data();
	}
};

class CLS__Proc_Step
{
public:
	CLS__Proc_Step()
	{

	}

	void Clear()
	{
		sList__Step_ID.RemoveAll();
		sList__Step_Start.RemoveAll();
		sList__Step_End.RemoveAll();
		sList__Step_Tack.RemoveAll();
	}

	// ...
	CStringArray sList__Step_ID;
	CStringArray sList__Step_Start;
	CStringArray sList__Step_End;
	CStringArray sList__Step_Tack;
};

class CLS__Proc_Log
{
private:
	// ...
	bool bActive__Event_Channel;
	CStringArray  mTable_Event_Item;
	CStringArray  mTable_Event_Title;

	bool bActive__Interval_Channel;
	CStringArray  mTable_Interval_Item;
	CStringArray  mTable_Interval_Title;

	// ...
	CString sDir__Temp_Log;

	CString sPath__Log_Viewer_Inf;
	CString sPath__Log_Viewer_Txt;

	// ...
	CProc_Log__XY_Data mProc__XY_Data;
	//

private:
	int  _Read__File_Path(const HWND hwnd, 
		                  const CString& file_path, 
						  CString& file_data);

public:
	CLS__Proc_Log();
	~CLS__Proc_Log();

	// ...
	void Set__Dir_Root(const CString& dir_log_root);
	void Set_Template___Only_Analog();

	// ...
	int  Update__Template_File(const HWND hwnd, const CString& file_path);
	
	int  Get__Template_Event(CStringArray& l_name, 
							 CStringArray& l_channel);

	int  Get__Template_Interrval(CStringArray& l_name, 
								 CStringArray& l_channel);
	int  Get__Template_Interrval(CStringArray& l_name, 
								 CStringArray& l_channel, 
								 CStringArray& l_log_cnt);

	// ...
	int  Make__Log_Txt_File(const HWND hwnd,
							const CString& log_path,
							const CString& log_file,
							const CString& template_name);
	int  Make__Log_Csv_File(const HWND hwnd,
							const CString& log_path,
							const CString& log_file,
							const CString& template_name,
							const CString& out_path,
							const bool align_left);

	// ...
	int  Upload__Proc_Data_Of_Log_File(const HWND hwnd, 
								       const CString& log_path);

	CProc_Log__XY_Data* Get_Addr__Proc_XY_Data();

	// ...
	CLS__Proc_Step mProc_Step;

	int  Upload__Proc_Step_Of_Log_File(const HWND hwnd, 
									   const CString& log_path);

	// ...
	bool bActive__CH_MIN;
	bool bActive__CH_MAX;
	bool bActive__CH_AVG;
};
