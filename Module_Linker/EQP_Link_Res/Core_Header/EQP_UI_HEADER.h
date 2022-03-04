#pragma once


//-----------------------------------------------------------------------
//------------------------------------------------------
#define  OBJECT_TYPE__STD							1
#define  OBJECT_TYPE__IO							2
#define  OBJECT_TYPE__MODULE						3
#define  OBJECT_TYPE__INTERLOCK						4
#define  OBJECT_TYPE__FA							5
#define  OBJECT_TYPE__ALARM							6
#define  OBJECT_TYPE__LOOKUP_TABLE					7


#define  VARIABLE_TYPE__FUNCTION					101
#define  VARIABLE_TYPE__OBJECT_DEBUG				102
#define  VARIABLE_TYPE__QUERY						103


#define  VARIABLE_ITEM__ANALOG_STD					1
#define  VARIABLE_ITEM__ANALOG_IO					2

#define  VARIABLE_ITEM__DIGITAL_STD					11
#define  VARIABLE_ITEM__DIGITAL_IO					12

#define  VARIABLE_ITEM__STRING_STD					21
#define  VARIABLE_ITEM__STRING_IO					22

#define  VARIABLE_ITEM__STRING_MODULE				26


#define  VARIABLE_INDEX__CTRL						-1001
#define  VARIABLE_INDEX__MODE						-1002
//------------------------------------------------------


//------------------------------------------------------
class CDS_Alarm__MSG_INFO
{
public:
	CDS_Alarm__MSG_INFO()
	{
		iSYS_ID   = -1;
		iALARM_ID = -1;
		iINTERNAL_ID = -1;
	}
	~CDS_Alarm__MSG_INFO()
	{
		sTITLE   = "";
		sMESSAGE = "";
		sTIME    = "";
		
		sLIST_OPTION_ACT.RemoveAll();
		sLIST_OPTION_EXP.RemoveAll();	
		
		sRECOVERY_RESULT = "";
	}

	// ...
	int iSYS_ID;
	int	iALARM_ID;

	CString sOBJ_NAME;
	int iINTERNAL_ID;

	CString sTITLE;
	CString sMESSAGE;
	CString sTIME;

	CStringArray sLIST_OPTION_ACT;
	CStringArray sLIST_OPTION_EXP;

	CString sRECOVERY_RESULT;

	CString sLEVEL;
};
//------------------------------------------------------
//-----------------------------------------------------------------------

