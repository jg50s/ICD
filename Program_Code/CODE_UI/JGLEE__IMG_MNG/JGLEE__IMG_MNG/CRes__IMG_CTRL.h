#pragma once

#include "Interface_Header.h"


// typedef unsigned __int32 ULONG_PTR;
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus")


// ...
#define IMG_TYPE__BMP				1
#define IMG_TYPE__JPG				2
#define IMG_TYPE__GIF				3
#define IMG_TYPE__PNG				4


class CRes__IMG_INFO
{
public:
	CRes__IMG_INFO()
	{
		iIMG_TYPE = -1;

		//
		hBIT_IMG = NULL;
		hBIT_MSK = NULL;

		hDC_IMG = NULL;
		hDC_MSK = NULL;

		//
		mOther_Image = NULL;

		//
		pSIZE.x = 0;
		pSIZE.y = 0;

		//
		iBLACK_FLAG = -1;
		mMASK_COLOR = RGB(0,0,0);
	}
	~CRes__IMG_INFO()
	{
		if(hDC_IMG != NULL)
		{
			DeleteDC(hDC_IMG);
			hDC_IMG = NULL;
		}
		if(hDC_MSK != NULL)
		{
			DeleteDC(hDC_MSK);
			hDC_MSK = NULL;
		}

		if(hBIT_IMG != NULL)
		{
			DeleteObject(hBIT_IMG);
			hBIT_IMG = NULL;
		}
		if(hBIT_MSK != NULL)
		{
			DeleteObject(hBIT_MSK);
			hBIT_MSK = NULL;
		}

		if(mOther_Image != NULL)
		{
			delete mOther_Image;
			mOther_Image = NULL;
		}
	}

	// ...
	CString sIMG_PATH;
	CString sIMG_STATE;
	CString sIMG_TIME;

	// ...
	int iIMG_TYPE;
	
	// bmp
	HBITMAP hBIT_IMG;
	HBITMAP hBIT_MSK;

	// png, jpg, gif
	Gdiplus::Image *mOther_Image;

	// ...
	HDC hDC_IMG;
	HDC	hDC_MSK;

	POINT pSIZE;

	// 
	COLORREF mMASK_COLOR;
	int iBLACK_FLAG;
};

class CRes__IMG_CTRL
{
private:
	CRITICAL_SECTION mCS_LOCK;
	CPtrArray pList;

	CString sIMG_STATE;
	int iIMG_INDEX;

	// ...
	void _Create_DC(CRes__IMG_INFO* p_info);
	void _Delete_DC(CRes__IMG_INFO* p_info);

	int  _Get__FILE_TYPE(const CString& path);
	int  _Check__FILE(const CString& path);

	int  _Load__IMG_PNG(const int res_id, CRes__IMG_INFO* p_info);
	int  _Load__IMG_RES(const int res_id,TCHAR* res_type, CRes__IMG_INFO* p_info);

	int  _Load__IMG_FILE(const int img_type,
						 const CString& path,
						 const int mode,
						 const COLORREF mask_color,
						 const HDC hdc,
						 const POINT& bmp_size,
						 CRes__IMG_INFO* p_info);
	int  _Load__BMP_FILE(const CString& path,
						 const int mode,
						 const COLORREF mask_color,
						 const HDC hdc,
						 const POINT& bmp_size,
						 CRes__IMG_INFO* p_info);

	void _Draw__BMP(const int bmp_index,
				    const HDC hdc_front,
					const HDC hdc_back,
					const HDC hdc_mem,
					const POINT& st,
					const POINT& et,
					const int mode,
					const int size_flag = 1);
	void _Draw__IMG(const int img_index,
					const HDC hdc_front,
					const HDC hdc_back,
					const HDC hdc_mem,
					const POINT& st,
					const POINT& et,
					const int mode,
					const int size_flag = 1);

	// ...
	Gdiplus::Image* _Get_ImageResource(const int res_id, TCHAR* res_type);

	void _Get_File_WriteTime(const CString& path,CString& write_time);
	//

public:
	CRes__IMG_CTRL();
	~CRes__IMG_CTRL();

	// ...
	void Delete__ALL_IMG();

	int  Load__IMG_PNG(const CString& img_state,
					   const int img_res);
	
	int  Load__IMG_FILE(const CString& img_state,
				        const CString& img_path);
	int  Load__IMG_FILE(const CString& img_state,
					    const CString& img_path,
					    const int mask_mode,
					    const COLORREF mask_color,
					    const POINT& in_img_size,
					    int& out_img_index,
					    POINT& out_img_size);

	// ...
	int  Draw__IMG(const CString& img_state,
				   const HDC hdc_front,
				   const HDC hdc_back,
				   const HDC hdc_mem,
				   const POINT& st,
				   const POINT& et,
				   const int mode,
				   const int size_flag = 1);
	void Draw__IMG(const int img_index,
				   const HDC hdc_front,
				   const HDC hdc_back,
				   const HDC hdc_mem,
				   const POINT& st,
				   const POINT& et,
				   const int mode,
				   const int size_flag = 1);

	// ...
	int  Get__IMG_NAME(const int img_index, CString& img_name);
	int  Get__INDEX_OF_IMG_PATH(const CString& img_path);
	int  Get__INDEX_OF_IMG_STATE(const CString& img_state);

	int  Get__IMG_INFO(CStringArray& l_name,CStringArray& l_path);
	int  Get__IMG_SIZE();

	int  Check__CUR_IMG_STATE(const CString& img_state);
	int  Check__CUR_IMG_INDEX(const int img_index);
};
