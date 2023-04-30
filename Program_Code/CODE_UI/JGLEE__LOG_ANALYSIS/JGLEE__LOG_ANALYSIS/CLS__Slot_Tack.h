#pragma once


class CLS__Slot_Tack_Info
{
public:
	CString sRef__SlotID;

	CStringArray sList__Module;
	CStringArray sList__Action;
	CStringArray sList__Result;
	CStringArray sList__Tack_Time;
	CStringArray sList__Comment;

public:
	CLS__Slot_Tack_Info()
	{

	}
	~CLS__Slot_Tack_Info()
	{

	}

	void Load__Slot_Info(const CStringArray& l_module,
						 const CStringArray& l_act,
						 const CStringArray& l_result,
						 const CStringArray& l_tack,
						 const CStringArray& l_comment)
	{
		sList__Module.Copy(l_module);
		sList__Action.Copy(l_act);
		sList__Result.Copy(l_result);
		sList__Tack_Time.Copy(l_tack);
		sList__Comment.Copy(l_comment);
	}
};
class CLS__Slot_Tack_Ctrl
{
private:
	CPtrArray pList_DB;

	CLS__Slot_Tack_Info* _Get_Addr__Slot_Tack_Into(const CString& str_slotid)
	{
		int i_limit = pList_DB.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CLS__Slot_Tack_Info *p_info = (CLS__Slot_Tack_Info*) pList_DB[i];

			if(p_info->sRef__SlotID.CompareNoCase(str_slotid) != 0)
				continue;

			return p_info;
		}
		return NULL;
	}

public:
	CLS__Slot_Tack_Ctrl()
	{

	}
	~CLS__Slot_Tack_Ctrl()
	{
		Clear();
	}

	void Clear()
	{
		int i_limit = pList_DB.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CLS__Slot_Tack_Info *p_info = (CLS__Slot_Tack_Info*) pList_DB[i];
			delete p_info;
		}
		pList_DB.RemoveAll();
	}
	void Load__Slot_Info(const CString& str_slotid,
						 const CStringArray& l_module,
						 const CStringArray& l_act,
						 const CStringArray& l_result,
						 const CStringArray& l_tack,
						 const CStringArray& l_comment)
	{
		CLS__Slot_Tack_Info* p_info = _Get_Addr__Slot_Tack_Into(str_slotid);

		if(p_info == NULL)
		{
			p_info = new CLS__Slot_Tack_Info;
			pList_DB.Add(p_info);

			p_info->sRef__SlotID = str_slotid;
		}

		p_info->Load__Slot_Info(l_module,l_act,l_result,l_tack,l_comment);
	}

	int Get__Slot_Size()
	{
		return pList_DB.GetSize();
	}
	int Get__Tack_Time(const CString& str_slotid,
					   CStringArray& l_tack_time)
	{
		l_tack_time.RemoveAll();

		CLS__Slot_Tack_Info* p_info = _Get_Addr__Slot_Tack_Into(str_slotid);
		if(p_info == NULL)			return -1;

		l_tack_time.Copy(p_info->sList__Tack_Time);
		return 1;
	}
	int Get__Tack_Time(const int  db_i,
					   CString& str_slotid,
					   CStringArray& l_tack_time)
	{
		int i_limit = pList_DB.GetSize();
		if(db_i >= i_limit)		return -1;

		CLS__Slot_Tack_Info *p_info = (CLS__Slot_Tack_Info*) pList_DB[db_i];

		str_slotid = p_info->sRef__SlotID;
		l_tack_time.Copy(p_info->sList__Tack_Time);
		return 1;
	}
	int Get__Tack_Count(const CString& str_slotid)
	{
		CLS__Slot_Tack_Info* p_info = _Get_Addr__Slot_Tack_Into(str_slotid);
		if(p_info == NULL)		return 0;

		return p_info->sList__Tack_Time.GetSize();
	}
	int Get__Tack_Count_Max()
	{
		int count_max = 0;

		int i_limit = pList_DB.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CLS__Slot_Tack_Info* p_info = (CLS__Slot_Tack_Info*) pList_DB[i];

			int cur_count = p_info->sList__Tack_Time.GetSize();
			if(count_max < cur_count)		count_max = cur_count;
		}
		return count_max;
	}

	CLS__Slot_Tack_Info*  Get_Addr__Slot_Tack_Info(const CString& str_slotid)
	{
		return _Get_Addr__Slot_Tack_Into(str_slotid);
	}

	CString Get__Slot_Comment(const CString& str_slotid, const int act_index)
	{
		CLS__Slot_Tack_Info* p_info = _Get_Addr__Slot_Tack_Into(str_slotid);
		if(p_info == NULL)		return "";

		if(act_index < 0)		return "";
		if(act_index >= p_info->sList__Comment.GetSize())		return"";

		if(p_info->sList__Action[act_index].CompareNoCase("PROCESS") == 0)
		{
			CString str_data;

			str_data.Format("%s %s", p_info->sList__Module[act_index],p_info->sList__Comment[act_index]);
			return str_data;
		}
		return p_info->sList__Comment[act_index];
	}
};

