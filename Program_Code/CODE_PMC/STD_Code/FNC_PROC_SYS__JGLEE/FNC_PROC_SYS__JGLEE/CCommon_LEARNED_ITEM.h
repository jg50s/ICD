#pragma once

#include "Interface_Code.h"


#define  _DEF_SIZE__LEARNED_ITEM			10


class CDS__LEARNED_STEP_DATA
{
public:
	int iSTEP_ID;

	CString sSTR__IO_TITLE;
	CString sSTR__RCP_NAME;
	CString sSTR__IO_RESULT;
};

class CDS__LEARNED_IO_ITEM
{
public:
	CString sSTR__IO_TITLE;
	CString sSTR__RCP_NAME;
	CX__VAR_STRING_CTRL mCH__IO_RESULT;
};
class CDS__LEARNED_STEP_ITEM
{
public:
	int iSTEP_ID;

	CString sSTR__IO_TITLE;
	CString sSTR__RCP_NAME;
	CString sSTR__IO_RESULT;

	//
	void Copy_To(CDS__LEARNED_STEP_DATA* p_data)
	{
		p_data->iSTEP_ID = iSTEP_ID;
		
		p_data->sSTR__IO_TITLE  = sSTR__IO_TITLE;
		p_data->sSTR__RCP_NAME  = sSTR__RCP_NAME;
		p_data->sSTR__IO_RESULT = sSTR__IO_RESULT;
	}
};

class CDS__LEARNED_ITEM_CTRL
{
public:
	CPtrArray pList__IO_ITEM;
	CPtrArray pList__STEP_ITEM;

	//
	~CDS__LEARNED_ITEM_CTRL()
	{
		Clear__IO_ITEM();
		Init__STEP_ITEM();
	}

	//
	int Load__IO_ITEM(CII_EXT_OBJECT__CREATE *p_ext_obj_create, 
					  const CString& io_title,
					  const CString& rcp_name, 
					  const CString& io_obj,  
					  const CString& io_var)
	{
		int i_size = pList__IO_ITEM.GetSize();
		if(i_size >= _DEF_SIZE__LEARNED_ITEM)			return -11;

		//
		CDS__LEARNED_IO_ITEM* p_io = new CDS__LEARNED_IO_ITEM;
		pList__IO_ITEM.Add(p_io);

		p_io->sSTR__IO_TITLE = io_title;
		p_io->sSTR__RCP_NAME = rcp_name;
		
		LINK__EXT_VAR_STRING_CTRL(p_io->mCH__IO_RESULT, io_obj,io_var);
		return 1;
	}
	void Clear__IO_ITEM()
	{
		CDS__LEARNED_IO_ITEM *p_io;

		int i_limit = pList__IO_ITEM.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			p_io = (CDS__LEARNED_IO_ITEM*) pList__IO_ITEM[i];
			delete p_io;
		}

		pList__IO_ITEM.RemoveAll();
	}

	// 
	void Init__STEP_ITEM()
	{
		CDS__LEARNED_STEP_ITEM *p_info;

		int i_limit = pList__STEP_ITEM.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			p_info = (CDS__LEARNED_STEP_ITEM*) pList__STEP_ITEM[i];
			delete p_info;
		}

		pList__STEP_ITEM.RemoveAll();
	}

	void Load__ITEM(const int step_id)
	{
		int i_limit = pList__IO_ITEM.GetSize();
		
		for(int i=0; i<i_limit; i++)
		{
			CDS__LEARNED_IO_ITEM* p_io = (CDS__LEARNED_IO_ITEM*) pList__IO_ITEM[i];

			//
			CDS__LEARNED_STEP_ITEM *p_step = new CDS__LEARNED_STEP_ITEM;
			pList__STEP_ITEM.Add(p_step);

			p_step->iSTEP_ID = step_id;
			p_step->sSTR__IO_TITLE  = p_io->sSTR__IO_TITLE;
			p_step->sSTR__RCP_NAME  = p_io->sSTR__RCP_NAME;
			p_step->sSTR__IO_RESULT = p_io->mCH__IO_RESULT->Get__STRING();
		}
	}
	int Get__STEP_DATA(const int db_index, CDS__LEARNED_STEP_DATA* p_data)
	{
		if(db_index < 0)								return -11;
		if(db_index >= pList__STEP_ITEM.GetSize())		return -12;

		//
		CDS__LEARNED_STEP_ITEM *p_step = (CDS__LEARNED_STEP_ITEM*) pList__STEP_ITEM[db_index];

		p_step->Copy_To(p_data);
		return 1;
	}
};

