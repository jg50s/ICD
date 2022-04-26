#include "StdAfx.h"



CString Macro__Get_Parity(const int parity_mode)
{
	if(parity_mode == 0)		return "None";
	if(parity_mode == 1)		return "Odd";
	if(parity_mode == 2)		return "Even";
	if(parity_mode == 3)		return "Mark";
	if(parity_mode == 4)		return "Space";

	return "Unknown";
}
