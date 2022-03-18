#include "StdAfx.h"

#include "CRes__IMG_CTRL.h"

#include "JGLEE__IMG_MNG.h"
extern CJGLEE__IMG_MNGApp theApp;


//-----------------------------------------------------------------------
CRes__IMG_CTRL::CRes__IMG_CTRL()
{
	InitializeCriticalSection(&mCS_LOCK);

}
CRes__IMG_CTRL::~CRes__IMG_CTRL()
{
	//-----------------------------------------
	CRes__IMG_INFO* p_info;

	int limit = pList.GetSize();
	int i;
		
	for(i=0; i<limit; i++)
	{
		p_info = (CRes__IMG_INFO*) pList[i];
		delete p_info;
	}

	pList.RemoveAll();
	//-----------------------------------------

	DeleteCriticalSection(&mCS_LOCK);
}

void CRes__IMG_CTRL::
_Create_DC(CRes__IMG_INFO* p_info)
{
	HDC hdc = GetDC(NULL);

	p_info->hDC_IMG = CreateCompatibleDC(hdc);
	SelectObject(p_info->hDC_IMG,p_info->hBIT_IMG);
	SetStretchBltMode(p_info->hDC_IMG,HALFTONE);

	if(p_info->iBLACK_FLAG > 0)
	{
		p_info->hDC_MSK = CreateCompatibleDC(hdc);
		SelectObject(p_info->hDC_MSK,p_info->hBIT_MSK);
		SetStretchBltMode(p_info->hDC_MSK,HALFTONE);
	}

	ReleaseDC(NULL,hdc);
}
void CRes__IMG_CTRL::
_Delete_DC(CRes__IMG_INFO* p_info)
{
	if(p_info->hDC_IMG != NULL)
	{
		DeleteDC(p_info->hDC_IMG);
		p_info->hDC_IMG = NULL;
	}

	if(p_info->hDC_MSK != NULL)
	{
		DeleteDC(p_info->hDC_MSK);
		p_info->hDC_MSK = NULL;
	}
}

int  CRes__IMG_CTRL::
_Get__FILE_TYPE(const CString& path)
{
	CString str_ext;
	char ch;

	int limit = path.GetLength();
	int i;

	for(i=limit-1; i>=0; i--)
	{
		ch = path.GetAt(i);

		if(ch == '.')
		{
			if(str_ext.CompareNoCase("bmp") == 0)		return IMG_TYPE__BMP;
			if(str_ext.CompareNoCase("png") == 0)		return IMG_TYPE__PNG;
			if(str_ext.CompareNoCase("jpg") == 0)		return IMG_TYPE__JPG;
			if(str_ext.CompareNoCase("gif") == 0)		return IMG_TYPE__GIF;

			return -1;
		}
		else
		{
			str_ext.Insert(0,ch);
		}
	}

	return IMG_TYPE__BMP;
}
int  CRes__IMG_CTRL::
_Check__FILE(const CString& path)
{
	HANDLE hFile;

	hFile = CreateFile(path,
					   GENERIC_READ,
					   FILE_SHARE_READ,
					   NULL,
					   OPEN_EXISTING,
					   FILE_ATTRIBUTE_NORMAL,
					   NULL);

	if(hFile == INVALID_HANDLE_VALUE)
	{
		return -1;
	}

	CloseHandle(hFile);
	return 1;
}

int  CRes__IMG_CTRL::
_Load__IMG_PNG(const int res_id, 
			   CRes__IMG_INFO* p_info)
{
	TCHAR *res_type = TEXT("PNG");

	return _Load__IMG_RES(res_id,res_type, p_info);
}
int  CRes__IMG_CTRL::
_Load__IMG_RES(const int res_id,TCHAR* res_type, CRes__IMG_INFO* p_info)
{
	p_info->mOther_Image = _Get_ImageResource(res_id, res_type);

	// ...
	{
		int sx = 0;
		int sy = 0;

		if(p_info->mOther_Image != NULL)
		{
			sx = p_info->mOther_Image->GetWidth();
			sy = p_info->mOther_Image->GetHeight();
		}

		if(sx < 10)		sx = 10;
		if(sy < 10)		sy = 10;

		p_info->pSIZE.x = sx;
		p_info->pSIZE.y = sy;
	}
	return 1;
}

int  CRes__IMG_CTRL::
_Load__IMG_FILE(const int img_type,
		        const CString& path,
		        const int mode,
		        const COLORREF mask_color,
		        const HDC hdc,
		        const POINT& bmp_size,
		        CRes__IMG_INFO* p_info)
{
	// ...
	{
		p_info->iIMG_TYPE = img_type;
	}

	if(img_type == IMG_TYPE__BMP)
	{
		return _Load__BMP_FILE(path,mode,mask_color,hdc,bmp_size,p_info);
	}
	
	// png, jgp, gif ...
	{
		CString str = path;

		LPWSTR lpszw = new WCHAR[MAX_PATH];
		LPTSTR lpstr = str.GetBuffer(str.GetLength());
		
		int i_len = MultiByteToWideChar(CP_ACP, 0, lpstr,-1, NULL,NULL);
		MultiByteToWideChar(CP_ACP, 0, lpstr,-1, lpszw,i_len);
		
		p_info->mOther_Image = Gdiplus::Image::FromFile(lpszw, FALSE);

		int sx = p_info->mOther_Image->GetWidth();
		int sy = p_info->mOther_Image->GetHeight();

		if(sx < 10)		sx = 10;
		if(sy < 10)		sy = 10;

		p_info->pSIZE.x = sx;
		p_info->pSIZE.y = sy;

		delete [] lpszw;
	}
	return 1;
}
int  CRes__IMG_CTRL::
_Load__BMP_FILE(const CString& path,
		        const int mode,
			    const COLORREF mask_color,
			    const HDC hdc,
			    const POINT& bmp_size,
			    CRes__IMG_INFO* p_info)
{
	HANDLE hFile;
	DWORD  FileSize, dwRead;
	BITMAPFILEHEADER *fh;
	PVOID  ih;

	//-----------------------------------------------------------------------
	hFile = CreateFile(path,
					   GENERIC_READ,FILE_SHARE_READ,NULL,
					   OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	if(hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL,
				   path,"CRes__BMP_CTRL::_Load__BMP() - ERROR",
			       MB_OK|MB_TOPMOST|MB_ICONERROR);
		return -1;
	}

	FileSize = GetFileSize(hFile,NULL);

	fh = (BITMAPFILEHEADER *) malloc(FileSize);
	ReadFile(hFile,fh,FileSize,&dwRead,NULL);
	CloseHandle(hFile);

	ih = ((PBYTE)fh+sizeof(BITMAPFILEHEADER));
	//-----------------------------------------------------------------------

	//-----------------------------------------------------------------------
	HBITMAP img_bit = NULL;
	HBITMAP msk_bit = NULL;
	
	HDC img_hdc = NULL;
	HDC msk_hdc = NULL;
	//-----------------------------------------------------------------------

	//-----------------------------------------------------------------------
	BITMAPINFO* pbit_info = (BITMAPINFO *) ih;

	p_info->pSIZE.x = pbit_info->bmiHeader.biWidth;
	p_info->pSIZE.y = pbit_info->bmiHeader.biHeight;

	if(p_info->pSIZE.x > 1920)		p_info->pSIZE.x = bmp_size.x;
	if(p_info->pSIZE.y > 1024)		p_info->pSIZE.y = bmp_size.y;

	//
	img_bit = CreateCompatibleBitmap(hdc,p_info->pSIZE.x,p_info->pSIZE.y);
	img_hdc = CreateCompatibleDC(hdc);
	SelectObject(img_hdc,img_bit);	

	if(mode > 0)
	{
		msk_bit = CreateCompatibleBitmap(hdc,p_info->pSIZE.x,p_info->pSIZE.y);
		msk_hdc = CreateCompatibleDC(hdc);
		SelectObject(msk_hdc,msk_bit);	
	}

	SetStretchBltMode(img_hdc, HALFTONE);

	::StretchDIBits(img_hdc,
					0,
					0,
					p_info->pSIZE.x,
					p_info->pSIZE.y,
					0,
					0,
					p_info->pSIZE.x,
					p_info->pSIZE.y,
					(PBYTE) fh+fh->bfOffBits,
					(BITMAPINFO *) ih,
					DIB_RGB_COLORS,
					SRCCOPY);

	SetStretchBltMode(img_hdc, BLACKONWHITE);
	//-----------------------------------------------------------------------
	
	free(fh);

	//-----------------------------------------------------------------------
	if(mode > 0)
	{
		SetStretchBltMode(msk_hdc, HALFTONE);

		COLORREF black_color = RGB(0,0,0);
		COLORREF white_color = RGB(255,255,255);

		int row, col, limit_x, limit_y;

		limit_x = p_info->pSIZE.x;
		limit_y = p_info->pSIZE.y;

		for(row=0;row<limit_y;++row)
		{
			for(col=0;col<limit_x;col++)
			{
				if(GetPixel(img_hdc,col,row) == mask_color)
				{
					SetPixel(msk_hdc,col,row,white_color);

					p_info->iBLACK_FLAG = 1;
				}
				else
				{
					SetPixel(msk_hdc,col,row,black_color);
				}
			}
		}

		SetStretchBltMode(msk_hdc, BLACKONWHITE);
	}
	//-----------------------------------------------------------------------

	//-----------------------------------------------------------------------
	BITMAPINFO bi;
    void *lpBits;

    ZeroMemory(&bi,sizeof(BITMAPINFOHEADER));

    bi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth       = p_info->pSIZE.x;
	bi.bmiHeader.biHeight      = p_info->pSIZE.y;
	bi.bmiHeader.biPlanes      = 1;
	bi.bmiHeader.biBitCount    = 16;
	bi.bmiHeader.biCompression = BI_RGB;
	//-----------------------------------------------------------------------

	//-----------------------------------------------------------------------
	p_info->hBIT_IMG = CreateDIBSection(hdc,(BITMAPINFO *)&bi,DIB_RGB_COLORS,&lpBits,NULL,(DWORD)0);

	if(p_info->iBLACK_FLAG > 0)
	{
		p_info->hBIT_MSK = CreateDIBSection(hdc,(BITMAPINFO *)&bi,DIB_RGB_COLORS,&lpBits,NULL,(DWORD)0);
	}
	//-----------------------------------------------------------------------

	_Create_DC(p_info);

	//-----------------------------------------------------------------------
	BitBlt(p_info->hDC_IMG,
		   0,
		   0,
		   p_info->pSIZE.x,
		   p_info->pSIZE.y,
		   img_hdc,
		   0,
		   0,
		   SRCCOPY);

	SetStretchBltMode(p_info->hDC_IMG,BLACKONWHITE);

	if(p_info->iBLACK_FLAG > 0)
	{
		BitBlt(p_info->hDC_MSK,
			   0,
			   0,
			   p_info->pSIZE.x,
			   p_info->pSIZE.y,
			   msk_hdc,
			   0,
			   0,
			   SRCCOPY);
	
		SetStretchBltMode(p_info->hDC_MSK,BLACKONWHITE);
	}
	//-----------------------------------------------------------------------

	//-------------------------------------------------------------
	if(img_bit != NULL)		DeleteObject(img_bit);	
	if(img_hdc != NULL)		DeleteDC(img_hdc);

	if(msk_bit != NULL)		DeleteObject(msk_bit);	
	if(msk_hdc != NULL)		DeleteDC(msk_hdc);
	//-------------------------------------------------------------

	_Delete_DC(p_info);
	return 1;
}


//-----------------------------------------------------------------------
int  CRes__IMG_CTRL::
Get__IMG_INFO(CStringArray& l_name,
		     CStringArray& l_path)
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	{
		l_name.RemoveAll();
		l_path.RemoveAll();
	}

	// ...
	{
		CRes__IMG_INFO *p_info;

		int i_limit = pList.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			p_info = (CRes__IMG_INFO *) pList[i];

			l_name.Add(p_info->sIMG_STATE);
			l_path.Add(p_info->sIMG_PATH);
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return 1;
}
int  CRes__IMG_CTRL::
Get__IMG_SIZE()
{
	EnterCriticalSection(&mCS_LOCK);

	int img_limit = pList.GetSize();

	LeaveCriticalSection(&mCS_LOCK);
	return img_limit;
}

int  CRes__IMG_CTRL::
Check__CUR_IMG_STATE(const CString& img_state)
{
	EnterCriticalSection(&mCS_LOCK);

	int check_img = -1;

	if(img_state.CompareNoCase(sIMG_STATE) == 0)
	{
		check_img = 1;
	}

	LeaveCriticalSection(&mCS_LOCK);
	return check_img;
}
int  CRes__IMG_CTRL::
Check__CUR_IMG_INDEX(const int img_index)
{
	EnterCriticalSection(&mCS_LOCK);

	int check_img = -1;

	if(img_index == iIMG_INDEX)
	{
		check_img = 1;
	}

	LeaveCriticalSection(&mCS_LOCK);
	return check_img;
}

// ...
void CRes__IMG_CTRL::
Delete__ALL_IMG()
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	{
		int i_limit = pList.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CRes__IMG_INFO* p_info = (CRes__IMG_INFO*) pList[i];

			delete p_info;
		}

		pList.RemoveAll();
	}

	LeaveCriticalSection(&mCS_LOCK);
}

int  CRes__IMG_CTRL::
Load__IMG_PNG(const CString& img_state,
			  const int img_res)
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	int check_state = -1;

	// ...
	{
		CRes__IMG_INFO* p_info;

		int i_limit = pList.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			p_info = (CRes__IMG_INFO*) pList[i];

			if(p_info->sIMG_STATE.CompareNoCase(img_state) != 0)
			{
				continue;
			}

			check_state = 1;
			break;
		}
	}

	if(check_state < 0)
	{
		CRes__IMG_INFO* p_info = new CRes__IMG_INFO;
		pList.Add(p_info);

		p_info->sIMG_STATE = img_state;
		_Load__IMG_PNG(img_res, p_info);
	}

	LeaveCriticalSection(&mCS_LOCK);
	return 1;
}

int  CRes__IMG_CTRL::
Load__IMG_FILE(const CString& img_name,
		       const CString& img_path)
{
	int mask_mode = -1;
    COLORREF mask_color = RGB(0,0,0);

	POINT in_img_size;

	int out_img_index;
	POINT out_img_size;

	in_img_size.x = 200;
	in_img_size.y = 200;

	return Load__IMG_FILE(img_name,img_path, 
						  mask_mode,mask_color, 
						  in_img_size, 
						  out_img_index,out_img_size);
}
int  CRes__IMG_CTRL::
Load__IMG_FILE(const CString& img_state,
			   const CString& img_path,
			   const int mask_mode,
			   const COLORREF mask_color,
			   const POINT& in_img_size,
			   int& out_img_index,
			   POINT& out_img_size)
{
	// ...
	{
		if(img_state.GetLength() < 1)		return -11;
		if(img_path.GetLength()  < 1)		return -12;
	}

	EnterCriticalSection(&mCS_LOCK);

	//-----------------------------------------
	if(_Check__FILE(img_path) < 0)
	{
		LeaveCriticalSection(&mCS_LOCK);
		return -1;
	}

	int img_type = _Get__FILE_TYPE(img_path);
	if(img_type < 1)
	{
		CString err_msg;

		err_msg.Format("알 수 없는 Image Type 입니다.");
		MessageBox(NULL, img_path,err_msg, MB_TOPMOST|MB_ICONERROR);

		LeaveCriticalSection(&mCS_LOCK);
		return -2;
	}
	//-----------------------------------------

	//-----------------------------------------
	CRes__IMG_INFO *p_info;
	int flag = -1;

	int limit = pList.GetSize();
	int i;

	for(i=0; i<limit; i++)
	{
		p_info = (CRes__IMG_INFO*) pList[i];

		if(p_info->sIMG_PATH.CompareNoCase(img_path) == 0)
		{
			CString write_time;
			_Get_File_WriteTime(img_path, write_time);
			
			if(p_info->sIMG_TIME.CompareNoCase(write_time) != 0)
			{
				p_info->sIMG_TIME = write_time;

				HDC hdc = GetDC(NULL);
				_Load__IMG_FILE(img_type,img_path,mask_mode,mask_color,hdc,in_img_size,p_info);
				ReleaseDC(NULL,hdc);
			}

			out_img_index = i;
			out_img_size  = p_info->pSIZE;

			flag = 1;
			break;
		}
	}

	if(flag < 0)
	{
		p_info = new CRes__IMG_INFO;
		pList.Add(p_info);

		p_info->sIMG_PATH  = img_path;
		p_info->sIMG_STATE = img_state;

		CString write_time;
		_Get_File_WriteTime(img_path,write_time);
		p_info->sIMG_TIME = write_time;

		HDC hdc = GetDC(NULL);
		_Load__IMG_FILE(img_type,img_path, mask_mode,mask_color, hdc,in_img_size, p_info);

		ReleaseDC(NULL,hdc);

		out_img_index = limit;
		out_img_size  = p_info->pSIZE;
	}
	//-----------------------------------------

	LeaveCriticalSection(&mCS_LOCK);
	return 1;
}

int CRes__IMG_CTRL::
Draw__IMG(const CString& img_state,
		  const HDC hdc_front,
		  const HDC hdc_back,
		  const HDC hdc_mem,
		  const POINT& st,
		  const POINT& et,
		  const int img_mode,
		  const int size_flag)
{
	EnterCriticalSection(&mCS_LOCK);

	int check_state = -1;

	int i_limit = pList.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CRes__IMG_INFO *p_info = (CRes__IMG_INFO*) pList[i];

		CString cur_state = p_info->sIMG_STATE;
		if(cur_state.GetLength() < 1)					continue;
		if(cur_state.CompareNoCase(img_state) != 0)		continue;

		sIMG_STATE = cur_state;
		Draw__IMG(i, hdc_front,hdc_back,hdc_mem, st,et, img_mode,size_flag);

		check_state = 1;
		break;
	}

	LeaveCriticalSection(&mCS_LOCK);
	return check_state;
}
void CRes__IMG_CTRL::
Draw__IMG(const int img_index,
		  const HDC hdc_front,
		  const HDC hdc_back,
		  const HDC hdc_mem,
		  const POINT& st,
		  const POINT& et,
		  const int img_mode,
		  const int size_flag)
{
	iIMG_INDEX = img_index;
	if(img_index < 0)			return;
	
	EnterCriticalSection(&mCS_LOCK);

	if(img_index < pList.GetSize())
	{
		CRes__IMG_INFO *p_info 
			= (CRes__IMG_INFO*) pList[img_index];

		if(p_info->iIMG_TYPE == IMG_TYPE__BMP)
		{
			_Draw__BMP(img_index, hdc_front,hdc_back,hdc_mem, st,et,img_mode,size_flag);
		}
		else
		{
			_Draw__IMG(img_index, hdc_front,hdc_back,hdc_mem, st,et,img_mode,size_flag);
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
}

void CRes__IMG_CTRL::
_Draw__BMP(const int bmp_index,
		   const HDC hdc_front,
		   const HDC hdc_back,
		   const HDC hdc_mem,
		   const POINT& st,
		   const POINT& et,
		   const int bmp_mode,
		   const int size_flag)
{
	if(bmp_index < pList.GetSize())
	{
		CRes__IMG_INFO *p_info = (CRes__IMG_INFO*) pList[bmp_index];
		
		int x_mode = bmp_mode;
		if(p_info->iBLACK_FLAG < 0)		x_mode = -1;
		
		int size_x;
		int size_y;
		
		if(size_flag > 0)
		{
			size_x = et.x - st.x;
			size_y = et.y - st.y;
		}
		else
		{
			size_x = p_info->pSIZE.x;
			size_y = p_info->pSIZE.y;
		}
		
		_Create_DC(p_info);
		
		if(x_mode > 0)		// Transparent
		{
			SetStretchBltMode(hdc_back, HALFTONE);
			
			StretchBlt(hdc_back, 
				       st.x, 
				       st.y, 
				       size_x, 
				       size_y,
				       p_info->hDC_MSK, 
 				       0, 
				       0, 
				       p_info->pSIZE.x, 
				       p_info->pSIZE.y, 
				       SRCAND);
			
			StretchBlt(hdc_back, 
				       st.x, 
				       st.y, 
				       size_x, 
				       size_y,
				       p_info->hDC_IMG, 
				       0, 
				       0, 
				       p_info->pSIZE.x, 
				       p_info->pSIZE.y, 
				       SRCINVERT);
			
			SetStretchBltMode(hdc_back, BLACKONWHITE);
		}
		else
		{
			SetStretchBltMode(hdc_back, HALFTONE);
			
			StretchBlt(hdc_back, 
				       st.x,
				       st.y, 
				       size_x, 
				       size_y,
				       p_info->hDC_IMG, 
				       0, 
				       0, 
				       p_info->pSIZE.x,
				       p_info->pSIZE.y, 
				       SRCCOPY);
			
			SetStretchBltMode(hdc_back, BLACKONWHITE);
		}

		if(hdc_front != hdc_back)
		{
			StretchBlt(hdc_front,      
				       st.x, 
				       st.y, 
				       size_x, 
				       size_y, 
				       hdc_back, 
				       st.x, 
				       st.y, 
				       size_x,
				       size_y,
				       SRCCOPY);
		}
		
		_Delete_DC(p_info);
	}
}
void CRes__IMG_CTRL::
_Draw__IMG(const int img_index,
		   const HDC hdc_front,
		   const HDC hdc_back,
		   const HDC hdc_mem,
		   const POINT& st,
		   const POINT& et,
		   const int img_mode,
		   const int size_flag)
{
	if(img_index < pList.GetSize())
	{
		CRes__IMG_INFO *p_info 
			= (CRes__IMG_INFO*) pList[img_index];
		
		int x_mode = img_mode;
		
		int size_x;
		int size_y;
		
		if(size_flag > 0)
		{
			size_x = et.x - st.x;
			size_y = et.y - st.y;
		}
		else
		{
			size_x = p_info->pSIZE.x;
			size_y = p_info->pSIZE.y;
		}

		if(p_info->mOther_Image != NULL)	
		{
			if(hdc_mem)
			{
				StretchBlt(hdc_back, st.x,st.y, size_x,size_y, hdc_mem, st.x,st.y, size_x,size_y, SRCCOPY);
			}
			if(hdc_back)
			{
				Graphics g(hdc_back);
				g.DrawImage(p_info->mOther_Image, st.x,st.y, size_x,size_y);	
			}
		}
		
		if(hdc_front != hdc_back)
		{
			StretchBlt(hdc_front, st.x,st.y, size_x,size_y, hdc_back, st.x,st.y, size_x,size_y, SRCCOPY);
		}
	}
}

int  CRes__IMG_CTRL::
Get__IMG_NAME(const int img_index,CString& img_state)
{
	if(img_index < 0)		return-1;

	EnterCriticalSection(&mCS_LOCK);

	//-----------------------------------------
	int flag = -1;

	if(img_index < pList.GetSize())
	{
		flag = 1;

		CRes__IMG_INFO *p_info = (CRes__IMG_INFO*) pList[img_index];
		img_state = p_info->sIMG_STATE;
	}
	//-----------------------------------------
	
	LeaveCriticalSection(&mCS_LOCK);
	return flag;
}
int CRes__IMG_CTRL::
Get__INDEX_OF_IMG_PATH(const CString& img_path)
{
	EnterCriticalSection(&mCS_LOCK);

	int img_index = -1;
	
	int i_limit = pList.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CRes__IMG_INFO *p_info = (CRes__IMG_INFO*) pList[i];
		
		if(p_info->sIMG_PATH.CompareNoCase(img_path) == 0)
		{
			img_index = i;
			break;
		}
	}
	
	LeaveCriticalSection(&mCS_LOCK);
	return img_index;
}
int CRes__IMG_CTRL::
Get__INDEX_OF_IMG_STATE(const CString& img_state)
{
	EnterCriticalSection(&mCS_LOCK);

	int img_index = -1;

	int i_limit = pList.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CRes__IMG_INFO *p_info = (CRes__IMG_INFO*) pList[i];

		if(p_info->sIMG_STATE.CompareNoCase(img_state) == 0)
		{
			img_index = i;
			break;
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return img_index;
}

void CRes__IMG_CTRL::
_Get_File_WriteTime(const CString& path,CString& write_time)
{
	CFileFind file_ctrl;
	CTime time;

	if(file_ctrl.FindFile(path) != NULL)
	{
		file_ctrl.FindNextFile();
		file_ctrl.GetLastWriteTime(time);
	}

	write_time = time.Format("%Y%m%d%H%M%S");
}

// ...
Gdiplus::Image* 
CRes__IMG_CTRL::_Get_ImageResource(const int res_id, TCHAR* res_type)
{
	HINSTANCE h_instance = theApp.m_hInstance;
	TCHAR* res_name = MAKEINTRESOURCE(res_id);

	CString log_err;
	log_err = "JGLEE__IMG_MNG - CRes__IMG_CTRL::_Get_ImageResource()";

	// ...
	Gdiplus::Image *image = NULL;

	HRSRC hResource = ::FindResource(h_instance, res_name,res_type);
	if(!hResource)
	{
		printf("%s \n", log_err);
		printf(" * Error 1 \n");
		return NULL;
	}

	DWORD imageSize = ::SizeofResource(h_instance, hResource);
	if(!imageSize)
	{
		printf("%s \n", log_err);
		printf(" * Error 2 \n");
		return NULL;
	}

	const void* pResourceData = ::LockResource(::LoadResource(h_instance, hResource));
	if(!pResourceData)
	{
		printf("%s \n", log_err);
		printf(" * Error 3 \n");
		return NULL;
	}

	HGLOBAL hBuffer = ::GlobalAlloc(GMEM_MOVEABLE, imageSize);
	if(hBuffer)
	{
		void* pBuffer = ::GlobalLock(hBuffer);
		if(pBuffer)
		{
			CopyMemory(pBuffer, pResourceData, imageSize);

			IStream* pStream = NULL;
			if(::CreateStreamOnHGlobal(hBuffer, FALSE, &pStream) == S_OK)
			{
				image = Gdiplus::Bitmap::FromStream(pStream);
				pStream->Release();

				if(image)
				{
					if(image->GetLastStatus() != Gdiplus::Ok)
					{
						delete image;
						image = NULL;

						printf("%s \n", log_err);
						printf(" * Error 4 \n");
					}
				}
			}
		}

		::GlobalUnlock(hBuffer);
		::GlobalFree(hBuffer);
	}
	return image;
}
