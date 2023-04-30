#pragma once

#include "Interface_Code.h"
#include "CInfo__Rcp_Common.h"


class CInfo__Step_DB
{

public:
	CInfo__Step_DB()
	{

	}

	void Copy_To(CInfo__Step_DB* p_add)
	{
		p_add->iList__CH_TYPE.Copy(iList__CH_TYPE);
		p_add->sList__CH_NAME.Copy(sList__CH_NAME);
		p_add->sList__CH_DATA.Copy(sList__CH_DATA);
	}

	// ...
	CUIntArray   iList__CH_TYPE;
	CStringArray sList__CH_NAME;
	CStringArray sList__CH_DATA;
};
class CCtrl__Step_DB
{
public:
	CUIntArray iList__STEP_ID;
	CPtrArray  pList__STEP_DB;		// CInfo__Step_DB

public:
	CCtrl__Step_DB()
	{

	}

	void Clear__Step_DB()
	{
		int i_limit = pList__STEP_DB.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CInfo__Step_DB *p_db = (CInfo__Step_DB*) pList__STEP_DB[i];
			delete p_db;
		}

		iList__STEP_ID.RemoveAll();
		pList__STEP_DB.RemoveAll();
	}
	int  Get__Step_Size()
	{
		return pList__STEP_DB.GetSize();
	}

	int  Load__Step_Info(const int step_id, const CString& ch_name,const int ch_type,const CString& ch_data)
	{
		CInfo__Step_DB *p_db = NULL;
		int db_index = -1;

		int i_limit = iList__STEP_ID.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(iList__STEP_ID[i] != step_id)		continue;

			db_index = i;
			p_db = (CInfo__Step_DB*) pList__STEP_DB[i];
			break;
		}

		if(db_index < 0)
		{
			iList__STEP_ID.Add(step_id);

			p_db = new CInfo__Step_DB;
			pList__STEP_DB.Add(p_db);
		}

		if(p_db != NULL)
		{
			p_db->sList__CH_NAME.Add(ch_name);
			p_db->iList__CH_TYPE.Add(ch_type);
			p_db->sList__CH_DATA.Add(ch_data);
		}
		return 1;
	}
	int  Append__Step_Info(const int step_id, const int add_id)
	{
		CInfo__Step_DB *p_db = NULL;
		int db_index = -1;

		int i_limit = iList__STEP_ID.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(iList__STEP_ID[i] != step_id)		continue;

			p_db = (CInfo__Step_DB*) pList__STEP_DB[i];
			break;
		}

		for(i=0; i<i_limit; i++)
		{
			if(iList__STEP_ID[i] != add_id)			continue;

			db_index = i;
			break;
		}

		if(p_db != NULL)
		{
			int st_size = iList__STEP_ID.GetSize() + 1;
			iList__STEP_ID.Add(st_size);

			CInfo__Step_DB *p_add = new CInfo__Step_DB;
			p_db->Copy_To(p_add);

			if(db_index < 0)		pList__STEP_DB.Add(p_add);
			else					pList__STEP_DB.InsertAt(db_index, p_add);
		}
		return 1;
	}
	int  Move__Step_Info(const int step_id, const int next_id)
	{
		CInfo__Step_DB *p_db = NULL;

		int step_index = -1;
		int next_index = -1;

		int i_limit = iList__STEP_ID.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(iList__STEP_ID[i] != step_id)		continue;

			p_db = (CInfo__Step_DB*) pList__STEP_DB[i];			
			step_index = i;
			break;
		}
		for(i=0; i<i_limit; i++)
		{
			if(iList__STEP_ID[i] != next_id)		continue;

			next_index = i;
			break;
		}

		if((step_index >= 0) && (next_index >= 0))
		{
			pList__STEP_DB.RemoveAt(step_index);
			pList__STEP_DB.InsertAt(next_index, p_db);
		}
		return 1;
	}
	int  Delete__Step_Info(const int step_id)
	{
		int i_limit = iList__STEP_ID.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(iList__STEP_ID[i] != step_id)		continue;

			// ...
			CInfo__Step_DB *p_db = (CInfo__Step_DB*) pList__STEP_DB[i];			
			delete p_db;

			iList__STEP_ID.RemoveAt(i_limit-1);
			pList__STEP_DB.RemoveAt(i);
			break;
		}
		return 1;
	}

	CString Get__Step_Data(const int step_id, const CString& ch_name)
	{
		int i_limit = iList__STEP_ID.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(iList__STEP_ID[i] != step_id)		continue;

			// ...
			CInfo__Step_DB* p_db = (CInfo__Step_DB*) pList__STEP_DB[i];

			int k_limit = p_db->sList__CH_NAME.GetSize();
			int k;

			for(k=0; k<k_limit; k++)
			{
				if(p_db->sList__CH_NAME[k].CompareNoCase(ch_name) != 0)	
					continue;

				return p_db->sList__CH_DATA[k];
			}
			break;
		}

		return "";
		// return "??";
	}
	void Set__Step_Data(const int step_id, const int ch_type, const CString& ch_name, const CString& ch_data)
	{
		bool active__ch_add = true;

		int i_limit = iList__STEP_ID.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(iList__STEP_ID[i] != step_id)		continue;

			// ...
			CInfo__Step_DB* p_db = (CInfo__Step_DB*) pList__STEP_DB[i];

			int k_limit = p_db->sList__CH_NAME.GetSize();
			int k;

			for(k=0; k<k_limit; k++)
			{
				if(p_db->sList__CH_NAME[k].CompareNoCase(ch_name) != 0)	
					continue;

				p_db->sList__CH_DATA[k] = ch_data;

				active__ch_add = false;
				break;
			}

			if(active__ch_add)
			{
				p_db->iList__CH_TYPE.Add(ch_type);
				p_db->sList__CH_NAME.Add(ch_name);
				p_db->sList__CH_DATA.Add(ch_data);
			}

			active__ch_add = false;
			break;
		}

		if(active__ch_add)
		{
			iList__STEP_ID.Add(step_id);
			
			// ...
			CInfo__Step_DB* p_db = new CInfo__Step_DB;
			pList__STEP_DB.Add(p_db);

			p_db->iList__CH_TYPE.Add(ch_type);
			p_db->sList__CH_NAME.Add(ch_name);
			p_db->sList__CH_DATA.Add(ch_data);
		}
	}
};

class CInfo__Rcp_File
{
public:
	// ...
	int iMODULE_ID;

	CCtrl__Step_DB mCtrl__Step_DB;
	UII__RCP_INTERLOCK_CTRL*  pI_Rcp_Interlock_Ctrl;

	// ...
	CString sPara__ITEM_TYPE;
	CString sPara__ITEM_CHANNEL;
	CString sPara__ITEM_DATA;

	int iPara__ITEM_COUNT;
	int iPara__ITEM_STATE;
	int iPara__ITEM_STEP;
	//

public:
	CInfo__Rcp_File()
	{
		iMODULE_ID = -1;
		pI_Rcp_Interlock_Ctrl = NULL;
	}
	~CInfo__Rcp_File()
	{

	}

	// ...
	void Clear__RCP_INFO();
	void Add__NEW_STEP_OF_RCP_INFO(const CStringArray& l_ch_name,const CUIntArray& l_ch_type,const CStringArray& l_io_list);

	void Append__STEP_ID(const int step_id,const int next_id);
	void Move__STEP_ID(const int step_id,const int next_id);
	void Delete__STEP_ID(const int step_id);

	// ...
	int  Upload__RCP_FILE(const HWND hwnd, const CString& rcp_path);

	void _PM_Init(const int step);

	int  _PM_Compile(const char& ch, 
		             const CString& word);

	int  _PM_Load(const int step_id,
				  const CString& ch_type,
				  const CString& ch_name,
				  const CString& ch_data);

	// ...
	int Get__Step_Size();

	CString Get__Step_Data(const int step_id, const CString& ch_name);
	void Set__Step_Data(const int step_id, const int ch_type, const CString& ch_name, const CString& ch_data);
};
