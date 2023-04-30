#pragma once

#include "CInfo__Rcp_Common.h"
#include "Interface_Code.h"


class CDS__Rcp_Item
{
public:
	CDS__Rcp_Item()
	{
		Clear();
	}
	
	void Clear()
	{
		sPara__RCP_TITLE = "";
		sPara__CATEGORY_NAME = "";

		sPara__CH_NAME = "";
		iPara__CH_TYPE = _CH_TYPE__STRING;

		//
		bActive__CH_TITLE = false;
		sPara__CH_TITLE = "";

		bActive__CH_D_LIST = false;
		sPara__CH_D_LIST = "";

		bActive__CH_RANGE_MIN = false;
		sPara__CH_RANGE_MIN = "";
		bActive__CH_RANGE_MAX = false;
		sPara__CH_RANGE_MAX = "";

		//
		bPara__CATEGORY_ACTIVE = FALSE;
		bPara__CATEGORY_EXPAND = TRUE;

		bPara__CHILD_ACTIVE = FALSE;

		sPara__D_LIST = "";
		sPara__A_LIST = "";

		//
		cColor_TEXT = RGB(0,0,0);
		cColor_BACK = RGB(250,250,210);
	}

	// ...
	CString sPara__RCP_TITLE;
	CString sPara__CATEGORY_NAME;

	CString sPara__CH_NAME;
	int  iPara__CH_TYPE;

	//
	bool bActive__CH_TITLE;
	CString sPara__CH_TITLE;

	bool bActive__CH_D_LIST;
	CString sPara__CH_D_LIST;

	bool bActive__CH_RANGE_MIN;
	CString sPara__CH_RANGE_MIN;
	bool bActive__CH_RANGE_MAX;
	CString sPara__CH_RANGE_MAX;

	//
	bool bPara__CATEGORY_ACTIVE;
	bool bPara__CATEGORY_EXPAND;

	bool bPara__CHILD_ACTIVE;

	CString sPara__D_LIST;
	CString sPara__A_LIST;

	//
	COLORREF cColor_TEXT;
	COLORREF cColor_BACK;
};

class CInfo__Rcp_Item
{
public:
	GObj__Resource_Info *pGObj_Res;

	// ...
	bool bActive__Header_Rcp;

	CString sRcp_Title;
	int iItem_Title__Width;

	// ...
	CStringArray sList__RCP_TITLE;
	CStringArray sList__CATEGORY_NAME;

	CStringArray sList__CH_NAME;
	CUIntArray   iList__CH_TYPE;

	//
	CUIntArray   iList__CH_TITLE;
	CStringArray sList__CH_TITLE;

	CUIntArray   iList__CH_D_LIST;
	CStringArray sList__CH_D_LIST;

	CUIntArray   iList__CH_RANGE_MIN;
	CStringArray sList__CH_RANGE_MIN;
	CUIntArray   iList__CH_RANGE_MAX;
	CStringArray sList__CH_RANGE_MAX;

	//
	CUIntArray   iList__CATEGORY_ACTIVE;
	CUIntArray   iList__CATEGORY_EXPAND;

	CUIntArray   iList__CHILD_ACTIVE;

	CStringArray sList__D_LIST;
	CStringArray sList__A_LIST;

	//
	CUIntArray   iList__COLOR_TEXT;
	CUIntArray   iList__COLOR_BACK;
	//

public:
	CInfo__Rcp_Item()
	{
		bActive__Header_Rcp = false;
	}
	~CInfo__Rcp_Item()
	{

	}

	// ...
	int  Upload__RCP_INFO(const HWND hwnd, const CString& dir_root,const CString& file_name);

	// ...
	void Clear__ITEM_INFO()
	{
		sList__RCP_TITLE.RemoveAll();
		sList__CATEGORY_NAME.RemoveAll();

		sList__CH_NAME.RemoveAll();
		iList__CH_TYPE.RemoveAll();

		//
		iList__CH_TITLE.RemoveAll();
		sList__CH_TITLE.RemoveAll();

		iList__CH_D_LIST.RemoveAll();
		sList__CH_D_LIST.RemoveAll();

		iList__CH_RANGE_MIN.RemoveAll();
		sList__CH_RANGE_MIN.RemoveAll();
		iList__CH_RANGE_MAX.RemoveAll();
		sList__CH_RANGE_MAX.RemoveAll();

		//
		iList__CATEGORY_ACTIVE.RemoveAll();
		iList__CATEGORY_EXPAND.RemoveAll();

		iList__CHILD_ACTIVE.RemoveAll();

		sList__D_LIST.RemoveAll();
		sList__A_LIST.RemoveAll();
	}

	void Add__ITEM_INFO(const CDS__Rcp_Item& rcp_item)
	{
		sList__RCP_TITLE.Add(rcp_item.sPara__RCP_TITLE);
		sList__CATEGORY_NAME.Add(rcp_item.sPara__CATEGORY_NAME);

		sList__CH_NAME.Add(rcp_item.sPara__CH_NAME);
		iList__CH_TYPE.Add(rcp_item.iPara__CH_TYPE);

		//
		iList__CH_TITLE.Add(rcp_item.bActive__CH_TITLE);
		sList__CH_TITLE.Add(rcp_item.sPara__CH_TITLE);

		iList__CH_D_LIST.Add(rcp_item.bActive__CH_D_LIST);
		sList__CH_D_LIST.Add(rcp_item.sPara__CH_D_LIST);

		iList__CH_RANGE_MIN.Add(rcp_item.bActive__CH_RANGE_MIN);
		sList__CH_RANGE_MIN.Add(rcp_item.sPara__CH_RANGE_MIN);
		iList__CH_RANGE_MAX.Add(rcp_item.bActive__CH_RANGE_MAX);
		sList__CH_RANGE_MAX.Add(rcp_item.sPara__CH_RANGE_MAX);

		//
		iList__CATEGORY_ACTIVE.Add(rcp_item.bPara__CATEGORY_ACTIVE);
		iList__CATEGORY_EXPAND.Add(rcp_item.bPara__CATEGORY_EXPAND);

		iList__CHILD_ACTIVE.Add(rcp_item.bPara__CHILD_ACTIVE);

		sList__D_LIST.Add(rcp_item.sPara__D_LIST);
		sList__A_LIST.Add(rcp_item.sPara__A_LIST);

		//
		iList__COLOR_TEXT.Add(rcp_item.cColor_TEXT);
		iList__COLOR_BACK.Add(rcp_item.cColor_BACK);
	}

	// ...
	void Get__LINK_CHANNEL_LIST(CStringArray& l_ch_name)
	{
		l_ch_name.RemoveAll();

		int i_limit = iList__CH_TITLE.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(iList__CH_TITLE[i]  > 0)			l_ch_name.Add(sList__CH_TITLE[i]);
			
			if(iList__CH_D_LIST[i] > 0)			l_ch_name.Add(sList__CH_D_LIST[i]);
			
			if(iList__CH_RANGE_MIN[i] > 0)		l_ch_name.Add(sList__CH_RANGE_MIN[i]);
			if(iList__CH_RANGE_MAX[i] > 0)		l_ch_name.Add(sList__CH_RANGE_MAX[i]);
		}
	}

	int  Get__ITEM_SIZE()
	{
		return iList__CATEGORY_ACTIVE.GetSize();
	}
	int  Get__ITEM_SIZE_EXCEPT_CATEGORY()
	{
		int item_count = 0;

		int i_limmit = iList__CATEGORY_ACTIVE.GetSize();
		int i;

		for(i=1; i<i_limmit; i++)
		{
			if(iList__CATEGORY_ACTIVE[i] > 0)		continue;

			item_count++;
		}
		return item_count;
	}

	void Get__ITEM_CATEGORY_LIST(CUIntArray& l_row)
	{
		l_row.RemoveAll();

		int i_limmit = iList__CATEGORY_ACTIVE.GetSize();
		int i;

		for(i=1; i<i_limmit; i++)
		{
			if(iList__CATEGORY_ACTIVE[i] < 1)		continue;

			l_row.Add(i);
		}
	}

	CString Get__TITLE_OF_SUB_PARA()
	{
		int i_limmit = iList__CH_TYPE.GetSize();
		int i;

		for(i=1; i<i_limmit; i++)
		{
			if(iList__CH_TYPE[i] != _CH_TYPE__SUB_PARA)		continue;

			return sList__RCP_TITLE[i];
		}
		return "";
	}

	int  Get__ITEM_INFO(const int db_index, CDS__Rcp_Item* p_item)
	{
		if(db_index <  0)									return -1;
		if(db_index >= iList__CATEGORY_ACTIVE.GetSize())	return -2;
		
		// ...
		{
			p_item->sPara__RCP_TITLE = sList__RCP_TITLE[db_index];
			p_item->sPara__CATEGORY_NAME = sList__CATEGORY_NAME[db_index];

			p_item->sPara__CH_NAME = sList__CH_NAME[db_index];
			p_item->iPara__CH_TYPE = iList__CH_TYPE[db_index];
			
			//
			p_item->bActive__CH_TITLE = iList__CH_TITLE[db_index];
			p_item->sPara__CH_TITLE   = sList__CH_TITLE[db_index];

			p_item->bActive__CH_D_LIST = iList__CH_D_LIST[db_index];
			p_item->sPara__CH_D_LIST   = sList__CH_D_LIST[db_index];

			p_item->bActive__CH_RANGE_MIN = iList__CH_RANGE_MIN[db_index];
			p_item->sPara__CH_RANGE_MIN   = sList__CH_RANGE_MIN[db_index];
			
			p_item->bActive__CH_RANGE_MAX = iList__CH_RANGE_MAX[db_index];
			p_item->sPara__CH_RANGE_MAX   = sList__CH_RANGE_MAX[db_index];

			//
			p_item->bPara__CATEGORY_ACTIVE = iList__CATEGORY_ACTIVE[db_index];
			p_item->bPara__CATEGORY_EXPAND = iList__CATEGORY_EXPAND[db_index];

			p_item->bPara__CHILD_ACTIVE = iList__CHILD_ACTIVE[db_index];

			p_item->sPara__D_LIST = sList__D_LIST[db_index];
			p_item->sPara__A_LIST = sList__A_LIST[db_index];

			//
			p_item->cColor_TEXT = iList__COLOR_TEXT[db_index];
			p_item->cColor_BACK = iList__COLOR_BACK[db_index];
		}
		return 1;
	}
	int Get__CHILD_SIZE_OF_ROW(const int db_index)
	{
		if(db_index <  0)									return -1;
		if(db_index >= iList__CATEGORY_ACTIVE.GetSize())	return -2;

		// ...
		int child_count = 0;

		int i_limit = iList__CATEGORY_ACTIVE.GetSize();
		int i;

		for(i=db_index+1; i<i_limit; i++)
		{
			if(iList__CHILD_ACTIVE[i] > 0)		child_count++;
			else								break;
		}
		
		return child_count;
	}

	// ...
	bool Check__CATEGORY_ACTIVE_OF_ROW(const int row)
	{
		if(row <  0)									return false;
		if(row >= iList__CATEGORY_ACTIVE.GetSize())		return false;

		return iList__CATEGORY_ACTIVE[row];
	}
	bool Check__CATEGORY_EXPAND_OF_ROW(const int row)
	{
		if(row <  0)									return false;
		if(row >= iList__CATEGORY_EXPAND.GetSize())		return false;

		return iList__CATEGORY_EXPAND[row];
	}
	
	int  Enable__CATEGORY_EXPAND_OF_ROW(const int row)
	{
		if(row <  0)									return -1;
		if(row >= iList__CATEGORY_EXPAND.GetSize())		return -1;

		iList__CATEGORY_EXPAND[row] = TRUE;
		return 1;
	}
	int  Disable__CATEGORY_EXPAND_OF_ROW(const int row)
	{
		if(row <  0)									return -1;
		if(row >= iList__CATEGORY_EXPAND.GetSize())		return -1;

		iList__CATEGORY_EXPAND[row] = FALSE;
		return 1;
	}
};
