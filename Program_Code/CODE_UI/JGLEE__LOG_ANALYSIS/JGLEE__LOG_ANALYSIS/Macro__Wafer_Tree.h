#pragma once

#include "CLS__Wafer_Trace.h"


extern void MACRO__Update__Wafer_Process(CTreeCtrl *p_tree, HTREEITEM h_node, CLS__MD_Info md_info);
extern void MACRO__Update__Wafer_Action(CTreeCtrl *p_tree, HTREEITEM h_node, CLS__MD_Info md_info);

extern void MACRO__Update__Wafer_Tree(CTreeCtrl* p_tree, 
									  CLS__Wafer_Info* p_wfr_info,
									  bool active_move,
									  bool active_proc);

extern void MACRO__Update__Wafer_Info(const CString& file_path, 
									  CLS__Wafer_Info *p_wafer_info);

