#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__Macro.h"


//----------------------------------------------------
class CDS_CASSETTE_INFO
{
public:
	CDS_CASSETTE_INFO()
	{
		iPTN = 0;
		iCAPACITY = 0;
		iSUBSTRATE_COUNT = 0;
		iCONTENT_LIMIT = 0;
		iSLOTMAP_LIMIT = 0;
	}

	CString sCARRIER_ACTION;
	CString sCARRIER_ID;
	int		iPTN;

	int     iCAPACITY;
	int     iSUBSTRATE_COUNT;
	CString sUSAGE;

	int		iCONTENT_LIMIT;
	CStringArray sLOTID_LIST;
	CStringArray sWAFERID_LIST;

	int		iSLOTMAP_LIMIT;
	CStringArray sSLOTMAP_LIST;

	int     iWID_ANGLG_LIMIT;
	CStringArray sWID_ANGLE_LIST;
};
//----------------------------------------------------

//----------------------------------------------------
class CI_FA_300mm__E87_CTRL
{
public:
	virtual ~CI_FA_300mm__E87_CTRL(){};


	//------------------------------------------------------------------------------------------
	virtual int  Event__LP__ACCESS_MODE__AUTO(const int ptn) = 0;
	virtual int  Event__LP__ACCESS_MODE__MANUAL(const int ptn) = 0;

	virtual int  Event__LP__IN_SERVICE(const int ptn) = 0;
	virtual int  Event__LP__OUT_OF_SERVICE(const int ptn) = 0;

	virtual int  Event__LP__TRANSFER_READY(const int ptn) = 0;
	virtual int  Event__LP__READY_TO_UNLOAD(const int ptn) = 0;
	virtual int  Event__LP__READY_TO_LOAD(const int ptn) = 0;
	virtual int  Event__LP__TRANSFER_BLOCKED(const int ptn) = 0;

	virtual int  Event__LP__ID_NOT_READ(const int ptn) = 0;
	virtual int  Event__LP__ID_WAITING_FOR_HOST(const int ptn) = 0;
	virtual int  Event__LP__ID_VERIFICATION_OK(const int ptn) = 0;
	virtual int  Event__LP__ID_VERIFICATION_FAIL(const int ptn) = 0;
	virtual	int  Event__LP__ID_WAITING_FOR_HOST__BypassReadID_False(const int ptn) = 0;
	virtual int  Event__LP__ID_VERIFICATION_OK__BypassReadID_True(const int ptn) = 0;
			
	virtual int  Event__LP__NOT_ACCESSED(const int ptn) = 0;
	virtual int  Event__LP__IN_ACCESS(const int ptn) = 0;
	virtual int  Event__LP__CARRIER_COMPLETE(const int ptn) = 0;
	virtual int  Event__LP__CARRIER_STOPPED(const int ptn) = 0;

	virtual int  Event__LP__SLOT_MAP_NOT_READ(const int ptn) = 0;
	virtual int  Event__LP__SLOT_MAP_WAITING_FOR_HOST(const int ptn) = 0;
	virtual int  Event__LP__SLOT_MAP_VERIFICATION_OK(const int ptn) = 0;
	virtual int  Event__LP__SLOT_MAP_VERIFICATION_FAIL(const int ptn) = 0;

	virtual int  Event__LP__NOT_RESERVED(const int ptn) = 0;
	virtual int  Event__LP__To_RESERVED(const int ptn) = 0;

	virtual int  Event__LP__NOT_ASSOCIATED(const int ptn) = 0;
	virtual int  Event__LP__ASSOCIATED(const int ptn) = 0;


	//----------------------------------------------------
	virtual int  Is_Active() = 0;

	
	//------------------------------------------------------------
	// Object Control
	virtual int  Load(const CDS_CASSETTE_INFO& cst_info) = 0;

	virtual int  Get_E87_Error(int& err_code,CString& err_text) = 0;


	//------------------------------------------------------------
	// VID MONITORING

	//------------------------------------
	// Carrier Attribute Definition
		
	// CarrierObject
	virtual int  Get_VID__CarrierID(const int ptn,CString& carrierid) = 0;

	// CarrierIDStatus
	virtual int  Get_VID__CarrierIDStatus(const int ptn,int& status) = 0;
		
	// CarrierAccessingStatus
	virtual int  Get_VID__CarrierAccessingStatus(const int ptn,int& status) = 0;
		
	// CarrierSlotMap
	// virtual int  Get_VID__CarrierSlotMap(const int ptn,CUIntArray& slot_map) = 0;

	// SlotMapStatus
	virtual int  Get_VID__SlotMapStatus(const int ptn,int& status) = 0;

	//------------------------------------
	// PortTransferState
	virtual int  Get_VID__PortTransferState(const int ptn,int& status) = 0;

	//------------------------------------
	// AccessMode
	virtual int  Get_VID__AccessMode(const int ptn,int& status) = 0;

	//------------------------------------
	// LoadPortReservationState
	virtual int  Get_VID__LoadPortReservationState(const int ptn,int& status) = 0;

	//------------------------------------
	// PortAssociationState
	virtual int  Get_VID__PortAssociationState(const int ptn,int& status) = 0;


	//------------------------------------------------------------
	virtual int  Set_Transfer__IN_SERVICE(const int ptn) = 0;
	virtual int  Set_Transfer__OUT_OF_SERVICE(const int ptn) = 0;

	virtual int  Set_AccessMode__AUTO(const int ptn) = 0;
	virtual int  Set_AccessMode__MANUAL(const int ptn) = 0;

	//------------------------------------------------------------
	virtual int  Set__CarrierID(const int ptn,
								const CString& carrierid) = 0;

	// SLOT_MAP_NOT_READ --> WAITING_FOR_HOST
	virtual int  Set_Reason__VERIFICATION_NEEDED(const int ptn) = 0;
	virtual int  Set_Reason__VERIFICATION_BY_EQUIPMENT_UNSUCCESSFUL(const int ptn) = 0;
	virtual int  Set_Reason__READ_FAIL(const int ptn) = 0;
	virtual int  Set_Reason__IMPROPER_SUBSTRATE_POSITION(const int ptn) = 0;

	virtual int  Get_Reason(const int ptn,int& reason) = 0;

	//------------------------------------------------------------
	virtual int  Receive__VERIFICATION_RESULT_From_HOST(const int ptn,
													    int& result) = 0;

	virtual int  Is_LP__ASSOCIATED(const int ptn) = 0;
	virtual int  Is__EQUIPMENT_BASED_VERIFICATION(const int ptn) = 0;

	virtual int  Get_LP__SLOT_MAP_INFO(const int ptn,
									   CStringArray& slot_map_list) = 0;	// "0" : EMPTY, "1" : OCCUPIED

	//------------------------------------------------------------
	virtual int  Create__LocalJOB(const CString& path,
								  const	CDS_CASSETTE_INFO& ds_cst_info) = 0;

	//------------------------------------------------------------
	virtual int  Create__CARRIER_With_CID_WAITING_FOR_HOST(const int ptn,
														   const CString& carrierid) = 0;

	virtual int  Create__CARRIER_With_CID_VERIFICATION_OK(const int ptn,
														  const CString& carrierid) = 0;


	//------------------------------------------------------------
	virtual int  Event__CARRIER_APPROACHING_COMPLETE(const int ptn) = 0;
	virtual int  Event__CARRIER_CLOSED(const int ptn) = 0;
	virtual int  Event__CARRIER_UNCLAMPED(const int ptn) = 0;
	virtual int  Event__ID_READER_UNAVAILABLE(const int ptn) = 0;
	virtual int  Event__ID_READER_AVILABLE(const int ptn) = 0;
	virtual int  Event__CARRIERID_READ_FAIL(const int ptn) = 0;
	virtual int  Event__CARRIER_CLAMPED(const int ptn) = 0;
	virtual int  Event__CARRIER_LOCATION_CHANGE(const int ptn,const CString& locid) = 0;
	virtual int  Event__CARRIER_OPENED(const int ptn) = 0;


	//------------------------------------------------------------
	virtual int  Set_PTN_CTRL__ReserveAtPort(const int ptn) = 0;
	virtual int  Set_PTN_CTRL__CancelReservationAtPort(const int ptn) = 0;

	virtual int  Read__CarrierTag(const CString& locid,
								  const CString& carrierspec,
								  const CString& dataseg,
								  const int datalen,
								  CString& tag_data) = 0;
	virtual int  Write__CarrierTag(const CString& locid,
								   const CString& carrierspec,
								   const CString& dataseg,
								   const int datalen,
								   const CString& tag_data) = 0;

	virtual int  Report_CarrierObject__CARRIER_To_NoState(const int ptn) = 0;
	virtual int  Report_CarrierIDStatus__NoState_To_ID_WAITING_FOR_HOST(const int ptn) = 0;

	virtual int  Event__UNKNOWN_CARRIERID(const int ptn) = 0;


	//------------------------------------------------------------
	virtual int  Report__LP__READY_TO_LOAD(const int ptn) = 0;
};
