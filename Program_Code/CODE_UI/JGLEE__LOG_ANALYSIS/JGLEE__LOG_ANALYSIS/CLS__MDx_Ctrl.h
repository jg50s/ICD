#pragma once


// ...
class CDB__Channel_Item
{
public:
	CDB__Channel_Item()
	{
		sCHANNEL = "";
		sNAME    = "";
		sUNIT    = "";
		sCOMMENT = "";
	}

	// ...
	CString sCHANNEL;
	CString sNAME;
	CString sUNIT;
	CString sCOMMENT;
};

class CDB__Group_Info
{
public:
	CString sGROUP_NAME;
	CPtrArray pList__CH_ITEM;

public:
	CDB__Group_Info()
	{

	}
	~CDB__Group_Info()
	{
		Clear__ALL_INFO();
	}

	// ...
	void Clear__ALL_INFO()
	{
		sGROUP_NAME = "";

		// ...
		{		
			int i_limit = pList__CH_ITEM.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				CDB__Channel_Item *p_item = (CDB__Channel_Item *) pList__CH_ITEM[i];
				delete p_item;
			}

			pList__CH_ITEM.RemoveAll();
		}
	}

	void Load__GROUP_NAME(const CString& group_name)
	{
		sGROUP_NAME = group_name;
	}
	void Load__CHANNEL_ITEM(const CString& ch_name,
							const CString& cfg_name,
							const CString& cfg_unit,
							const CString& cfg_comment)
	{
		CDB__Channel_Item *p_item = new CDB__Channel_Item;
		pList__CH_ITEM.Add(p_item);

		p_item->sCHANNEL = ch_name;
		p_item->sNAME    = cfg_name;
		p_item->sUNIT    = cfg_unit;
		p_item->sCOMMENT = cfg_comment;
	}

	CString Get__ALL_INFO()
	{
		CString str_info = "";
		CString str_bff;

		str_info.Format("%s \n", sGROUP_NAME);

		int i_limit = pList__CH_ITEM.GetSize();
		int i;

		str_bff.Format(" * CFG_SIZE : %1d \n", i_limit);
		str_info += str_bff;

		for(i=0; i<i_limit; i++)
		{
			CDB__Channel_Item *p_item = (CDB__Channel_Item *) pList__CH_ITEM[i];

			str_bff.Format("  %1d) [%s] [%s] [%s] [%s] \n", 
							i+1,
							p_item->sCHANNEL,
							p_item->sNAME,
							p_item->sUNIT,
							p_item->sCOMMENT);
			str_info += str_bff;
		}

		return str_info;
	}

	void Get__CHANNEL_LIST(CStringArray& l_channel,
							CStringArray& l_name,
							CStringArray& l_unit,
							CStringArray& l_comment)
	{
		// ...
		{
			l_channel.RemoveAll();
			l_name.RemoveAll();
			l_unit.RemoveAll();
			l_comment.RemoveAll();
		}

		// ...
		int i_limit = pList__CH_ITEM.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CDB__Channel_Item *p_item = (CDB__Channel_Item *) pList__CH_ITEM[i];

			l_channel.Add(p_item->sCHANNEL);
			l_name.Add(p_item->sNAME);
			l_unit.Add(p_item->sUNIT);
			l_comment.Add(p_item->sCOMMENT);
		}
	}
	void Get__CHANNEL_LIST(CStringArray& l_channel)
	{
		int i_limit = pList__CH_ITEM.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CDB__Channel_Item *p_item = (CDB__Channel_Item *) pList__CH_ITEM[i];

			l_channel.Add(p_item->sCHANNEL);
		}
	}

	int  Get__INFO_OF_CH_NAME(const CString& ch_name,
							  CString& str_name,
							  CString& str_unit,
							  CString& str_comment)
	{
		int i_limit = pList__CH_ITEM.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CDB__Channel_Item *p_item = (CDB__Channel_Item *) pList__CH_ITEM[i];

			if(ch_name.CompareNoCase(p_item->sCHANNEL) != 0)
				continue;

			str_name = p_item->sNAME;
			str_unit = p_item->sUNIT;

			str_comment = p_item->sCOMMENT;
			return 1;
		}
		return -1;
	}
};

class CDB__MDx_Info
{
public:
	CString sMDx_NAME;
	CPtrArray pList__GROUP_ITEM;

	CDB__Group_Info* pCUR_GROUP;

public:
	CDB__MDx_Info()
	{
		pCUR_GROUP = NULL;
	}
	~CDB__MDx_Info()
	{
		Clear__ALL_INFO();
	}

	// ...
	void Clear__ALL_INFO()
	{
		sMDx_NAME = "";

		// ...
		{		
			int i_limit = pList__GROUP_ITEM.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				CDB__Group_Info *p_item = (CDB__Group_Info *) pList__GROUP_ITEM[i];
				delete p_item;
			}

			pList__GROUP_ITEM.RemoveAll();
		}
	}

	CDB__Group_Info* _Get__GROUP_ADDR(const CString& group_name)
	{
		int i_limit = pList__GROUP_ITEM.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CDB__Group_Info* p_db = (CDB__Group_Info*) pList__GROUP_ITEM[i];
			if(p_db->sGROUP_NAME != group_name)			continue;

			return p_db;
		}
		return NULL;
	}

	void Load__MDx_NAME(const CString& md_name)
	{
		sMDx_NAME = md_name;
	}
	void Load__GROUP_NAME(const CString& group_name)
	{
		CDB__Group_Info* p_db = _Get__GROUP_ADDR(group_name);

		if(p_db == NULL)
		{
			CDB__Group_Info* p_db = new CDB__Group_Info;
			pList__GROUP_ITEM.Add(p_db);

			p_db->sGROUP_NAME = group_name;
		}

		pCUR_GROUP = p_db;
	}
	void Load__CHANNEL_ITEM(const CString& ch_name,
							const CString& cfg_name,
							const CString& cfg_unit,
							const CString& cfg_comment)
	{
		if(pCUR_GROUP == NULL)			return;

		pCUR_GROUP->Load__CHANNEL_ITEM(ch_name,cfg_name,cfg_unit,cfg_comment);
	}

	CString Get__ALL_INFO()
	{
		CString str_info = "";
		CString str_bff;

		str_info.Format("MDx_Name [%s] \n", sMDx_NAME);

		int i_limit = pList__GROUP_ITEM.GetSize();
		int i;

		str_bff.Format(" * Group_Size [%1d] \n", i_limit);
		str_info += str_bff;

		for(i=0; i<i_limit; i++)
		{
			CDB__Group_Info *p_db = (CDB__Group_Info *) pList__GROUP_ITEM[i];

			str_info += p_db->Get__ALL_INFO();
		}
		return str_info;
	}

	void Get__GROUP_LIST(CStringArray& l_group)
	{
		int i_limit = pList__GROUP_ITEM.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CDB__Group_Info* p_db = (CDB__Group_Info*) pList__GROUP_ITEM[i];

			l_group.Add(p_db->sGROUP_NAME);
		}
	}

	void Get__CHANNEL_LIST(const CString& group_name,
						   CStringArray& l_channel,
						   CStringArray& l_name,
						   CStringArray& l_unit,
						   CStringArray& l_comment)
	{
		CDB__Group_Info* p_db = _Get__GROUP_ADDR(group_name);
		if(p_db == NULL)		return;

		p_db->Get__CHANNEL_LIST(l_channel,l_name,l_unit,l_comment);
	}
	void Get__CHANNEL_LIST(CStringArray& l_channel)
	{
		int i_limit = pList__GROUP_ITEM.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CDB__Group_Info* p_db = (CDB__Group_Info*) pList__GROUP_ITEM[i];

			p_db->Get__CHANNEL_LIST(l_channel);
		}
	}

	int  Get__INFO_OF_CH_NAME(const CString& ch_name,
							  CString& str_group,
							  CString& str_name,
							  CString& str_unit,
							  CString& str_comment)
	{
		int i_limit = pList__GROUP_ITEM.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CDB__Group_Info* p_db = (CDB__Group_Info*) pList__GROUP_ITEM[i];

			if(p_db->Get__INFO_OF_CH_NAME(ch_name, str_name,str_unit,str_comment) < 0)
				continue;

			str_group = p_db->sGROUP_NAME;
			return 1;
		}
		return -1;
	}
};

class CDB__MDx_Ctrl
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CPtrArray pList__MDx_INFO;
	CDB__Group_Info *pCUR__GROUP_INFO;

	CDB__MDx_Info* _Get_Addr__CDB_MDx_Info(const CString& md_name);

public:
	CDB__MDx_Ctrl();
	~CDB__MDx_Ctrl();

	// ...
	void Clear__ALL_INFO();

	void Load__MDx_NAME(const CString& md_name);
	void Change__First_MDx_NAME(const CString& md_name);

	void Load__GROUP_NAME_OF_MDx(const CString& md_name,
								 const CString& group_name);
	void Load__CHANNEL_ITEM(const CString& ch_name,
							const CString& cfg_name,
							const CString& cfg_unit,
							const CString& cfg_comment);

	// ...
	CString Get__ALL_INFO();

	CString Get__First_MDx_NAME();
	void Get__MDx_LIST(CStringArray& l_md_name);

	void Get__GROUP_LIST(const CString& md_name,
						 CStringArray& l_group);

	int  Get__CHANNEL_LIST_OF_GROUP(const CString& md_name,
									const CString& group_name,
									CStringArray& l_channel,
									CStringArray& l_name,
									CStringArray& l_unit,
									CStringArray& l_comment);

	void Get__ALL_CHANNEL_LIST(CStringArray& l_channel);

	int  Get__INFO_OF_CH_NAME(const CString& ch_name,
							  CString& md_name,
							  CString& group_name,
							  CString& str_name,
							  CString& str_unit,
							  CString& str_comment);
};

