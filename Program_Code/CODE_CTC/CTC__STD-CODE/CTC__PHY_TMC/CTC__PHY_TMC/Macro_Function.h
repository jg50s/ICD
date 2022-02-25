#pragma once


extern int  Macro__LLx_ID(const CString& ll_name);

extern int  Macro__Check_Material_Status(const CString& material_sts);
extern int  Macro__Analyze_Title_Info(const CString& title,int& wfr_ptn,int& wfr_slot);

extern int  Macro__Get_Date_Time(CString& date_time);
extern void Macro__Get_DateTime(CString& str_date, CString& str_time);

extern CString Macro__Get_Current_Date();
extern CString Macro__Get_Current_Time();

