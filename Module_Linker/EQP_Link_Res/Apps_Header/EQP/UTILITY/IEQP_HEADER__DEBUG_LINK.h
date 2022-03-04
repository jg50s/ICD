#pragma once


#ifdef _DEBUG
	#pragma comment(lib, "C:\\Module_Linker\\EQP_Link_Res\\EQP_Lib\\EQP__Debug_Link_D.lib")
#else
	#pragma comment(lib, "C:\\Module_Linker\\EQP_Link_Res\\EQP_Lib\\EQP__Debug_Link_R.lib")
#endif


class SCI__CONSOLE_CTRL
{
public:
	virtual ~SCI__CONSOLE_CTRL(){};
	
	// ...
	virtual int Create_Console() = 0;
	virtual int Delete_Console() = 0;

	// ...
	virtual int Clear_Screen() = 0;

	virtual int Change_Current_Mode_To_Debug_Mode() = 0;
	virtual int Exit_Current_Mode() = 0;

	// Engine Message Control ... 
	virtual int Link__Engine_Object(const CString& obj_name) = 0;
	virtual CString Get__Link_Engine_Object_Name() = 0;
	
	virtual int Enable__Engine_Object() = 0;
	virtual int Disable__Engine_Object() = 0;

	virtual int Print__Engine_Message(const CString& str_msg) = 0;

	// Engine Log Control ...
	virtual int Enable__Engine_All_Object() = 0;
	virtual int Disable__Engine_All_Object() = 0;
	virtual int Control__Engine_All_Object() = 0;

	// Application Log Control ...
	virtual int Enable__Application_All_Object() = 0;
	virtual int Disable__Application_All_Object() = 0;
	virtual int Control__Application_All_Object() = 0;
};

class SCI__DEBUG_CTRL
{
public:
	virtual ~SCI__DEBUG_CTRL(){};

	// ...
	virtual int Link__Object(const CString& obj_name) = 0;
	virtual CString Get__Link_Object_Name() = 0;
	
	virtual int Enable__Object() = 0;
	virtual int Disable__Object() = 0;
	
	virtual int Print__Message(const CString& log_msg) = 0;
};
