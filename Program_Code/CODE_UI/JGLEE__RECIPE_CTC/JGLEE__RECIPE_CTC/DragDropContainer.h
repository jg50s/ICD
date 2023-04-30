// DragDropContainer.h: interface for the CDragDropContainer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAGDROPCONTAINER_H__14DF1D87_F782_42DA_8CCF_8FBC3668B612__INCLUDED_)
#define AFX_DRAGDROPCONTAINER_H__14DF1D87_F782_42DA_8CCF_8FBC3668B612__INCLUDED_

#include "DragDropTreeCtrl.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CDragDropTreeCtrl;
class CDragDropContainer  
{
public:
	CImageList* GetDragImage();
	void SetDragImage(CImageList *pImageList);
	CDragDropTreeCtrl* GetDropTarget();
	CDragDropTreeCtrl* GetDragSource();
	void SetSecondComponent(CDragDropTreeCtrl *pSecondTree);
	void SetFirstComponent(CDragDropTreeCtrl *pFirstTree);
	BOOL IsDragging();
	void SetIsDragging(BOOL bDragging);
	void RegisterDragSource(CDragDropTreeCtrl *pTreeCtrl);
	CDragDropContainer();
	virtual ~CDragDropContainer();

private:
	CImageList *m_pImageList;
	CDragDropTreeCtrl *m_pSecondTree;
	CDragDropTreeCtrl *m_pFirstTree;
	CDragDropTreeCtrl *m_pDragSource;
	CDragDropTreeCtrl *m_pDropTarget;
	BOOL m_bDragging;
};

#endif // !defined(AFX_DRAGDROPCONTAINER_H__14DF1D87_F782_42DA_8CCF_8FBC3668B612__INCLUDED_)
