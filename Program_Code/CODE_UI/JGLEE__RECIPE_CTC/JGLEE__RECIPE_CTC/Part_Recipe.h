#pragma once

#include "Button_Image.h"


// ...
class CPart__Rcp_Common : public CButton_Image
{
private:
	int iState;

	bool bBlink_High;

public:
	CPart__Rcp_Common();
	~CPart__Rcp_Common();

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


class CPart__Rcp_New : public CPart__Rcp_Common
{
public:
	CPart__Rcp_New();
	~CPart__Rcp_New();

	// ...
	void Init_Resource(CWnd* p_parent_wnd, CDC* p_dc_back);
};
class CPart__Rcp_Undo : public CPart__Rcp_Common
{
public:
	CPart__Rcp_Undo();
	~CPart__Rcp_Undo();

	// ...
	void Init_Resource(CWnd* p_parent_wnd, CDC* p_dc_back);
};
class CPart__Rcp_Save : public CPart__Rcp_Common
{
public:
	CPart__Rcp_Save();
	~CPart__Rcp_Save();

	// ...
	void Init_Resource(CWnd* p_parent_wnd, CDC* p_dc_back);
};
class CPart__Rcp_SaveAs : public CPart__Rcp_Common
{
public:
	CPart__Rcp_SaveAs();
	~CPart__Rcp_SaveAs();

	// ...
	void Init_Resource(CWnd* p_parent_wnd, CDC* p_dc_back);
};
class CPart__Rcp_Delete : public CPart__Rcp_Common
{
public:
	CPart__Rcp_Delete();
	~CPart__Rcp_Delete();

	// ...
	void Init_Resource(CWnd* p_parent_wnd, CDC* p_dc_back);
};
