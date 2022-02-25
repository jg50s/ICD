#pragma once


// ...
extern int Macro__Get_PMx_INDEX(const CString& str_name);
extern int Macro__Get_LLx_INDEX(const CString& str_name);

extern int Macro__LLx_ID(const CString& ll_name);
extern int Macro__LPx_ID(const CString& lp_name);
extern int Macro__STx_ID(const CString& st_name);
extern int Macro__ALx_ID(const CString& al_name);

extern int Macro__Get_Wafer_Info(const CString& wfr_title, int& lp_id,int& lp_slot);

extern CString Macro__Get_Current_Date();
extern CString Macro__Get_Current_Time();

