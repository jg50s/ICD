#include "StdAfx.h"
#include "CObj__LBx_ManiFold_X.h"
#include "CObj__LBx_ManiFold_X__DEF.h"


//----------------------------------------------------------------------------------------------------
int  CObj__LBx_ManiFold_X
::Call__PICK_READY(CII_OBJECT__VARIABLE* p_variable)
{
	printf(" * [%s] PICK_READY - Start ... \n", sObject_Name);

	// ...
	CString ch_slot;

	aCH__PARA_HANDSHAKE_SLOT->Get__DATA(ch_slot);
	printf(" ** Handshake Slot <- %s \n", ch_slot);

	// ...
	{

	}

	printf(" * [%s] PICK_READY - End ... \n", sObject_Name);
	return 1;
}
int  CObj__LBx_ManiFold_X
::Call__PICK_EXTEND(CII_OBJECT__VARIABLE* p_variable)
{
	printf(" * [%s] PICK_EXTEND - Start ... \n", sObject_Name);

	// ...
	CString ch_slot;

	aCH__PARA_HANDSHAKE_SLOT->Get__DATA(ch_slot);
	printf(" ** Handshake Slot <- %s \n", ch_slot);

	// ...
	{

	}

	printf(" * [%s] PICK_EXTEND - End ... \n", sObject_Name);
	return 1;
}
int  CObj__LBx_ManiFold_X
::Call__PICK_COMPLETE(CII_OBJECT__VARIABLE* p_variable)
{
	printf(" * [%s] PICK_COMPLETE - Start ... \n", sObject_Name);

	// ...
	CString ch_slot;

	aCH__PARA_HANDSHAKE_SLOT->Get__DATA(ch_slot);
	printf(" ** Handshake Slot <- %s \n", ch_slot);

	// ...
	{

	}

	printf(" * [%s] PICK_COMPLETE - End ... \n", sObject_Name);
	return 1;
}


// ...
int  CObj__LBx_ManiFold_X
::Call__PLACE_READY(CII_OBJECT__VARIABLE* p_variable)
{
	printf(" * [%s] PLACE_READY - Start ... \n", sObject_Name);

	// ...
	CString ch_slot;

	aCH__PARA_HANDSHAKE_SLOT->Get__DATA(ch_slot);
	printf(" ** Handshake Slot <- %s \n", ch_slot);

	// ...
	{

	}

	printf(" * [%s] PLACE_READY - End ... \n", sObject_Name);
	return 1;
}
int  CObj__LBx_ManiFold_X
::Call__PLACE_EXTEND(CII_OBJECT__VARIABLE* p_variable)
{
	printf(" * [%s] PLACE_EXTEND - Start ... \n", sObject_Name);

	// ...
	CString ch_slot;

	aCH__PARA_HANDSHAKE_SLOT->Get__DATA(ch_slot);
	printf(" ** Handshake Slot <- %s \n", ch_slot);

	// ...
	{

	}

	printf(" * [%s] PLACE_EXTEND - End ... \n", sObject_Name);
	return 1;
}
int  CObj__LBx_ManiFold_X
::Call__PLACE_COMPLETE(CII_OBJECT__VARIABLE* p_variable)
{
	printf(" * [%s] PLACE_COMPLETE - Start ... \n", sObject_Name);

	// ...
	CString ch_slot;

	aCH__PARA_HANDSHAKE_SLOT->Get__DATA(ch_slot);
	printf(" ** Handshake Slot <- %s \n", ch_slot);

	// ...
	{

	}

	printf(" * [%s] PLACE_COMPLETE - End ... \n", sObject_Name);
	return 1;
}

