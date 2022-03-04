#pragma once


//----------------------------------------------------
class CI_FA_300mm__E30_CTRL
{
public:
	virtual ~CI_FA_300mm__E30_CTRL(){};

	//----------------------------------------------------
	// ONLINE CONTROL
	virtual int  Set_OFFLINE() = 0;
	virtual int  Set_LOCAL()   = 0;
	virtual int  Set_REMOTE()  = 0;

	virtual int  Is_ONLINE() = 0;
	virtual int  Is_LOCAL()  = 0;
	virtual	int  Is_REMOTE() = 0;

	// SYSTEM CONTROL
	virtual int  Set_SYSTEM__PAUSE()  = 0;
	virtual int  Set_SYSTEM__RESUME() = 0;
	virtual int  Set_SYSTEM__END()    = 0;
	virtual int  Set_SYSTEM__STOP()   = 0;
	virtual int  Set_SYSTEM__ABORT()  = 0;

	virtual int  Can_SYSTEM__PAUSE()  = 0;
	virtual int  Can_SYSTEM__RESUME() = 0;
	virtual int  Can_SYSTEM__END()    = 0;
	virtual int  Can_SYSTEM__STOP()   = 0;
	virtual int  Can_SYSTEM__ABORT()  = 0;

	// LOAD-PORT CONTROL
	virtual int  Is_LP__IN_SERVICE(const int ptn) = 0;
	virtual int  Is_LP__BYPASS_READ_ID(const int ptn) = 0;

	virtual int  Set_LP__CANCEL(const int ptn) = 0;
	virtual int  Set_LP__PAUSE(const int ptn)  = 0;
	virtual int  Set_LP__RESUME(const int ptn) = 0;
	virtual int  Set_LP__ABORT(const int ptn)  = 0;

	virtual int  Can_LP__CANCEL(const int ptn) = 0;
	virtual int  Can_LP__PAUSE(const int ptn)  = 0;
	virtual int  Can_LP__RESUME(const int ptn) = 0;
	virtual int  Can_LP__ABORT(const int ptn)  = 0;

	virtual int  Read_LP__PAGE(const int ptn,
							   const int data_seg,
							   const int data_len,
							   const int sec,
							   CString& data_page) = 0;
	virtual int  Read_LP__CID(const int ptn,
							  const int sec,
							  CString& data_cid) = 0;

	virtual int  Write_LP__PAGE(const int ptn,
							    const int data_seg,
							    const int data_len,
								const int sec,
								const CString& data_page) = 0;
	virtual int  Write_LP__CID(const int ptn,
							   const int sec,
							   const CString& data_cid) = 0;

	//------------------------------------------------------------------
	// PTN

	virtual int  Event__LP__STATUS_CHANGE(const int ptn) = 0;
	virtual int  Event__LP__START(const int ptn) = 0;
	virtual int  Event__LP__RESERVE(const int ptn) = 0;
	virtual int  Event__LP__COMPLETE(const int ptn) = 0;
	virtual int  Event__LP__CANCEL(const int ptn) = 0;
	virtual int  Event__LP__PAUSE(const int ptn) = 0;
	virtual int  Event__LP__RESUME(const int ptn) = 0;
	virtual int  Event__LP__STOP(const int ptn) = 0;
	virtual int  Event__LP__ABORT(const int ptn) = 0;

	virtual int  Event__LP__FOUP_DOOR_OPEN(const int ptn) = 0;
	virtual int  Event__LP__FOUP_DOOR_CLOSE(const int ptn) = 0;
	virtual int  Event__LP__FOUP_CLAMPED(const int ptn) = 0;
	virtual int  Event__LP__FOUP_UNCLAMPED(const int ptn) = 0;
	virtual	int  Event__LP__FOUP_DOCKED(const int ptn) = 0;
	virtual int  Event__LP__FOUP_UNDOCKED(const int ptn) = 0;
	
	virtual int  Event__LP__CSTID_READ_START(const int ptn) = 0;
	virtual int  Event__LP__CSTID_READ_END(const int ptn) = 0;
	
	virtual int  Event__LP__SLOT_MAP_START(const int ptn) = 0;
	virtual int  Event__LP__SLOT_MAP_END(const int ptn) = 0;

	virtual int  Event__LP__LOT_DATA_REPORT(const int ptn) = 0;

	virtual int  Event__LP__LOAD_REQUEST(const int ptn) = 0;
	virtual int  Event__LP__LOAD_COMPLETE(const int ptn) = 0;
	
	virtual int  Event__LP__UNLOAD_REQUEST(const int ptn) = 0;
	virtual int  Event__LP__UNLOAD_COMPLETE(const int ptn) = 0;
	
	
	virtual int  Event__LP__AccessMode__AUTO(const int ptn) = 0;
	virtual int  Event__LP__AccessMode__MANUAL(const int ptn) = 0;

	virtual int  Event__LP__CarrierIDStatus__ID_NOT_READ(const int ptn) = 0;
	virtual int  Event__LP__CarrierIDStatus__ID_WAITING_FOR_HOST(const int ptn) = 0;
	virtual int  Event__LP__CarrierIDStatus__ID_VERIFICATION_OK(const int ptn) = 0;
	virtual int  Event__LP__CarrierIDStatus__ID_VERIFICATION_FAILED(const int ptn) = 0;

	virtual int  Event__LP__SlotMapStatus__SLOT_MAP_NOT_READ(const int ptn) = 0;
	virtual int  Event__LP__SlotMapStatus__SLOT_MAP_WAITING_FOR_HOST(const int ptn) = 0;
	virtual int  Event__LP__SlotMapStatus__SLOT_MAP_VERIFICATION_OK(const int ptn) = 0;
	virtual int  Event__LP__SlotMapStatus__SLOT_MAP_VERIFICATION_FAILED(const int ptn) = 0;

	virtual int  Event__LP__CarrierAccessStatus__NOT_ACCESSED(const int ptn) = 0;
	virtual int  Event__LP__CarrierAccessStatus__IN_ACCESS(const int ptn) = 0;
	virtual int  Event__LP__CarrierAccessStatus__CARRIER_COMPLETE(const int ptn) = 0;
	virtual int  Event__LP__CarrierAccessStatus__CARRIER_STOPPED(const int ptn) = 0;

	virtual int  Event__LP__ReservationStatus__NOT_RESERVED(const int ptn) = 0;
	virtual int  Event__LP__ReservationStatus__RESERVED(const int ptn) = 0;

	virtual int  Event__LP__AssociationStatus__NOT_ASSOCIATED(const int ptn) = 0;
	virtual int  Event__LP__AssociationStatus__ASSOCIATED(const int ptn) = 0;
	
	virtual int  Event__LP__TransferStatus__OUT_OF_SERVICE(const int ptn) = 0;
	virtual int  Event__LP__TransferStatus__TRANSFER_BLOCKED(const int ptn) = 0;
	virtual int  Event__LP__TransferStatus__READY_TO_LOAD(const int ptn) = 0;
	virtual int  Event__LP__TransferStatus__READY_TO_UNLOAD(const int ptn) = 0;
	virtual int  Event__LP__TransferStatus__IN_SERVICE(const int ptn) = 0;
	
	
	//------------------------------------------------------------------
	// PTN & SLOT

	virtual int  Event__LP__FIRST_WAFER_FROM_FOUP(const int ptn,const int slot) = 0;
	virtual int  Event__LP__LAST_WAFER_INTO_FOUP(const int ptn,const int slot) = 0;
	
	virtual int  Event__LP__WAFER_FROM_FOUP(const int ptn,const int slot) = 0;
	virtual int  Event__LP__WAFER_INTO_FOUP(const int ptn,const int slot) = 0;
	
	virtual int  Event__LP__WAFER_TRANSFER_START(const int ptn,
												 const int slot,
												 const CString& trg_module) = 0;
	virtual int  Event__LP__WAFER_TRANSFER_END(const int ptn,const int slot) = 0;

	virtual int  Event__LP__WAFER_INTO_PMC(const int ptn,
										   const int slot,
										   const int pmc_id,
										   const CString& pmc_module) = 0;
	virtual int  Event__LP__WAFER_FROM_PMC(const int ptn,
										   const int slot,
										   const int pmc_id) = 0;
	
	virtual int  Event__LP__WAFER_PROCESS_START(const int ptn,
												const int slot,
												const int pmc_id,
												const CString& recipe) = 0;
	virtual int  Event__LP__WAFER_PROCESS_END(const int ptn,
											  const int slot,
											  const int pmc_id) = 0;
	virtual int  Event__LP__WAFER_PROCESS_DATA_REPORT(const int ptn,const int slot) = 0;
	
	virtual int  Event__LP__WAFER_STEP_START(const int ptn,const int slot) = 0;
	virtual int  Event__LP__WAFER_STEP_END(const int ptn,const int slot) = 0;
	virtual int  Event__LP__WAFER_STEP_DATA_REPORT(const int ptn,const int slot) = 0;
	
	virtual	int  Event__LP__WAFER_VISIT_HISTORY_REPORT(const int ptn,const int slot) = 0;


	//------------------------------------------------------------------
	// RCMD LIST

	virtual int  RCMD__Is_ENABLED__SYSTEM_PAUSE()   = 0;
	virtual int  RCMD__Is_ENABLED__SYSTEM_RESUME()  = 0;
	virtual int  RCMD__Is_ENABLED__SYSTEM_END()     = 0;
	virtual int  RCMD__Is_ENABLED__SYSTEM_STOP()    = 0;
	virtual int  RCMD__Is_ENABLED__SYSTEM_ABORT()   = 0;

	virtual int  RCMD__Is_ENABLED__SYSTEM_REMOTE()  = 0;
	virtual int  RCMD__Is_ENABLED__SYSTEM_LOCAL()   = 0;
	virtual int  RCMD__Is_ENABLED__SYSTEM_OFFLINE() = 0;

	virtual int  RCMD__Is_ENABLED__PTN_CANCEL() = 0;
	virtual int  RCMD__Is_ENABLED__PTN_PAUSE()  = 0;
	virtual int  RCMD__Is_ENABLED__PTN_RESUME() = 0;
	virtual int  RCMD__Is_ENABLED__PTN_ABORT()  = 0;

	virtual int  RCMD__Is_ENABLED__PM_ENABLE()  = 0;
	virtual int  RCMD__Is_ENABLED__PM_DISABLE() = 0;
	virtual int  RCMD__Is_ENABLED__PM_CONTROL() = 0;

	virtual int  RCMD__Does_EXIST__PMC(const int pmc_id) = 0;

 	virtual int  RCMD__Set_PM__USE(const int pmc_id,
								   const int use_flag) = 0;


	//------------------------------------------------------------------
	virtual int  Event__OPERATOR_COMMAND_ISSUED() = 0;

	virtual int  Event__PROCESSING_STARTED() = 0;
	virtual int  Event__PROCESSING_COMPLETED() = 0;
	virtual int  Event__PROCESSING_STOPPED() = 0;
	virtual int  Event__PROCESSING_STATUS_CHANGE() = 0;
	
	virtual int  Event__ALARM_DETECTED() = 0;
	virtual int  Event__ALARM_CLEARED() = 0;
	
	virtual int  Event__OPERATOR_ECID_CHANGE() = 0;
	
	virtual int  Event__PROCESS_PROGRAM_CHANGE() = 0;
	virtual int  Event__PROCESS_PROGRAM_SELECTED() = 0;
	
	virtual int  Event__MATERIAL_RECEIVED(const int ptn) = 0;
	virtual int  Event__MATERIAL_REMOVED(const int ptn) = 0;
	
	virtual int  Event__SPOOLING_ACTIVATED() = 0;
	virtual int  Event__SPOOLING_DEACTIVATED() = 0;
	virtual int  Event__SPOOL_TRANSMIT_FAILURE() = 0;
	
	virtual int  Event__MESSAGE_RECOGNITION() = 0;
	
	virtual int  Event__NEW_EXECUTION_RECIPE() = 0;
	virtual int  Event__EXECUTION_RECIPE_CHANGE() = 0;
	
	virtual int  Event__SUCCESSFUL_UPLOAD() = 0;
	virtual int  Event__BAD_UPLOAD() = 0;


	//------------------------------------------------------------------
	virtual int  Spool__Transmit() = 0;
	virtual int  Spool__Purge() = 0;

	virtual int  Spool__Clear_All_SxFy() = 0;
	virtual int  Spool__Clear_SxFy(const int sx) = 0;
	virtual int  Spool__Load_SxFy(const int sx,const int fy) = 0;


	//------------------------------------------------------------------
	// RCMD LIST

	virtual int  RCMD__Set_ON__ALARM_BUZZER() = 0;
	virtual int  RCMD__Set_OFF_ALARM_BUZZER() = 0;

	virtual int  RCMD__Set_ON__SIG_RED()    = 0;
	virtual int  RCMD__Set_ON__SIG_YELLOW() = 0;
	virtual int  RCMD__Set_ON__SIG_GREEN()  = 0;
	virtual int  RCMD__Set_ON__SIG_BLUE()   = 0;

	virtual int  RCMD__Set_OFF__SIG_RED()    = 0;
	virtual int  RCMD__Set_OFF__SIG_YELLOW() = 0;
	virtual int  RCMD__Set_OFF__SIG_GREEN()  = 0;
	virtual int  RCMD__Set_OFF__SIG_BLUE()   = 0;

	virtual int  RCMD__Set_BLINK__SIG_RED()    = 0;
	virtual int  RCMD__Set_BLINK__SIG_YELLOW() = 0;
	virtual int  RCMD__Set_BLINK__SIG_GREEN()  = 0;
	virtual int  RCMD__Set_BLINK__SIG_BLUE()   = 0;


	virtual int  RCMD__Is_ENABLED__ALARM_BUZZER() = 0;

	virtual int  RCMD__Is_ENABLED__SIG_RED()    = 0;
	virtual int  RCMD__Is_ENABLED__SIG_YELLOW() = 0;
	virtual int  RCMD__Is_ENABLED__SIG_GREEN()  = 0;
	virtual int  RCMD__Is_ENABLED__SIG_BLUE()   = 0;


	virtual int  Event__PROCESS_PROGRAM_CHANGE__WITH_PARA(const CString& pp_name,
														  const int pp_status) = 0;
	virtual int  Event__PROCESS_PROGRAM_SELECTED__WITH_PARA(const CString& pp_name) = 0;


	//------------------------------------------------------------------
	virtual int  Event__CHM__WAFER_PROCESS_START(const int chm_id) = 0;
	virtual int  Event__CHM__WAFER_PROCESS_END(const int chm_id) = 0;
	virtual int  Event__CHM__STEP_START(const int chm_id) = 0;
	virtual int  Event__CHM__STEP_END(const int chm_id)   = 0;
	virtual int  Event__CHM__WAFER_IN(const int chm_id)   = 0;
	virtual int  Event__CHM__WAFER_OUT(const int chm_id)  = 0;


	//------------------------------------------------------------------
	virtual int  Set__REPORT_ALL_ALARM()   = 0;
	virtual int  Clear__REPORT_ALL_ALARM() = 0;
	virtual int  Check__REPORT_ALL_ALARM() = 0;


	//------------------------------------------------------------------
	virtual int  Event__VIS_PROC_START(const int vis_id) = 0;
	virtual int  Event__VIS_PROC_END(const int vis_id) = 0;


	//------------------------------------------------------------------
	virtual int  Event__CHM__CLEAN_START(const int pmc_id) = 0;
	virtual int  Event__CHM__CLEAN_END(const int pmc_id)   = 0;

	virtual int  Event__CHM__LeakCheck_START(const int pmc_id) = 0;
	virtual int  Event__CHM__LeakCheck_END(const int pmc_id)   = 0;
	virtual int  Event__CHM__LeakCheck_SAMPLING_DATA(const int pmc_id) = 0;

	//.....
	virtual int  Event__CHM__DOWN(const int pmc_id) = 0;

	virtual int  Event__CHM__DOOR_OPEN(const int pmc_id)  = 0;
	virtual int  Event__CHM__DOOR_CLOSE(const int pmc_id)  = 0;
	
	virtual int  Event__CHM__LIFT_PIN_UP(const int pmc_id)   = 0;
	virtual int  Event__CHM__LIFT_PIN_DOWN(const int pmc_id) = 0;


	//------------------------------------------------------------------
	virtual int  Event__EQUIPMENT_ENG_CALL() = 0;
	virtual int  Event__PROCESS_ENG_CALL() = 0;


	//------------------------------------------------------------------
	virtual	int  Is_OFFLINE() = 0;
	virtual int  Is_CONNECT() = 0;


	//------------------------------------------------------------------
	virtual int  Event__EFEM__CARRIER_READY_TO_LOAD(const int ptn)   = 0;
	virtual int  Event__EFEM__CARRIER_READY_TO_UNLOAD(const int ptn) = 0;

	virtual int  Event__EFEM__CARRIER_ARRIVED(const int ptn)      = 0;
	virtual int  Event__EFEM__CARRIER_CLAMPED(const int ptn)      = 0;
	virtual int  Event__EFEM__CARRIER_DOCKING(const int ptn)      = 0;
	virtual int  Event__EFEM__CARRIER_DOOR_OPEN(const int ptn)    = 0;
	virtual int  Event__EFEM__CARRIER_SLOT_MAP(const int ptn)     = 0;
	virtual int  Event__EFEM__CARRIER_DOOR_CLOSE(const int ptn)   = 0;
	virtual int  Event__EFEM__CARRIER_UNDOCKING(const int ptn)    = 0;
	virtual int  Event__EFEM__CARRIER_UNCLAMPING(const int ptn)   = 0;
	virtual int  Event__EFEM__CARRIER_REMOVED(const int ptn)      = 0;
	virtual int  Event__EFEM__BCR_VERIFY_OK(const int ptn)        = 0;
	virtual int  Event__EFEM__SLOTMAP_VERIFY_OK(const int ptn)    = 0;
	virtual int  Event__EFEM__STATE_CHANGE(const int ptn)         = 0;
	virtual int  Event__EFEM__MODE_CHANGE(const int ptn)          = 0;
	virtual int  Event__EFEM__CARRIERID_READ(const int ptn)       = 0;
	virtual int  Event__EFEM__CARRIERID_READ_ERROR(const int ptn) = 0;
	virtual int  Event__EFEM__SLOTMAP_RESULT(const int ptn)       = 0;

	//.....
	virtual int  EFEM__Set_CID_VERIFY_RESULT(const int ptn,const int ok_flag) = 0;
	virtual int  EFEM__Set_SLOTMAP_VERIFY_RESULT(const int ptn,const int ok_flag) = 0;

	virtual int  EFEM__Receive_CID_VERIFY_RESULT_From_HOST(const int ptn,int& result) = 0;
	virtual int  EFEM__Receive_SLOTMAP_VERIFY_RESULT_From_HOST(const int ptn,int& result) = 0;

	//.....
	virtual int  Event__EFEM__AUTO_INITIATED()  = 0;
	virtual int  Event__EFEM__AUTO_COMPLETED()  = 0;
	virtual int  Event__EFEM__PAUSE_INITIATED() = 0;
	virtual int  Event__EFEM__PAUSE_COMPLETED() = 0;

	virtual int  Event__EFEM__PROCESSING_START(const int ptn) = 0;
	virtual int  Event__EFEM__PROCESSING_END(const int ptn)   = 0;

	//....
	virtual int  Event__CHM__WAFER_PROCESS_START_EX(const int chm_id,
													const int ptn,
													const int slot) = 0;
	virtual int  Event__CHM__WAFER_PROCESS_END_EX(const int chm_id,
												  const int ptn,
												  const int slot) = 0;


	//------------------------------------------------------------------
	// PTN & SLOT

	virtual int  Event__LP__WAFER_MHP_REPORT(const int ptn,const int slot) = 0;
	virtual int  Check_CEID__LPx_WAFER_MHP_REPORT(const int ceid,int& ptn) = 0;
	
	//.....
	virtual int  Get__MPH_INFO(CString& lp_slotid,
							   CString& cjobid,
							   CString& pjobid,
							   CString& lotid,
							   CString& cstid) = 0;


	//------------------------------------------------------------------
	virtual int  Set_LOCAL_BY_HOST()  = 0;
	virtual int  Set_REMOTE_BY_HOST() = 0;


	//------------------------------------------------------------------
	virtual int  Event__CHM__WAFER_PROCESS_FAIL(const int chm_id) = 0;

	virtual	int  Event__COMMUNICATION_STATE__DISABLE_TO_ENABLE() = 0;
	virtual int  Event__COMMUNICATION_STATE__ENABLE_TO_DISABLE() = 0;

	virtual int  Check__CONTROL_STATE__EQUIPMENT_OFFLINE() = 0;
	virtual int  Check__CONTROL_STATE__ONLINE_LOCAL() = 0;
	virtual int  Check__CONTROL_STATE__ONLINE_REMOTE() = 0;

	virtual int  Event__MESSAGE_CONFIRM() = 0;

	virtual int  Set__ALARM_CODE(const CString& str_alcode) = 0;

	virtual int  Check__SPOOLING_ACTIVE() = 0;
	virtual int  Get__SPOOLING_COUNT_ACTUAL() = 0;

	virtual int  Request__SPOOLING_ACTIVE() = 0;
	virtual int  Request__SPOOLING_INACTIVE() = 0;
	virtual int  Request__SPOOLING_PURGE() = 0;
	virtual int  Request__SPOOLING_TRANSMIT() = 0;

	//
	virtual int  Set__FA_LINE_STATUS__OFFLINE() = 0;
	virtual int  Set__FA_LINE_STATUS__LOCAL()   = 0;
	virtual int  Set__FA_LINE_STATUS__REMOTE()  = 0;

	//
	virtual int  Check__EVENT_OFFLINE__ACTIVE() = 0;
	virtual int  Check__EVENT_LOCAL__ACTIVE()   = 0;
	virtual int  Check__EVENT_REMOTE__ACTIVE()  = 0;

	virtual int  Set__EVENT_OFFLINE__ACTIVE() = 0;
	virtual int  Set__EVENT_LOCAL__ACTIVE()   = 0;
	virtual int  Set__EVENT_REMOTE__ACTIVE()  = 0;


	//------------------------------------------------------------------
	// SYSTEM CONTROL
	virtual int  Set_LP__RETURN(const int ptn)  = 0;

	// ...
	virtual int  Event__CHM__STEP_START_EX(const int chm_id, const int step_id) = 0;
	virtual int  Event__CHM__STEP_END_EX(const int chm_id, const int step_id)   = 0;

	//------------------------------------------------------------------
	// ...
	virtual int  Event__CHMx_STAGEy__STEP_START(const int chm_id,const int stage_id, const int step_id, const int lp_ptn,const int lp_slot) = 0;
	virtual int  Event__CHMx_STAGEy__STEP_END(const int chm_id,const int stage_id, const int step_id, const int lp_ptn,const int lp_slot)   = 0;

	virtual int  Event__CHMx_STAGEy__WAFER_IN(const int chm_id,const int stage_id, const int lp_ptn,const int lp_slot)  = 0;
	virtual int  Event__CHMx_STAGEy__WAFER_OUT(const int chm_id,const int stage_id, const int lp_ptn,const int lp_slot) = 0;
	
	virtual int  Event__CHMx_STAGEy__WAFER_PROCESS_START(const int chm_id,const int stage_id, const int lp_ptn,const int lp_slot) = 0;
	virtual int  Event__CHMx_STAGEy__WAFER_PROCESS_END(const int chm_id,const int stage_id, const int lp_ptn,const int lp_slot) = 0;
};
//----------------------------------------------------
