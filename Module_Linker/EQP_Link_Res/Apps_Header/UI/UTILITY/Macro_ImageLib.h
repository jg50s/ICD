#ifndef  _MACRO_IMAGELIB_H_
#define  _MACRO_IMAGELIB_H_


//------------------------------------------
class CDS_XXX
{
public:
	CString sPara;
	int		iPara;
};

class CI_Image
{
public:
	virtual ~CI_Image(){};

	
	virtual bool LoadImage(HINSTANCE hInst, int resID) = 0;
	virtual bool LoadImage(LPCSTR fileName) = 0;
	virtual bool SetMaskColor(COLORREF lowColor, COLORREF highColor = NULL) = 0;
	virtual void SetImageAttrib(POINT st, POINT et, int degree) = 0;
	virtual bool DrawImage(HWND wnd, HDC back) = 0;
	virtual bool DrawImage(HDC hFrontDC, HDC hBackDC, POINT ptStart, POINT ptEnd, int degree) = 0;
	virtual bool DrawImage(HDC hDC, POINT ptStart, POINT ptEnd, int degree) = 0;
	virtual bool Flip(HDC hFrontDC, HDC hBackDC, POINT ptStart, POINT ptEnd) = 0;
	virtual bool Flip(HWND wnd, HDC dc, POINT st, POINT et) = 0;
	virtual bool SetFont(int size = 10, int style = 0, char * charset = "Arial") = 0;	/*  FontStyleRegular = 0,
																							FontStyleBold = 1,
																							FontStyleItalic = 2,
																							FontStyleBoldItalic = 3,
																							FontStyleUnderline = 4,
																							FontStyleStrikeout = 8
																						*/
	
	virtual bool PrintText(HDC hDC, POINT pt, COLORREF brushColor, LPCSTR msg) = 0;
	virtual bool DrawPolygon(HDC dc, POINT * pt, POINT origin, int num, int degree, COLORREF penColor, COLORREF brushColor, byte trans = 255) = 0;
	virtual char * GetErrorString() = 0;
	virtual bool CopyDC(HDC destDC, int x, int y, int cx, int cy, HDC srcDC, int sx, int sy, int degree) = 0;
	virtual bool Ellipse(HDC hDC, int x, int y, int cx, int cy, COLORREF color, int alpha =  255) = 0;
};
//------------------------------------------

//------------------------------------------
extern "C"
{
	CI_Image * New_Image();
};
//------------------------------------------

//------------------------------------------
class CX_ImageLib
{
private:
	CI_Image *m_PT;

public:
	CX_ImageLib()
	{
		m_PT = New_Image();
	}
	~CX_ImageLib()
	{
		if(m_PT != NULL)
		{
			delete m_PT;
		}
	}
	CI_Image * operator->() const
	{
		return m_PT;
	}

	CI_Image* Get_PTR()
	{
		return m_PT;
	}
};
//------------------------------------------

#endif
