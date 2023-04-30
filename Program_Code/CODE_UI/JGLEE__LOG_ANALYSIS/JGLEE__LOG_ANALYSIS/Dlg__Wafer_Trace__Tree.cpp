#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Wafer_Trace.h"

#include "Macro_Function.h"
#include "Macro__Wafer_Tree.h"


// ...
void CDlg__Wafer_Trace
::_Update__Wafer_Tree()
{	
	bool active_move = false;
	bool active_proc = false;

	if(mCheck__Search_Move.GetCheck() > 0)			active_move = true;
	if(mCheck__Search_Proc.GetCheck() > 0)			active_proc = true;

	// ...
	CTreeCtrl *p_tree = &mTree_Wafer;

	if(!bActive__Wafer_Tree)
	{
		bActive__Wafer_Tree = true;

		CImageList *p_img = &mTree_Image;
		if(p_img->GetImageCount() < 1)
		{
			CBitmap bmp;
			bmp.LoadBitmap(IDB_IMAGE_LIST);

			p_img->Create(16, 16, ILC_COLORDDB|ILC_MASK, 9, 9);
			p_img->Add(&bmp, RGB(0, 0, 0)); 

			p_tree->SetImageList(p_img, TVSIL_NORMAL);
		}
	}

	MACRO__Update__Wafer_Tree(p_tree, &mWfr_Info, active_move,active_proc);

	_Expand__Node_History();
}

