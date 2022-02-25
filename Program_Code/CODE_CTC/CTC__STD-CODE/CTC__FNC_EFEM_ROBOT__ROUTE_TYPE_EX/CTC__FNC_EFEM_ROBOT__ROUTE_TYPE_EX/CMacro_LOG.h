#pragma once

#include "Interface_Code.h"


class CMacro_Log
{
private:
	SCX__SEQ_INFO  xI_SYS_INFO;
	SCX__CTC__LOT_SUMMARY_CTRL  xI_LOT_SUMMARY;
	SCX__CTC__MATERIAL_LOG_CTRL xI_MATERIAL_LOG;

	int iINIT_LOG;

public:
	CMacro_Log();
	~CMacro_Log();

	// ...
	int Init_LOG();

	// ...
	int Get_DateTime(CString &date,CString &time);

	int Get_ArmType(const CString& arm);
	int Get_ModuleType(const CString& module);

	int Log_Material_Pick(const CString& arm,
							const CString& module,
							const CString& material,
							const CString& lotid,
							const CString& recipe,
							int	ex_flag);
	int Log_Material_Picking(const CString& arm,
							const CString& module,
							const CString& material,
							const CString& lotid,
							const CString& recipe,
							int	ex_flag);

	int Log_Material_Place(const CString& arm,
							const CString& module,
							const CString& material,
							const CString& lotid,
							const CString& recipe,
							int	ex_flag);
	int Log_Material_Placing(const CString& arm,
							const CString& module,
							const CString& material,
							const CString& lotid,
							const CString& recipe,
							int	ex_flag);

	// ...
	int Lot_Write(const CString& lotid,const CString& portid);
	int Lot_End_Write(const CString& lotid,const CString& portid);

	int Lot_Slot_Write(const CString& lotid,const CString& portid,
					   int slot,const CString& module,const CString& recipeid,const CString& log);
	int Lot_Slot_End_Write(const CString& lotid,const CString& portid,int slot);

	int Lot_Slot_AlarmPost(const CString& lotid,const CString& portid,int slot,int alarmid);
	int Lot_Slot_AlarmClear(const CString& lotid,const CString& portid,int slot,int alarmid);
};
