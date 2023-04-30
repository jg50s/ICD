#include "stdafx.h"
#include "CInfo__Rcp_Item.h"

#include "Macro_Function.h"


// ...
#define  CMMD_STR__ITEM_ACTIVE				"##ITEM"
#define  CMMD_STR__TITLE					"#TITLE"
#define  CMMD_STR__CH_TITLE					"#CH_TITLE"
#define  CMMD_STR__CHANNEL_TYPE				"#CHANNEL_TYPE"
#define  CMMD_STR__CHANNEL					"#CHANNEL"
#define  CMMD_STR__CH_CHANNEL_ITEM			"#CH_CHANNEL_ITEM"
#define  CMMD_STR__LIST						"#LIST"
#define  CMMD_STR__RANGE					"#RANGE"
#define  CMMD_STR__CH_ALG_MIN				"#CH_ALG_MIN"
#define  CMMD_STR__CH_ALG_MAX				"#CH_ALG_MAX"
#define  CMMD_STR__TEXT_COLOR				"#TEXTCOLOR"
#define  CMMD_STR__BACK_COLOR				"#BACKCOLOR"
#define  CMMD_STR__CATEGORY					"#CATEGORY"

#define  CMMD_ID__SIZE                      13
#define  CMMD_ID__ITEM_ACTIVE				0
#define  CMMD_ID__TITLE						1
#define  CMMD_ID__CH_TITLE					2
#define  CMMD_ID__CHANNEL_TYPE				3
#define  CMMD_ID__CHANNEL					4
#define  CMMD_ID__CH_CHANNEL_ITEM			5
#define  CMMD_ID__LIST						6
#define  CMMD_ID__RANGE						7
#define  CMMD_ID__CH_ALG_MIN				8
#define  CMMD_ID__CH_ALG_MAX				9
#define  CMMD_ID__TEXT_COLOR				10
#define  CMMD_ID__BACK_COLOR				11
#define  CMMD_ID__CATEGORY					12


// ...
int  CInfo__Rcp_Item::
Upload__RCP_INFO(const HWND hwnd, const CString& dir_root, const CString& file_name)
{
	Clear__ITEM_INFO();

	// ...
	CStringArray l_line;

	// ...
	{
		CString rcp_path;
		rcp_path.Format("%s\\%s", dir_root,file_name);

		CString file_data;
		if(MACRO__Get_File_Data(rcp_path, file_data) < 0)
		{
			printf(" * ERROR ! : Upload__RCP_INFO() <- [%s] \n", rcp_path);
			return -1;
		}

		MACRO__Get_Line_List_From_File_Data(file_data, l_line);
	}

	// ...
	CDS__Rcp_Item rcp_item;

	rcp_item.sPara__RCP_TITLE = "Step No.";
	Add__ITEM_INFO(rcp_item);

	rcp_item.Clear();

	// ...
	bool active_item = false;
	int  active_para_count = 0;

	CString str_category;

	int i_limit = l_line.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_line = l_line[i];

		// ...
		CString key_name;

		int k_limit = CMMD_ID__SIZE;
		int k;

		for(k=0; k<k_limit; k++)
		{
				 if(k == CMMD_ID__ITEM_ACTIVE)			key_name = CMMD_STR__ITEM_ACTIVE;
			else if(k == CMMD_ID__TITLE)				key_name = CMMD_STR__TITLE;
			else if(k == CMMD_ID__CH_TITLE)				key_name = CMMD_STR__CH_TITLE;
			else if(k == CMMD_ID__CHANNEL_TYPE)			key_name = CMMD_STR__CHANNEL_TYPE;
			else if(k == CMMD_ID__CHANNEL)				key_name = CMMD_STR__CHANNEL;
			else if(k == CMMD_ID__CH_CHANNEL_ITEM)		key_name = CMMD_STR__CH_CHANNEL_ITEM;
			else if(k == CMMD_ID__LIST)					key_name = CMMD_STR__LIST;
			else if(k == CMMD_ID__RANGE)				key_name = CMMD_STR__RANGE;
			else if(k == CMMD_ID__CH_ALG_MIN)			key_name = CMMD_STR__CH_ALG_MIN;
			else if(k == CMMD_ID__CH_ALG_MAX)			key_name = CMMD_STR__CH_ALG_MAX;
			else if(k == CMMD_ID__TEXT_COLOR)			key_name = CMMD_STR__TEXT_COLOR;
			else if(k == CMMD_ID__BACK_COLOR)			key_name = CMMD_STR__BACK_COLOR;
			else if(k == CMMD_ID__CATEGORY)				key_name = CMMD_STR__CATEGORY;
			else										continue;

			int s_index = str_line.Find(key_name);
			if(s_index < 0)		continue;

			CString str_data = str_line;

			str_data.Delete(0, s_index+key_name.GetLength());
			str_data.TrimLeft();
			str_data.TrimRight();

			// printf(" * %02d) [%s] \n", i,str_line);
			// printf(" ** Data <- [%s] \n", str_line);

			active_para_count++;

			if(k == CMMD_ID__ITEM_ACTIVE)
			{
				if(active_item)
				{
					if(rcp_item.bPara__CATEGORY_ACTIVE)
						str_category = rcp_item.sPara__RCP_TITLE;
					else if(rcp_item.bPara__CHILD_ACTIVE)
						rcp_item.sPara__CATEGORY_NAME = str_category;

					/*
					printf("===================================================== \n");
					printf(" *    TITLE  <- [%s] \n",  rcp_item.sPara__RCP_TITLE);
					printf(" *  CH_NAME  <- [%s] \n",  rcp_item.sPara__CH_NAME);
					printf(" *  CH_TYPE  <- [%1d] \n", rcp_item.iPara__CH_TYPE);
					printf(" *  CH_TITLE <- [%s] \n",  rcp_item.sPara__CH_TITLE);
					printf(" * CH_D_LIST <- [%s] \n",  rcp_item.sPara__CH_D_LIST);
					printf(" * CH_RANGE_MIN <- [%s] \n", rcp_item.sPara__CH_RANGE_MIN);
					printf(" * CH_RANGE_MAX <- [%s] \n", rcp_item.sPara__CH_RANGE_MAX);
					printf(" * CATEGORY <- [%1d] \n", rcp_item.bPara__CATEGORY_ACTIVE);
					printf(" *   D_LIST <- [%s] \n",  rcp_item.sPara__D_LIST);
					printf(" *   A_LIST <- [%s] \n",  rcp_item.sPara__A_LIST);
					printf("===================================================== \n");
					*/

					Add__ITEM_INFO(rcp_item);						
				}

				rcp_item.Clear();
				active_item = true;
				active_para_count = 0;
			}
			else if(k == CMMD_ID__CHANNEL)
			{
				rcp_item.sPara__CH_NAME = str_data;
			}
			else if(k == CMMD_ID__TITLE)
			{
				rcp_item.sPara__RCP_TITLE = str_data;
			}
			else if(k == CMMD_ID__CH_TITLE)
			{
				if(str_data.GetLength() > 0)
				{
					rcp_item.bActive__CH_TITLE = true;
					rcp_item.sPara__CH_TITLE = str_data;
				}
			}
			else if(k == CMMD_ID__CHANNEL_TYPE)
			{
				int ch_type = _CH_TYPE__STRING;

				     if(str_data.CompareNoCase("ANALOG")  == 0)				ch_type = _CH_TYPE__ANALOG;
				else if(str_data.CompareNoCase("DIGITAL") == 0)				ch_type = _CH_TYPE__DIGITAL;
				else if(str_data.CompareNoCase("SUB_PARAMETER") == 0)		ch_type = _CH_TYPE__SUB_PARA;

				rcp_item.iPara__CH_TYPE = ch_type;
			}
			else if(k == CMMD_ID__CH_CHANNEL_ITEM)
			{
				if(str_data.GetLength() > 0)
				{
					rcp_item.bActive__CH_D_LIST = true;
					rcp_item.sPara__CH_D_LIST = str_data;
				}
			}
			else if(k == CMMD_ID__LIST)	
			{
				rcp_item.sPara__D_LIST = str_data;
			}
			else if(k == CMMD_ID__RANGE)
			{
				rcp_item.sPara__A_LIST = str_data;
			}
			else if(k == CMMD_ID__CH_ALG_MIN)
			{
				if(str_data.GetLength() > 0)
				{
					rcp_item.bActive__CH_RANGE_MIN = true;
					rcp_item.sPara__CH_RANGE_MIN = str_data;
				}
			}
			else if(k == CMMD_ID__CH_ALG_MAX)
			{
				if(str_data.GetLength() > 0)
				{
					rcp_item.bActive__CH_RANGE_MAX = true;
					rcp_item.sPara__CH_RANGE_MAX = str_data;
				}
			}
			else if(k == CMMD_ID__TEXT_COLOR)
			{
				if(str_data.GetLength() > 0)
				{
					int r, g, b;	
					pGObj_Res->pGOBJ_PARA_CTRL->Get_RGB_Color(str_data, r,g,b);

					rcp_item.cColor_TEXT = RGB(r,g,b);
				}
			}
			else if(k == CMMD_ID__BACK_COLOR)
			{
				if(str_data.GetLength() > 0)
				{
					int r, g, b;	
					pGObj_Res->pGOBJ_PARA_CTRL->Get_RGB_Color(str_data, r,g,b);

					rcp_item.cColor_BACK = RGB(r,g,b);
				}
			}
			else if(k == CMMD_ID__CATEGORY)
			{
				if(str_data.CompareNoCase("YES") == 0)
				{
					rcp_item.bPara__CATEGORY_ACTIVE = true;
					rcp_item.iPara__CH_TYPE = _CH_TYPE__CATEGORY;
				}
				else
				{
					rcp_item.bPara__CHILD_ACTIVE = true;
				}
			}

			break;
		}
	}

	if(active_item)
	{
		if(active_para_count > 0)
		{
			/*
			printf("===================================================== \n");
			printf(" *    TITLE <- [%s] \n",  rcp_item.sPara__RCP_TITLE);
			printf(" *  CH_NAME <- [%s] \n",  rcp_item.sPara__CH_NAME);
			printf(" *  CH_TYPE <- [%1d] \n", rcp_item.iPara__CH_TYPE);
			printf(" *  CH_TITLE <- [%s] \n", rcp_item.sPara__CH_TITLE);
			printf(" * CH_D_LIST <- [%s] \n", rcp_item.sPara__CH_D_LIST);
			printf(" * CH_RANGE_MIN <- [%s] \n", rcp_item.sPara__CH_RANGE_MIN);
			printf(" * CH_RANGE_MAX <- [%s] \n", rcp_item.sPara__CH_RANGE_MAX);
			printf(" * CATEGORY <- [%1d] \n", rcp_item.bPara__CATEGORY_ACTIVE);
			printf(" *   D_LIST <- [%s] \n",  rcp_item.sPara__D_LIST);
			printf(" *   A_LIST <- [%s] \n",  rcp_item.sPara__A_LIST);
			printf("===================================================== \n");
			*/

			Add__ITEM_INFO(rcp_item);
		}
	}

	printf("\n");
	return 1;
}

