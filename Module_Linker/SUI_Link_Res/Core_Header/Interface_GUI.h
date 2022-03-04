#pragma once

#include "Afxwin.h"


//------------------------------------------------------------------------------------
class CInterface_GUI : public CWinThread
{
public:
	CStringArray	mParameter;
	CStringArray	mData;
	CStringArray	mID;

	CString			mFeedback_Command;
	CString			mFeedback_Channel1;
	CString			mFeedback_Data1;
	CString			mFeedback_Channel2;
	CString			mFeedback_Data2;
	CString			mFeedback_Channel3;
	CString			mFeedback_Data3;
	CString			mFeedback_Channel4;
	CString			mFeedback_Data4;
	CString			mFeedback_Channel5;
	CString			mFeedback_Data5;

	CString			mTimer_Command;
	CString			mTimer_Channel1;
	CString			mTimer_Data1;
	CString			mTimer_Channel2;
	CString			mTimer_Data2;
	CString			mTimer_Channel3;
	CString			mTimer_Data3;
	CString			mTimer_Channel4;
	CString			mTimer_Data4;
	CString			mTimer_Channel5;
	CString			mTimer_Data5;

	CString         mGui_Root;

	CString			mDir_Root;
	CString			mDir_Recipe;
	CString			mDir_Datalog;
	CString			mDir_Config;
	CString			mScreen_Name;
	CString			mPage_Type;
	CString			mString;


	POINT			mSt;
	POINT			mEt;
	
	HWND			mHWND;
	HDC				mHDC;
	HDC				mHDC_Back;
	HDC				mHDC_Mem;
	POINT			mMouse_Pt;

	//---------------------------------------------------------
	virtual int Get_Property() = 0;
	virtual int Interface_Show() = 0;
	virtual int Interface_Init() = 0;
	virtual int Interface_Parameter() = 0;
	virtual int Interface_Delete() = 0;
	virtual int Interface_EditTimer() = 0;

	virtual int WM_Timer() = 0;
	virtual int WM_LButtonDown() = 0;
	virtual int WM_LButtonUp()   = 0;
	virtual int WM_RButtonDown() = 0;
	virtual int WM_RButtonUp()   = 0;
	virtual int WM_MouseMove()	 = 0;
};

class CDS_GUI__FEEDBACK_INFO
{
public:
	CString	     sFEEDBACK_COMMAND;
	CStringArray sFEEDBACK_CHANNEL;
	CStringArray sFEEDBACK_DATA;
};

class CDS_GUI__RES_INFO
{
public:
	HWND  hHWND;
	HDC	  hDC;
	HDC	  hDC_Back;
	HDC	  hDC_Mem;
};

class CInterface_GUI_Ex
{
public:
	//---------------------------------------------------------
	virtual int Interface_Parameter(const int& module_id,
									const POINT& st,
									const POINT& et,
									const CStringArray& para_list) = 0;

	virtual int Interface_Show(const CDS_GUI__RES_INFO& res_info) = 0;

	virtual int Interface_Hide() = 0;

	
	//---------------------------------------------------------
	virtual int WM_Timer(const CStringArray& data_list,
						 const CDS_GUI__RES_INFO& res_info,
						 CDS_GUI__FEEDBACK_INFO& feedback_info) = 0;

	virtual int WM_SimTimer(const CStringArray& data_list,
							const CDS_GUI__RES_INFO& res_info,
							CDS_GUI__FEEDBACK_INFO& feedback_info) = 0;

	
	virtual int WM_LButtonDown(const POINT& mouse_pt,
							   const int module_id,
							   const CDS_GUI__RES_INFO& res_info,
							   CDS_GUI__FEEDBACK_INFO& feedback_info) = 0;

	virtual int WM_LButtonUp(const CDS_GUI__RES_INFO& res_info) = 0;

	
	virtual int WM_RButtonDown(const POINT& mouse_pt,
							   const CDS_GUI__RES_INFO& res_info) = 0;

	virtual int WM_RButtonUp(const CDS_GUI__RES_INFO& res_info) = 0;

public:
	int iCLEAR_REQ;
};

class CInterface_GUI_Notify
{
public:
	virtual ~CInterface_GUI_Notify(){}; 

	//---------------------------------------------------------
	virtual int Interface_Parameter(const int& module_id,
									const POINT& st,
									const POINT& et,
									const CStringArray& para_list) = 0;
	virtual int Initialize_Data(const CDS_GUI__RES_INFO& res_info) {  return 1;  };
 
	virtual int Interface_Show(const CDS_GUI__RES_INFO& res_info) = 0;
	virtual int Interface_Hide() = 0;

	
	//---------------------------------------------------------
	virtual int WM_Timer(const CStringArray& data_list,
						 const CDS_GUI__RES_INFO& res_info,
						 CDS_GUI__FEEDBACK_INFO& feedback_info) = 0;

	virtual int WM_SimTimer(const CStringArray& data_list,
							const CDS_GUI__RES_INFO& res_info,
							CDS_GUI__FEEDBACK_INFO& feedback_info) = 0;

	
	virtual int WM_LButtonDown(const POINT& mouse_pt,
							   const int module_id,
							   const CDS_GUI__RES_INFO& res_info,
							   CDS_GUI__FEEDBACK_INFO& feedback_info) = 0;

	virtual int WM_LButtonUp(const CDS_GUI__RES_INFO& res_info) = 0;

	
	virtual int WM_RButtonDown(const POINT& mouse_pt,
							   const CDS_GUI__RES_INFO& res_info) = 0;

	virtual int WM_RButtonUp(const CDS_GUI__RES_INFO& res_info) = 0;


	//---------------------------------------------------------
	virtual int WM_Notify(UINT message,WPARAM wparam,LPARAM lparam) = 0;

};
//------------------------------------------------------------------------------------
