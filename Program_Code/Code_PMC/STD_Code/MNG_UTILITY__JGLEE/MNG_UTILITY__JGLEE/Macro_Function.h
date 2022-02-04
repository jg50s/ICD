#pragma once


// ...
extern int Macro__Check_1Point(const CString& str_data,int& check_percent);

extern CString Macro__Get_String_Without_KeyChar(const CString& src_word, const CStringArray& l_keyword, const CStringArray& l_keydata);
extern void Macro__Get_Date(CString& date, CString& time);

extern int Macro__Convert_String_To_Array(const CString& str_data, CStringArray& l_data);
extern int Macro__Convert_String_To_String(const CString& str_data, CString& data1, CString& data2);

