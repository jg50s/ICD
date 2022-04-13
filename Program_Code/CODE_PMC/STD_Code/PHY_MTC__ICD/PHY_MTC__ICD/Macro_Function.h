#pragma once


extern CString Macro__Get_Date();
extern CString Macro__Get_Month();
extern void Macro__Get_Date(CString& date, CString& time);

extern int Macro__Get_StringArrray_From_String(const CString& str_org_data,const CString& str_sep,CStringArray& l_data);
extern int Macro__Get_Hexa_From_String(const CString& xxx_data);

