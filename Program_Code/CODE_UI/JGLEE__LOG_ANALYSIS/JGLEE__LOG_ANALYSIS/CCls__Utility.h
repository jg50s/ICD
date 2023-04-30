#pragma once

#include "afxwin.h"


class CCls__ReSize
{
private:
	CDialog* pDLG;

	int iDLG__X_Offset;
	int iDLG__Y_Offset;
	double dDLG__Width;
	double dDLG__Height;

	CUIntArray iList__RES_ID;
	CUIntArray iList__RES_LLIMIT;
	CUIntArray iList__RES_RLIMIT;
	CUIntArray iList__RES_LSIDE_SPACE;
	CUIntArray iList__RES_RSIDE_SPACE;

	CUIntArray iList__POS_SX;
	CUIntArray iList__POS_SY;
	CUIntArray iList__POS_EX;
	CUIntArray iList__POS_EY;

	int _Check_ResID(const int res_id);

public:
	CCls__ReSize();
	~CCls__ReSize();

	// ...
	void Link_Dlg(CDialog* p_dlg);

	void Link_ResID(const int res_id);
	void Link_ResID__LLimit(const int res_id, const int llimit, const int left_space = 0, const int right_space = 0);
	void Link_ResID__RLimit(const int res_id, const int rlimit, const int left_space = 0, const int right_space = 0);
	
	int  Get_ResID__LLimit(const int res_id);
	void Change_ResID__LLimit(const int res_id, const int llimit, const int left_space = 0, const int right_space = 0);
	void Change_ResID__RLimit(const int res_id, const int rlimit, const int left_space = 0, const int right_space = 0);

	void Init_Position();
	void Move_Position(const POINT p_st,const POINT p_et, const bool x_resize = true,const bool y_resize = true);
};
