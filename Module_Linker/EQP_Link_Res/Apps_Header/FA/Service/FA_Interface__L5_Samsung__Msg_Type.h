#pragma once


// ...
#define Msg_Type__Event_Info						          1
#define Msg_Type__Glass_DCOLL_Info					          2
#define Msg_Type__Job_DCOLL_Info					          3
#define Msg_Type__Unit_Info							          4
#define Msg_Type__Tool_Info							          5
#define Msg_Type__EQP_Info							          6
#define Msg_Type__Glass_Info						          7
#define Msg_Type__Alarm_Info						          8
#define Msg_Type__Alarm_Item						          9
#define Msg_Type__PPBody_Step_Info					          10
#define Msg_Type__Item_Info							          11
#define Msg_Type__EOMD_Info							          12
#define Msg_Type__EOID_Info							          13
#define Msg_Type__ECID_Info							          14
#define Msg_Type__ECID_Item							          15
#define Msg_Type__Reason_Code_Info					          16
#define Msg_Type__Current_Process_Control_Data		          17
#define Msg_Type__Process_Control_Result_Report               18
#define Msg_Type__Terminal_Message_To_Host			          19

#define Msg_Type__PLC_Process_Glass_Info                      101
#define Msg_Type__PLC_Process_Unload_Info                     102
#define Msg_Type__PLC_Component_Info						  103

// ...
#define DEF_SIZE__TOOL								          10
#define DEF_SIZE__UNIT								          10

#define GLS_STATE__Nothing							          0		 // Nothing
#define GLS_STATE__Idle								          1      // Idle
#define GLS_STATE__Selected_To_Process				          2      // Selected to Process
#define GLS_STATE__Processing						          3      // Processing
#define GLS_STATE__Done								          4      // Done
#define GLS_STATE__Aborting							          5      // Aborting
#define GLS_STATE__Aborted							          6	     // Aborted
#define GLS_STATE__Cancelled						          7      // Cancelled
#define GLS_STATE__Processing_Again					          8      // Processing Again
#define GLS_STATE__Done_Again						          9      // Done Again
#define GLS_STATE__Selected_To_Process_Again		          10     // Selected to Process Again

// ...
#define BYWHO__BY_HOST										  1		 // By Host 
#define BYWHO__BY_OPERATOR									  2      // By Operator
#define BYWHO__BY_EQUIPMENT                                   3      // By Equipment itself

#define MCMD__ONLINE_REMOTE									  1      // ONLINE REMOTE
#define MCMD__ONLINE_LOCAL									  2      // ONLINE LOCAL

#define EQST__MANUAL										  1      // MANUAL (DOWN)
#define EQST__IDLE											  2      // IDLE
#define EQST__BUSY											  3      // BUSY
#define EQST__ALARM											  4      // ALARM (STOPPING)

// ...
#define LOCAL_STS__MCMD							"MCMD"
#define LOCAL_STS__EQST							"EQST"
#define LOCAL_STS__EQSTATE						"EQSTATE"
#define LOCAL_STS__PPID							"PPID"
#define LOCAL_STS__GLASS_SIZE					"GLASS_SIZE"
#define LOCAL_STS__LOT_KIND						"LOT_KIND"
#define LOCAL_STS__DIRECTION					"DIRECTION"
#define LOCAL_STS__TACT							"TACT"
#define LOCAL_STS__STDCELL						"STDCELL"
#define LOCAL_STS__GLASS_TYPE					"GLASS_TYPE"
#define LOCAL_STS__CUT_RULE						"CUT_RULE"

// ...
#define GLS_KEY__EXIST							"KEY.EXIST"
#define GLS_KEY__UNITID							"KEY.UNITID"

// Job Info
#define GLS_ITEM__JSTATE						"JSTATE"
#define GLS_ITEM__STIF							"STIF"
#define GLS_ITEM__TOTALGSTATE					"TOTALGSTATE"
#define GLS_ITEM__SPLIT_MODE					"SPLIT_MODE"
#define GLS_ITEM__SORT_MODE						"SORT_MODE"

// Standard Type 
#define GLS_ITEM__OPID							"OPID"
#define GLS_ITEM__OCID							"OCID"
#define GLS_ITEM__GLASSID						"GLASSID"
#define GLS_ITEM__SLOTNO						"SLOTNO"

// Standard & Inline Type 
#define GLS_ITEM__LOTID							"LOTID"
#define GLS_ITEM__IPID							"IPID"
#define GLS_ITEM__ICID							"ICID"
#define GLS_ITEM__JOBID							"JOBID"
#define GLS_ITEM__PPID							"PPID"
#define GLS_ITEM__PROCESSID						"PROCESSID"
#define GLS_ITEM__PARTID						"PARTID"
#define GLS_ITEM__STEPID						"STEPID"
#define GLS_ITEM__GLASSTYPE						"GLASSTYPE"
#define GLS_ITEM__FSLOTID						"FSLOTID"
#define GLS_ITEM__TSLOTID						"TSLOTID"
#define GLS_ITEM__GLASS_STATE					"GLASS_STATE"
#define GLS_ITEM__UNITID						"UNITID"
#define GLS_ITEM__EQ_VAL						"EQ_VAL"
#define GLS_ITEM__RESULT						"RESULT"
#define GLS_ITEM__JUDGEMENT						"JUDGEMENT"
#define GLS_ITEM__NG_CODE						"NG_CODE"

// Inline Type
#define GLS_ITEM__H_GLASSID						"H_GLASSID"
#define GLS_ITEM__R_GLASSID						"R_GLASSID"
#define GLS_ITEM__CELLGRADE						"CELLGRADE"
#define GLS_ITEM__DIRECTION						"DIRECTION"
#define GLS_ITEM__GLASS_SIZE					"GLASS_SIZE"
#define GLS_ITEM__STD_CELL						"STD_CELL"
#define GLS_ITEM__LOT_KIND						"LOT_KIND"
#define GLS_ITEM__RUN_LINE						"RUN_LINE"
#define GLS_ITEM__POSITION						"POSITION"
#define GLS_ITEM__PAIR_SLOTNO					"PAIR_SLOTNO"
#define GLS_ITEM__PAIR_IPID						"PAIR_IPID"
#define GLS_ITEM__PAIR_ICID						"PAIR_ICID"
#define GLS_ITEM__PAIR_LOTID					"PAIR_LOTID"
#define GLS_ITEM__PAIR_H_GLASSID				"PAIR_H_GLASSID"
#define GLS_ITEM__PAIR_R_GLASSID				"PAIR_R_GLASSID"
#define GLS_ITEM__GLASSINFO						"GLASSINFO"
#define GLS_ITEM__SYSTEMBYTE					"SYSTEMBYTE"
#define GLS_ITEM__TACT							"TACT"
#define GLS_ITEM__COURSE						"COURSE"
#define GLS_ITEM__CUT_RULE						"CUT_RULE"
#define GLS_ITEM__PTID							"PTID"
#define GLS_ITEM__CSID							"CSID"
#define GLS_ITEM__RECEIVEMODE					"RECEIVEMODE"
#define GLS_ITEM__UNLOADTYPE					"UNLOADTYPE"
#define GLS_ITEM__SPLITMODE						"SPLITMODE"
#define GLS_ITEM__PTST							"PTST"
#define GLS_ITEM__PTMD							"PTMD"
#define GLS_ITEM__BCRMODE						"BCRMODE"
#define GLS_ITEM__VCRMODE						"VCRMODE"
#define GLS_ITEM__SORTMODE						"SORTMODE"

// Inline Type : All Glass Info
#define GLS_ITEM__INLINE__IPID				    "IPID"					    // 01.
#define GLS_ITEM__INLINE__ICID				    "ICID"					    // 02.
#define GLS_ITEM__INLINE__JOBID				    "JOBID" 				    // 03.
#define GLS_ITEM__INLINE__PROCESSID			    "PROCESSID"					// 04.
#define GLS_ITEM__INLINE__PARTID			    "PARTID" 				    // 05.
#define GLS_ITEM__INLINE__STEPID			    "STEPID"				    // 06.
#define GLS_ITEM__INLINE__GLASSTYPE			    "GLASSTYPE"					// 07.
#define GLS_ITEM__INLINE__LOTID				    "LOTID" 				    // 08.
#define GLS_ITEM__INLINE__H_GLASSID			    "H_GLASSID"					// 09.
#define GLS_ITEM__INLINE__R_GLASSID			    "R_GLASSID"					// 10.
#define GLS_ITEM__INLINE__PPID				    "PPID"					    // 11.
#define GLS_ITEM__INLINE__CELLGRADE			    "CELLGRADE"					// 12.
#define GLS_ITEM__INLINE__DIRECTION			    "DIRECTION"					// 13.
#define GLS_ITEM__INLINE__GLASS_SIZE			"GLASS_SIZE"				// 14.
#define GLS_ITEM__INLINE__STD_CELL			    "STD_CELL"					// 15.
#define GLS_ITEM__INLINE__LOT_KIND			    "LOT_KIND"					// 16.
#define GLS_ITEM__INLINE__RUN_LINE			    "RUN_LINE"					// 17.
#define GLS_ITEM__INLINE__POSITION			    "POSITION"					// 18.
#define GLS_ITEM__INLINE__PAIR_SLOTNO		    "PAIR_SLOTNO"				// 19.
#define GLS_ITEM__INLINE__PAIR_IPID			    "PAIR_IPID" 				// 20.  
#define GLS_ITEM__INLINE__PAIR_ICID			    "PAIR_ICID"					// 21.  
#define GLS_ITEM__INLINE__PAIR_LOTID		    "PAIR_LOTID"			    // 22.
#define GLS_ITEM__INLINE__PAIR_H_GLASSID		"PAIR_H_GLASSID"			// 23.
#define GLS_ITEM__INLINE__PAIR_R_GLASSID		"PAIR_R_GLASSID"			// 24.
#define GLS_ITEM__INLINE__GLASSINFO			    "GLASSINFO"   				// 25.
#define GLS_ITEM__INLINE__SYSTEMBYTE			"SYSTEMBYTE"  				// 26.
#define GLS_ITEM__INLINE__TACT					"TACT"    					// 27.
#define GLS_ITEM__INLINE__FSLOTID				"FSLOTID"   				// 28.
#define GLS_ITEM__INLINE__COURSE				"COURSE"     				// 29.
#define GLS_ITEM__INLINE__CUT_RULE				"CUT_RULE"  				// 30.   

#define GLS_ITEM__INLINE__RESULT				"RESULT"    				// 31. 
#define GLS_ITEM__INLINE__JUDGEMENT			    "JUDGEMENT"   				// 32.
#define GLS_ITEM__INLINE__NG_CODE				"NG_CODE"    				// 33.   

#define GLS_ITEM__INLINE__PTID					"PTID"     					// 34.
#define GLS_ITEM__INLINE__CSID					"CSID"    					// 35.
#define GLS_ITEM__INLINE__TOTALGSTATE			"TOTALGSTATE" 				// 36.
#define GLS_ITEM__INLINE__RECEIVEMODE			"RECEIVEMODE"  				// 37.
#define GLS_ITEM__INLINE__UNLOADTYPE			"UNLOADTYPE"   				// 38.
#define GLS_ITEM__INLINE__SPLITMODE			    "SPLITMODE"   				// 39.
#define GLS_ITEM__INLINE__PTST					"PTST"    					// 40.
#define GLS_ITEM__INLINE__PTMD					"PTMD"    					// 41.
#define GLS_ITEM__INLINE__BCRMODE				"BCRMODE"   				// 42.
#define GLS_ITEM__INLINE__VCRMODE				"VCRMODE"   				// 43.
#define GLS_ITEM__INLINE__SORTMODE				"SORTMODE"   				// 44.

#define GLS_ITEM__INLINE__SLOTNO				"SLOTNO"					// 45.
#define GLS_ITEM__INLINE__GLASS_STATE			"GLASS_STATE"				// 46.
#define GLS_ITEM__INLINE__UNITID				"UNITID"					// 47.

//
#define GLS_STS__NONE							"NONE"


// ...
class CDS_Msg_Type__Event_Header
{
public:
	int iEvent_ID;
	
	int iSx;
	int iFy;
	int iSxFy_Type;
	
	int iEvent_Type;
	int iCEID;

	int iMsg_Size;
};
class CDS_Msg_Type__Msg_Header
{
public:
	int iMsg_Size;
	
	CUIntArray iList__Msg_ID;
	CPtrArray  pList__Msg_Info;
};


// Event Info
class CDS_Msg_Type__Event_Info
{
public:
	CString sToolID;
	int iMCMD;
	int iEQST;
	int iBYWHO;
};

// Glass Data Collection Of Normal Equipment
class CDS_Msg_Type__Glass_DCOLL_Info
{
public:
	CString sIPID;				// 1.
	CString sOPID;				// 2.
	CString sICID;				// 3.
	CString sOCID;				// 4.
	CString sJOBID;				// 5.
	CString sSLOTNO;			// 6.
	CString sPROCESSID;			// 7.
	CString sPARTID;			// 8.
	CString sSTEPID;			// 9.
	CString sGLASSTYPE;			// 10.
	CString sGLASSID;			// 11.
	CString sPPID;				// 12.
	CString sGSTATE;			// 13.

	// 
	CStringArray sList__Data_Name;
	CStringArray sList__Data_Value;

	//
	CString sUnitID;
};

// Job Data Collection Of Normal Equipment
class CDS_Msg_Type__Job_DCOLL_Info
{
public:
	CString sIPID;				// 1.
	CString sOPID;				// 2.
	CString sICID;				// 3.
	CString sOCID;				// 4.
	CString sJOBID;				// 5.
	CString sPROCESSID;			// 6.
	CString sPARTID;			// 7.
	CString sSTEPID;			// 8.
	CString sTOTALGSTATE;		// 9.
	
	// 
	CStringArray sList__Data_Name;
	CStringArray sList__Data_Value;
};

// EQP Info
class CDS_Msg_Type__Unit_Info
{
public:
	CString sUnitID;
	int iEQP_State;
	int iPROC_State;
};
class CDS_Msg_Type__Tool_Info
{
public:
	CString sToolID;
	int iTool_EqpState;
	int iTool_ProcState;

	int iUnit_Size;
	CDS_Msg_Type__Unit_Info mList__Unit_Info[DEF_SIZE__UNIT];
};
class CDS_Msg_Type__EQP_Info
{
public:
	CString sChanged_EQP_ModuleID;

	int iChange_Flag__EQP_State;
	int iChanged_EQP_State;

	int iChange_Flag__PROC_State;
	int iChanged_PROC_State;

	CString sEQP_ModuleID;
	int iEQP_State;
	int iPROC_State;

	int iTool_Size;
	CDS_Msg_Type__Tool_Info mList__Tool_Info[DEF_SIZE__TOOL];
};

// Panel(Glass,Cell) Info
class CDS_Msg_Type__Glass_Info
{
public:
	CString sLostID;								// 1
	CString sIPID;									// 2
	CString sOPID;									// 3
	CString sICID;									// 4
	CString sOCID;									// 5
	CString sJobID;									// 6
	CString sPPID;									// 7
	CString sProcessID;								// 8
	CString sPartID;								// 9
	CString sStepID;								// 10
	CString sGlassType;								// 11
	CString sGlassID;								// 12
	CString sFSlotID;								// 13
	CString sTSlotID;								// 14
	
	int     iEQ_VAL;								// 15.1
	CString sUnitID;								//   .2

	CString sResult;								// 16.1
	CString sJudgement;								//   .2
	CString sNGCode;								//   .3
};


// PLC Event Info ...
class CDS__PLC_Sub_Glass_Info
{
public:
	CString sJOBID;									// 1
	CString sSLOTNO;								// 2
	CString sPROCESSID;								// 3
	CString sPARTID;								// 4
	CString sSTEPID;								// 5
	CString sGLASSTYPE;								// 6
	CString sLOTID;									// 7
	CString sH_GLASSID;								// 8
	CString sR_GLASSID;								// 9
	CString sPPID;									// 10
	CString sCELLGRADE;								// 11
	CString sDIRECTION;								// 12.   PLC MAP : Lot Type (CF Only)
	CString sGLASS_SIZE;							// 13 
	CString sSTD_CELL;                              // 14.   Standard Cell Count
	CString sLOT_KIND;								// 15.   Lot Kind (TFT/CF ...)
	CUIntArray iList__RUN_LINE;					    // 16
	CString sRESULT;								// 17.   Processing Result
	CString sJUDGEMENT;								// 18
    CString sNG_CODE;								// 19
	CString sPOSITION;								// 20.   Glass Position
	CString sPAIR_SLOTNO;							// 21
	CString sPAIR_IPID;								// 22
	CString sPAIR_ICID;								// 23  
	CString sPAIR_LOTID;							// 24
	CString sPAIR_H_GLASSID;						// 25
	CString sPAIR_R_GLASSID;						// 26
	CString sCUT_RULE;								// 27
};
class CDS_Msg_Type__PLC_Process_Glass_Info
{
public:
	CString sPTID;									// 1
	CString sCSID;									// 2
	CString sIPID;									// 3
	CString sICID;									// 4
	CString sJOBID;									// 5
	CString sTOTALGSTATE;							// 6.   Status of the all glass (from #1 to #70 order)
	// CDS__PLC_Sub_Glass_Info
	CPtrArray pList__PLC_Sub_Glass_Info;			// 7
};
class CDS_Msg_Type__PLC_Process_Unload_Info
{
public:
	CString sRECEIVEMODE;							// 1.   Unload Method (D, DF, R, RF) 
	CString sUNLOADTYPE;							// 2.   Unload Type as a Result (Port Mode)
	CString sSPLITMODE;								// 3.   Split Mode as a Result
	CString sPTST;									// 4.   Port Status
	CString sPTMD;									// 5.   Port Mode (AGV, MGV)
	CString sBCRMODE;								// 6.   BCR Mode
	CString sVCRMODE;								// 7.   VCR Mode
	CString sSORTMODE;								// 8.   CF Sorting Mode (CF Only)
};

class CDS_Msg_Type__PLC_Component_Info
{
public:
	CString sIPID;									// 1
	CString sICID;									// 2
	CString sJOBID;									// 3
	CString sPROCESSID;								// 4
	CString sPARTID;								// 5
	CString sSTEPID;								// 6
	CString sGLASSTYPE;								// 7
	CString sLOTID;									// 8
	CString sH_GLASSID;								// 9
	CString sR_GLASSID;								// 10
	CString sPPID;									// 11
	CString sCELLGRADE;								// 12
	CString sDIRECTION;								// 13.   PLC MAP : Lot Type (CF Only)
	CString sGLASS_SIZE;							// 14
    CString sSTD_CELL;								// 15.   Standard Cell Count
	CString sLOT_KIND;								// 16.   Lot Kind (TFT/CF ...)
	CUIntArray iList__RUN_LINE;						// 17
	CString sPOSITION;								// 18.   Glass Position
	CString sPAIR_SLOTNO;							// 19
	CString sPAIR_IPID;								// 20
	CString sPAIR_ICID;								// 21
	CString sPAIR_LOTID;							// 22
	CString sPAIR_H_GLASSID;						// 23
	CString sPAIR_R_GLASSID;						// 24
	CString sGLASSINFO;								// 25
	CUIntArray iList__SYSTEM_BYTE;					// 26
	int     iTACT;									// 27
	CString sFSLOTID;								// 28
	CString sCOURSE;								// 29.   Transfer Course (Ex. LA, LB, UA, UB ...)                            
	CString sCUT_RULE;								// 30
	
	int     iEQ_VAL;								// 1
	CString sUNITID;								// 2
	
	CString sRESULT;								// 1
	CString sJUDGEMENT;								// 2
	CString sNGCODE;								// 3
};

// Alarm Info
class CDS_Msg_Type__Alarm_Info
{
public:
	CUIntArray   iList_ALCD;
	CUIntArray   iList_ALID;
	CStringArray sList_ALTX;
	CStringArray sList_ALTM;
	CStringArray sList_UNITID;
};
class CDS_Msg_Type__Alarm_Item
{
public:
	int iALCD;
	int iALID;
	CString sALTX;
	CString sALTM;
	CString sUNITID;
};

// PPBody Info
class CDS_Msg_Type__PPBody_Parameter_Info
{
public:
	CString sCCode;

	CStringArray sList__PPBody_Name;
	CStringArray sList__PPBody_Data;
};
class CDS_Msg_Type__PPBody_Step_Info
{
public:
	~CDS_Msg_Type__PPBody_Step_Info()
	{
		CDS_Msg_Type__PPBody_Parameter_Info *p_ds;

		int limit = pList__PPBody_Parameter_Info.GetSize();
		int i;

		for(i=0; i<limit; i++)
		{
			p_ds = (CDS_Msg_Type__PPBody_Parameter_Info*) pList__PPBody_Parameter_Info[i];
			delete p_ds;
		}
		
		pList__PPBody_Parameter_Info.RemoveAll();
	}

	// ...
	int iMode;			
	   // 1 : Creation of PPID
	   // 2 : Deletion of PPID
	   // 3 : Modification of PPID
	
	CString sModuleID;
	CString sPPID_Name;
	CString sPPID_Type;
	CString sSoft_VER;

	// CDS_Msg_Type__PPBody_Parameter_Info
	CPtrArray pList__PPBody_Parameter_Info;
};

class CDS_Msg_Type__PPID_List
{
public:
	CStringArray sList__ModuleID;
	CStringArray sList__PPID_Name;
	CStringArray sList__PPID_Type;
};

// Item Info
class CDS_Msg_Type__Item_Info
{
public:
	CString sModuleID;

	CStringArray sList__Item_Name;
	CStringArray sList__Item_Data;
};

// EOID Info
class CDS_Msg_Type__EOMD_Info
{
public:
	CStringArray sList__EOMD_ID;
	CStringArray sList__EOMD_Data;
};
class CDS_Msg_Type__EOID_Info
{
public:
	~CDS_Msg_Type__EOID_Info()
	{
		CDS_Msg_Type__EOMD_Info *p_ds;
		
		int limit = pList__EOMD.GetSize();
		int i;

		for(i=0; i<limit; i++)
		{
			p_ds = (CDS_Msg_Type__EOMD_Info*) pList__EOMD[i];
			delete p_ds;
		}
	
		pList__EOMD.RemoveAll();
	}

	// ...
	CUIntArray iList__EOID;

	// CDS_Msg_Type__EOMD_Info
	CPtrArray  pList__EOMD;
};

// ECID Info
class CDS_Msg_Type__ECID_Info
{
public:
	CUIntArray iList__iECID;

	CStringArray sList__ECNAME;
	CStringArray sList__ECDEF;
	CStringArray sList__ECSLL;
	CStringArray sList__ECSUL;
	CStringArray sList__ECWLL;
	CStringArray sList__ECWUL;
};
class CDS_Msg_Type__ECID_Item
{
public:
	int iECID;
	
	CString sECNAME;
	CString sECDEF;
	CString sECSLL;
	CString sECSUL;
	CString sECWLL;
	CString sECWUL;
};

// Reason Code
class CDS_Msg_Type__Reason_Code_Info
{
public:
	CString sList_Time;				// hhmmss
	CString sRCODE;
};


// Current Process Control Data
class CDS_Msg_Type__Process_Control_Parameter_Info
{
public:
	CString sCode;

	CStringArray sList__Para_Name;
	CStringArray sList__Para_Data;
};
class CDS_Msg_Type__Process_Control_Item_Info
{
public:
	CStringArray sList__Item_Name;
	CStringArray sList__Item_Data;
};
class CDS_Msg_Type__Process_Control_Module_Info
{
public:
	~CDS_Msg_Type__Process_Control_Module_Info()
	{
		int limit;
		int i;

		// ...
		{
			CDS_Msg_Type__Process_Control_Parameter_Info* p_ds;

			limit = pList__Process_Control_Parameter_Info.GetSize();

			for(i=0; i<limit; i++)
			{
				p_ds = (CDS_Msg_Type__Process_Control_Parameter_Info*) pList__Process_Control_Parameter_Info[i];
				delete p_ds;
			}
			pList__Process_Control_Parameter_Info.RemoveAll();
		}
	}

	// ...
	CString sModuleID;
	CString sPPID_Name;
	CString sPPID_Type;

	// CDS_Msg_Type__Process_Control_Parameter_Info
	CPtrArray pList__Process_Control_Parameter_Info;

	CDS_Msg_Type__Process_Control_Item_Info mProcess_Control_Item_Info;
};
class CDS_Msg_Type__Process_Control_Panel_Info
{
public:
	~CDS_Msg_Type__Process_Control_Panel_Info()
	{
		CDS_Msg_Type__Process_Control_Module_Info *p_ds;

		int limit = pList__Process_Control_Module_Info.GetSize();
		int i;

		for(i=0; i<limit; i++)
		{
			p_ds = (CDS_Msg_Type__Process_Control_Module_Info*) pList__Process_Control_Module_Info[i];
			delete p_ds;
		}
		pList__Process_Control_Module_Info.RemoveAll();
	}

	// ...
	CString sHost_PanelID;
	int iSeq_NO;

	// CDS_Msg_Type__Process_Control_Module_Info
	CPtrArray pList__Process_Control_Module_Info;
};
class CDS_Msg_Type__Current_Process_Control_Data
{
public:
	~CDS_Msg_Type__Current_Process_Control_Data()
	{
		CDS_Msg_Type__Process_Control_Panel_Info *p_ds;
		
		int limit = pList__Process_Control_Panel_Info.GetSize();
		int i;

		for(i=0; i<limit; i++)
		{
			p_ds = (CDS_Msg_Type__Process_Control_Panel_Info*) pList__Process_Control_Panel_Info[i];
			delete p_ds;
		}
		pList__Process_Control_Panel_Info.RemoveAll();
	}

	// ...
	CString sModuleID;
	int iMode;
	int iByWho;

	// CDS_Msg_Type__Process_Control_Panel_Info
	CPtrArray pList__Process_Control_Panel_Info;
};


// Process Control Result Report
class CDS_Msg_Type__Process_Control_Result_Report
{
public:
	CString sModuleID;
	int iResult;

	CString sHost_PanelID;
	int iSeqID;

	CStringArray sList__ModuleID;
	CStringArray sList__PPID_Name;
	CUIntArray   iList__PPID_Type;
};


// Terminal message to the host
class CDS_Msg_Type__Terminal_Message_To_Host
{
public:
	int iTID;
	CString sTEXT;	
};


// Terminal message or operator call
class CDS_L5__TID_INFO
{
public:
	CDS_L5__TID_INFO()
	{
		iSx = -1;
		iFy = -1;
		
		iTID = -1;

	}
	
	// ...
	CString sRef_ToolID;

	int iSx;
	int iFy;
	
	int iTID;
	CString sTitle;
	CStringArray sList_Message;
};
