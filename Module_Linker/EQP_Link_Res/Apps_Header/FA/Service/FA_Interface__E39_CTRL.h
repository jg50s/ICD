#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__Macro.h"


class CI_FA_300mm__E39_CTRL
{
public:
	virtual ~CI_FA_300mm__E39_CTRL(){};

	//----------------------------------------------------
	virtual int  Get__ERROR_CODE(int& err_code,
								 CString& err_text) = 0;

	virtual int  GetAttr(const CString& objspec,
						 const CString& objtype,
						 const CString& objid,
						 const CString& attrid,
						 const CString& attrdata,
						 const CString& attrreln,
						 CDS_ATTR_DATA& attr_data) = 0;

	virtual int  GetAttr__ObjID(const CString& objspec,
								const CString& objtype,
								CStringArray& l_objid) = 0;

	virtual int  SetAttr(const CString& objspec,
						 const CString& objtype,
						 const CString& objid,
						 const CString& attrid,
						 const CString& attrdata) = 0;

	virtual int  GetType(const CString& objspec,
						 CStringArray& l_objtype) = 0;

	virtual int  GetAttrName(const CString& objspec,
							 const CString& objtype,
							 CStringArray& l_attrid) = 0;

	virtual int  Delete__Object(const CString& objspec,
							    const CString& attrid,
								const CString& attrdata) = 0;

	virtual int  Is__ObjID(const CString& objspec,
						   const CString& objtype,
						   const CString& objid) = 0;

};
