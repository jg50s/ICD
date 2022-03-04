#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Apps_Header\SUI__INTERFACE_LINK3__HEADER.h"


#ifdef _DEBUG
	#pragma comment(lib, "C:\\Module_Linker\\SUI_Link_Res\\SUI_LIB\\SUI__INTERFACE_LINK3_D.lib")
#else
	#pragma comment(lib, "C:\\Module_Linker\\SUI_Link_Res\\SUI_LIB\\SUI__INTERFACE_LINK3_R.lib")
#endif


extern "C"
{
CI_BMP*				New_BMP();
CI_DRAW*			New_DRAW();
CI_BUTTON*			New_BUTTON();
CI_UTILITY*			New_UTILITY();
CI_VSCROLLBAR*		New_VSCROLLBAR();
CI_HSCROLLBAR*		New_HSCROLLBAR();
CI_TABLE*			New_TABLE();
CI_DB_MDB*			New_DB_MDB();
CI_TABLE_MDB*		New_TABLE_MDB();
CI_TABLE_GRID*		New_TABLE_GRID();
CI_GRAPH*			New_GRAPH();
CI_DB_RCP*			New_DB_RCP();
CI_TABLE_CSV*		New_TABLE_CSV();
CI_TABLE_CSV_300*	New_TABLE_CSV_300();
CI_PROGRAM_CONTROL* New_PROGRAM_CONTROL(); 
CI_RECIPE_CONFIG*	New_RECIPE_CONFIG();
}


//----------------------------------------------------
class CX_UTILITY
{
private:
	CI_UTILITY *m_pT;

public:
	CX_UTILITY()
	{
		m_pT = New_UTILITY();
	}
	~CX_UTILITY()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_UTILITY* operator->() const
	{
		return m_pT;
	}
};

class CX_PROGRAM_CONTROL
{
private:
	CI_PROGRAM_CONTROL *m_pT;

public:
	CX_PROGRAM_CONTROL()
	{
		m_pT = New_PROGRAM_CONTROL();
	}
	~CX_PROGRAM_CONTROL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_PROGRAM_CONTROL* operator->() const
	{
		return m_pT;
	}
};
