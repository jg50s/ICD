#include "stdafx.h"
#include "Dlg__Job_History.h"

#include "Macro_Function.h"


#define _TREE_SEL__SLOT_COMPLETED				1
#define _TREE_SEL__SLOT_ERROR					2
#define _TREE_SEL__SLOT_NOT_COMPLETE			3


// ...
void CDlg__Job_History
::_Clear__Slot_Info()
{
	CTreeCtrl *p_tree = &mTree__Slot_Info;
	p_tree->DeleteAllItems();

	_Clear__Wafer_Tree();
}

void CDlg__Job_History
::_Update__Slot_Info(const CStringArray& l_wfr)
{
	CTreeCtrl *p_tree = &mTree__Slot_Info;
	p_tree->DeleteAllItems();
	p_tree->SetRedraw(FALSE);

	// ...
	{
		CStringArray l_name;
		CUIntArray   l_id;

		int i_limit = 10;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(i == 0)
			{
				l_name.Add("Completed");
				l_id.Add(_TREE_SEL__SLOT_COMPLETED);
			}
			else if(i == 1)
			{
				l_name.Add("Not complete");
				l_id.Add(_TREE_SEL__SLOT_NOT_COMPLETE);
			}
			else if(i == 2)
			{
				l_name.Add("Error");
				l_id.Add(_TREE_SEL__SLOT_ERROR);
			}
			else
			{
				continue;
			}
		}

		// ...
		i_limit = l_name.GetSize();

		for(i=0; i<i_limit; i++)
		{
			CString node_name = l_name[i];
			int node_id = l_id[i];

			HTREEITEM h_node = p_tree->InsertItem(node_name, node_id,node_id, TVI_ROOT, TVI_LAST);

				 if(node_id == _TREE_SEL__SLOT_COMPLETED)			hTree__Slot_Node__COMPLETED    = h_node;
			else if(node_id == _TREE_SEL__SLOT_NOT_COMPLETE)		hTree__Slot_Node__NOT_COMPLETE = h_node;
			else if(node_id == _TREE_SEL__SLOT_ERROR)				hTree__Slot_Node__ERROR = h_node;
		}
	}

	// ...
	CStringArray l_slot;

	// ...
	{
		int i_limit = l_wfr.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CString str_wfr = l_wfr[i];

			CStringArray l_para;
			MACRO__Convert__LIST('_', str_wfr, l_para);

			if(l_para.GetSize() > 1)		str_wfr = l_para[1];
			else							str_wfr = "??";

			l_slot.Add(str_wfr);
		}

		MACRO__Change_Order(l_slot, false, true);
	}

	// ...
	{
		HTREEITEM h_root = hTree__Slot_Node__COMPLETED;
		int node_id = _TREE_SEL__SLOT_COMPLETED;

		int i_limit = l_slot.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CString node_name = l_slot[i];

			p_tree->InsertItem(node_name, node_id,0, h_root, TVI_LAST);
		}

		MACRO__Expand_Tree(p_tree, h_root, 1);
	}

	sList__Tree_Slot_Info.Copy(l_slot);

	p_tree->SetRedraw(TRUE);
}

