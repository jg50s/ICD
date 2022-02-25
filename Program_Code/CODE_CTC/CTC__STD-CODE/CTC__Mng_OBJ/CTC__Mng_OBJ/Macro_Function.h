#pragma once


// ...
extern int  Macro__Get_SeqID_From_String(const CString& str_name);
extern int  Macro__Check_String(const CString& cmp_str,const CStringArray& l_str);

extern CString Macro__Get_String_Without_KeyChar(const CString& src_word,const CStringArray& l_keyword,const CStringArray& l_keydata);


// ...
extern int  MACRO__Get_Line_List_From_File_Data(const CString& file_data, CStringArray& l_line);
extern int  MACRO__Get_File_Data(const CString& file_path, CString& file_data);

extern void MACRO__Convert__LIST(const char parc, const CString& string, CStringArray& data_list, const int array_max);


// ...
extern CString MACRO__Get_Alarm_Level(const int alm_level);

