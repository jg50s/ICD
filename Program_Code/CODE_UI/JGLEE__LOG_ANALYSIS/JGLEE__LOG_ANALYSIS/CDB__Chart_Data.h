#pragma once


#define _CFG__IO_MAX				8


class CDB__Chart_Data_Info
{
public:	
	CDB__Chart_Data_Info()
	{
		dX_Pos = 0;

		dY1_Value = 0;
		dY2_Value = 0;
	}

	// ...
	double dX_Pos;

	double dY1_Value;
	double dY2_Value;
};

class CDB__Chart_Data_Ctrl
{
private:
	CRITICAL_SECTION mCS_LOCK;
	CPtrArray pList__DB;

public:	
	CDB__Chart_Data_Ctrl()
	{
		InitializeCriticalSection(&mCS_LOCK);
	}
	~CDB__Chart_Data_Ctrl()
	{
		_Clear__All_Data_Info();

		DeleteCriticalSection(&mCS_LOCK);
	}

	// ...
	CDB__Chart_Data_Info* _Get__Chart_Data_Info(const double x_pos)
	{
		CDB__Chart_Data_Info* p_db;

		int i_limit = pList__DB.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			p_db = (CDB__Chart_Data_Info*) pList__DB[i];
			if(p_db->dX_Pos != x_pos)		continue;

			return p_db;
		}
		return NULL;
	}

	void Load__Y1_Data(const double x_pos, const double y1_value)
	{
		EnterCriticalSection(&mCS_LOCK);

		_Load__Y1_Data(x_pos, y1_value);

		LeaveCriticalSection(&mCS_LOCK);
	}
	void Load__Y2_Data(const double x_pos, const double y2_value)
	{
		EnterCriticalSection(&mCS_LOCK);

		_Load__Y2_Data(x_pos, y2_value);

		LeaveCriticalSection(&mCS_LOCK);
	}
	void Load__Data_Info(const double x_pos, const double y1_value, const double y2_value)
	{
		EnterCriticalSection(&mCS_LOCK);

		_Load__Y1_Data(x_pos, y1_value);
		_Load__Y2_Data(x_pos, y2_value);

		LeaveCriticalSection(&mCS_LOCK);
	}
	void _Load__Y1_Data(const double x_pos, const double y1_value)
	{
		CDB__Chart_Data_Info* p_db = _Get__Chart_Data_Info(x_pos);

		if(p_db == NULL)
		{
			p_db = new CDB__Chart_Data_Info;
			pList__DB.Add(p_db);
		}
		if(p_db != NULL)
		{
			p_db->dX_Pos = x_pos;
			p_db->dY1_Value = y1_value;
		}
	}
	void _Load__Y2_Data(const double x_pos, const double y2_value)
	{
		CDB__Chart_Data_Info* p_db = _Get__Chart_Data_Info(x_pos);

		if(p_db == NULL)
		{
			p_db = new CDB__Chart_Data_Info;
			pList__DB.Add(p_db);
		}
		if(p_db != NULL)
		{
			p_db->dX_Pos = x_pos;
			p_db->dY2_Value = y2_value;
		}
	}

	void Get__All_Data_Info(CStringArray& l_x,
						    CStringArray& l_y1,
							CStringArray& l_y2)
	{
		EnterCriticalSection(&mCS_LOCK);

		// ...
		{
			l_x.RemoveAll();
			l_y1.RemoveAll();
			l_y2.RemoveAll();
		}

		// ...
		CString str_data;

		int i_limit = pList__DB.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CDB__Chart_Data_Info* p_db = (CDB__Chart_Data_Info*) pList__DB[i];

			str_data.Format("%.1f", p_db->dX_Pos);
			l_x.Add(str_data);

			str_data.Format("%.1f", p_db->dY1_Value);
			l_y1.Add(str_data);

			str_data.Format("%.1f", p_db->dY2_Value);
			l_y2.Add(str_data);
		}
		
		LeaveCriticalSection(&mCS_LOCK);
	}

	void Start__Data_Lock()
	{
		EnterCriticalSection(&mCS_LOCK);
	}
	void Stop__Data_Lock()
	{
		LeaveCriticalSection(&mCS_LOCK);
	}
	int _Get__Data_Size()
	{
		return pList__DB.GetSize();
	}
	CDB__Chart_Data_Info* _Get__Data_Info(const int db_i)
	{
		return (CDB__Chart_Data_Info*) pList__DB[db_i];
	}
	void _Clear__All_Data_Info()
	{
		int i_limit = pList__DB.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CDB__Chart_Data_Info* p_db = (CDB__Chart_Data_Info*) pList__DB[i];
			delete p_db;
		}
		pList__DB.RemoveAll();
	}
};

