#if !defined(AFX_DRAGDROPTREECTRL_H__63AC05AD_E0DC_11D1_8E53_006008A82731__INCLUDED_)
#define AFX_DRAGDROPTREECTRL_H__63AC05AD_E0DC_11D1_8E53_006008A82731__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DragDropTreeCtrl.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CDragDropTreeCtrl window
#include <vector>

#include "DragDrop_Common.h"
#include "DragDrop_Link.h"


class CDragEventListener;
class CDragDropTreeCtrl;

class CDragDropTreeCtrl : public CTreeCtrl
{
public:
	void Set_LinkDragDrop(CLink__DragDrop * p_link);

private:
	CLink__DragDrop *pLink_DragDrop;
	
	CImageList m_ImageList;
	EVENT_LISTENER_LIST m_vEventListener;
	BOOL m_bDragging;
	CImageList* m_pImageList;
	HTREEITEM m_hDragItem;
	HTREEITEM m_hItemDrop;
	SEL_ITEM_LIST m_vSelItem;
	CPoint	m_ptScreenLastClicked;	// Holds the screen coordinates of last mouse click
	UINT m_uiTimer;
	HTREEITEM  m_hLastTreeItemClicked;   // Holds last tree item clicked
	DWORD	m_dwTimeLastLButtonDown;



	void OnDrag(CPoint point);
	SEL_ITEM_LIST m_vTempSelItemList; 
	HTREEITEM m_hLastSelItem;

	void ClearSelection();
	void RemoveFromSelectionList(HTREEITEM hItem);
	void SelectItems(HTREEITEM hItemFrom,HTREEITEM hItemTo);
	CImageList* CreateDragImageEx();
	void OnShiftKeyPress(HTREEITEM hCurItem);
	void OnControlKeyPress(HTREEITEM hCurItem);
	BOOL IsItemPresent(HTREEITEM hItem);
	BOOL IsInTheSameLevel(HTREEITEM hItem);

	// Construction
public:
	CDragDropTreeCtrl();

	// Attributes
public:

	// Operations
public:


	//void OnMouseMove(UINT nFlags, CPoint point);
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragDropTreeCtrl)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	// Implementation
public:
	void AddDragEventListener(CDragEventListener* pListener);
	void RemoveFromSelList(HTREEITEM hItem);
	SEL_ITEM_LIST GetSelectedItems();
	int GetID();
	void SetID(int nID);
	virtual ~CDragDropTreeCtrl();

	// Generated message map functions
protected:
	bool m_bLButtonDown;
	HTREEITEM HighlightDropTarget (CPoint point);
	int m_nDelayInterval;
	BOOL IsItemExpanded (HTREEITEM hItem);
	int m_nScrollMargin;
	int m_nScrollInterval;
	BOOL IsChildOf (HTREEITEM hItem1, HTREEITEM hItem2);
	//{{AFX_MSG(CDragDropTreeCtrl)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAGDROPTREECTRL_H__63AC05AD_E0DC_11D1_8E53_006008A82731__INCLUDED_)
