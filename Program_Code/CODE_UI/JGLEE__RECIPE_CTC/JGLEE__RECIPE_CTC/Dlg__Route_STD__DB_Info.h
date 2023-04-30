#pragma once


class _DB_Info__Module
{
public:
	_DB_Info__Module()
	{

	}

	// ...
	CString sTitle;
	CStringArray sList_Para;
};
class _DB_Info__Category
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CPtrArray pList_Module;		

public:
	CString sTitle;

	// ...
	_DB_Info__Category();
	~_DB_Info__Category();

	int Load__Module_Info(const _DB_Info__Module& db_info);

	int Get__Module_Size();
	_DB_Info__Module* Get__Module_Info(const int db_index);

	// ...
	int Init_DB();
	int Copy_From(_DB_Info__Category& dd_info);
};
