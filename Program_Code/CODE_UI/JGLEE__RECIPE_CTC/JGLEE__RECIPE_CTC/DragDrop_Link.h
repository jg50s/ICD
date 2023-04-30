#pragma once


class CLink__DragDrop
{
public:	
	virtual int  Call__DragDrop(CTreeCtrl* p_tree, const HTREEITEM h_item, const POINT scr_pt) = 0;
};
