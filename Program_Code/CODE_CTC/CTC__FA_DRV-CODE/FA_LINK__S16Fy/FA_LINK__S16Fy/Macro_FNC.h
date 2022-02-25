#pragma once


extern int  Macro__Split_String(const CString& str_cmmd,
								 CStringArray& l_str,
								 const char ch_key);

extern int  Macro__Get_PmID_From_String(const CString& str_pm);
extern int  Macro__Get_PmID_And_StepID_And_ParaName(const CString& str_cmmd,
													 int& pm_id,
													 int& step_id,
													 CString& para_name);

extern int  Macro__Check_ID(const int id,const CUIntArray& l_id);
