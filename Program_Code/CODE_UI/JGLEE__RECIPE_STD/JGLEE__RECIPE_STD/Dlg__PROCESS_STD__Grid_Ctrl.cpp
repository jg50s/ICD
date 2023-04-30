#include "stdafx.h"
#include "JGLEE__RECIPE_STD.h"
#include "Dlg__PROCESS_STD.h"

#include "Macro_Function.h"


// ...
void CDlg__PROCESS_STD::OnGridSelChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW *pItem = (NM_GRIDVIEW *)pNMHDR;

	int row = pItem->iRow; 
	int col = pItem->iColumn;

	printf(" * OnGridSelChanged() ... \n");
	printf(" ** hdr <- [%1d] \n", pItem->hdr);
	printf(" ** row <- [%1d] \n", row);
	printf(" ** col <- [%1d] \n", col);
	printf("\n");

	if((row < 0) || (col < 0))
	{
		if(m_Grid.bActive_Fixed)
		{
			printf(" ** fix.row <- [%1d] \n", m_Grid.iSel_Row);
			printf(" ** fix.col <- [%1d] \n", m_Grid.iSel_Col);
			printf("\n");

			row = m_Grid.iSel_Row;
			col = m_Grid.iSel_Col;

			if(col == 0)
			{
				_Fnc__Grid_SelChanged(row, col);
			}
		}
		else
		{
			m_Grid.bActive_Fixed = false;

			m_Grid.iSel_Row = -1;
			m_Grid.iSel_Col = -1;
		}

		_Change__Grid_Info(m_Grid.iSel_Col, m_Grid.iSel_Row);
	}
	else
	{
		_Fnc__Grid_SelChanged(row, col);
	}

	*pResult = 0;
}
void CDlg__PROCESS_STD::_Fnc__Grid_SelChanged(const int row,const int col)
{
	m_Grid.bActive_Fixed = FALSE;
	m_Grid.iSel_Row = row;
	m_Grid.iSel_Col = col;

	_Change__Grid_Info(m_Grid.iSel_Col, m_Grid.iSel_Row);

	// ...
	GObj__Parameter_Ctrl *p_para_ctrl = pGObj_Res->pGOBJ_PARA_CTRL;
	CInfo__Rcp_Item* p_rcp_item = pCur_Rcp_Item;

	bool active_item = true;

	if((col == 0) && (p_rcp_item != NULL))
	{
		if(row == 0)
		{
			m_Grid.SetSelectedRange(-1,-1,-1,-1);
			m_Grid.SetFocusCell(-1,-1);
			return;
		}

		if(p_rcp_item->Check__CATEGORY_ACTIVE_OF_ROW(row))
		{
			if(p_rcp_item->Check__CATEGORY_EXPAND_OF_ROW(row))
			{
				_Fnc__Grid_Contract(row,col, p_rcp_item);
			}
			else 
			{
				_Fnc__Grid_Expand(row,col, p_rcp_item);
			}

			active_item = false;
		}

		if(row > 0)
		{
			int col_max = m_Grid.GetColumnCount() - 1;

			m_Grid.SetSelectedRange(row,0, row,col_max);
		}
	}

	if(active_item)
	{
		CDS__Rcp_Item rcp_item;

		if(p_rcp_item->Get__ITEM_INFO(row, &rcp_item) > 0)
		{
			CString ch_name = rcp_item.sPara__CH_NAME;
			int     ch_type = rcp_item.iPara__CH_TYPE;

			printf(" * Item_Info ... \n");
			printf(" ** [%s] <- [%s][%1d] \n", rcp_item.sPara__RCP_TITLE, ch_name,ch_type);
			printf("\n");

			if(rcp_item.iPara__CH_TYPE == _CH_TYPE__DIGITAL)
			{
				CString out_data;
				CString d_list;

				if(rcp_item.bActive__CH_D_LIST)
				{
					CString ch_d_name = rcp_item.sPara__CH_D_LIST;
					CString ch_d_data;

					p_para_ctrl->Get__Data_From_Ch_Name(ch_d_name, ch_d_data);
					d_list = ch_d_data;

					printf(" ** CH_D_LIST : [%s] <- [%s] \n", ch_d_name,ch_d_data);
				}
				else
				{
					d_list = rcp_item.sPara__D_LIST;
				}

				if(DigitalPAD_PopUp(false,d_list, row,col, out_data) > 0)
				{
					if(col == 0)
					{
						int step_size = m_Grid.GetColumnCount();
						int i;

						for(i=1; i<step_size; i++)
							m_Grid.SetItemText(row,i, out_data);

						m_Grid.RedrawRow(row);

						for(i=1; i<step_size; i++)
						{
							m_Rcp_File.Set__Step_Data(i, ch_type, ch_name, out_data);

							if(bActive__Interlock_Dll)
							{
								xI_Rcp_Interlock_Ctrl->Set__CHANNEL_OF_SUB_PAGE(iMODULE_ID, i, ch_name, out_data);
							}
						}
					} 
					else 
					{
						printf(" * (%1d, %1d) <- [%s] \n", row,col, out_data);

						m_Grid.SetItemText(row,col, out_data);
						m_Grid.RedrawCell(row,col);

						m_Rcp_File.Set__Step_Data(col, ch_type, ch_name, out_data);

						if(bActive__Interlock_Dll)
						{
							xI_Rcp_Interlock_Ctrl->Set__CHANNEL_OF_SUB_PAGE(iMODULE_ID, col, ch_name, out_data);
						}
					}

					bActive__Rcp_item_Change = true;
				}
			}
			else if(rcp_item.iPara__CH_TYPE == _CH_TYPE__ANALOG)
			{
				CString out_data;
				CString a_min;
				CString a_max;

				MACRO__Convert__MIN_MAX(rcp_item.sPara__A_LIST, a_min,a_max);
				printf(" * (%s) -> (%s ~ %s) \n\n", rcp_item.sPara__A_LIST, a_min,a_max);

				if(rcp_item.bActive__CH_RANGE_MIN)
				{
					CString ch_a_name = rcp_item.sPara__CH_RANGE_MIN;
					CString ch_a_data;

					p_para_ctrl->Get__Data_From_Ch_Name(ch_a_name, ch_a_data);
					a_min = ch_a_data;

					printf(" ** CH_A_MIN : [%s] <- [%s] \n", ch_a_name,ch_a_data);
				}
				if(rcp_item.bActive__CH_RANGE_MAX)
				{
					CString ch_a_name = rcp_item.sPara__CH_RANGE_MAX;
					CString ch_a_data;

					p_para_ctrl->Get__Data_From_Ch_Name(ch_a_name, ch_a_data);
					a_max = ch_a_data;

					printf(" ** CH_A_MAX : [%s] <- [%s] \n", ch_a_name,ch_a_data);
				}

				if(AnalogPAD_PopUp(row,col, a_min,a_max, out_data) > 0)
				{
					if(col == 0)
					{
						int step_size = m_Grid.GetColumnCount();

						for(int i=1; i<step_size; i++)	
							m_Grid.SetItemText(row,i, out_data);
						
						m_Grid.RedrawRow(row);

						for(int i=1; i<step_size; i++)	
						{
							m_Rcp_File.Set__Step_Data(i, ch_type, ch_name, out_data);

							if(bActive__Interlock_Dll)
							{
								xI_Rcp_Interlock_Ctrl->Set__CHANNEL_OF_SUB_PAGE(iMODULE_ID, i, ch_name, out_data);
							}
						}
					} 
					else 
					{
						m_Grid.SetItemText(row,col, out_data);
						m_Grid.RedrawCell(row,col);

						m_Rcp_File.Set__Step_Data(col, ch_type, ch_name, out_data);

						if(bActive__Interlock_Dll)
						{
							xI_Rcp_Interlock_Ctrl->Set__CHANNEL_OF_SUB_PAGE(iMODULE_ID, col, ch_name, out_data);
						}
					}

					bActive__Rcp_item_Change = true;
				}
			}
			else if(rcp_item.iPara__CH_TYPE == _CH_TYPE__STRING)
			{
				int dual_flag = -1;
				CString out_data;
				CString out_data2;

				if(StringPAD_PopUp(row,col, out_data,out_data2,dual_flag) > 0)
				{
					if(col == 0)
					{
						int step_size = m_Grid.GetColumnCount();
						int i;

						for(i=1; i<step_size; i++)
							m_Grid.SetItemText(row,i, out_data);

						m_Grid.RedrawRow(row);

						for(i=1; i<step_size; i++)
							m_Rcp_File.Set__Step_Data(i, ch_type, ch_name, out_data);

						/*
						// DUAL-UP
						if(dual_flag == 1)
						{
							int row = m_dGridRow + 1;

							if(row < m_arrChannel_Type.GetSize())
							{
								for(i=1;i<size_col;i++)
								{
									CString strPreData = m_Grid.GetItemText(row,i);
									m_Grid.SetItemText(row,i,out_data2);
								}
							}
						}
						// DUAL-DOWN
						else if(dual_flag == 2)
						{
							int row = m_dGridRow - 1;

							if(row >= 0)
							{
								for(i=1;i<size_col;i++)
								{
									CString strPreData = m_Grid.GetItemText(row,i);
									m_Grid.SetItemText(row,i,out_data2);
								}
							}
						}
						*/
					} 
					else 
					{
						m_Grid.SetItemText(row,col, out_data);
						m_Grid.RedrawCell(row,col);

						m_Rcp_File.Set__Step_Data(col, ch_type, ch_name, out_data);

						/*
						// DUAL-UP
						if(dual_flag == 1)
						{
							int row = m_dGridRow + 1;

							if(row < m_arrChannel_Type.GetSize())
							{
								CString strPreData = m_Grid.GetItemText(row,m_dGridCol);
								m_Grid.SetItemText(row,m_dGridCol,out_data2);

								strDataEMP.Format("  [ Edit - Data ]");
								m_strLog += strDataEMP;

								strDataEMP.Format("  ( %d, %s )  %s -> %s\r\n",m_dGridCol,strTitleData,strPreData,out_data2);
								m_strLog += strDataEMP;
							}
						}
						// DUAL-DOWN
						else if(dual_flag == 2)
						{
							int row = m_dGridRow - 1;

							if(row >= 0)
							{
								CString strPreData = m_Grid.GetItemText(row,m_dGridCol);
								m_Grid.SetItemText(row,m_dGridCol,out_data2);

								strDataEMP.Format("  [ Edit - Data ]");
								m_strLog += strDataEMP;

								strDataEMP.Format("  ( %d, %s )  %s -> %s\r\n",m_dGridCol,strTitleData,strPreData,out_data2);
								m_strLog += strDataEMP;
							}
						}
						*/
					}

					bActive__Rcp_item_Change = true;
				}
			}
			else if(rcp_item.iPara__CH_TYPE == _CH_TYPE__SUB_PARA)
			{
				if(bActive__Interlock_Dll)
				{
					CString in_data;
					CString out_type;
					CString result_data;

					int step_size = m_Grid.GetColumnCount();
					int i;

					in_data.Format("MAX_COL=%1d\n", step_size-1);
					in_data += "STEP_MSG=";

					for(i=1; i<step_size; i++)
					{
						CString item_data = m_Grid.GetItemText(1, i);
						item_data += "^";

						in_data += item_data;
					}
					in_data += "\n";

					if(xI_Rcp_Interlock_Ctrl->Call__SUB_PAGE(iMODULE_ID, row,col, in_data,out_type, result_data) > 0)
					{
						bActive__Rcp_item_Change = true;
					}

					// ...
					{
						CStringArray l_title;
						xI_Rcp_Interlock_Ctrl->Get__ALL_TITLE_OF_SUB_PAGE(iMODULE_ID, l_title);

						int limit = l_title.GetSize();
						int i;

						for(i=0; i<limit; i++)
						{
							if(i >= step_size)			continue;

							m_Grid.SetItemText(row,i+1, l_title[i]);
						}
						m_Grid.RedrawRow(row);
					}
				}
			}

			// ...
		}
	}
	
	// ...
}

void CDlg__PROCESS_STD::_GoTo__Step_ID(const int st_id)
{
	bActive__Rcp_item_Change = true;
	m_Grid.iSel_Col = st_id;

	int row = m_Grid.iSel_Row;
	if(row < 0)		row = 0;

	// ...
	{
		int st_max = m_Grid.GetColumnCount();

		int st_fisrt = st_id - 4;
		int st_end   = st_id + 2;
		if(st_fisrt < 0)			st_fisrt = 0;
		
		if(st_end > st_max)
		{
			m_Grid.EnsureVisible(row, st_max-1);
		}
		else
		{
			m_Grid.EnsureVisible(row, st_fisrt);
			if(!m_Grid.IsCellVisible(row, st_id))		m_Grid.EnsureVisible(row, st_end);
			if(!m_Grid.IsCellVisible(row, st_id))		m_Grid.EnsureVisible(row, st_id);
		}

		int row_max = pCur_Rcp_Item->Get__ITEM_SIZE();
		m_Grid.SetSelectedRange(0,st_id, row_max-1,st_id);
		m_Grid.SetFocusCell(row, st_id);
	}

	// ...
	{
		CString str_data;
	
		str_data.Format("%1d", st_id);
		mCtrl__Sel_Step_ID.SetWindowText(str_data);
	}
}
void CDlg__PROCESS_STD::_Change__Grid_Info(const int step_id,const int item_id)
{
	CString str_data;

	str_data.Format("%1d", step_id);
	mCtrl__Sel_Step_ID.SetWindowText(str_data);

	str_data.Format("%1d", item_id);
	mCtrl__Sel_Item_ID.SetWindowText(str_data);
}
void CDlg__PROCESS_STD::_Draw__Grid_Table(CInfo__Rcp_Item* p_rcp_item)
{
	// ...
	{
		m_Grid.DeleteAllItems();

		m_Grid.bActive_Fixed = false;
		m_Grid.iSel_Row = -1;
		m_Grid.iSel_Col = -1;
	}

	if(p_rcp_item == NULL)
	{
		return;
	}

	// ...
	{
		CString str_data;

		int para_count = p_rcp_item->Get__ITEM_SIZE_EXCEPT_CATEGORY();
		int step_count = m_Rcp_File.Get__Step_Size();
		if(step_count < 1)		step_count = 1;

		str_data.Format("%1d", para_count);
		mData__Sel_Para_Count.SetWindowText(str_data);
		
		str_data.Format("%1d", step_count);
		mData__Sel_Step_Count.SetWindowText(str_data);
	}

	// ...
	COLORREF color__child_col  = RGB( 40, 108, 149);	
	COLORREF color__dark_blue  = RGB(  0,  66, 123);
	COLORREF color__navy_blue  = RGB(  0,  50, 149);
	COLORREF color__light_blue = RGB( 95, 164, 226);

	COLORREF color__cian       = RGB(24, 218, 245);
	COLORREF color__light_gray = RGB(234, 239, 242);
	COLORREF color__dark_gray  = RGB(117, 129, 138);
	COLORREF color__mid_gray   = RGB(223, 225, 225);

	COLORREF color__white = RGB(255, 255, 255);	
	COLORREF color__black = RGB(  0,   0,   0);	
	COLORREF color__blue  = RGB(  0, 125, 205);	

	// ...
	{
		GObj__Parameter_Ctrl *p_para_ctrl = pGObj_Res->pGOBJ_PARA_CTRL;

		int row_limit = p_rcp_item->Get__ITEM_SIZE();
		int row;

		int m_nFixRows = 1;
		int m_nFixCols = 1;

		m_Grid.SetHeaderSort(FALSE);

		m_Grid.SetRowResize(TRUE);
		// m_Grid.SetRowResize(FALSE);
		// m_Grid.SetColumnResize(FALSE);

		// m_Grid.SetEditable(TRUE);
		m_Grid.SetEditable(FALSE);

		// m_Grid.SetListMode(TRUE);
		m_Grid.SetListMode(FALSE);

		m_Grid.EnableDragAndDrop(FALSE);
		// m_Grid.EnableDragAndDrop(TRUE);

		m_Grid.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));
		m_Grid.EnableScrollBar(ESB_ENABLE_BOTH, TRUE);

		// m_Grid.SetFixedRowCount(1);
		// m_Grid.SetFixedRowCount(2);
		m_Grid.SetFixedRowCount(m_nFixRows);

		// m_Grid.SetFixedColumnCount(0);
		// m_Grid.SetFixedColumnCount(1);
		m_Grid.SetFixedColumnCount(m_nFixCols);

		//
		DWORD txt_center_style = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
		DWORD txt_left_style   = DT_LEFT   | DT_VCENTER | DT_SINGLELINE;

		// ...
		int step_count = m_Rcp_File.Get__Step_Size();
		if(step_count < 1)						step_count = 1;
		if(p_rcp_item->bActive__Header_Rcp)		step_count = 1;

		int col_limit = step_count + 1;

		m_Grid.SetRowCount(row_limit);
		m_Grid.SetColumnCount(col_limit);

		// Rcp Data ...
		for(row = 0; row < row_limit; row++) 
		{
			CDS__Rcp_Item rcp_item;

			if(p_rcp_item->Get__ITEM_INFO(row, &rcp_item) < 0)
			{
				continue;
			}

			// ...
			CString row_title;

			if(row == 0)		row_title = p_rcp_item->sRcp_Title;
			else				row_title = rcp_item.sPara__RCP_TITLE;

			int ch_type = rcp_item.iPara__CH_TYPE;

			for(int col = 0; col < col_limit; col++) 
			{ 
				GV_ITEM Item;

				Item.mask = GVIF_TEXT |GVIF_FORMAT | GVIF_IMAGE;
				Item.row  = row;
				Item.col  = col;
				Item.iImage = -1;

				if(row < m_nFixRows) 
				{
					Item.nFormat = txt_center_style;

					if(col == 0)			Item.strText = row_title;
					else					Item.strText.Format("%1d", col);
				} 
				else if(col < m_nFixCols) 
				{
					Item.nFormat = txt_left_style;

					if(col == 0) 
					{
						if(rcp_item.bPara__CATEGORY_ACTIVE)
						{
							if(rcp_item.bPara__CATEGORY_EXPAND)			Item.iImage = _ITEM_IMG__EXPAND;
							else										Item.iImage = _ITEM_IMG__CONTRACT;
						}
						else if(rcp_item.bPara__CHILD_ACTIVE)
						{
							Item.iImage = _ITEM_IMG__CHILD;
						}

						if(rcp_item.bPara__CATEGORY_ACTIVE)
						{
							Item.strText.Format("  %s", row_title);
						}
						else
						{
							if(rcp_item.bActive__CH_TITLE)
							{
								CString ch_name = rcp_item.sPara__CH_TITLE;
								CString ch_data;

								p_para_ctrl->Get__Data_From_Ch_Name(ch_name, ch_data);
								Item.strText = ch_data;
							}
							else
							{
								Item.strText = row_title;
							}
						}
					}
					else
					{
						Item.strText = "???";
					}
				} 
				else 
				{
					Item.nFormat = txt_center_style;
					Item.strText = m_Rcp_File.Get__Step_Data(col, rcp_item.sPara__CH_NAME);
				}

				if(row == 0)
				{
					COLORREF bk_color = color__dark_blue;

					m_Grid.SetItemBkColour(row, col, bk_color);
					m_Grid.SetItemFgColour(row, col, color__white);
				}
				else
				{
					if(col < m_nFixCols) 
					{
						COLORREF bk_color = color__child_col;

							 if(Item.iImage <  0)						bk_color = color__dark_blue;
						else if(Item.iImage == _ITEM_IMG__EXPAND)		bk_color = color__dark_gray;
						else if(Item.iImage == _ITEM_IMG__CONTRACT)		bk_color = color__dark_gray;

						m_Grid.SetItemBkColour(row, col, bk_color);
						m_Grid.SetItemFgColour(row, col, color__white);
					}
					else
					{
						COLORREF tx_color = color__black;
						COLORREF bk_color = color__white;

						if(rcp_item.bPara__CATEGORY_ACTIVE)
						{
							bk_color = color__light_gray;
							Item.strText = "";
						}
						else
						{
							tx_color = rcp_item.cColor_TEXT;
							bk_color = rcp_item.cColor_BACK;
						}

						m_Grid.SetItemBkColour(row, col, bk_color);
						m_Grid.SetItemFgColour(row, col, tx_color);
					}
				}

				m_Grid.SetItem(&Item);  
			}

			if(ch_type == _CH_TYPE__SUB_PARA)
			{
				if(bActive__Interlock_Dll)
				{
					CStringArray l_title;
					xI_Rcp_Interlock_Ctrl->Get__ALL_TITLE_OF_SUB_PAGE(iMODULE_ID, l_title);

					int limit = l_title.GetSize();
					int i;

					for(i=0; i<limit; i++)
					{
						if(i >= col_limit)			continue;
	
						m_Grid.SetItemText(row,i+1, l_title[i]);
					}
				}
			}
		}

		m_Grid.AutoSize();

		if(row_limit > 0)
		{
			m_Grid.SetRowHeight(0, 35);

			for(row = 1; row < row_limit; row++) 
			{
				m_Grid.SetRowHeight(row, iItem_Height);
			}
		}
		if(col_limit > 0)
		{
			int col_width = p_rcp_item->iItem_Title__Width;
			if(col_width < 120)		col_width = 120;

			// ...
			int col;

			for(col = m_nFixCols; col < col_limit; col++) 
			{ 
				m_Grid.SetColumnWidth(col, 120);
			}
			for(col = 0; col < m_nFixCols; col++) 
			{
				m_Grid.SetColumnWidth(col, col_width);
			}
		}
	}

	m_Grid.Refresh();
}
void CDlg__PROCESS_STD::_Append__Grid_Table(CInfo__Rcp_Item* p_rcp_item, const int next_id, const int first_id)
{
	if(p_rcp_item == NULL)
	{
		return;
	}

	// ...
	int col_size = next_id;
	if(next_id < 0)		col_size = m_Grid.GetColumnCount();

	int step_count = first_id;
	if(first_id < 0)	step_count = m_Rcp_File.Get__Step_Size();

	// ...
	{
		CString str_data;

		str_data.Format("%1d", step_count);
		mData__Sel_Step_Count.SetWindowText(str_data);
	}

	// ...
	COLORREF color__child_col  = RGB( 40, 108, 149);	
	COLORREF color__dark_blue  = RGB(  0,  66, 123);
	COLORREF color__navy_blue  = RGB(  0,  50, 149);
	COLORREF color__light_blue = RGB( 95, 164, 226);

	COLORREF color__cian       = RGB(24, 218, 245);
	COLORREF color__light_gray = RGB(234, 239, 242);
	COLORREF color__dark_gray  = RGB(117, 129, 138);
	COLORREF color__mid_gray   = RGB(223, 225, 225);

	COLORREF color__white = RGB(255, 255, 255);	
	COLORREF color__black = RGB(  0,   0,   0);	
	COLORREF color__blue  = RGB(  0, 125, 205);	

	// ...
	{
		int row_limit = p_rcp_item->Get__ITEM_SIZE();
		int row;

		int m_nFixRows = 1;
		int m_nFixCols = 1;

		//
		DWORD txt_center_style = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
		DWORD txt_left_style   = DT_LEFT   | DT_VCENTER | DT_SINGLELINE;

		// ...
		if(step_count < 1)						step_count = 1;
		if(p_rcp_item->bActive__Header_Rcp)		step_count = 1;

		int col_limit = step_count + 1;

		m_Grid.SetRowCount(row_limit);
		m_Grid.SetColumnCount(col_limit);

		// Rcp Data ...
		for(row = 0; row < row_limit; row++) 
		{
			CDS__Rcp_Item rcp_item;

			if(p_rcp_item->Get__ITEM_INFO(row, &rcp_item) < 0)
			{
				continue;
			}

			// ...
			int ch_type = rcp_item.iPara__CH_TYPE;

			for(int col = col_size; col < col_limit; col++) 
			{ 
				GV_ITEM Item;

				Item.mask = GVIF_TEXT |GVIF_FORMAT | GVIF_IMAGE;
				Item.row  = row;
				Item.col  = col;
				Item.iImage = -1;

				if(row < m_nFixRows) 
				{
					Item.nFormat = txt_center_style;
					Item.strText.Format("%1d", col);
				} 
				else 
				{
					Item.nFormat = txt_center_style;
					Item.strText = m_Rcp_File.Get__Step_Data(col, rcp_item.sPara__CH_NAME);
				}

				if(row == 0)
				{
					COLORREF bk_color = color__dark_blue;

					m_Grid.SetItemBkColour(row, col, bk_color);
					m_Grid.SetItemFgColour(row, col, color__white);
				}
				else
				{
					COLORREF tx_color = color__black;
					COLORREF bk_color = color__white;

					if(rcp_item.bPara__CATEGORY_ACTIVE)
					{
						bk_color = color__light_gray;
						Item.strText = "";
					}
					else
					{
						tx_color = rcp_item.cColor_TEXT;
						bk_color = rcp_item.cColor_BACK;
					}

					m_Grid.SetItemBkColour(row, col, bk_color);
					m_Grid.SetItemFgColour(row, col, tx_color);
				}

				m_Grid.SetItem(&Item);  
			}

			if(ch_type == _CH_TYPE__SUB_PARA)
			{
				if(bActive__Interlock_Dll)
				{
					CStringArray l_title;
					xI_Rcp_Interlock_Ctrl->Get__ALL_TITLE_OF_SUB_PAGE(iMODULE_ID, l_title);

					int limit = l_title.GetSize();
					int i;

					for(i=0; i<limit; i++)
					{
						if(i >= col_limit)			continue;

						m_Grid.SetItemText(row,i+1, l_title[i]);
					}
				}
			}
		}

		for (int col = col_size; col < col_limit; col++) 
		{ 
			m_Grid.SetColumnWidth(col, 120);
		}
	}

	m_Grid.Refresh();
}

void CDlg__PROCESS_STD::
_Fnc__Grid_Contract(const int row,const int col, CInfo__Rcp_Item* p_rcp_item)
{
	int node_state = _ITEM_IMG__CONTRACT;

	_Fnc__Grid_Catergory(row,col, p_rcp_item,node_state);
}
void CDlg__PROCESS_STD::
_Fnc__Grid_Expand(const int row,const int col, CInfo__Rcp_Item* p_rcp_item)
{
	int node_state = _ITEM_IMG__EXPAND;

	_Fnc__Grid_Catergory(row,col, p_rcp_item,node_state);
}
void CDlg__PROCESS_STD::
_Fnc__Grid_Catergory(const int row,const int col, CInfo__Rcp_Item* p_rcp_item,const int node_state)
{
	GV_ITEM Item;

	Item.nFormat = DT_LEFT | DT_VCENTER | DT_SINGLELINE;
	Item.mask = GVIF_TEXT | GVIF_FORMAT | GVIF_IMAGE;
	Item.row  = row;
	Item.col  = col;

	Item.iImage  = node_state;					
	Item.strText = m_Grid.GetItemText(row, col);

	m_Grid.SetItem(&Item);  

	//
	int child_size   = p_rcp_item->Get__CHILD_SIZE_OF_ROW(row);
	int child_height = iItem_Height;

	if(node_state == _ITEM_IMG__CONTRACT)
	{
		child_height = 0;
		p_rcp_item->Disable__CATEGORY_EXPAND_OF_ROW(row);
	}
	else
	{
		p_rcp_item->Enable__CATEGORY_EXPAND_OF_ROW(row);
	}

	for (int i = 1; i <= child_size; i++) 
	{ 
		m_Grid.SetRowHeight(row+i, child_height);
	}
	m_Grid.Refresh();
}
