#pragma once

#include "Button_Image.h"


// ...
class CPart__Cfg_Common : public CButton_Image
{
private:
	int iState;

	bool bBlink_High;

public:
	CPart__Cfg_Common();
	~CPart__Cfg_Common();

	// ...
	CString sDir_IMG;

	// ...
	void Init_Common(CWnd* p_parent_wnd, CDC* p_dc_back);

	// ...
	void Set_Blink();
	void Set_Disable();

	int  Is_Disable();

	void Draw_State();
};


class CPart__Cfg_Refresh : public CPart__Cfg_Common
{
public:
	CPart__Cfg_Refresh();
	~CPart__Cfg_Refresh();

	// ...
	void Init_Resource(CWnd* p_parent_wnd, CDC* p_dc_back);
};

class CPart__Cfg_Search : public CPart__Cfg_Common
{
public:
	CPart__Cfg_Search();
	~CPart__Cfg_Search();

	// ...
	void Init_Resource(CWnd* p_parent_wnd, CDC* p_dc_back);
};
class CPart__Cfg_Undo : public CPart__Cfg_Common
{
public:
	CPart__Cfg_Undo();
	~CPart__Cfg_Undo();

	// ...
	void Init_Resource(CWnd* p_parent_wnd, CDC* p_dc_back);
};
class CPart__Cfg_Save : public CPart__Cfg_Common
{
public:
	CPart__Cfg_Save();
	~CPart__Cfg_Save();

	// ...
	void Init_Resource(CWnd* p_parent_wnd, CDC* p_dc_back);
};
