#pragma once


// ...
#define _DEF_ALx__MAX				1
#define _DEF_LLx__MAX				2
#define _DEF_PMx__MAX				6
#define _DEF_STx__MAX				3

// ...
#define _LIST__MODULE				0
#define _LIST__ALx					1
#define _LIST__LLx_IN				2
#define _LIST__PROCESSx				3
#define _LIST__LLx_OUT				4
#define _LIST__STx					5

#define _LIST__LLx_PROC             6
#define _LIST__LOOPx_PROC           7

// ...
#define _EDIT__ROUTE				0
#define _EDIT__ALx					1
#define _EDIT__LLx_IN				2
#define _EDIT__PROCESS_XX			3
#define _EDIT__LLx_OUT				4
#define _EDIT__STx_XX				5

#define _EDIT__LLx_PROC             6
#define _EDIT__LOOPx_PROC           7

// ...
#define _SEL_ID__ALx				100
#define _SEL_ID__LLx				200
#define _SEL_ID__PMx				300
#define _SEL_ID__STx				400

#define _SEL_ID__LLx_PROC           500
#define _SEL_ID__LOOPx_PROC         600


class CDB__Module_Info
{
public:
	CDB__Module_Info()
	{

	}

	// ...
	CString sTitle;
	int iImg_ID;
	int iSel_ID;

	CStringArray sList_Item;
	CUIntArray iList_ImgID;
	CUIntArray iList_SelID;
};
class CDB__Category_Info
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CPtrArray pList_Module;		// CDB__Module_Info

public:
	CString sTitle;
	int iImg_ID;
	int iSel_ID;

	// ...
	CDB__Category_Info();
	~CDB__Category_Info();

	int Load__Module_Info(const CDB__Module_Info& db_info);

	int Get__Module_Size();
	CDB__Module_Info* Get__Module_Info(const int db_index);
};


// ...
#define _LLx__MAX							4

#define _ROUTE_TYPE__LLx_IN					1
#define _ROUTE_TYPE__LLx_OUT				2


class CDB__Route_Info
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CPtrArray pList_Category;			// CDB__Category_Info

public:
	CDB__Route_Info();
	~CDB__Route_Info();

	// ...
	int Load__Category_Info(const CString& category_name, 
							const int category_imgid,
							const int category_selid);
	int Load__Module_Info(const CDB__Module_Info& db_info);

	// ...
	int Get__Category_Size();
	CDB__Category_Info* Get__Category_Info(const int c_index);

	// ...
	CString Get__ALx_Of_Route_Info();
	CString Get__LLx_Of_Route_Info(const int ll_type);
	CString Get__STx_Of_Route_Info();	

	CString Get__PROCESSx_Of_Route_Info();
	CString Get__LLx_PROC_Of_Route_Info();	
	CString Get__LOOPx_PROC_Of_Route_Info();	
};

