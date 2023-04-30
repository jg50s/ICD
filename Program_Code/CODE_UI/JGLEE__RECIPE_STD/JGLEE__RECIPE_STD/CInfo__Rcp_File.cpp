#include "stdafx.h"
#include "CInfo__Rcp_File.h"

#include "Macro_Function.h"


// ...
void CInfo__Rcp_File::
Clear__RCP_INFO()
{
	mCtrl__Step_DB.Clear__Step_DB();

	if(pI_Rcp_Interlock_Ctrl != NULL)
	{
		pI_Rcp_Interlock_Ctrl->Set__CHANNEL_OF_SUB_PAGE(iMODULE_ID, 0, "","");
	}
}
void CInfo__Rcp_File::
Add__NEW_STEP_OF_RCP_INFO(const CStringArray& l_ch_name,
						  const CUIntArray& l_ch_type,
						  const CStringArray& l_io_list)
{
	int step_id = 1;

	int i_limit = l_ch_name.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString ch_name = l_ch_name[i];
		int     ch_type = l_ch_type[i];
		CString ch_data = "";

		if(ch_type == _CH_TYPE__ANALOG)
		{
			ch_data = "0";
		}
		else if(ch_type == _CH_TYPE__DIGITAL)
		{
			CString str_list = l_io_list[i];

			CStringArray l_data;
			char ch_dist = '/';

			MACRO__Convert__LIST(ch_dist, str_list, l_data);

			if(l_data.GetSize() > 0)		ch_data = l_data[0];

			printf(" * ch_name <- %s \n", ch_name);
			printf("  ** str_list <- %s \n", str_list);
		}

		mCtrl__Step_DB.Load__Step_Info(step_id, ch_name,ch_type,ch_data);

		if(pI_Rcp_Interlock_Ctrl != NULL)
		{
			pI_Rcp_Interlock_Ctrl->Set__CHANNEL_OF_SUB_PAGE(iMODULE_ID, step_id, ch_name,ch_data);
		}
	}
}

void CInfo__Rcp_File::
Append__STEP_ID(const int step_id, const int next_id)
{
	int st_copy;

	if(next_id < 0)			st_copy = mCtrl__Step_DB.Get__Step_Size() + 1;
	else					st_copy = next_id;

	mCtrl__Step_DB.Append__Step_Info(step_id, st_copy);

	if(pI_Rcp_Interlock_Ctrl != NULL)
	{
		pI_Rcp_Interlock_Ctrl->Call__STEP_COPY(iMODULE_ID, step_id, st_copy);
	}
}
void CInfo__Rcp_File::
Move__STEP_ID(const int step_id, const int next_id)
{
	mCtrl__Step_DB.Move__Step_Info(step_id, next_id);

	if(pI_Rcp_Interlock_Ctrl != NULL)
	{
		pI_Rcp_Interlock_Ctrl->Call__STEP_MOVE(iMODULE_ID, step_id, next_id);
	}
}
void CInfo__Rcp_File::
Delete__STEP_ID(const int step_id)
{
	mCtrl__Step_DB.Delete__Step_Info(step_id);

	if(pI_Rcp_Interlock_Ctrl != NULL)
	{
		pI_Rcp_Interlock_Ctrl->Call__STEP_DELETE(iMODULE_ID, step_id);
	}
}

// ...
int  CInfo__Rcp_File::
Upload__RCP_FILE(const HWND hwnd, const CString& rcp_path)
{
	Clear__RCP_INFO();

	// ...
	CString file_data;

	// ...
	{
		// printf(" * Upload__RCP_FILE() <- [%s] \n", rcp_path);

		FILE *fp = fopen(rcp_path, "r");
		if(fp == NULL)
		{
			MessageBox(hwnd, rcp_path, "PM_Undo() : File Path - Error !", MB_OK|MB_TOPMOST);
			return -1;
		}

		fseek(fp,0,SEEK_END);
		int totalbytes = ftell(fp);

		char *p_file = new char[totalbytes+1];
		if(p_file == NULL)
		{
			fclose(fp);

			MessageBox(hwnd, rcp_path, "PM_Undo() : File Memory Allocation - Error !", MB_OK|MB_TOPMOST);
			return -2;
		}

		rewind(fp);

		// ...
		int numread = fread(p_file,1,totalbytes,fp);
		p_file[numread] = 0;

		fclose(fp);

		file_data = p_file;
		delete [] p_file;
	}

	/*
	printf("================================================\n");
	printf("%s \n", file_data);
	printf("================================================\n\n");
	*/

	// ...
	sPara__ITEM_TYPE    = "";
	sPara__ITEM_CHANNEL = "";
	sPara__ITEM_DATA    = "";

	iPara__ITEM_COUNT = 0;
	iPara__ITEM_STATE = 0;
	iPara__ITEM_STEP  = 0;

	// ...
	CString word;
	int flag;

	int limit = file_data.GetLength();
	int i;

	for(i=0; i<limit; i++)
	{
		char ch = file_data.GetAt(i);

		if((ch != '^')
		&& (ch != ',')
		&& (ch != ';')
		&& (ch != '\n'))
		{
			word += ch;
		}
		else
		{	
			if((ch == '^')||(ch == ',')||(ch == ';'))
			{
				flag = _PM_Compile(ch,word);
			}	
			word = "";

			if(ch == ';')
			{
				if(flag == 102)
				{
					_PM_Load(iPara__ITEM_STEP, sPara__ITEM_TYPE,sPara__ITEM_CHANNEL,sPara__ITEM_DATA);
				}

				sPara__ITEM_TYPE    = "";
				sPara__ITEM_CHANNEL = "";
				sPara__ITEM_DATA    = "";
			}
		}
	}	

	return 1;
}

int  CInfo__Rcp_File::
_PM_Compile(const char& ch, 
			const CString& word)
{
	if(word.CompareNoCase("@") == 0)
	{
		iPara__ITEM_STEP++;
		iPara__ITEM_COUNT = 0;
		iPara__ITEM_STATE = 0;

		_PM_Init(iPara__ITEM_STEP);
		return 1;
	}
	if(word.CompareNoCase("&") == 0)
	{
		iPara__ITEM_COUNT = 0;
		iPara__ITEM_STATE = 1;
		return 1;
	}
	if(word.CompareNoCase("#DESCRIPT") == 0)
	{
		iPara__ITEM_COUNT = 0;
		iPara__ITEM_STATE = 2;
		return 1;
	}

	if(iPara__ITEM_STATE == 1)
	{
			 if(iPara__ITEM_COUNT == 0)			sPara__ITEM_TYPE    = word;
		else if(iPara__ITEM_COUNT == 1)			sPara__ITEM_CHANNEL = word;
		else if(iPara__ITEM_COUNT == 2)
		{
			sPara__ITEM_DATA = word;
			return 102;
		}

		iPara__ITEM_COUNT++;
		return 1;
	} 
	if(iPara__ITEM_STATE == 2)
	{
		/*
		sRCP__Description += word;

			 if(ch == ',')			sRCP__Description += ",";
		else if(ch == '^')			sRCP__Description += "\r\n";
		*/
	}

	return 1000;
}
int  CInfo__Rcp_File::
_PM_Load(const int step_id,
		 const CString& ch_type,
		 const CString& ch_name,
		 const CString& ch_data)
{
	if(step_id < 1)
	{
		return -1;
	}

	// ...
	{
		int i_type = _CH_TYPE__STRING;

		     if(ch_type.CompareNoCase("ANALOG")  == 0)		i_type = _CH_TYPE__ANALOG;
		else if(ch_type.CompareNoCase("DIGITAL") == 0)		i_type = _CH_TYPE__DIGITAL;

		mCtrl__Step_DB.Load__Step_Info(step_id, ch_name,i_type,ch_data);
	}

	// Sub Parameter ...
	if(pI_Rcp_Interlock_Ctrl != NULL)
	{
		if(pI_Rcp_Interlock_Ctrl->Set__CHANNEL_OF_SUB_PAGE(iMODULE_ID, step_id, ch_name,ch_data) > 0)
		{
			return 1;
		}
	}

	return 1;
}
void CInfo__Rcp_File::
_PM_Init(const int step_id)
{
	if(step_id < 1)			return;

	// ...
	int index = step_id - 1;

	if(index == 0)
	{
		if(pI_Rcp_Interlock_Ctrl != NULL)
		{
			pI_Rcp_Interlock_Ctrl->Set__CHANNEL_OF_SUB_PAGE(iMODULE_ID, 0, "","");
		}
	}
}


int CInfo__Rcp_File::Get__Step_Size()
{
	return mCtrl__Step_DB.iList__STEP_ID.GetSize();
}

CString CInfo__Rcp_File::Get__Step_Data(const int step_id, const CString& ch_name)
{
	return mCtrl__Step_DB.Get__Step_Data(step_id, ch_name);
}
void CInfo__Rcp_File::Set__Step_Data(const int step_id, const int ch_type, const CString& ch_name, const CString& ch_data)
{
	mCtrl__Step_DB.Set__Step_Data(step_id, ch_type, ch_name, ch_data);
}
