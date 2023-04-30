#include "stdafx.h"
#include "Button_Image.h"


#define  _BTN_STATE__UP					1
#define  _BTN_STATE__DOWN				2
#define  _BTN_STATE__ACTIVE				3
#define  _BTN_STATE__DISABLE			4


// ...
CButton_Image::CButton_Image()
{
	pParent_Wnd = NULL;

	hBit_Up      = NULL;
	hBit_Down    = NULL;
	hBit_Active  = NULL;
	hBit_Disable = NULL;

	iCurrent_State = _BTN_STATE__DISABLE;

	pDC_Scr  = NULL;
	pDC_Back = NULL;
	pDC_Mem  = NULL;

	bOnwer_Draw = FALSE;
	mButton_Notify = TRUE;

	bMask_Use = FALSE;
	mMask_Color = RGB(0,0,0);

	// ...
	{
		mPT_XY.x = 0;
		mPT_XY.y = 0;
		mPT_CS.x = 100;
		mPT_CS.y = 100;

		iInit__Set_Pos = -1;
	}
}
CButton_Image::~CButton_Image()
{
}

BEGIN_MESSAGE_MAP(CButton_Image, CButton)
	//{{AFX_MSG_MAP(CButton_Image)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// ...
void CButton_Image::Set__Owner_Draw()
{	
	SetButtonStyle(GetButtonStyle() | BS_OWNERDRAW);
}
void CButton_Image::Set__Mask_Color(COLORREF mask_color)
{
	bMask_Use   = TRUE;
	mMask_Color = mask_color;
}

void CButton_Image::
Enable__Button_Notify()
{
	mButton_Notify = TRUE;
}
void CButton_Image::
Disable__Button_Notify()
{
	mButton_Notify = FALSE;
}

// ...
void CButton_Image::Link_Resource(CWnd* p_upper_wnd, CDC* p_cdc_back, CDC* p_cdc_mem)
{
	if(GetButtonStyle() & BS_OWNERDRAW)				bOnwer_Draw = TRUE;
	else											bOnwer_Draw = FALSE;

	pParent_Wnd = p_upper_wnd;

	pDC_Scr  = p_upper_wnd->GetDC();
	pDC_Back = p_cdc_back;
	pDC_Mem  = p_cdc_mem;
}

void CButton_Image
::Set_Position(const CWnd* p_parent_wnd, 
			   int x,  int y, 
			   int cx, int cy, 
			   UINT n_flag)
{
	mPT_XY.x = x;
	mPT_XY.y = y;
	mPT_CS.x = cx;
	mPT_CS.y = cy;

	SetWindowPos(p_parent_wnd, x,y, cx,cy, n_flag);
}
void CButton_Image
::Set_Position(const CWnd* p_wnd, 
			   UINT n_flag)
{
	if(iInit__Set_Pos < 0)
	{
		iInit__Set_Pos = 1;

		int offset_x = 0;
		int offset_y = 0;

		if(pParent_Wnd != NULL)
		{
			CRect w_rt;
			pParent_Wnd->GetWindowRect(w_rt);

			offset_x = w_rt.left;
			offset_y = w_rt.top;
		}

		CRect win_rt;
		this->GetWindowRect(win_rt);

		mPT_XY.x = win_rt.left - offset_x;
		mPT_XY.y = win_rt.top  - offset_y;
		mPT_CS.x = win_rt.Width();
		mPT_CS.y = win_rt.Height();
	}

	// ...
	{
		int x  = mPT_XY.x;
		int y  = mPT_XY.y;
		int cx = mPT_CS.x;
		int cy = mPT_CS.y;

		SetWindowPos(p_wnd, x,y, cx,cy, n_flag);
	}
}

// ...
void CButton_Image::Link_Bitmap__Up_State(const CString& bitmap_path)
{
	hBit_Up = (HBITMAP) ::LoadImage (NULL, bitmap_path, IMAGE_BITMAP, 0,0, LR_LOADFROMFILE); 

	if(hBit_Up == NULL)
	{
		MessageBox(bitmap_path, TEXT("Link_Bitmap__Idle_State() - Error !"), MB_OK);
	}
}
void CButton_Image::Link_Bitmap__Down_State(const CString& bitmap_path)
{
	hBit_Down = (HBITMAP) ::LoadImage (NULL, bitmap_path, IMAGE_BITMAP, 0,0, LR_LOADFROMFILE); 

	if(hBit_Down == NULL)
	{
		MessageBox(bitmap_path, TEXT("Link_Bitmap__Idle_State() - Error !"), MB_OK);
	}
}
void CButton_Image::Link_Bitmap__Active_State(const CString& bitmap_path)
{
	hBit_Active = (HBITMAP) ::LoadImage (NULL, bitmap_path, IMAGE_BITMAP, 0,0, LR_LOADFROMFILE); 

	if(hBit_Active == NULL)
	{
		MessageBox(bitmap_path, TEXT("Link_Bitmap__Active_State() - Error !"), MB_OK);
	}
}
void CButton_Image::Link_Bitmap__Disable_State(const CString& bitmap_path)
{
	hBit_Disable = (HBITMAP) ::LoadImage (NULL, bitmap_path, IMAGE_BITMAP, 0,0, LR_LOADFROMFILE); 

	if(hBit_Disable == NULL)
	{
		MessageBox(bitmap_path, TEXT("Link_Bitmap__Disable_State() - Error !"), MB_OK);
	}
}

void CButton_Image::Link_Bitmap__Up_State(const int bitmap_id)
{
	hBit_Up = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(bitmap_id));
}
void CButton_Image::Link_Bitmap__Down_State(const int bitmap_id)
{
	hBit_Down = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(bitmap_id));
}
void CButton_Image::Link_Bitmap__Active_State(const int bitmap_id)
{
	hBit_Active = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(bitmap_id));
}
void CButton_Image::Link_Bitmap__Disable_State(const int bitmap_id)
{
	hBit_Disable = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(bitmap_id));
}

// ...
void CButton_Image::Draw__Buttn_State()
{
	if(bOnwer_Draw)			DrawItem();	
}
void CButton_Image::Draw__Up_State()
{
	if(hBit_Up == NULL)				return;

	iCurrent_State = _BTN_STATE__UP;

	if(bOnwer_Draw)			DrawItem();							
	else					SetBitmap(hBit_Up);
}
void CButton_Image::Draw__Down_State()
{
	if(hBit_Down == NULL)			return;

	iCurrent_State = _BTN_STATE__DOWN;

	if(bOnwer_Draw)			DrawItem();							
	else					SetBitmap(hBit_Down);
}
void CButton_Image::Draw__Active_State()
{
	if(hBit_Active == NULL)			return;

	iCurrent_State = _BTN_STATE__ACTIVE;

	if(bOnwer_Draw)			DrawItem();							
	else					SetBitmap(hBit_Active);
}
void CButton_Image::Draw__Disable_State()
{
	if(hBit_Disable == NULL)		return;

	iCurrent_State = _BTN_STATE__DISABLE;

	if(bOnwer_Draw)			DrawItem();							
	else					SetBitmap(hBit_Disable);
}

void CButton_Image::Draw__Background()
{
	if(pDC_Scr == NULL)			return;

	// ...
	int pt_x = mPT_XY.x;
	int pt_y = mPT_XY.y;
	int pt_w = mPT_CS.x;
	int pt_h = mPT_CS.y;

	if(bMask_Use)
	{
		pt_x--;   pt_y--;
		pt_w++;   pt_h++;
	}

	if((pDC_Mem  != NULL)
	&& (pDC_Back != NULL))
	{
		pDC_Back->StretchBlt(pt_x,pt_y, pt_w,pt_h, pDC_Mem, pt_x,pt_y, pt_w,pt_h, SRCCOPY);
		pDC_Scr->StretchBlt(pt_x,pt_y, pt_w,pt_h, pDC_Back, pt_x,pt_y, pt_w,pt_h, SRCCOPY);
	}
}

int  CButton_Image::Is__Disable_State()
{
	if(iCurrent_State == _BTN_STATE__DISABLE)		return 1;

	return -1;
}
int  CButton_Image::Is__Active_State()
{
	if(iCurrent_State == _BTN_STATE__ACTIVE)		return 1;

	return -1;
}
int  CButton_Image::Is__Up_State()
{
	if(iCurrent_State == _BTN_STATE__UP)			return 1;

	return -1;
}
int  CButton_Image::Is__Down_State()
{
	if(iCurrent_State == _BTN_STATE__DOWN)			return 1;

	return -1;
}


// ...
void CButton_Image::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	DrawItem();
}
void CButton_Image::DrawItem()
{
	bool bttn_visible = GetStyle() & WS_VISIBLE;
	if(!bttn_visible)
	{
		return;
	}

	if(pDC_Scr == NULL)
	{
		return;
	}

	// ...
	HBITMAP hbitmap = NULL;

	     if(iCurrent_State == _BTN_STATE__UP)				hbitmap	= hBit_Up;
	else if(iCurrent_State == _BTN_STATE__DOWN)				hbitmap	= hBit_Down;
	else if(iCurrent_State == _BTN_STATE__ACTIVE)			hbitmap = hBit_Active;
	else if(iCurrent_State == _BTN_STATE__DISABLE)			hbitmap = hBit_Disable;
	else													return;

	if(hbitmap == NULL)
	{
		return;
	}

	CBitmap *p_bmp = CBitmap::FromHandle(hbitmap);

	BITMAP bitMapInfo; 
	p_bmp->GetBitmap(&bitMapInfo); 

	// ...
	CDC memDC;

	if(pDC_Back != NULL)		memDC.CreateCompatibleDC(pDC_Back);
	else						memDC.CreateCompatibleDC(pDC_Scr);

	memDC.SelectObject(p_bmp);

	int w = bitMapInfo.bmWidth;
	int h = bitMapInfo.bmHeight;

	// ...
	int pt_x = mPT_XY.x;
	int pt_y = mPT_XY.y;
	int pt_w = mPT_CS.x;
	int pt_h = mPT_CS.y;

	if(bMask_Use)
	{
		pt_x--;   pt_y--;
		pt_w++;   pt_h++;
	}

	/*
	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = " * CButton_Image::DrawItem() ... \n";

		log_bff.Format("  ** Pos : (%1d,%1d) (%1d,%1d) \n", pt_x,pt_y,pt_w,pt_h);
		log_msg += log_bff;

		printf(log_msg);
	}
	*/

	if(pDC_Back != NULL)
	{
		if(bMask_Use)		pDC_Back->TransparentBlt(pt_x,pt_y, pt_w,pt_h, &memDC, 0,0,w,h, mMask_Color);
		else				pDC_Back->StretchBlt(pt_x,pt_y, pt_w,pt_h, &memDC, 0,0,w,h, SRCCOPY);	

		pDC_Scr->StretchBlt(pt_x,pt_y, pt_w,pt_h, pDC_Back, pt_x,pt_y, pt_w,pt_h, SRCCOPY);
	}
	else
	{
		pDC_Scr->StretchBlt(pt_x,pt_y, pt_w,pt_h, &memDC, 0,0,w,h, SRCCOPY);	
	}

	memDC.DeleteDC();
}

// ...
void CButton_Image::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(mButton_Notify)
	{
		NMHDR hdr;

		hdr.code = _BTN__LDOWN;
		hdr.hwndFrom = this->GetSafeHwnd();
		hdr.idFrom = GetDlgCtrlID();

		this->GetParent()->SendMessage(WM_NOTIFY, (WPARAM)hdr.idFrom, (LPARAM)&hdr);
	}

	CButton::OnLButtonDown(nFlags, point);
}
void CButton_Image::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(mButton_Notify)
	{
		NMHDR hdr;

		hdr.code = _BTN__LUP;
		hdr.hwndFrom = this->GetSafeHwnd();
		hdr.idFrom = GetDlgCtrlID();

		this->GetParent()->SendMessage(WM_NOTIFY, (WPARAM)hdr.idFrom, (LPARAM)&hdr);
	}

	CButton::OnLButtonUp(nFlags, point);
}

void CButton_Image::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if(mButton_Notify)
	{

	}

	CButton::OnRButtonUp(nFlags, point);
}
void CButton_Image::OnRButtonUp(UINT nFlags, CPoint point) 
{
	if(mButton_Notify)
	{
		NMHDR hdr;

		hdr.code = NM_RCLICK;
		hdr.hwndFrom = this->GetSafeHwnd();
		hdr.idFrom = GetDlgCtrlID();

		this->GetParent()->SendMessage(WM_NOTIFY, (WPARAM)hdr.idFrom, (LPARAM)&hdr);
	}

	CButton::OnRButtonUp(nFlags, point);
}
