#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Wafer_Trace.h"

#include "Macro_Function.h"
#include "Macro__Wafer_Tree.h"


// ...
void CDlg__Wafer_Trace::
_Update__Wafer_Info(const CString& file_path)
{
	MACRO__Update__Wafer_Info(file_path, &mWfr_Info);
}
