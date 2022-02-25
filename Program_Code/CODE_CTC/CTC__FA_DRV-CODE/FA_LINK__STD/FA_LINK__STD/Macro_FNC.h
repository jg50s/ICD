#pragma once


extern void Macro__Get_ERRTEXT_From_ERRCODE(const int errcode,CString& errtext);

extern CString Macro__Get_Date_Time();

extern int  Macro__Make_File_Data(const CString& file_path, 
								  const CString& file_data,
								  const bool open_mode);
