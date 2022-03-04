#pragma once


class CI_MODULE_PROPERTY_CTRL
{
public:
	virtual ~CI_MODULE_PROPERTY_CTRL(){};

	//----------------------------------------------------
	virtual int Set_Current_PM(int pm_id) = 0;
	virtual int Get_Current_PM() = 0;

	virtual int Get_Root_Driver(CString& data) = 0;
	virtual int Get_Dir_Root(CString& data) = 0;
	virtual int Get_Dir_Config(CString& data) = 0;
	virtual int Get_Dir_Datalog(CString& data) = 0;
	virtual int Get_Dir_Process(CString& data) = 0;

	virtual int Get_Data_Of_Rename(const CString& rename,CString& data) = 0;
};
