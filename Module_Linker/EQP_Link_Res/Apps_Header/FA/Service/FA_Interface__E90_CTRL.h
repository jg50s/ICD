#pragma once


class CI_FA_300mm__E90_CTRL
{
public:
	virtual ~CI_FA_300mm__E90_CTRL(){};

	//-----------------------------------------------------------------------------
	// Event (E90)

	virtual int  Create__OBJECT(const int ptn) = 0;
	virtual int  Delete__OBJECT(const int ptn) = 0;


	virtual int  Event__SUBSTRATE__AT_SOURCE(const int ptn,const int slot) = 0;
	virtual int  Event__SUBSTRATE__AT_WORK(const int ptn,const int slot) = 0;
	virtual int  Event__SUBSTRATE__AT_DESTINATION(const int ptn,const int slot) = 0;

	virtual int  Event__SUBSTRATE__IN_PROCESS(const int ptn,const int slot) = 0;
	virtual int  Event__SUBSTRATE__PROCESSED(const int ptn,const int slot) = 0;
	virtual int  Event__SUBSTRATE__NEEDS_PROCESSING(const int ptn,const int slot) = 0;	
	virtual int  Event__SUBSTRATE__ABORTED(const int ptn,const int slot) = 0;
	virtual int  Event__SUBSTRATE__STOPPED(const int ptn,const int slot) = 0;
	virtual int  Event__SUBSTRATE__REJECTED(const int ptn,const int slot) = 0;
	virtual int  Event__SUBSTRATE__LOST(const int ptn,const int slot) = 0;
	virtual int  Event__SUBSTRATE__SKIPPED(const int ptn,const int slot) = 0;


	virtual int  Get_Attr__SubstID(const int ptn,
								   const int slot,
								   CString& data) = 0;
	virtual int  Get_Attr__SubstLocState(const int ptn,
										 const int slot,
										 int& state) = 0;
	virtual int  Get_Attr__SubstProcState(const int ptn,
										  const int slot,
										  int& state) = 0;
	virtual int  Get_Attr__SubstState(const int ptn,
									  const int slot,
									  int& state) = 0;
	virtual int  Get_Attr__LOCID(const int ptn,
								 const int slot,
								 CString& locid) = 0;
	virtual int  Get_Attr__LOCID_LIST(const int ptn,
									  const int slot,
									  CStringArray& l_locid) = 0;


	virtual int  Set__SUBSTRATE__LOCID(const int ptn,
									   const int slot,
									   const CString& locid) = 0;


	virtual int  Event__SUBSTRATE__UNOCCUPIED(const int ptn,
											  const int slot) = 0;
	virtual int  Event__SUBSTRATE__OCCUPIED(const int ptn,
											const int slot) = 0;
};
