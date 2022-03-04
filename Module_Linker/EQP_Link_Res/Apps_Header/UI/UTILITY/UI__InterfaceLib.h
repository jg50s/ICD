#include "c:\ges__application_interface\interface_header\ui\utility\ui__interfacelib_header.h"

#ifndef _UI__INTERFACE_LIB_H_
#define _UI__INTERFACE_LIB_H_
	

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


#endif

