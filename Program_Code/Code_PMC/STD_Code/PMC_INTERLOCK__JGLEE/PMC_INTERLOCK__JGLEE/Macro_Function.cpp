#include "stdafx.h"
#include "Macro_Function.h"


void _Macro__Get_Channel_To_Obj_Variable(const CString& ch_name, CString& obj_name,CString& var_name)
{
	obj_name = ch_name;
	var_name = "";

	int s_index = ch_name.Find("+");
	if(s_index < 0)		return;

	int ch_len = ch_name.GetLength();
	var_name = ch_name;

	obj_name.Delete(s_index, ch_len-s_index);
	var_name.Delete(0, s_index+1);
}
