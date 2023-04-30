#include "stdafx.h"
#include "Dlg__Route_STD__DB_Info.h"


// ...
_DB_Info__Category::_DB_Info__Category()
{
	InitializeCriticalSection(&mCS_LOCK);

}
_DB_Info__Category::~_DB_Info__Category()
{
	Init_DB();

	DeleteCriticalSection(&mCS_LOCK);
}

// ...
int _DB_Info__Category::
Load__Module_Info(const _DB_Info__Module& db_info)
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	{
		_DB_Info__Module *p_info = new _DB_Info__Module;
		pList_Module.Add(p_info);

		p_info->sTitle = db_info.sTitle;
		p_info->sList_Para.Copy(db_info.sList_Para);
	}

	LeaveCriticalSection(&mCS_LOCK);
	return 1;
}

int _DB_Info__Category::
Get__Module_Size()
{
	EnterCriticalSection(&mCS_LOCK);

	int i_size = pList_Module.GetSize();

	LeaveCriticalSection(&mCS_LOCK);
	return i_size;
}
_DB_Info__Module* _DB_Info__Category::
Get__Module_Info(const int db_index)
{
	EnterCriticalSection(&mCS_LOCK);

	_DB_Info__Module *p_db = NULL;

	if((db_index >= 0)
	&& (db_index < pList_Module.GetSize()))
	{
		p_db = (_DB_Info__Module *) pList_Module[db_index];
	}

	LeaveCriticalSection(&mCS_LOCK);
	return p_db;
}


// ...
int _DB_Info__Category::
Init_DB()
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	{
		sTitle = "";

		int i_limit = pList_Module.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			_DB_Info__Module *p_db
				= (_DB_Info__Module *) pList_Module[i];

			delete p_db;
		}
		pList_Module.RemoveAll();
	}

	LeaveCriticalSection(&mCS_LOCK);
	return 1;
}

int _DB_Info__Category::
Copy_From(_DB_Info__Category& db_info)
{
	// ...
	{
		sTitle = db_info.sTitle;

		int i_limit = db_info.Get__Module_Size();
		int i;

		for(i=0; i<i_limit; i++)
		{
			_DB_Info__Module *p_info = db_info.Get__Module_Info(i);

			Load__Module_Info(*p_info);
		}
	}
	return 1;
}
