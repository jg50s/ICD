#pragma once

#include "afxwin.h"


#define  _BTN__LDOWN          WM_USER + 1
#define  _BTN__LUP            WM_USER + 2


class CButton_Image : public CButton 
{
	// Construction
public:
	CButton_Image();

	// Attributes
public:

private:
	CWnd* pParent_Wnd;
	
	HBITMAP hBit_Up;
	HBITMAP hBit_Down;
	HBITMAP hBit_Active;
	HBITMAP hBit_Disable;

	int iCurrent_State;

	CDC* pDC_Scr;
	CDC* pDC_Back;
	CDC* pDC_Mem;

	BOOL bOnwer_Draw;
	bool mButton_Notify;

	BOOL bMask_Use;
	COLORREF mMask_Color;

	POINT mPT_XY;
	POINT mPT_CS;

	int iInit__Set_Pos;

	// Operations
public:
	void Set__Owner_Draw();
	void Set__Mask_Color(COLORREF mask_color);

	void Enable__Button_Notify();
	void Disable__Button_Notify();

	void Link_Resource(CWnd* p_upper_wnd, CDC* p_cdc_back, CDC* p_dc_mem = NULL);

	void Set_Position(const CWnd* p_parent_wnd, 
					  int x,  int y, 
					  int cx, int cy, 
					  UINT n_flag);
	void Set_Position(const CWnd* p_parent_wnd, 
					  UINT n_flag);

	//
	void Link_Bitmap__Up_State(const CString& bitmap_path);
	void Link_Bitmap__Down_State(const CString& bitmap_path);
	void Link_Bitmap__Active_State(const CString& bitmap_path);
	void Link_Bitmap__Disable_State(const CString& bitmap_path);

	void Link_Bitmap__Up_State(const int bitmap_id);
	void Link_Bitmap__Down_State(const int bitmap_id);
	void Link_Bitmap__Active_State(const int bitmap_id);
	void Link_Bitmap__Disable_State(const int bitmap_id);

	//
	void Draw__Buttn_State();
	void Draw__Up_State();
	void Draw__Down_State();
	void Draw__Active_State();
	void Draw__Disable_State();
	void Draw__Background();

	int  Is__Disable_State();
	int  Is__Active_State();
	int  Is__Up_State();
	int  Is__Down_State();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButton_Image)
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CButton_Image();

	// Generated message map functions
protected:
	//{{AFX_MSG(CButton_Image)
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	void DrawItem();
};

