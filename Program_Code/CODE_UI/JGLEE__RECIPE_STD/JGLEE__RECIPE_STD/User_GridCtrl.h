#pragma once

#include "GridCtrl.h"


class CUser_GridCtrl : public CGridCtrl
{
public:
	bool bActive_Fixed;
	int  iSel_Row;
	int  iSel_Col;

public:
	virtual void OnFixedColumnClick(CCellID& cell)
	{
		bActive_Fixed = TRUE;
		iSel_Row = cell.row;
		iSel_Col = cell.col;

		CGridCtrl::OnFixedColumnClick(cell);
	}
	virtual void OnFixedRowClick(CCellID& cell)
	{
		bActive_Fixed = TRUE;
		iSel_Row = cell.row;
		iSel_Col = cell.col;

		CGridCtrl::OnFixedRowClick(cell);
	}
};
