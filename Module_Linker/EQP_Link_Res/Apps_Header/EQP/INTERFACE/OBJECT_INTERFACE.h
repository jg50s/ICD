#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\EQP\UTILITY\IEQP_HEADER__UTILITY_LINK.h"


// ...
#define  ANALOG__IO_TYPE__USER_DATA											0
#define  ANALOG__IO_TYPE__LINEAR_DATA										1
#define  ANALOG__IO_TYPE__LOOKUP_TABLE										2


// ...
#define CORE_VER__1_0														1.0

#define VERSION_1_0															1.0


// ...
#define EMPTY__BODY		{return 0;}
#define PROC__OK		return 1;


// ...
#define  DECLARE_START__DLL_STD_OBJ__GET_VERSION									\
extern "C" __declspec(dllexport)													\
void __DLL_STD_OBJ__GET_VERSION(double& version,int& debug_mode)					\
{																					\
	version = VERSION_1_0;

#define  DECLARE_END__DLL_STD_OBJ__GET_VERSION										\
}


#define  DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST									\
extern "C" __declspec(dllexport)													\
void __DLL_STD_OBJ__GET_CLASS_LIST(CStringArray& l_class)							\
{																					\
	l_class.RemoveAll();

#define  DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST									\
}


#define  DECLARE_START__DLL_STD_OBJ__CREATE_LINK									\
extern "C" __declspec(dllexport)													\
__IOBJ__STD_TYPE* __DLL_STD_OBJ__CREATE_LINK(const CString& cls_name)				\
{

#define  DECLARE_END__DLL_STD_OBJ__CREATE_LINK   									\
	return NULL;																	\
}


// ...
#define  DECLARE_START__DLL_IO_OBJ__GET_VERSION										\
extern "C" __declspec(dllexport)													\
void __DLL_IO_OBJ__GET_VERSION(double& version,int& debug_mode)						\
{																					\
	version = VERSION_1_0;

#define  DECLARE_END__DLL_IO_OBJ__GET_VERSION										\
}


#define  DECLARE_START__DLL_IO_OBJ__GET_CLASS_LIST									\
extern "C" __declspec(dllexport)													\
void __DLL_IO_OBJ__GET_CLASS_LIST(CStringArray& l_class)							\
{																					\
	l_class.RemoveAll();

#define  DECLARE_END__DLL_IO_OBJ__GET_CLASS_LIST									\
}


#define  DECLARE_START__DLL_IO_OBJ__CREATE_LINK										\
extern "C" __declspec(dllexport)													\
__IOBJ__IO_TYPE* __DLL_IO_OBJ__CREATE_LINK(const CString& cls_name)					\
{

#define  DECLARE_END__DLL_IO_OBJ__CREATE_LINK   									\
	return NULL;																	\
}
	

// ...
#define  DECLARE_START__DLL_LINK_OBJ__GET_VERSION									\
extern "C" __declspec(dllexport)													\
void __DLL_LINK_OBJ__GET_VERSION(double& version,int& debug_mode)					\
{																					\
	version = VERSION_1_0;

#define  DECLARE_END__DLL_LINK_OBJ__GET_VERSION										\
}


#define  DECLARE_START__DLL_LINK_OBJ__GET_CLASS_LIST								\
extern "C" __declspec(dllexport)													\
void __DLL_LINK_OBJ__GET_CLASS_LIST(CStringArray& l_class)							\
{																					\
	l_class.RemoveAll();

#define  DECLARE_END__DLL_LINK_OBJ__GET_CLASS_LIST									\
}


#define  DECLARE_START__DLL_LINK_OBJ__CREATE_LINK									\
extern "C" __declspec(dllexport)													\
__IOBJ__LINK_TYPE* __DLL_LINK_OBJ__CREATE_LINK(const CString& cls_name)				\
{

#define  DECLARE_END__DLL_LINK_OBJ__CREATE_LINK   									\
	return NULL;																	\
}


// ...
#define  DECLARE_START__DLL_INTERLOCK_OBJ__GET_VERSION								\
extern "C" __declspec(dllexport)													\
void __DLL_INTERLOCK_OBJ__GET_VERSION(double& version,int& debug_mode)				\
{																					\
	version = VERSION_1_0;

#define  DECLARE_END__DLL_INTERLOCK_OBJ__GET_VERSION								\
}


#define  DECLARE_START__DLL_INTERLOCK_OBJ__GET_CLASS_LIST							\
extern "C" __declspec(dllexport)													\
void __DLL_INTERLOCK_OBJ__GET_CLASS_LIST(CStringArray& l_class)						\
{																					\
	l_class.RemoveAll();

#define  DECLARE_END__DLL_INTERLOCK_OBJ__GET_CLASS_LIST								\
}


#define  DECLARE_START__DLL_INTERLOCK_OBJ__CREATE_LINK								\
extern "C" __declspec(dllexport)													\
__IOBJ__INTERLOCK_TYPE* __DLL_INTERLOCK_OBJ__CREATE_LINK(const CString& cls_name)	\
{

#define  DECLARE_END__DLL_INTERLOCK_OBJ__CREATE_LINK   								\
	return NULL;																	\
}


#define INTERLOCK_REGISTER(CLS_TYPE,FNC_NAME)										\
int FNC_NAME(void *p_void)															\
{																					\
	CLS_TYPE *p_class = (CLS_TYPE*) p_void;											\
																					\
	return p_class->I##FNC_NAME();													\
}


// ...
#define  DECLARE_START__DLL_FA_OBJ__GET_VERSION										\
extern "C" __declspec(dllexport)													\
void __DLL_FA_OBJ__GET_VERSION(double& version,int& debug_mode)						\
{																					\
	version = VERSION_1_0;

#define  DECLARE_END__DLL_FA_OBJ__GET_VERSION										\
}


#define  DECLARE_START__DLL_FA_OBJ__GET_CLASS_LIST									\
extern "C" __declspec(dllexport)													\
void __DLL_FA_OBJ__GET_CLASS_LIST(CStringArray& l_class)							\
{																					\
	l_class.RemoveAll();

#define  DECLARE_END__DLL_FA_OBJ__GET_CLASS_LIST									\
}


#define  DECLARE_START__DLL_FA_OBJ__CREATE_LINK										\
extern "C" __declspec(dllexport)													\
__IOBJ__FA_TYPE* __DLL_FA_OBJ__CREATE_LINK(const CString& cls_name)					\
{

#define  DECLARE_END__DLL_FA_OBJ__CREATE_LINK   									\
	return NULL;																	\
}


// ...
#define  IF__OBJ_CLS(obj_cls)														\
if(cls_name == obj_cls  ?  true  :  false)	

#define  ADD__OBJ_CLS(obj_cls)														\
l_class.Add(obj_cls);


// ...
#define  MONITORING_TIMER(mSEC)														\
if(p_variable->Exception_Timer(mSEC) < 0)			break;					

#define  MONITORING_TIMER_RETURN_INT(mSEC,RETURN_DATA)								\
if(p_variable->Exception_Timer(mSEC) < 0)			return RETURN_DATA;		

#define  MONITORING_TIMER_RETURN(mSEC)												\
if(p_variable->Exception_Timer(mSEC) < 0)			return;		


// ...
class CII_DEFINE__IO_INTERLOCK
{
public:
	virtual ~CII_DEFINE__IO_INTERLOCK(){};

	// ...
	virtual int REGISTER__VARIABLE_NAME(const CString& obj_name,
								        const CString& var_name,
								        const CString& var_data,
								        void* p_fnc) = 0;

	// cmp_para : "<=", "<", ">", ">=" "=="
	virtual int REGISTER__CHANNEL_NAME(const CString& ch_name,
									    const CString& ch_data,
									    void* p_fnc,
									    const CString& cmp_para = "") = 0;
};

class CII_DEFINE__UI_INTERLOCK
{
public:
	virtual ~CII_DEFINE__UI_INTERLOCK(){};

	// ...
	virtual int REGISTER__VARIABLE_NAME(const CString& obj_name,
										const CString& var_name,
										const CString& var_data,
										void* p_fnc) = 0;

	// cmp_para : "<=", "<", ">", ">=" "=="
	virtual int REGISTER__CHANNEL_NAME(const CString& ch_name,
										const CString& ch_data,
										void* p_fnc,
										const CString& cmp_para = "") = 0;
};


class CII_CTRL__DESCRIPTOR
{
public:
	virtual ~CII_CTRL__DESCRIPTOR(){};

	// ...
	virtual int Make__DESCRIPTOR(const CString& descriptor_name,
							     const CStringArray& l_data) = 0;
				     
	virtual int Get__DESCRIPTOR(const CString& obj_name,
								const CString& descriptor_name,
							    CStringArray& l_data) = 0;

	virtual int Get__DESCRIPTOR(const CString& obj_name,
								const CString& descriptor_name,
							    CString& str_data) = 0;
};


// ...
#define ALARM_LEVEL__HEAVY				0
#define ALARM_LEVEL__LIGHT				1
#define ALARM_LEVEL__WARNING			2

class CII_CTRL__ALARM
{
public:
	virtual ~CII_CTRL__ALARM(){};

	// ...
	virtual int Make__ALARM(const int alarm_id) = 0;

	virtual int Make__ALARM_EX(const int alarm_id,
							   const CString& title,
							   const CString& message,
							   const CStringArray& l_option) = 0;	

	//
	virtual int Make__ALARM_WITH_LEVEL(const int alarm_id,
		                               const int alarm_level,
							           const CString& title,
							           const CString& message,
							           const CStringArray& l_option) = 0;	

	virtual int Set__ALARM_HOST_REPORT(const int alarm_id,
		                               const int flag_host_report) = 0;	
};

class CII_CTRL__ANALOG_VIRTUAL
{
public:
	virtual ~CII_CTRL__ANALOG_VIRTUAL(){};

	// ...
	virtual int Add__ANALOG(const CString& variable_name,
							const CString& unit,
							const int dec,
							const double min,
							const double max,
							const CString& external_object_name = "",
							const CString& lookup_table_name = "",
							const CString& comment = "") = 0;

	virtual int Add__ANALOG_WITH_X_OPTION(const CString& variable_name,
									   	  const CString& unit,
										  const int dec,
										  const double min,
										  const double max,
										  const CString& external_object_name = "",
										  const CString& lookup_table_name = "",
										  const CString& comment = "") = 0;

	virtual int Add__ANALOG_WITH_OPTION(const CString& variable_name,
									   	const CString& unit,
										const int dec,
										const double min,
										const double max,
										const int x_option,
										const CString& log_option,				// "L"  "E"
									    const CString& comment = "") = 0;
};
class CII_CTRL__ANALOG_IO
{
public:
	virtual ~CII_CTRL__ANALOG_IO(){};

	//
	virtual int Add__ANALOG_READ(const CString& variable_name,
									const CString& fnc_name,
									const CString& unit,
									const int dec,
									const double min,
									const double max,
									const int auto_polling = 1,
									const CString& external_object_name = "",
									const CString& lookup_table_name = "",
									const CString& comment = "") = 0;

	virtual int Add__ANALOG_WRITE(const CString& variable_name,
									const CString& fnc_name,
									const CString& unit,
									const int dec,
									const double min,
									const double max,
									const int auto_polling = 1,
									const CString& external_object_name = "",
									const CString& lookup_table_name = "",
									const CString& comment = "") = 0;

	//
	virtual int Add__ANALOG_READ_EX(const CString& variable_name,
									const CString& fnc_name,
									const CString& unit,
									const int dec,
									const double min,
									const double max,
									const CString& cmmd1,
									const CString& cmmd2,
									const CString& cmmd3,
									const int auto_polling = 1,
									const CString& external_object_name = "",
									const CString& lookup_table_name = "",
									const CString& comment = "") = 0;

	virtual int Add__ANALOG_WRITE_EX(const CString& variable_name,
									const CString& fnc_name,
									const CString& unit,
									const int dec,
									const double min,
									const double max,
									const CString& cmmd1,
									const CString& cmmd2,
									const CString& cmmd3,
									const int auto_polling = 1,
									const CString& external_object_name = "",
									const CString& lookup_table_name = "",
									const CString& comment = "") = 0;

	//
	virtual int Add__ANALOG_READ_EX2(const CString& variable_name,
									const CString& fnc_name,
									const CString& unit,
									const int dec,
									const double min,
									const double max,
									const CString& cmmd1,
									const CString& cmmd2,
									const CString& cmmd3,
									const double auto_polling,
									const CString& comment) = 0;

	virtual int Add__ANALOG_WRITE_EX2(const CString& variable_name,
									const CString& fnc_name,
									const CString& unit,
									const int dec,
									const double min,
									const double max,
									const CString& cmmd1,
									const CString& cmmd2,
									const CString& cmmd3,
									const double auto_polling,
									const CString& comment) = 0;

	// ...
	virtual int Change__LOG_INTERVAL() = 0;
	virtual int Change__LOG_EVENT() = 0;
};

class CII_CTRL__DIGITAL_VIRTUAL
{
public:
	virtual ~CII_CTRL__DIGITAL_VIRTUAL(){};

	// ...
	virtual int Add__DIGITAL(const CString& variable_name,
							 const CString& external_object_name,
							 const CString& descriptor_name) = 0;

	virtual int Add__DIGITAL(const CString& variable_name,
							 const CString& item_list) = 0;

	virtual int Add__DIGITAL_WITH_COMMENT(const CString& variable_name,
										  const CString& external_object_name,
										  const CString& descriptor_name,
										  const CString& comment) = 0;

	virtual int Add__DIGITAL_WITH_COMMENT(const CString& variable_name,
										  const CString& item_list,
										  const CString& comment) = 0;

	virtual int Add__DIGITAL_WITH_X_OPTION(const CString& variable_name,
										   const CString& item_list,
										   const CString& comment) = 0;

	virtual int Add__DIGITAL_WITH_OPTION(const CString& variable_name,
										 const CString& item_list,
										 const int x_option,
										 const CString& log_option,
										 const CString& comment) = 0;
};
class CII_CTRL__DIGITAL_IO
{
public:
	virtual ~CII_CTRL__DIGITAL_IO(){};

	// ...
	virtual int Add__DIGITAL_READ(const CString& variable_name,
								  const CString& fnc_name,
								  const CString& external_object_name,
								  const CString& descriptor_name,
								  const int auto_polling = 1) = 0;

	virtual int Add__DIGITAL_WRITE(const CString& variable_name,
								   const CString& fnc_name,
								   const CString& external_object_name,
								   const CString& descriptor_name,
								   const int auto_polling = 1) = 0;

	virtual int Add__DIGITAL_READ(const CString& variable_name,
								  const CString& fnc_name,
								  const CString& item_list,
								  const int auto_polling = 1) = 0;

	virtual int Add__DIGITAL_WRITE(const CString& variable_name,
								   const CString& fnc_name,
								   const CString& item_list,
								   const int auto_polling = 1) = 0;

	virtual int Add__DIGITAL_READ_EX(const CString& variable_name,
									 const CString& fnc_name,
									 const CString& item_list,
									 const CString& cmmd1,
									 const CString& cmmd2,
									 const CString& cmmd3,
									 const int auto_polling = 1) = 0;

	virtual int Add__DIGITAL_WRITE_EX(const CString& variable_name,
									  const CString& fnc_name,
									  const CString& item_list,
									  const CString& cmmd1,
									  const CString& cmmd2,
									  const CString& cmmd3,
									  const int auto_polling = 1) = 0;

	virtual int Add__DIGITAL_READ_WITH_COMMENT(const CString& variable_name,
											   const CString& fnc_name,
											   const CString& external_object_name,
											   const CString& descriptor_name,
											   const int auto_polling = 1,
											   const CString& comment = "") = 0;

	virtual int Add__DIGITAL_WRITE_WITH_COMMENT(const CString& variable_name,
											    const CString& fnc_name,
											    const CString& external_object_name,
											    const CString& descriptor_name,
											    const int auto_polling = 1,
												const CString& comment = "") = 0;

	virtual int Add__DIGITAL_READ_WITH_COMMENT(const CString& variable_name,
											   const CString& fnc_name,
											   const CString& item_list,
											   const int auto_polling = 1,
											   const CString& comment = "") = 0;

	virtual int Add__DIGITAL_WRITE_WITH_COMMENT(const CString& variable_name,
											    const CString& fnc_name,
											    const CString& item_list,
											    const int auto_polling = 1,
												const CString& comment = "") = 0;

	virtual int Add__DIGITAL_READ_EX_WITH_COMMENT(const CString& variable_name,
												  const CString& fnc_name,
												  const CString& item_list,
												  const CString& cmmd1,
												  const CString& cmmd2,
												  const CString& cmmd3,
												  const int auto_polling = 1,
												  const CString& comment = "") = 0;

	virtual int Add__DIGITAL_WRITE_EX_WITH_COMMENT(const CString& variable_name,
												   const CString& fnc_name,
												   const CString& item_list,
												   const CString& cmmd1,
												   const CString& cmmd2,
												   const CString& cmmd3,
												   const int auto_polling = 1,
												   const CString& comment = "") = 0;

	virtual int Add__DIGITAL_READ_EX2(const CString& variable_name,
									  const CString& fnc_name,
									  const CString& item_list,
									  const CString& cmmd1,
									  const CString& cmmd2,
									  const CString& cmmd3,
									  const double auto_polling,
									  const CString& comment) = 0;

	virtual int Add__DIGITAL_WRITE_EX2(const CString& variable_name,
									   const CString& fnc_name,
									   const CString& item_list,
									   const CString& cmmd1,
									   const CString& cmmd2,
									   const CString& cmmd3,
									   const double auto_polling,
									   const CString& comment) = 0;

	// ...
	virtual int Change__LOG_INTERVAL() = 0;
	virtual int Change__LOG_EVENT() = 0;
};

class CII_CTRL__STRING_VIRTUAL
{
public:
	virtual ~CII_CTRL__STRING_VIRTUAL(){};

	// ...
	virtual int Add__STRING(const CString& variable_name,
							const int length_limit = 0) = 0;

	virtual int Add__STRING_WITH_COMMENT(const CString& variable_name,
										 const int length_limit = 0,
										 const CString& comment = "") = 0;

	virtual int Add__STRING_WITH_X_OPTION(const CString& variable_name,
										  const int length_limit = 0,
										  const CString& comment = "") = 0;

	virtual int Add__STRING_WITH_OPTION(const CString& variable_name,
										const int x_option,
										const CString& log_option,
										const int length_limit = 0,
										const CString& comment = "") = 0;
};
class CII_CTRL__STRING_IO
{
public:
	virtual ~CII_CTRL__STRING_IO(){};

	// ...
	virtual int Add__STRING_READ(const CString& variable_name,
								 const CString& fnc_name,
								 const int auto_polling = 1,
								 const int length_limit = 0) = 0;

	virtual int Add__STRING_WRITE(const CString& variable_name,
								  const CString& fnc_name,
								  const int auto_polling = 1,
								  const int length_limit = 0) = 0;

	virtual int Add__STRING_READ_EX(const CString& variable_name,
									const CString& fnc_name,
									const CString& cmmd1,
									const CString& cmmd2,
									const CString& cmmd3,
									const int auto_polling = 1,
									const int length_limit = 0) = 0;

	virtual int Add__STRING_WRITE_EX(const CString& variable_name,
								    const CString& fnc_name,
									const CString& cmmd1,
									const CString& cmmd2,
									const CString& cmmd3,
								    const int auto_polling = 1,
								    const int length_limit = 0) = 0;

	virtual int Add__STRING_READ_WITH_COMMENT(const CString& variable_name,
											  const CString& fnc_name,
											  const int auto_polling = 1,
											  const int length_limit = 0,
											  const CString& comment = "") = 0;

	virtual int Add__STRING_WRITE_WITH_COMMENT(const CString& variable_name,
											   const CString& fnc_name,
											   const int auto_polling = 1,
											   const int length_limit = 0,
											   const CString& comment = "") = 0;

	virtual int Add__STRING_READ_EX_WITH_COMMENT(const CString& variable_name,
												 const CString& fnc_name,
												 const CString& cmmd1,
												 const CString& cmmd2,
												 const CString& cmmd3,
												 const int auto_polling = 1,
												 const int length_limit = 0,
												 const CString& comment = "") = 0;

	virtual int Add__STRING_WRITE_EX_WITH_COMMENT(const CString& variable_name,
											      const CString& fnc_name,
												  const CString& cmmd1,
												  const CString& cmmd2,
												  const CString& cmmd3,
											      const int auto_polling = 1,
											      const int length_limit = 0,
												  const CString& comment = "") = 0;

	virtual int Add__STRING_READ_EX2(const CString& variable_name,
									 const CString& fnc_name,
									 const CString& cmmd1,
									 const CString& cmmd2,
									 const CString& cmmd3,
									 const double auto_polling,
									 const int length_limit,
									 const CString& comment) = 0;

	virtual int Add__STRING_WRITE_EX2(const CString& variable_name,
									  const CString& fnc_name,
									  const CString& cmmd1,
									  const CString& cmmd2,
									  const CString& cmmd3,
									  const double auto_polling,
									  const int length_limit,
									  const CString& comment) = 0;

	// ...
	virtual int Change__LOG_INTERVAL() = 0;
	virtual int Change__LOG_EVENT() = 0;
};

class CII__VAR_ANALOG_CTRL
{
public:
	~CII__VAR_ANALOG_CTRL(){};

	// ...
	virtual CString Get__CHANNEL_NAME() = 0;

	virtual int Set__DATA(const CString& data) = 0;
	virtual int Get__DATA(CString& data) = 0;
	virtual int Check__DATA(const CString& data) = 0;

	virtual CString Get__VARIABLE_NAME() = 0;

	virtual int Set__VALUE(const double value) = 0;
	virtual int Inc__VALUE(const double inc_value = 1.0) = 0;

	// return value ( 0 > : OK, 0 < : TimeOut, 0 == : Upper Object Abort)
	virtual int When__LESS_THAN(const double ref_value,const double sec = -1) = 0;
	// return value ( 0 > : OK, 0 < : TimeOut, 0 == : Upper Object Abort)
	virtual int When__MORE_THAN(const double ref_value,const double sec = -1) = 0;

	virtual int Link__UPPER_OBJECT_ABORT(const CString& obj_name) = 0;
	virtual int Enable__UPPER_OBJECT_ABORT_CHECK() = 0;
	virtual int Disable__UPPER_OBJECT_ABORT_CHECK() = 0;

	virtual int Get__MIN_MAX_DEC(double& min_value,double& max_value,int& i_dec) = 0;
	virtual int Get__MIN_MAX_INFO(CString& str_min,CString& str_max) = 0;

	virtual int Change__MIN_MAX_DEC(const double min_value,
								    const double max_value,
									const int i_dec) = 0;			// < 0 : No Change

	virtual int Check__CHANNEL_NAME(const CString& ch_name) = 0;

	virtual int Disable__AUTO_POLLING() = 0;
	virtual int Enable__AUTO_POLLING(const double poll_sec) = 0;

	//
	virtual int Update__CHANNEL_DATA() = 0;

	//
	virtual int Check__LESS_THAN(const double check_value) = 0;
	virtual int Check__MORE_THAN(const double check_value) = 0;

	//
	virtual double Get__VALUE() = 0;

	virtual int Check__VARIABLE_NAME(const CString& var_name) = 0;

	//
	virtual CString Get__STRING() = 0;
};
class CII__VAR_DIGITAL_CTRL
{
public:
	~CII__VAR_DIGITAL_CTRL(){};

	// ...	
	virtual CString Get__CHANNEL_NAME() = 0;

	virtual int Set__DATA(const CString& data) = 0;
	virtual int Get__DATA(CString& data) = 0;
	virtual int Check__DATA(const CString& data) = 0;

	// return value ( 0 > : OK, 0 < : TimeOut, 0 == : Upper Object Abort)
	virtual int When__DATA(const CString& data,const double sec = -1) = 0;
	virtual int When__DATA(const CString& data1,const CString& data2,const double sec = -1) = 0;

	// return value ( 0 > : OK, 0 < : TimeOut, 0 == : Upper Object Abort)
	virtual int When__NOT_DATA(const CString& data,const double sec = -1) = 0;
	virtual int When__NOT_DATA(const CString& data1,const CString& data2,const double sec = -1) = 0;

	// ...
	virtual CString Get__VARIABLE_NAME() = 0;

	virtual int Link__UPPER_OBJECT_ABORT(const CString& obj_name) = 0;
	virtual int Enable__UPPER_OBJECT_ABORT_CHECK() = 0;
	virtual int Disable__UPPER_OBJECT_ABORT_CHECK() = 0;

	virtual int Check__CHANNEL_NAME(const CString& ch_name) = 0;

	virtual int Disable__AUTO_POLLING() = 0;
	virtual int Enable__AUTO_POLLING(const double poll_sec)  = 0;

	// ...
	// return value ( 0 > : OK, 0 < : TimeOut, 0 == : Upper Object Abort)
	virtual int When__DATA_LIST(const CStringArray& l_data,const double sec = -1) = 0;

	//
	virtual int Update__CHANNEL_DATA() = 0;
	virtual CString Get__STRING() = 0;

	virtual int Check__VARIABLE_NAME(const CString& var_name) = 0;
};
class CII__VAR_STRING_CTRL
{
public:
	~CII__VAR_STRING_CTRL(){};
	
	// ...
	virtual CString Get__CHANNEL_NAME() = 0;

	virtual int Set__DATA(const CString& data) = 0;
	virtual int Get__DATA(CString& data) = 0;
	virtual int Check__DATA(const CString& data) = 0;

	// return value ( 0 > : OK, 0 < : TimeOut, 0 == : Upper Object Abort)
	virtual int When__DATA(const CString& data,const double sec = -1) = 0;
	virtual int When__DATA(const CString& data1,const CString& data2,const double sec = -1) = 0;

	// return value ( 0 > : OK, 0 < : TimeOut, 0 == : Upper Object Abort)
	virtual int When__NOT_DATA(const CString& data,const double sec = -1) = 0;
	virtual int When__NOT_DATA(const CString& data1,const CString& data2,const double sec = -1) = 0;

	// ...
	virtual CString Get__VARIABLE_NAME() = 0;

	virtual int Link__UPPER_OBJECT_ABORT(const CString& obj_name) = 0;
	virtual int Enable__UPPER_OBJECT_ABORT_CHECK() = 0;
	virtual int Disable__UPPER_OBJECT_ABORT_CHECK() = 0;

	virtual int Check__CHANNEL_NAME(const CString& ch_name) = 0;

	virtual int Disable__AUTO_POLLING() = 0;
	virtual int Enable__AUTO_POLLING(const double poll_sec)  = 0;

	// ...
	// return value ( 0 > : OK, 0 < : TimeOut, 0 == : Upper Object Abort)
	virtual int When__DATA_LIST(const CStringArray& l_data,const double sec = -1) = 0;

	//
	virtual int Update__CHANNEL_DATA() = 0;
	virtual CString Get__STRING() = 0;

	virtual int Check__VARIABLE_NAME(const CString& var_name) = 0;
};


// ...
#define MAKE__XCLS(XCLS,ICLS)				\
class XCLS									\
{											\
private:									\
	ICLS *m_pT;								\
											\
public:										\
	XCLS()									\
	{										\
		m_pT = NULL;  					    \
	}										\
	~XCLS()									\
	{										\
		if(m_pT != NULL)					\
		{									\
			delete m_pT;					\
		}									\
	}										\
											\
	ICLS* operator->() const				\
	{										\
		return m_pT;						\
	}										\
	void Set__PTR(ICLS* p_ptr)				\
	{										\
		m_pT = p_ptr;						\
	}										\
	ICLS* Get__PTR()						\
	{										\
		return m_pT;						\
	}										\
};

MAKE__XCLS(CX__VAR_ANALOG_CTRL, CII__VAR_ANALOG_CTRL );
MAKE__XCLS(CX__VAR_DIGITAL_CTRL,CII__VAR_DIGITAL_CTRL);
MAKE__XCLS(CX__VAR_STRING_CTRL, CII__VAR_STRING_CTRL );

//
#define  LINK__VAR_ANALOG_CTRL(XCLS,VAR_NAME)										\
XCLS.Set__PTR(p_variable->Get__VAR_ANALOG_CTRL(VAR_NAME));

#define  LINK__VAR_DIGITAL_CTRL(XCLS,VAR_NAME)										\
XCLS.Set__PTR(p_variable->Get__VAR_DIGITAL_CTRL(VAR_NAME));

#define  LINK__VAR_STRING_CTRL(XCLS,VAR_NAME)										\
XCLS.Set__PTR(p_variable->Get__VAR_STRING_CTRL(VAR_NAME));

//
#define  LINK__IO_VAR_ANALOG_CTRL(XCLS,VAR_NAME)									\
XCLS.Set__PTR(p_io_variable->Get__VAR_ANALOG_CTRL(VAR_NAME));

#define  LINK__IO_VAR_DIGITAL_CTRL(XCLS,VAR_NAME)									\
XCLS.Set__PTR(p_io_variable->Get__VAR_DIGITAL_CTRL(VAR_NAME));

#define  LINK__IO_VAR_STRING_CTRL(XCLS,VAR_NAME)									\
XCLS.Set__PTR(p_io_variable->Get__VAR_STRING_CTRL(VAR_NAME));

//
#define  LINK__EXT_VAR_ANALOG_CTRL(XCLS,OBJ_NAME,VAR_NAME)							\
XCLS.Set__PTR(p_ext_obj_create->Get__VAR_ANALOG_CTRL(OBJ_NAME,VAR_NAME));

#define  LINK__EXT_VAR_DIGITAL_CTRL(XCLS,OBJ_NAME,VAR_NAME)							\
XCLS.Set__PTR(p_ext_obj_create->Get__VAR_DIGITAL_CTRL(OBJ_NAME,VAR_NAME));

#define  LINK__EXT_VAR_STRING_CTRL(XCLS,OBJ_NAME,VAR_NAME)							\
XCLS.Set__PTR(p_ext_obj_create->Get__VAR_STRING_CTRL(OBJ_NAME,VAR_NAME));


class CII__ERROR_FEEDBACK__DEF_VARIABLE
{
public:
	virtual ~CII__ERROR_FEEDBACK__DEF_VARIABLE() { };

	//
	virtual int Call__ERROR__GET_DEF_DIGITAL_DESCRIPTION(const CString& obj_name,
														 const CString& dsc_name) EMPTY__BODY;

	//
	virtual int Call__ERROR__GET_DEF_CONST_DATA(const CString& obj_name,const CString& def_var) EMPTY__BODY;
	virtual int Call__ERROR__GET_CHANNEL_TYPE_CTRL(const CString& ch_type,
												   const CString& obj_name,
												   const CString& var_name) EMPTY__BODY;
};


// STD_DSP_NAME  -  LIST

#define DSP__OBJ_CTRL			"STD_OBJ_CTRL"
#define DSP__OBJ_STATUS			"STD_OBJ_STATUS"
#define DSP__SLOT_STATUS		"STD_SLOT_STATUS"
#define DSP__PRESSURE_STATUS	"STD_PRESSURE_STATUS"
#define DSP__VALVE_STATUS		"STD_VALVE_STATUS"
#define DSP__ENABLE_DISABLE     "STD_ENABLE_DISABLE"


class CII_DEFINE__VARIABLE
{
public:
	virtual ~CII_DEFINE__VARIABLE(){};

	// ...
	CII_CTRL__DESCRIPTOR      *pCTRL__DESCRIPTOR;

	CII_CTRL__ANALOG_VIRTUAL  *pCTRL__ANALOG;
	CII_CTRL__DIGITAL_VIRTUAL *pCTRL__DIGITAL;
	CII_CTRL__STRING_VIRTUAL  *pCTRL__STRING;

	// ...
	virtual int Add__MONITORING_PROC(const double sec,const int id) = 0;
	virtual int Stop__MONITORING_PROC(const int id)  = 0;

	virtual int Change__OBJECT_MODE(const CStringArray& l_mode) = 0;

	virtual int Link__DEF_VARIABLE__ERROR_FEEDBACK(CII__ERROR_FEEDBACK__DEF_VARIABLE* p_cls) = 0;

	virtual int Get__STD_DESCRIPTION(const CString& std_dsc_name,CString& dsc_item_list) = 0;
	// STD_DSP_NAME  -  LIST
	// STD_OBJ_CTRL				"ABORTED  AVAILABLE  RUN  ABORT  PAUSE  RESUME  UNKNOWN"
	// STD_OBJ_STATUS			"OFFLINE  UNINIT  NOTREADY  STANDBY  CTCINUSE  MAINTMODE  DISABLE"
	// STD_SLOT_STATUS			"UNKNOWN  NONE  EXIST  PROCESSING  PROCESSED  COMPLETED  ABORTED  MAPPED"
	// STD_PRESSURE_STATUS		"UNKNOWN  VAC  BTW  ATM"
	// STD_VALVE_STATUS			"UNKNOWN  CLOSE  OPEN"
	// STD_ENABLE_DISABLE       "ENABLE  DISABLE"

	virtual int Get__DEF_DIGITAL_DESCRIPTION(const CString& dsc_name,CString& dsc_item_list) = 0;
	virtual int Get__DEF_CONST_LIST(CStringArray& l_def_var,CStringArray& l_def_data) = 0;
	virtual int Get__DEF_CONST_DATA(const CString& def_var,CString& def_data) = 0;

	virtual CII__VAR_ANALOG_CTRL*  Get__VAR_ANALOG_CTRL(const CString& var_name)  = 0;
	virtual CII__VAR_DIGITAL_CTRL* Get__VAR_DIGITAL_CTRL(const CString& var_name) = 0;
	virtual CII__VAR_STRING_CTRL*  Get__VAR_STRING_CTRL(const CString& var_name)  = 0;
};


// ...
class CII_DEFINE__ALARM
{
public:
	virtual ~CII_DEFINE__ALARM(){};

	// ...
	CII_CTRL__ALARM	*pCTRL__ALARM;
};

class CII_DEFINE__IO_VARIABLE
{
public:
	virtual ~CII_DEFINE__IO_VARIABLE(){};

	// ...
	CII_CTRL__DESCRIPTOR  *pCTRL__DESCRIPTOR;

	CII_CTRL__ANALOG_IO   *pCTRL__ANALOG_IO;
	CII_CTRL__DIGITAL_IO  *pCTRL__DIGITAL_IO;
	CII_CTRL__STRING_IO   *pCTRL__STRING_IO;

	// ...
	virtual int Link__DEF_VARIABLE__ERROR_FEEDBACK(CII__ERROR_FEEDBACK__DEF_VARIABLE* p_cls) = 0;	
	virtual int Get__DEF_DIGITAL_DESCRIPTION(const CString& dsc_name,CString& dsc_item_list) = 0;

	// ...
	virtual CII__VAR_ANALOG_CTRL*  Get__VAR_ANALOG_CTRL(const CString& var_name)  = 0;
	virtual CII__VAR_DIGITAL_CTRL* Get__VAR_DIGITAL_CTRL(const CString& var_name) = 0;
	virtual CII__VAR_STRING_CTRL*  Get__VAR_STRING_CTRL(const CString& var_name)  = 0;
};


// ...
class CII_OBJECT__DEBUG
{
public:
	virtual ~CII_OBJECT__DEBUG(){};

	// ...
	virtual int Load__LOG(const CString& log_msg) = 0;
};


class CII__EXT_FNC_MODE_CTRL
{
public:
	virtual ~CII__EXT_FNC_MODE_CTRL(){};

	// ...
	virtual int Get__FNC_MODE_LIST(CStringArray& l_fnc_name,
								   CStringArray& l_obj_name,
								   CStringArray& l_mode_name,
								   CUIntArray&   l_err_flag) = 0;

	virtual int Get__FNC_PARAMETER(CStringArray& l_para) = 0;

	// Available > 0, Timeout = 0, Aborted < 0
	virtual int Call__FNC_MODE(const CString& fnc_name) = 0;
	virtual int Call_TimeOut__FNC_MODE(const CString& fnc_name,const double sec) = 0;

	virtual int Call__FNC_MODE(const CString& fnc_name,const CStringArray& l_para) = 0;
	virtual int Call_TimeOut__FNC_MODE(const CString& fnc_name,const CStringArray& l_para,const double sec) = 0;

	//
	virtual int Run__FNC_MODE(const CString& fnc_name) = 0;
	virtual int Run__FNC_MODE(const CString& fnc_name,const CStringArray& l_para) = 0;

	virtual int Wait__FNC_MODE(const CString& fnc_name) = 0;
	virtual int Wait_TimeOut__FNC_MODE(const CString& fnc_name,const double sec) = 0;

	//.....
	virtual int Init__FNC_MODE_GROUP() = 0;

	virtual int Register__WaitException__FNC_MODE(const CString& fnc_name) = 0;
	virtual int Register__WaitException__FNC_MODE(const CStringArray& l_fnc_name) = 0;
	virtual int Register__Wait__FNC_MODE(const CString& fnc_name) = 0;
	virtual int Register__Wait__FNC_MODE(const CStringArray& l_fnc_name) = 0;

	virtual int Wait__FNC_MODE_GROUP() = 0;
	virtual int Wait_TimeOut__FNC_MODE_GROUP(const double sec) = 0;

	//.....
	virtual int Get__FNC_MODE__CTRL_STS(const CString& fnc_name,CString& ctrl_sts) = 0; 
	virtual int Get__FNC_MODE__CTRL_STS(const CStringArray& l_fnc_name,CStringArray& l_ctrl_sts) = 0; 

	//-------------------------------------------------------------------------------------------------
	//.....
	virtual int Check__CTRL_ABORT() = 0;
	virtual int Abort__CTRL_STS() = 0;

	//
	virtual int Set__RETURN_FNC_PARAMETER(const CStringArray& l_para) = 0;
	virtual int Get__RETURN_FNC_PARAMETER(CStringArray& l_para) = 0;

	//.....
	virtual int Check__FNC_MODE_BUSY(const CString& fnc_name) = 0;

	//.....
	virtual CString Get__UPPER_OBJECT_NAME() = 0;

	//.....
	virtual int Abort__FNC_MODE(const CString& fnc_name) = 0;
};

//----------------------------------------------------
class CII__EXT_FNC_VAR_CTRL
{
public:
	virtual ~CII__EXT_FNC_VAR_CTRL(){};


	//-------------------------------------------------------------------------------------------------
	//.....
	virtual int Get__FNC_VARIABLE_LIST(CStringArray& l_ext_var,
									   CStringArray& l_obj_name,
									   CStringArray& l_obj_var,
									   CUIntArray& l_err_flag) = 0;


	//-------------------------------------------------------------------------------------------------
	//.....
	virtual int Get__FNC_VARIABLE_DATA(const CString& ext_var,CString& var_data) = 0;
	virtual int Check__FNC_VARIABLE_DATA(const CString& ext_var,const CString& var_data) = 0;

	virtual int Set__FNC_VARIABLE_DATA(const CString& ext_var,const CString& var_data) = 0;

	//
	virtual int Get__SYNC_FNC_VARIABLE_DATA(const CString& ext_var,CString& var_data) = 0;
	virtual int Check__SYNC_FNC_VARIABLE_DATA(const CString& ext_var,const CString& var_data) = 0;

	//.....
	virtual int When__FNC_VARIABLE_DATA(const CString& var_name,
										const CString& var_data,
										const double sec = 0.0) = 0;
	virtual int When__FNC_VARIABLE_DATA(const CString& var_name,
										const CStringArray& l_var_data,
										const double sec = 0.0) = 0;

	virtual int When__LESS_THAN(const CString& var_name,
								const double var_data,
								const double sec = 0.0) = 0;
	virtual int When__MORE_THAN(const CString& var_name,
								const double var_data,
								const double sec = 0.0) = 0;

	//.....
	virtual int Get__FNC_VARIABLE_INFO(const CString& ext_var,
									   CString& obj_name,
									   CString& obj_var) = 0;

	//-------------------------------------------------------------------------------------------------
	//.....
	virtual int When__FNC_VARIABLE_DATA__CHECK_ABORT(const CString& abort_channel,
													 const CString& var_name,
													 const CString& var_data,
													 const double sec = 0.0) = 0;
	virtual int When__FNC_VARIABLE_DATA__CHECK_ABORT(const CString& abort_channel,
													 const CString& var_name,
												     const CStringArray& l_var_data,
													 const double sec = 0.0) = 0;

	virtual int When__LESS_THAN__CHECK_ABORT(const CString& abort_channel,
											 const CString& var_name,
											 const double var_data,
											 const double sec = 0.0) = 0;
	virtual int When__MORE_THAN__CHECK_ABORT(const CString& abort_channel,
											 const CString& var_name,
											 const double var_data,
											 const double sec = 0.0) = 0;

};

//----------------------------------------------------
class CII__EXT_USER_FNC_CTRL
{
public:
	virtual ~CII__EXT_USER_FNC_CTRL(){};


	//-------------------------------------------------------------------------------------------------
	//.....
	virtual int Get__USER_FNC_CTRL(CUIntArray& l_fnc_type,
								   CStringArray& l_fnc_name,
								   CStringArray& l_obj_name,
								   CStringArray& l_obj_fnc,
								   CUIntArray&   l_err_flag) = 0;


	//-------------------------------------------------------------------------------------------------
	//.....
	virtual int Call__RET_INT(const CString& fnc_name) = 0;
	virtual int Call__RET_INT(const CString& fnc_name,int& r_flag) = 0;

	virtual double  Call__RET_DOUBLE(const CString& fnc_name) = 0;
	virtual double  Call__RET_DOUBLE(const CString& fnc_name,int& r_flag) = 0;

	virtual CString Call__RET_STRING(const CString& fnc_name) = 0;
	virtual CString Call__RET_STRING(const CString& fnc_name,int& r_flag) = 0;

	virtual SCI__CONDITION* Call__RET_CONDITION(const CString& fnc_name) = 0;
	virtual SCI__CONDITION* Call__RET_CONDITION(const CString& fnc_name,int& r_flag) = 0;

	//
	virtual int Call__RET_INT__INT_STRING(const CString& fnc_name,const int i_para,const CString& str_para) = 0;
	virtual int Call__RET_INT__INT_STRING(const CString& fnc_name,const int i_para,const CString& str_para,int& r_flag) = 0;

	virtual int Call__RET_INT__STRING_STRING(const CString& fnc_name,const CString& str_para1,const CString& str_para2) = 0;
	virtual int Call__RET_INT__STRING_STRING(const CString& fnc_name,const CString& str_para1,const CString& str_para2,int& r_flag) = 0;

	virtual CString Call__RET_STRING__INT(const CString& fnc_name,const int i_para) = 0;
	virtual CString Call__RET_STRING__INT(const CString& fnc_name,const int i_para,int& r_flag) = 0;

	virtual CString Call__RET_STRING__STRING(const CString& fnc_name,const CString& str_para) = 0;
	virtual CString Call__RET_STRING__STRING(const CString& fnc_name,const CString& str_para,int& r_flag) = 0;
};


//------------------------------------------------------------------------------------------------
//----------------------------------------------------
#define ERROR_TYPE__VARIABLE_SET						1
#define ERROR_TYPE__VARIABLE_GET						2
#define ERROR_TYPE__VARIABLE_CHECK						3
		

class CII__ERROR_FEEDBACK
{
public:
	virtual ~CII__ERROR_FEEDBACK(){};

	//-------------------------------------------------------------------------
	virtual int Call__VARIABLE_ERROR(const int error_type,
									 const CString& obj_name,
									 const CString& var_name,
									 const CString& var_data,
									 const CString& err_msg) = 0;
	
};


//
#define USER_FNC_TYPE__RET_INT							1
#define USER_FNC_TYPE__RET_DOUBLE						2
#define USER_FNC_TYPE__RET_STRING						3
#define USER_FNC_TYPE__RET_CONDITION					4

#define USER_FNC_TYPE__RET_INT__INT_STRING				5
#define USER_FNC_TYPE__RET_INT__STRING_STRING			6
#define USER_FNC_TYPE__RET_STRING__INT					7
#define USER_FNC_TYPE__RET_STRING__STRING				8


#define FNC_MODE_WAIT__AVAILABLE						1
#define FNC_MODE_WAIT__ABORTED							-1
#define FNC_MODE_WAIT__TIMEOUT							0


class CII_OBJECT__VARIABLE
{
public:
	virtual ~CII_OBJECT__VARIABLE(){};

	//-------------------------------------------------------------------------
	virtual int Set__VARIABLE_DATA(const CString& var_name,const CString& var_data) = 0;
	virtual int Get__VARIABLE_DATA(const CString& var_name,CString& var_data) = 0;
	virtual int Check__VARIABLE_DATA(const CString& var_name,const CString& var_data) = 0;

	virtual int When__VARIABLE_DATA(const CString& var_name,const CString& var_data,const double sec = 0.0) = 0;
	virtual int When__VARIABLE_DATA(const CString& var_name,const CStringArray& l_var_data,const double sec = 0.0) = 0;

	virtual int When__LESS_THAN(const CString& var_name,const double var_data,const double sec = 0.0) = 0;
	virtual int When__MORE_THAN(const CString& var_name,const double var_data,const double sec = 0.0) = 0;

	virtual int Get__SYNC_VARIABLE_DATA(const CString& var_name,CString& var_data) = 0;
	virtual int Check__SYNC_VARIABLE_DATA(const CString& var_name,const CString& var_data) = 0;

	virtual int Get__CTRL_STATUS(CString& ctrl_sts) = 0;

	virtual int Stop__MONITORING_PROC(const int id)  = 0;
	virtual int Start__MONITORING_PROC(const int id) = 0;

	//-------------------------------------------------------------------------
	virtual int Link__ERROR_FEEDBACK(CII__ERROR_FEEDBACK *p_class) = 0;

	virtual int Get__EXT_FNC_MODE_LIST(CStringArray& l_fnc_name,CStringArray& l_obj_name,CStringArray& l_mode_name,CUIntArray& l_err_flag) = 0;
	virtual int Get__EXT_FNC_RET_LIST(CUIntArray& l_fnc_type,CStringArray& l_fnc_name,CStringArray& l_obj_name,CStringArray& l_obj_fnc,CUIntArray& l_err_flag) = 0;

	virtual int Call__FNC_MODE(const CString& fnc_name) = 0;
	virtual int Call__FNC_MODE(const CString& fnc_name,const CStringArray& l_para) = 0;

	virtual int Run__FNC_MODE(const CString& fnc_name) = 0;
	virtual int Run__FNC_MODE(const CString& fnc_name,const CStringArray& l_para) = 0;

	virtual int Wait__FNC_MODE(const CString& fnc_name) = 0;

	virtual int Init__FNC_MODE_GROUP() = 0;
	virtual int Register__WaitException__FNC_MODE(const CString& fnc_name) = 0;
	virtual int Register__WaitException__FNC_MODE(const CStringArray& l_fnc_name) = 0;
	virtual int Register__Wait__FNC_MODE(const CString& fnc_name) = 0;
	virtual int Register__Wait__FNC_MODE(const CStringArray& l_fnc_name) = 0;
	virtual int Wait__FNC_MODE_GROUP() = 0;

	virtual int Get__FNC_MODE__CTRL_STS(const CString& fnc_name,CString& ctrl_sts) = 0; 
	virtual int Get__FNC_MODE__CTRL_STS(const CStringArray& l_fnc_name,CStringArray& l_ctrl_sts) = 0; 

	virtual int Get__FNC_PARAMETER(CStringArray& l_para) = 0;

	virtual int     Call__RET_INT(const CString& fnc_name,int& r_flag)    = 0;
	virtual double  Call__RET_DOUBLE(const CString& fnc_name,int& r_flag) = 0;
	virtual CString Call__RET_STRING(const CString& fnc_name,int& r_flag) = 0;

	virtual SCI__CONDITION* Call__RET_CONDITION(const CString& fnc_name,int& r_flag) = 0;

	//
	virtual int Get__EXT_FNC_VARIABLE(const CString& ext_var,CString& var_data) = 0;
	virtual int Check__EXT_FNC_VARIABLE(const CString& ext_var,const CString& var_data) = 0;

	virtual int Set__EXT_FNC_VARIABLE(const CString& ext_var,const CString& var_data) = 0;

	virtual int Get__EXT_VARIABLE_LIST(CStringArray& l_ext_var,
									   CStringArray& l_obj_name,
									   CStringArray& l_obj_var,
									   CUIntArray&   l_err_flag) = 0;

	//
	virtual int Get__DEF_CONST_LIST(CStringArray& l_def_var,CStringArray& l_def_data) = 0;

	virtual int Get__DEF_CONST_DATA(const CString& def_var,CString& def_data) = 0;

	//-------------------------------------------------------------------------
	//
	virtual int  Check__CTRL_ABORT() = 0;
	virtual bool Check__OBJ_MODE(const CString& seq_mode,const CString& fnc_name) = 0;
	virtual int  Abort__CTRL_STS() = 0;

	//-------------------------------------------------------------------------
	virtual int  Call_TimeOut__FNC_MODE(const CString& fnc_name,const double sec) = 0;
	virtual int  Call_TimeOut__FNC_MODE(const CString& fnc_name,
										const CStringArray& l_para,
										const double sec) = 0;

	virtual int  Wait_TimeOut__FNC_MODE(const CString& fnc_name,const double sec) = 0;
	virtual int  Wait_TimeOut__FNC_MODE_GROUP(const double sec) = 0;

	//-------------------------------------------------------------------------
	virtual int  Get__Remote_Seq_ID(const CString& obj_name,const CString& var_name) = 0;

	virtual int  Change__MONITORING_TIME(const int id,const double sec)  = 0;

	//-------------------------------------------------------------------------
	virtual CII__EXT_FNC_MODE_CTRL* Get__EXT_FNC_MODE_CTRL() = 0;
	virtual CII__EXT_FNC_VAR_CTRL*  Get__EXT_FNC_VAR_CTRL() = 0;
	virtual CII__EXT_USER_FNC_CTRL* Get__EXT_USER_FNC_CTRL() = 0;

	//-------------------------------------------------------------------------
	virtual int  Change__ANALOG_RANGE(const CString& variable_name,
									  const int dec,        // < 0 : No Change
									  const double min,
									  const double max) = 0;
	
	// ...
	virtual int Add__OBJECT_MODE(const CStringArray& l_mode) = 0;
	virtual int Change__DIGITAL_LIST(const CString& var_name,
									 const CStringArray& l_item) = 0;

	// ...
	virtual int Get__NODE_PROPERTY(CString& card_name,
								   CStringArray& l_macid,
								   CStringArray& l_dev_name) = 0;

	// ...
	virtual int Exception_Timer(const double msec) = 0;


	//-------------------------------------------------------------------------
	virtual HANDLE Link__EVENT_HANDLE(const int event_id, const double ref_sec) = 0;
	virtual void Wait__EVENT_HANDLE(HANDLE h_event) = 0;

	virtual void Active__SINGLE_OBJECT(const double ref_sec) = 0;
	virtual void Wait__SINGLE_OBJECT(const double ref_sec = 0.0) = 0;
};


#define DECLARE__EXT_CTRL(pVAR)														\
CII__EXT_FNC_MODE_CTRL *p_ext_mode_ctrl = pVAR->Get__EXT_FNC_MODE_CTRL();			\
CII__EXT_FNC_VAR_CTRL  *p_ext_var_ctrl  = pVAR->Get__EXT_FNC_VAR_CTRL();			\
CII__EXT_USER_FNC_CTRL *p_ext_user_ctrl = pVAR->Get__EXT_USER_FNC_CTRL();


//----------------------------------------------------
class CII_INTERLOCK__ALARM
{
public:
	virtual ~CII_INTERLOCK__ALARM(){};

	//-------------------------------------------------------------------------
	virtual int Post__ALARM(const int id) = 0;
	virtual int Post__ALARM_WITH_MESSAGE(const int id,const CString& message) = 0;

	virtual int Check__ALARM(const int id,CString& recovery_act) = 0;
};

//----------------------------------------------------
class CII_OBJECT__ALARM
{
public:
	virtual ~CII_OBJECT__ALARM(){};

	//-------------------------------------------------------------------------
	virtual int Popup__ALARM(const int id, CString& recovery_action) = 0;
	virtual int Post__ALARM(const int id) = 0;

	virtual int Check__ALARM(const int id, CString& recovery_action) = 0;
	virtual int Clear__ALARM(const int id) = 0;

	//-------------------------------------------------------------------------
	virtual int Is__ALARM(const int id) = 0;

	virtual int Post__ALARM_WITH_BLOCKING(const int alm_id, CString& recovery_action) = 0;

	virtual int Is__AlarmOption(const int id, 
								CString& option1,
								CString& option2, 
								CString& option3) = 0;

	//-------------------------------------------------------------------------
	virtual int Popup__ALARM_With_MESSAGE(const int id,const CString& msg,CString& recovery_action) = 0;
	virtual int Post__ALARM_With_MESSAGE(const int id,const CString& msg)  = 0;

	//-------------------------------------------------------------------------
	virtual int Popup__MESSAGE_BOX(const CString& title,
								   const CString& message,
								   const CString& option,
								   CString& act_result) = 0;
	virtual int Popup__MESSAGE_BOX(const CString& title,
								   const CString& message,
								   const CStringArray& l_option,
								   CString& act_result) = 0;

	//-------------------------------------------------------------------------
	virtual int Update__MESSAGE_BOX(const CString& box_title,const CString& box_msg,int& sys_id) = 0;
	virtual int Check__MESSAGE_BOX(const int sys_id,CString& r_act) = 0;

	//-------------------------------------------------------------------------
	virtual int Is__SEQ_ALARM(const int seq_id,const int external_id) = 0;

	virtual int Clear__ALL_ALARM() = 0;

	//-------------------------------------------------------------------------
	virtual int Post__WARNING_With_MESSAGE(const int id,const CString& msg) = 0;

	//-------------------------------------------------------------------------
	virtual int Check__Posted_Internal_Alarm(const CUIntArray& l_internal_id) = 0;
	virtual int Get__Posted_Internal_Alarm(CUIntArray& l_internal_id) = 0;

	virtual int Get__Posted_All_Alarm(CUIntArray& l_eqp_id,
									  CUIntArray& l_sys_id,
									  CStringArray& l_obj_name,
									  CUIntArray& l_internal_id) = 0;

	virtual int Delete__Cleared_All_Alarm() = 0;
	virtual int Get__Posted_Alarm_DB_Size() = 0;
};


//----------------------------------------------------
#define  OBJECT_STATUS__UNKNOWN						-1
#define  OBJECT_STATUS__ABORTED						1
#define  OBJECT_STATUS__AVAILABLE					2
#define  OBJECT_STATUS__RUN							3
#define  OBJECT_STATUS__ABORT						4
#define  OBJECT_STATUS__PAUSE						5
#define  OBJECT_STATUS__RESUME						6


class CDS__IO_CHANNEL_INFO
{
public:
	// Analog & Digital & String ...
	int iMD_NO;				// 
	int iCH_NO;				// 

	CString sCOMMAND1;      // 
	CString sCOMMAND2;      // 
	CString sCOMMAND3;		// 
	
	// Only Analog ...
	double dMIN_VALUE;      // All Type
	double dMAX_VALUE;      // All Type
	
	double dMIN_VOLT;		// 
	double dMAX_VOLT;       // 
};


class CII_EXT_OBJECT__CTRL
{
public:
	virtual ~CII_EXT_OBJECT__CTRL(){};

	//-------------------------------------------------------------------------
	virtual int Run__OBJECT(const CString& mode) = 0;
	virtual int Abort__OBJECT()  = 0;
	virtual int Pause__OBJECT()  = 0;
	virtual int Resume__OBJECT() = 0;

	virtual int Get__OBJECT_STATUS() = 0;
	virtual int When__OBJECT()  = 0;
	

	//-------------------------------------------------------------------------
	virtual int Set__VARIABLE_DATA(const CString& name,const CString& data) = 0;
	virtual int Get__VARIABLE_DATA(const CString& name,CString& data) = 0;

	//-------------------------------------------------------------------------
	virtual int Check__VARIABLE_DATA(const CString& var_name,
									 const CString& var_data) = 0;
	virtual int When__VARIABLE_DATA(const CString& var_name,
									const CString& var_data,
									const double sec = 0.0) = 0;
	virtual int When__VARIABLE_DATA(const CString& var_name,
									const CStringArray& l_var_data,
									const double sec = 0.0) = 0;

	virtual int When__LESS_THAN(const CString& var_name,
								const double var_data,
								const double sec = 0.0) = 0;
	virtual int When__MORE_THAN(const CString& var_name,
								const double var_data,
								const double sec = 0.0) = 0;


	//-------------------------------------------------------------------------
	virtual int Get__OBJECT_STATUS(CString& ctrl_sts) = 0;


	//-------------------------------------------------------------------------
	virtual int When__VARIABLE_DATA__CHECK_ABORT(const CString& abort_channel,
												 const CString& var_name,
												 const CString& var_data,
												 const double sec = 0.0) = 0;
	virtual int When__VARIABLE_DATA__CHECK_ABORT(const CString& abort_channel,
												 const CString& var_name,
											     const CStringArray& l_var_data,
												 const double sec = 0.0) = 0;

	virtual int When__LESS_THAN__CHECK_ABORT(const CString& abort_channel,
											 const CString& var_name,
											 const double var_data,
											 const double sec = 0.0) = 0;
	virtual int When__MORE_THAN__CHECK_ABORT(const CString& abort_channel,
											 const CString& var_name,
											 const double var_data,
											 const double sec = 0.0) = 0;

	//-------------------------------------------------------------------------
	virtual int Call__OBJECT(const CString& mode) = 0;

	//-------------------------------------------------------------------------
	virtual int Link__ERROR_FEEDBACK(CII__ERROR_FEEDBACK *p_class) = 0;

	//-------------------------------------------------------------------------
	virtual int When_TimeOut__OBJECT(const double sec) = 0;
	virtual int Call_TimeOut__OBJECT(const CString& mode,const double sec) = 0;

	//
	virtual int Call__OBJ_MODE(const CString& mode,CStringArray& l_para) = 0;
	virtual int Run__OBJ_MODE(const CString& mode,const CStringArray& l_para) = 0;
	virtual int When__OBJ_MODE(const CString& mode,CStringArray& l_para) = 0;

	//
	virtual int Get__OBJ_MODE(CString& mode) = 0;

	//-------------------------------------------------------------------------
	virtual int Link__UPPER_OBJECT() = 0;
	virtual int Dislink__UPPER_OBJECT() = 0;
	
	//-------------------------------------------------------------------------
	virtual int Set__RETURN_FNC_PARAMETER(const CStringArray& l_para) = 0;
	virtual int Get__RETURN_FNC_PARAMETER(CStringArray& l_para) = 0;	

	//-------------------------------------------------------------------------
	virtual int Call__QUERY(const CString& query_name,CString& query_data) = 0;

	//-------------------------------------------------------------------------
	// BUSY > 0,  AVAILABLE = -1, ABORTED = -2, IDLE = -3
	virtual int Is__OBJ_BUSY() = 0;		

	// ...
	virtual CString Get__OBJ_NAME() = 0;
	virtual int Get__IO_InVariable_List(CStringArray& l_var_name)   = 0;
	virtual int Get__IO_OutVariable_List(CStringArray& l_var_name)  = 0;
	virtual int Get__Virtual_Channel_List(CStringArray& l_var_name) = 0;

	// ...
	virtual int Check__OBJ_MODE(const CString& mode) = 0;
	virtual int Check__OBJ_MODE(const CStringArray& l_mode) = 0;

	// ...
	virtual int Call__QUERY_LIST(const CString& query_name,CStringArray& l_data) = 0;

	//-------------------------------------------------------------------------
	virtual int Get__IO_InVariable_Info(const CString& var_name,  CDS__IO_CHANNEL_INFO& ds_info) = 0;
	virtual int Get__IO_OutVariable_Info(const CString& var_name, CDS__IO_CHANNEL_INFO& ds_info) = 0;

	// ...
	virtual int Enable_IO_InVariable__Auto_Polling_Option() = 0;			// Default
	virtual int Disable_IO_InVariable__Auto_Polling_Option() = 0;			
	virtual int Updata__All_IO_InVariable() = 0;							// In only case that auto-polling option is disabled.

	// ...
	// Type : A (Analog), D(Digital), S(String)
	virtual int Get__IO_InVariable_Type_List(CStringArray& l_var_name,  CStringArray& l_var_type) = 0;
	virtual int Get__IO_OutVariable_Type_List(CStringArray& l_var_name, CStringArray& l_var_type) = 0;
	virtual int Get__Virtual_Channel_Type_List(CStringArray& l_var_name,CStringArray& l_var_Type) = 0;

	virtual int Get__Item_Info_Of_Digital_Variable(const CString& var_name,CString& cur_item,CStringArray& l_item) = 0;
	virtual int Get__Item_Info_Of_Analog_Variable(const CString& var_name,double& cur_data,double& min_data,double& max_data) = 0;
	virtual int Get__Item_Info_Of_String_Variable(const CString& var_name,CString& cur_data) = 0;

	virtual int Set__Digital_Variable_With_Item_Index(const CString& var_name,const int item_index) = 0;


	//-------------------------------------------------------------------------
	// ...
	virtual int Call__QUERY(const CString& query_name,const CStringArray& l_sub_query, CString& query_data) EMPTY__BODY;
	virtual int Call__QUERY_LIST(const CString& query_name,const CStringArray& l_sub_query, CStringArray& l_data) EMPTY__BODY;
};

class CII_EXT_OBJECT__CREATE
{
public:
	virtual ~CII_EXT_OBJECT__CREATE(){};

	//-------------------------------------------------------------------------
	virtual CII_EXT_OBJECT__CTRL *Create__OBJECT_CTRL(const CString& obj_name) = 0;
	

	//-------------------------------------------------------------------------
	virtual int Link__DEF_VARIABLE__ERROR_FEEDBACK(CII__ERROR_FEEDBACK__DEF_VARIABLE* p_cls) = 0;

	//
	virtual int Get__DEF_CONST_LIST(CStringArray& l_def_var,CStringArray& l_def_data) = 0;
	virtual int Get__DEF_CONST_DATA(const CString& def_var,CString& def_data) = 0;

	//
	virtual CII__VAR_ANALOG_CTRL*  Get__VAR_ANALOG_CTRL(const CString& obj_name,const CString& var_name)  = 0;
	virtual CII__VAR_DIGITAL_CTRL* Get__VAR_DIGITAL_CTRL(const CString& obj_name,const CString& var_name) = 0;
	virtual CII__VAR_STRING_CTRL*  Get__VAR_STRING_CTRL(const CString& obj_name,const CString& var_name)  = 0;

	//
	virtual int Get__DIGITAL_DESCRIPTOR_INFO(const CString& remote_obj_name,
										     const CString& remote_var_name,
											 CString& dsp_name) = 0;
	virtual int Change__LOCAL_DIGITAL_DESCRIPTOR_INFO(const CString& local_var_name,
													  const CString& dsp_name) = 0;

	//
	virtual int Get__DEF_CONST_DATA_EX(const CString& def_var,CString& def_data,const int err_check) = 0;

	//
	virtual int Get__CHANNEL_To_OBJ_VAR(const CString& ch_name,CString& obj_name,CString& var_name) = 0;
};

class CII_FA_SERVICE__CTRL
{
public:
	virtual ~CII_FA_SERVICE__CTRL(){};

	//-------------------------------------------------------------------------

};
class CII_FA_SERVICE__CREATE
{
public:
	virtual ~CII_FA_SERVICE__CREATE(){};

	//-------------------------------------------------------------------------
	virtual int Check__FA_SERVICE(const CString& service_name) = 0;

	virtual CII_FA_SERVICE__CTRL* Create__FA_SERVICE(const CString& service_name,const CString& fa_file_name) = 0;

	//-------------------------------------------------------------------------

};
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
typedef int     (*FNC_RET_INT)(void *p_void);
typedef double  (*FNC_RET_DOUBLE)(void *p_void);
typedef CString (*FNC_RET_STRING)(void *p_void);

typedef SCI__CONDITION* (*FNC_RET_CONDITION)(void *p_void);

//
typedef int (*FNC_RET_INT__INT_STRING)(void* p_void,const int i_para,const CString& str_para);
typedef int (*FNC_RET_INT__STRING_STRING)(void* p_void,const CString& str_para1,const CString& str_para2);

typedef CString (*FNC_RET_STRING__INT)(void* p_void,const int i_para);
typedef CString (*FNC_RET_STRING__STRING)(void* p_void,const CString& str_para);


class CII__ERROR_FEEDBACK__USER_FNC
{
public:
	virtual ~CII__ERROR_FEEDBACK__USER_FNC() { };

	//
	virtual int Call__ERROR__EXT_FNC_MODE(const CString& fnc_name,
										  const CString& obj_name,
										  const CString& obj_mode,
										  const CString& err_msg,
										  CII_OBJECT__ALARM *p_alarm) EMPTY__BODY;

	virtual int Call__ERROR__EXT_USER_FNC(const int fnc_type,
										  const CString& fnc_name,
									      const CString& obj_name,
										  const CString& obj_fnc,
										  const CString& err_msg,
										  CII_OBJECT__ALARM *p_alarm) EMPTY__BODY;

	//
	virtual int Register__ERROR__EXT_FNC_MODE(const CString& mode_name)     EMPTY__BODY;
	virtual int Register__ERROR__EXT_FNC_VAR(const CString& var_name)       EMPTY__BODY;
	
	virtual int Register__ERROR__EXT_RET_INT(const CString& fnc_name)       EMPTY__BODY;
	virtual int Register__ERROR__EXT_RET_DOUBLE(const CString& fnc_name)    EMPTY__BODY;
	virtual int Register__ERROR__EXT_RET_STRING(const CString& fnc_name)    EMPTY__BODY;
	virtual int Register__ERROR__EXT_RET_CONDITION(const CString& fnc_name) EMPTY__BODY;

	virtual int Register__ERROR__EXT_RET_INT__INT_STRING(const CString& fnc_name)       EMPTY__BODY;
	virtual int Register__ERROR__EXT_RET_INT__STRING_STRING(const CString& fnc_name)    EMPTY__BODY;
	virtual int Register__ERROR__EXT_RET_STRING__INT(const CString& fnc_name)			EMPTY__BODY;
	virtual int Register__ERROR__EXT_RET_STRING__STRING(const CString& fnc_name)        EMPTY__BODY;

	//
	virtual int Get__ERROR__DEF_CONST_DATA(const CString& obj_name,
										   const CString& def_var,
										   const CString& def_data) EMPTY__BODY;
};

class CII__COMMON_CODE__ERROR_FEEDBACK__USER_FNC : public CII__ERROR_FEEDBACK__USER_FNC
{
public:
	virtual ~CII__COMMON_CODE__ERROR_FEEDBACK__USER_FNC() { };
	
	// ...
	virtual int Set__Object_Name(const CString& obj_name) = 0;
};


// ...
class CII_DEFINE__FUNCTION
{
public:
	virtual ~CII_DEFINE__FUNCTION(){};

	//-------------------------------------------------------------------------
	virtual int Link__ERROR_FEEDBACK(CII__ERROR_FEEDBACK__USER_FNC *p_class) = 0;

	//-------------------------------------------------------------------------
	virtual int Register__RET_INT(const CString& fnc_name,
								  void* p_cls,
								  FNC_RET_INT p_fnc) = 0;

	virtual int Register__RET_DOUBLE(const CString& fnc_name,
									 void* p_cls,
									 FNC_RET_DOUBLE p_fnc) = 0;

	virtual int Register__RET_STRING(const CString& fnc_name,
									 void* p_cls,
									 FNC_RET_STRING p_fnc) = 0;

	virtual int Register__RET_CONDITION(const CString& fnc_name,
										void* p_cls,
										FNC_RET_CONDITION p_fnc) = 0;

	//
	virtual int Register__EXT_VARIABLE(const CString& ext_var_name) = 0;
	virtual int Register__EXT_VARIABLE_With_COMMENT(const CString& ext_var_name,const CString& comment) = 0;

	virtual int Register__EXT_FNC_MODE_With_COMMENT(const CString& ext_fnc_mode,const CString& comment = "") = 0;

	virtual int Register__EXT_RET_INT(const CString& ext_fnc_name,const CString& comment = "") = 0;
	virtual int Register__EXT_RET_DOUBLE(const CString& ext_fnc_name,const CString& comment = "") = 0;
	virtual int Register__EXT_RET_STRING(const CString& ext_fnc_name,const CString& comment = "") = 0;
	virtual int Register__EXT_RET_CONDITION(const CString& ext_fnc_name,const CString& comment = "") = 0;

	//-------------------------------------------------------------------------
	virtual int Register__RET_INT__INT_STRING(const CString& fnc_name,
											  void* p_cls,
											  FNC_RET_INT__INT_STRING p_fnc) = 0;

	virtual int Register__RET_INT__STRING_STRING(const CString& fnc_name,
												 void* p_cls,
												 FNC_RET_INT__STRING_STRING p_fnc) = 0;

	virtual int Register__RET_STRING__INT(const CString& fnc_name,
										  void* p_cls,
										  FNC_RET_STRING__INT p_fnc) = 0;

	virtual int Register__RET_STRING__STRING(const CString& fnc_name,
											 void* p_cls,
											 FNC_RET_STRING__STRING p_fnc) = 0;

	//
	virtual int Register__EXT_RET_INT__INT_STRING(const CString& ext_fnc_name,const CString& comment = "") = 0;
	virtual int Register__EXT_RET_INT__STRING_STRING(const CString& ext_fnc_name,const CString& comment = "") = 0;
	virtual int Register__EXT_RET_STRING__INT(const CString& ext_fnc_name,const CString& comment = "") = 0;
	virtual int Register__EXT_RET_STRING__STRING(const CString& ext_fnc_name,const CString& comment = "") = 0;

	//-------------------------------------------------------------------------
	virtual int Get__DEF_CONST_DATA(const CString& def_var,CString& def_data) = 0;
};


//----------------------------------------------------------------------------------------
//.....
#define  ADD__EXT_VARIABLE(EXT_VAR_BFF,EXT_VAR_NAME)										\
EXT_VAR_BFF = EXT_VAR_NAME;																	\
p_fnc_ctrl->Register__EXT_VARIABLE(EXT_VAR_NAME);

//
#define  ADD__EXT_VARIABLE_WITH_COMMENT(EXT_VAR_BFF,EXT_VAR_NAME,EXT_COMMENT)				\
EXT_VAR_BFF = EXT_VAR_NAME;																	\
p_fnc_ctrl->Register__EXT_VARIABLE_With_COMMENT(EXT_VAR_NAME,EXT_COMMENT);


//.....
#define  ADD__EXT_FNC_MODE_WITH_COMMENT(EXT_MODE_BFF,EXT_MODE_NAME,COMMENT)					\
EXT_MODE_BFF = EXT_MODE_NAME;																\
p_fnc_ctrl->Register__EXT_FNC_MODE_With_COMMENT(EXT_MODE_NAME,COMMENT);


//.....
#define  ADD__EXT_RET_INT_WITH_COMMENT(EXT_FNC_BFF,EXT_FNC_NAME,COMMENT)					\
EXT_FNC_BFF = EXT_FNC_NAME;																	\
p_fnc_ctrl->Register__EXT_RET_INT(EXT_FNC_NAME,COMMENT)

//
#define  ADD__EXT_RET_DOUBLE_WITH_COMMENT(EXT_FNC_BFF,EXT_FNC_NAME,COMMENT)					\
EXT_FNC_BFF = EXT_FNC_NAME;																	\
p_fnc_ctrl->Register__EXT_RET_DOUBLE(EXT_FNC_NAME,COMMENT);

//
#define  ADD__EXT_RET_STRING_WITH_COMMNET(EXT_FNC_BFF,FNC_NAME,COMMENT)						\
EXT_FNC_BFF = EXT_FNC_NAME;																	\
p_fnc_ctrl->Register__EXT_RET_STRING(EXT_FNC_NAME,COMMENT);

//
#define  ADD__EXT_RET_CONDITION_WITH_COMMENT(EXT_FNC_BFF,EXT_FNC_NAME,COMMENT)				\
EXT_FNC_BFF = EXT_FNC_NAME;																	\
p_fnc_ctrl->Register__EXT_RET_CONDITION(EXT_FNC_NAME,COMMENT);

//
#define  ADD__EXT_RET_INT__INT_STRING_WITH_COMMENT(EXT_FNC_BFF,EXT_FNC_NAME,COMMENT)		\
EXT_FNC_BFF = EXT_FNC_NAME;																	\
p_fnc_ctrl->Register__EXT_RET_INT__INT_STRING(EXT_FNC_NAME,COMMENT);

//
#define  ADD__EXT_RET_INT__STRING_STRING_WITH_COMMENT(EXT_FNC_BFF,EXT_FNC_NAME,COMMENT)		\
EXT_FNC_BFF = EXT_FNC_NAME;																	\
p_fnc_ctrl->Register__EXT_RET_INT__STRING_STRING(EXT_FNC_NAME,COMMENT);

//
#define  ADD__EXT_RET_STRING__INT_WITH_COMMENT(EXT_FNC_BFF,EXT_FNC_NAME,COMMENT)			\
EXT_FNC_BFF = EXT_FNC_NAME;																	\
p_fnc_ctrl->Register__EXT_RET_STRING__INT(EXT_FNC_NAME,COMMENT);

//
#define  ADD__EXT_RET_STRING__STRING_WITH_COMMENT(EXT_FNC_BFF,EXT_FNC_NAME,COMMENT)			\
EXT_FNC_BFF = EXT_FNC_NAME;																	\
p_fnc_ctrl->Register__EXT_RET_STRING__STRING(EXT_FNC_NAME,COMMENT);


//----------------------------------------------------------------------------------------


//
#define  DECLARE__FNC_RET_INT(CLS_TYPE,FNC_NAME)											\
int  CLS_TYPE##FNC_NAME(void *p_void)														\
{																							\
	CLS_TYPE *p_cls = (CLS_TYPE*) p_void;													\
																							\
	return p_cls->FNC_NAME();																\
}

#define  DECLARE__FNC_RET_DOUBLE(CLS_TYPE,FNC_NAME)											\
double CLS_TYPE##FNC_NAME(void *p_void)														\
{																							\
	CLS_TYPE *p_cls = (CLS_TYPE*) p_void;													\
																							\
	return p_cls->FNC_NAME();																\
}

#define  DECLARE__FNC_RET_STRING(CLS_TYPE,FNC_NAME)											\
CString CLS_TYPE##FNC_NAME(void *p_void)													\
{																							\
	CLS_TYPE *p_cls = (CLS_TYPE*) p_void;													\
																							\
	return p_cls->FNC_NAME();																\
}

#define  DECLARE__FNC_RET_CONDITION(CLS_TYPE,FNC_NAME)										\
SCI__CONDITION* CLS_TYPE##FNC_NAME(void *p_void)											\
{																							\
	CLS_TYPE *p_cls = (CLS_TYPE*) p_void;													\
																							\
	return p_cls->FNC_NAME();																\
}

#define  DECLARE__FNC_RET_INT__INT_STRING(CLS_TYPE,FNC_NAME)								\
int  CLS_TYPE##FNC_NAME(void *p_void,const int i_para,const CString& str_para)				\
{																							\
	CLS_TYPE *p_cls = (CLS_TYPE*) p_void;													\
																							\
	return p_cls->FNC_NAME(i_para,str_para);												\
}

#define  DECLARE__FNC_RET_INT__STRING_STRING(CLS_TYPE,FNC_NAME)								\
int  CLS_TYPE##FNC_NAME(void *p_void,const CString& str_para1,const CString& str_para2)		\
{																							\
	CLS_TYPE *p_cls = (CLS_TYPE*) p_void;													\
																							\
	return p_cls->FNC_NAME(str_para1,str_para2);											\
}

#define  DECLARE__FNC_RET_STRING__INT(CLS_TYPE,FNC_NAME)									\
CString CLS_TYPE##FNC_NAME(void *p_void,const int i_para)									\
{																							\
	CLS_TYPE *p_cls = (CLS_TYPE*) p_void;													\
																							\
	return p_cls->FNC_NAME(i_para);															\
}

#define  DECLARE__FNC_RET_STRING__STRING(CLS_TYPE,FNC_NAME)									\
CString CLS_TYPE##FNC_NAME(void *p_void,const CString& str_para)							\
{																							\
	CLS_TYPE *p_cls = (CLS_TYPE*) p_void;													\
																							\
	return p_cls->FNC_NAME(str_para);														\
}


//
#define  REGISTER__FNC_RET_INT(FNC_NAME,CLS_TYPE,FNC_PTR)									\
p_fnc_ctrl->Register__RET_INT(FNC_NAME,this,CLS_TYPE##FNC_PTR);

#define  REGISTER__FNC_RET_DOUBLE(FNC_NAME,CLS_TYPE,FNC_PTR)								\
p_fnc_ctrl->Register__RET_DOUBLE(FNC_NAME,this,CLS_TYPE##FNC_PTR);

#define  REGISTER__FNC_RET_STRING(FNC_NAME,CLS_TYPE,FNC_PTR)								\
p_fnc_ctrl->Register__RET_STRING(FNC_NAME,this,CLS_TYPE##FNC_PTR);

#define  REGISTER__FNC_RET_CONDITION(FNC_NAME,CLS_TYPE,FNC_PTR)								\
p_fnc_ctrl->Register__RET_CONDITION(FNC_NAME,this,CLS_TYPE##FNC_PTR);

//
#define  REGISTER__FNC_RET_INT__INT_STRING(FNC_NAME,CLS_TYPE,FNC_PTR)						\
p_fnc_ctrl->Register__RET_INT__INT_STRING(FNC_NAME,this,CLS_TYPE##FNC_PTR);

#define  REGISTER__FNC_RET_INT__STRING_STRING(FNC_NAME,CLS_TYPE,FNC_PTR)					\
p_fnc_ctrl->Register__RET_INT__STRING_STRING(FNC_NAME,this,CLS_TYPE##FNC_PTR);

#define  REGISTER__FNC_RET_STRING__INT(FNC_NAME,CLS_TYPE,FNC_PTR)							\
p_fnc_ctrl->Register__RET_STRING__INT(FNC_NAME,this,CLS_TYPE##FNC_PTR);

#define  REGISTER__FNC_RET_STRING__STRING(FNC_NAME,CLS_TYPE,FNC_PTR)						\
p_fnc_ctrl->Register__RET_STRING__STRING(FNC_NAME,this,CLS_TYPE##FNC_PTR);


//------------------------------------------------------------------------------------------------
#define VIRTUAL_INT																			\
virtual int


//------------------------------------------------------------------------------------------------
#define  __DEFINE__IO_INTERLOCK(p_interlock)												\
__Define__IO_INTERLOCK(CII_DEFINE__IO_INTERLOCK *p_interlock)

#define  __DEFINE__UI_INTERLOCK(p_interlock)												\
__Define__UI_INTERLOCK(CII_DEFINE__UI_INTERLOCK *p_interlock)


//------------------------------------------------------------------------------------------------
#define  __DEFINE__VERSION_HISTORY(version)													\
__Define__VERSION_HISTORY(CString& version)

#define  __DEFINE__CONTROL_MODE(obj,l_mode)													\
__Define__CONTROL_MODE(const CString& obj, CStringArray& l_mode)

#define  __DEFINE__VARIABLE_STD(p_variable)													\
__Define__VARIABLE_STD(CII_DEFINE__VARIABLE *p_variable)

#define  __DEFINE__VARIABLE_IO(p_io_variable)												\
__Define__VARIABLE_IO(CII_DEFINE__IO_VARIABLE *p_io_variable)

#define  __DEFINE__ALARM(p_alarm)															\
__Define__ALARM(CII_DEFINE__ALARM *p_alarm)


//------------------------------------------------------------------------------------------------
class CII_DEFINE__IO_PARAMETER
{
public:
	virtual ~CII_DEFINE__IO_PARAMETER(){};

	//-------------------------------------------------------------------------
	virtual int Get__PARAMETER_DATA(const CString& para_name, CString& para_data) = 0;
	
	virtual int Get__PARAMETER_SIZE() = 0;
	virtual int Get__PARAMETER_INFO(const int db_index, CString& para_name,CString& para_data) = 0;

	// ...
	virtual int Set__DRIVER_DEADLOCK_TIMEOUT(const double cfg_sec) = 0;
	virtual double Get__DRIVER_DEADLOCK_TIMEOUT() = 0;						// Default : 30.0 sec, Min : 10.0 sec 

	virtual CString Get__IO_FILE() = 0;
};

class CII_DEFINE__FA_PARAMETER
{
public:
	virtual ~CII_DEFINE__FA_PARAMETER(){};

	//-------------------------------------------------------------------------
	CString sFA_FILE_NAME;
	CString sFA_SERVICE_NAME;

	//-------------------------------------------------------------------------
	virtual int Get__PARAMETER_DATA(const CString& para_name, CString& para_data) = 0;

	virtual int Get__PARAMETER_SIZE() = 0;
	virtual int Get__PARAMETER_INFO(const int db_index, CString& para_name,CString& para_data) = 0;
};


#define  __INITIALIZE__OBJECT(p_variable,p_ext_obj_create)									\
__Initialize__OBJECT(CII_OBJECT__VARIABLE *p_variable,										\
				     CII_EXT_OBJECT__CREATE *p_ext_obj_create)

#define  __INITIALIZE__IO(p_io_para)														\
__Initialize__IO(CII_DEFINE__IO_PARAMETER* p_io_para)

#define  __INITIALIZE__FA(p_fa_create,p_fa_para)											\
__Initialize__FA(CII_FA_SERVICE__CREATE* p_fa_create,										\
				 CII_DEFINE__FA_PARAMETER* p_fa_para)


//------------------------------------------------------------------------------------------------
#define  __START__OBJECT()																	\
__Start__OBJECT()

#define  __CLOSE__OBJECT()																	\
__Close__OBJECT()


//------------------------------------------------------------------------------------------------
#define __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)								\
__Call__CONTROL_MODE(const CString& mode,													\
					 CII_OBJECT__DEBUG *p_debug,											\
					 CII_OBJECT__VARIABLE *p_variable,										\
					 CII_OBJECT__ALARM *p_alarm)

#define  __CALL__MONITORING(id,p_variable,p_alarm)											\
__Call__MONITORING(const int id,															\
				   CII_OBJECT__VARIABLE *p_variable,										\
				   CII_OBJECT__ALARM *p_alarm)


//------------------------------------------------------------------------------------------------
class CI_PROC_RES
{
public:
	CII_OBJECT__VARIABLE *pVariable_Ctrl;
	CII_OBJECT__ALARM    *pAlarm_Ctrl;
};


//------------------------------------------------------------------------------------------------
class __IOBJ__INTERLOCK_TYPE
{
public:
	virtual ~__IOBJ__INTERLOCK_TYPE(){};

	//-------------------------------------------------------------------------
	CII_INTERLOCK__ALARM *pII_ALARM;  

	//-------------------------------------------------------------------------	
	VIRTUAL_INT __DEFINE__CONTROL_MODE(obj,l_mode) = 0;
	VIRTUAL_INT __DEFINE__VERSION_HISTORY(version) = 0;

	VIRTUAL_INT __DEFINE__VARIABLE_STD(p_variable) EMPTY__BODY;
	VIRTUAL_INT __DEFINE__ALARM(p_alarm) EMPTY__BODY;

	VIRTUAL_INT __DEFINE__UI_INTERLOCK(p_interlock) EMPTY__BODY;
	VIRTUAL_INT __DEFINE__IO_INTERLOCK(p_interlock) EMPTY__BODY;

	//-------------------------------------------------------------------------
	VIRTUAL_INT __INITIALIZE__OBJECT(p_variable,p_ext_obj_create) = 0;
	VIRTUAL_INT __START__OBJECT() EMPTY__BODY;

	//-------------------------------------------------------------------------
	VIRTUAL_INT __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm) = 0;
	VIRTUAL_INT __CALL__MONITORING(id,p_variable,p_alarm) EMPTY__BODY;

	//-------------------------------------------------------------------------
	VIRTUAL_INT __CLOSE__OBJECT() EMPTY__BODY;


	//-------------------------------------------------------------------------
	virtual int __Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)	EMPTY__BODY;

	//-------------------------------------------------------------------------
	virtual int __Define__QUERY(CStringArray& l_query) EMPTY__BODY;

	virtual int __Call__QUERY(const CString& query_name,CString& query_data) EMPTY__BODY;
	virtual int __Call__QUERY_LIST(const CString& query_name,CStringArray& l_data) EMPTY__BODY;

	virtual int __Call__QUERY(const CString& query_name,const CStringArray& l_sub_query, CString& query_data) EMPTY__BODY;
	virtual int __Call__QUERY_LIST(const CString& query_name,const CStringArray& l_sub_query, CStringArray& l_data) EMPTY__BODY;

	/*
	virtual int __Call__QUERY_EX(const CString& query_name,const CString& sub_query,CString& query_data) EMPTY__BODY;
	virtual int __Call__QUERY_LIST_EX(const CString& query_name,const CString& sub_query,CStringArray& l_data) EMPTY__BODY;

	virtual int __Call__QUERY_USER_CLASS(const CString& query_name,const int cls_id,void* cls_body) EMPTY__BODY;
	*/
};


//------------------------------------------------------------------------------------------------
class __IOBJ__STD_TYPE
{
public:
	virtual ~__IOBJ__STD_TYPE(){};

	//-------------------------------------------------------------------------	
	VIRTUAL_INT __DEFINE__CONTROL_MODE(obj,l_mode) = 0;
	VIRTUAL_INT __DEFINE__VERSION_HISTORY(version) = 0;
	
	VIRTUAL_INT __DEFINE__VARIABLE_STD(p_variable) EMPTY__BODY;
	VIRTUAL_INT __DEFINE__ALARM(p_alarm) EMPTY__BODY;

	//-------------------------------------------------------------------------
	VIRTUAL_INT __INITIALIZE__OBJECT(p_variable,p_ext_obj_create) = 0;
	VIRTUAL_INT __START__OBJECT() EMPTY__BODY;

	//-------------------------------------------------------------------------
	VIRTUAL_INT __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm) = 0;
	VIRTUAL_INT __CALL__MONITORING(id,p_variable,p_alarm) EMPTY__BODY;

	//-------------------------------------------------------------------------
	VIRTUAL_INT __CLOSE__OBJECT() EMPTY__BODY;


	//-------------------------------------------------------------------------
	virtual int __Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)	EMPTY__BODY;

	//-------------------------------------------------------------------------
	virtual int __Define__QUERY(CStringArray& l_query) EMPTY__BODY;

	virtual int __Call__QUERY(const CString& query_name,CString& query_data) EMPTY__BODY;
	virtual int __Call__QUERY_LIST(const CString& query_name,CStringArray& l_data) EMPTY__BODY;

	virtual int __Call__QUERY(const CString& query_name,const CStringArray& l_sub_query, CString& query_data) EMPTY__BODY;
	virtual int __Call__QUERY_LIST(const CString& query_name,const CStringArray& l_sub_query, CStringArray& l_data) EMPTY__BODY;
};


//------------------------------------------------------------------------------------------------
class CDS_IO__CHANNEL_INFO
{
public:
	int iMD_NO;
	int iCH_NO;

	CString sCOMMAND1;
	CString sCOMMAND2;
	CString sCOMMAND3;

	double dMIN_VALUE;
	double dMAX_VALUE;

	double dMIN_VOLT;
	double dMAX_VOLT;
};

class __IOBJ__IO_TYPE
{
public:
	virtual ~__IOBJ__IO_TYPE(){};

	//-------------------------------------------------------------------------
	VIRTUAL_INT __DEFINE__CONTROL_MODE(obj,l_mode) = 0;
	VIRTUAL_INT __DEFINE__VERSION_HISTORY(version) = 0;

	VIRTUAL_INT __DEFINE__VARIABLE_STD(p_variable) EMPTY__BODY;
	VIRTUAL_INT __DEFINE__VARIABLE_IO(p_io_variable) = 0;

	VIRTUAL_INT __DEFINE__ALARM(p_alarm) EMPTY__BODY;

	//-------------------------------------------------------------------------
	VIRTUAL_INT __INITIALIZE__OBJECT(p_variable,p_ext_obj_create) = 0;
	VIRTUAL_INT __INITIALIZE__IO(p_io_para) = 0;
	VIRTUAL_INT __START__OBJECT() EMPTY__BODY;

	//-------------------------------------------------------------------------
	VIRTUAL_INT __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm) = 0;
	VIRTUAL_INT __CALL__MONITORING(id,p_variable,p_alarm) EMPTY__BODY;

	//-------------------------------------------------------------------------
	VIRTUAL_INT __CLOSE__OBJECT() EMPTY__BODY;

	//-------------------------------------------------------------------------
	VIRTUAL_INT __Read__ANALOG(const CString& var_name,  const CDS_IO__CHANNEL_INFO& io_info, double&  read_data) EMPTY__BODY;
	VIRTUAL_INT __Read__DIGITAL(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index) EMPTY__BODY;
	VIRTUAL_INT __Read__STRING(const CString& varc_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data) EMPTY__BODY;

	VIRTUAL_INT __Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double   set_data) EMPTY__BODY;
	VIRTUAL_INT __Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index) EMPTY__BODY;
	VIRTUAL_INT __Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data) EMPTY__BODY;


	//-------------------------------------------------------------------------
	virtual int __Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl) EMPTY__BODY;

	//-------------------------------------------------------------------------
	virtual int __Define__QUERY(CStringArray& l_query) EMPTY__BODY;

	virtual int __Call__QUERY(const CString& query_name,CString& query_data) EMPTY__BODY;
	virtual int __Call__QUERY_LIST(const CString& query_name,CStringArray& l_data) EMPTY__BODY;

	virtual int __Call__QUERY(const CString& query_name,const CStringArray& l_sub_query, CString& query_data) EMPTY__BODY;
	virtual int __Call__QUERY_LIST(const CString& query_name,const CStringArray& l_sub_query, CStringArray& l_data) EMPTY__BODY;
};


//------------------------------------------------------------------------------------------------
class __IOBJ__LINK_TYPE
{
public:
	virtual ~__IOBJ__LINK_TYPE(){};

	//-------------------------------------------------------------------------
	VIRTUAL_INT __DEFINE__CONTROL_MODE(obj,l_mode) = 0;
	VIRTUAL_INT __DEFINE__VERSION_HISTORY(version) = 0;

	VIRTUAL_INT __DEFINE__VARIABLE_STD(p_variable) EMPTY__BODY;
	VIRTUAL_INT __DEFINE__ALARM(p_alarm) EMPTY__BODY;

	//-------------------------------------------------------------------------
	VIRTUAL_INT __INITIALIZE__OBJECT(p_variable,p_ext_obj_create) = 0;
	VIRTUAL_INT __START__OBJECT() EMPTY__BODY;

	//-------------------------------------------------------------------------
	VIRTUAL_INT __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm) = 0;
	VIRTUAL_INT __CALL__MONITORING(id,p_variable,p_alarm) EMPTY__BODY;

	//-------------------------------------------------------------------------
	VIRTUAL_INT __CLOSE__OBJECT() EMPTY__BODY;


	//-------------------------------------------------------------------------
	virtual int __Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl) EMPTY__BODY;

	//-------------------------------------------------------------------------
	virtual int __Define__QUERY(CStringArray& l_query) EMPTY__BODY;

	virtual int __Call__QUERY(const CString& query_name,CString& query_data) EMPTY__BODY;
	virtual int __Call__QUERY_LIST(const CString& query_name,CStringArray& l_data) EMPTY__BODY;

	virtual int __Call__QUERY(const CString& query_name,const CStringArray& l_sub_query, CString& query_data) EMPTY__BODY;
	virtual int __Call__QUERY_LIST(const CString& query_name,const CStringArray& l_sub_query, CStringArray& l_data) EMPTY__BODY;
};


//------------------------------------------------------------------------------------------------
class __IOBJ__FA_TYPE
{
public:
	virtual ~__IOBJ__FA_TYPE(){};

	//-------------------------------------------------------------------------
	VIRTUAL_INT __DEFINE__CONTROL_MODE(obj,l_mode) = 0;
	VIRTUAL_INT __DEFINE__VERSION_HISTORY(version) = 0;

	VIRTUAL_INT __DEFINE__VARIABLE_STD(p_variable) EMPTY__BODY;
	VIRTUAL_INT __DEFINE__ALARM(p_alarm) EMPTY__BODY;

	//-------------------------------------------------------------------------
	VIRTUAL_INT __INITIALIZE__OBJECT(p_variable,p_ext_obj_create) = 0;
	VIRTUAL_INT __INITIALIZE__FA(p_fa_create,p_fa_para) = 0;
	VIRTUAL_INT __START__OBJECT() EMPTY__BODY;

	//-------------------------------------------------------------------------
	VIRTUAL_INT __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm) = 0;
	VIRTUAL_INT __CALL__MONITORING(id,p_variable,p_alarm) EMPTY__BODY;

	//-------------------------------------------------------------------------
	VIRTUAL_INT __CLOSE__OBJECT() EMPTY__BODY;


	//-------------------------------------------------------------------------
	virtual int __Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl) EMPTY__BODY;

	//-------------------------------------------------------------------------
	virtual int __Define__QUERY(CStringArray& l_query) EMPTY__BODY;

	virtual int __Call__QUERY(const CString& query_name,CString& query_data) EMPTY__BODY;
	virtual int __Call__QUERY_LIST(const CString& query_name,CStringArray& l_data) EMPTY__BODY;

	virtual int __Call__QUERY(const CString& query_name,const CStringArray& l_sub_query, CString& query_data) EMPTY__BODY;
	virtual int __Call__QUERY_LIST(const CString& query_name,const CStringArray& l_sub_query, CStringArray& l_data) EMPTY__BODY;
};


//------------------------------------------------------------------------------------------------
#define  OBJ_ABORT								-1
#define  OBJ_AVAILABLE							1
#define  OBJ_RETRY								1001
#define  OBJ_EXIT								throw  -1


#define  CTRL_MODE__CHECK(FNC_NAME)																\
p_variable->Check__OBJ_MODE(mode,FNC_NAME)


#define  IF__CTRL_MODE(FNC_NAME)																\
if(p_variable->Check__OBJ_MODE(mode,FNC_NAME))

#define  ELSE_IF__CTRL_MODE(FNC_NAME)															\
else if(p_variable->Check__OBJ_MODE(mode,FNC_NAME))

#define  ELSE_IF__CTRL_MODE1_MODE2(FNC_NAME1,FNC_NAME2)											\
else if((p_variable->Check__OBJ_MODE(mode,FNC_NAME1))											\
|| (p_variable->Check__OBJ_MODE(mode,FNC_NAME2)))


#define  CHECK__CTRL_MODE(FNC_NAME)																\
p_variable->Check__OBJ_MODE(mode,FNC_NAME)


/*
#define  ADD__CTRL_MODE(ctrl_mode)																\
l_mode.Add(ctrl_mode);
*/

#define  ADD__CTRL_VAR(CTRL_VAR,ctrl_mode)														\
CTRL_VAR = ctrl_mode;																			\
l_mode.Add(ctrl_mode);


//------------------------------------------------------------------------------------------------
#define  DECLARE__STD_VARIABLE																	\
CII_CTRL__ANALOG_VIRTUAL  *p_analog  = p_variable->pCTRL__ANALOG;								\
CII_CTRL__DIGITAL_VIRTUAL *p_digital = p_variable->pCTRL__DIGITAL;								\
CII_CTRL__STRING_VIRTUAL  *p_string  = p_variable->pCTRL__STRING;


#define  STD__ADD_ANALOG(var_name,unit,dec,min,max)												\
p_analog->Add__ANALOG(var_name,unit,dec,min,max);
#define  STD__ADD_ANALOG_WITH_COMMENT(var_name,unit,dec,min,max,comment)						\
p_analog->Add__ANALOG(var_name,unit,dec,min,max,"","",comment);
#define  STD__ADD_ANALOG_WITH_X_OPTION(var_name,unit,dec,min,max,comment)						\
p_analog->Add__ANALOG_WITH_X_OPTION(var_name,unit,dec,min,max,"","",comment);
#define  STD__ADD_ANALOG_WITH_OPTION(var_name,unit,dec,min,max,x_option,log_type,comment)		\
p_analog->Add__ANALOG_WITH_OPTION(var_name,unit,dec,min,max,x_option,log_type,comment);

#define  STD__ADD_DIGITAL(var_name,item_list)													\
p_digital->Add__DIGITAL(var_name,item_list);
#define  STD__ADD_DIGITAL_WITH_COMMENT(var_name,item_list,comment)								\
p_digital->Add__DIGITAL_WITH_COMMENT(var_name,item_list,comment);
#define  STD__ADD_DIGITAL_WITH_X_OPTION(var_name,item_list,comment)								\
p_digital->Add__DIGITAL_WITH_X_OPTION(var_name,item_list,comment);
#define  STD__ADD_DIGITAL_WITH_OPTION(var_name,item_list,x_option,log_type,comment)				\
p_digital->Add__DIGITAL_WITH_OPTION(var_name,item_list,x_option,log_type,comment);

#define  STD__ADD_STRING(var_name)																\
p_string->Add__STRING(var_name);
#define  STD__ADD_STRING_WITH_COMMENT(var_name,comment)											\
p_string->Add__STRING_WITH_COMMENT(var_name,0,comment);
#define  STD__ADD_STRING_WITH_X_OPTION(var_name,comment)										\
p_string->Add__STRING_WITH_X_OPTION(var_name,0,comment);
#define  STD__ADD_STRING_WITH_OPTION(var_name,x_option,log_type,comment)						\
p_string->Add__STRING_WITH_OPTION(var_name,x_option,log_type,0,comment);


//------------------------------------------------------------------------------------------------
#define  DECLARE__IO_VARIABLE																	\
CII_CTRL__ANALOG_IO  *p_analog_io  = p_io_variable->pCTRL__ANALOG_IO;							\
CII_CTRL__DIGITAL_IO *p_digital_io = p_io_variable->pCTRL__DIGITAL_IO;							\
CII_CTRL__STRING_IO  *p_string_io  = p_io_variable->pCTRL__STRING_IO;


#define  IO__ADD_ANALOG_READ(var_name,unit,dec,min,max)											\
p_analog_io->Add__ANALOG_READ(var_name,var_name,unit,dec,min,max);
#define  IO__ADD_ANALOG_WRITE(var_name,unit,dec,min,max)										\
p_analog_io->Add__ANALOG_WRITE(var_name,var_name,unit,dec,min,max);

#define  IO__ADD_ANALOG_READ_WITH_COMMENT(var_name,unit,dec,min,max,comment)					\
p_analog_io->Add__ANALOG_READ(var_name,var_name,unit,dec,min,max,1,"","",comment);
#define  IO__ADD_ANALOG_WRITE_WITH_COMMENT(var_name,unit,dec,min,max,comment)					\
p_analog_io->Add__ANALOG_WRITE(var_name,var_name,unit,dec,min,max,1,"","",comment);

#define  IO__ADD_ANALOG_READ__MANUAL(var_name,unit,dec,min,max)									\
p_analog_io->Add__ANALOG_READ(var_name,var_name,unit,dec,min,max,-1);
#define  IO__ADD_ANALOG_WRITE__MANUAL(var_name,unit,dec,min,max)								\
p_analog_io->Add__ANALOG_WRITE(var_name,var_name,unit,dec,min,max,-1);

#define  IO__ADD_ANALOG_READ__MANUAL_WITH_COMMENT(var_name,unit,dec,min,max,comment)			\
p_analog_io->Add__ANALOG_READ(var_name,var_name,unit,dec,min,max,-1,"","",comment);
#define  IO__ADD_ANALOG_WRITE__MANUAL_WITH_COMMENT(var_name,unit,dec,min,max,comment)			\
p_analog_io->Add__ANALOG_WRITE(var_name,var_name,unit,dec,min,max,-1,"","",comment);


#define  IO__ADD_ANALOG_READ_EX(var_name,unit,dec,min,max,cmmd1,cmmd2,cmmd3)					\
p_analog_io->Add__ANALOG_READ_EX(var_name,var_name,unit,dec,min,max,cmmd1,cmmd2,cmmd3);
#define  IO__ADD_ANALOG_WRITE_EX(var_name,unit,dec,min,max,cmmd1,cmmd2,cmmd3)					\
p_analog_io->Add__ANALOG_WRITE_EX(var_name,var_name,unit,dec,min,max,cmmd1,cmmd2,cmmd3);

#define  IO__ADD_ANALOG_READ_EX_WITH_COMMENT(var_name,unit,dec,min,max,cmmd1,cmmd2,cmmd3,comment)				\
p_analog_io->Add__ANALOG_READ_EX(var_name,var_name,unit,dec,min,max,cmmd1,cmmd2,cmmd3,1,"","",comment);
#define  IO__ADD_ANALOG_WRITE_EX_WITH_COMMENT(var_name,unit,dec,min,max,cmmd1,cmmd2,cmmd3,comment)				\
p_analog_IO->Add__ANALOG_WRITE_EX(var_name,var_name,unit,dec,min,max,cmmd1,cmmd2,cmmd3,1,"","",comment);

#define  IO__ADD_ANALOG_READ__MANUAL_EX(var_name,unit,dec,min,max,cmmd1,cmmd2,cmmd3)			\
p_analog_io->Add__ANALOG_READ_EX(var_name,var_name,unit,dec,min,max,cmmd1,cmmd2,cmmd3,-1);
#define  IO__ADD_ANALOG_WRITE__MANUAL_EX(var_name,unit,dec,min,max,cmmd1,cmmd2,cmmd3)			\
p_analog_io->Add__ANALOG_WRITE_EX(var_name,var_name,unit,dec,min,max,cmmd1,cmmd2,cmmd3,-1);

#define  IO__ADD_ANALOG_READ__MANUAL_EX_WITH_COMMENT(var_name,unit,dec,min,max,cmmd1,cmmd2,cmmd3,comment)		\
p_analog_io->Add__ANALOG_READ_EX(var_name,var_name,unit,dec,min,max,cmmd1,cmmd2,cmmd3,-1,"","",comment);
#define  IO__ADD_ANALOG_WRITE__MANUAL_EX_WITH_COMMENT(var_name,unit,dec,min,max,cmmd1,cmmd2,cmmd3,comment)		\
p_analog_io->Add__ANALOG_WRITE_EX(var_name,var_name,unit,dec,min,max,cmmd1,cmmd2,cmmd3,-1,"","",comment);

#define  IO__ADD_ANALOG_READ__WITH_OPTION(var_name,unit,dec,min,max,cmmd1,cmmd2,cmmd3,auto_polling,comment)		\
p_analog_io->Add__ANALOG_READ_EX2(var_name,var_name,unit,dec,min,max,cmmd1,cmmd2,cmmd3,auto_polling,comment);
#define  IO__ADD_ANALOG_WRITE__WITH_OPTION(var_name,unit,dec,min,max,cmmd1,cmmd2,cmmd3,auto_polling,comment)	\
p_analog_io->Add__ANALOG_WRITE_EX2(var_name,var_name,unit,dec,min,max,cmmd1,cmmd2,cmmd3,auto_polling,comment);

#define  IO__CHANGE_ANALOG__LOG_INTERVAL()			\
p_analog_io->Change__LOG_INTERVAL();
#define  IO__CHANGE_ANALOG__LOG_EVENT()				\
p_analog_io->Change__LOG_EVENT();


#define  IO__ADD_DIGITAL_READ(var_name,item_list)												\
p_digital_io->Add__DIGITAL_READ(var_name,var_name,item_list);	
#define  IO__ADD_DIGITAL_WRITE(var_name,item_list)												\
p_digital_io->Add__DIGITAL_WRITE(var_name,var_name,item_list);

#define  IO__ADD_DIGITAL_READ_WITH_COMMENT(var_name,item_list,comment)							\
p_digital_io->Add__DIGITAL_READ_WITH_COMMENT(var_name,var_name,item_list,1,comment);
#define  IO__ADD_DIGITAL_WRITE_WITH_COMMENT(var_name,item_list,comment)							\
p_digital_io->Add__DIGITAL_WRITE_WITH_COMMENT(var_name,var_name,item_list,1,comment);

#define  IO__ADD_DIGITAL_READ__MANUAL(var_name,item_list)										\
p_digital_io->Add__DIGITAL_READ(var_name,var_name,item_list,-1);
#define  IO__ADD_DIGITAL_WRITE__MANUAL(var_name,item_list)										\
p_digital_io->Add__DIGITAL_WRITE(var_name,var_name,item_list,-1);

#define  IO__ADD_DIGITAL_READ__MANUAL_WITH_COMMENT(var_name,item_list,comment)					\
p_digital_io->Add__DIGITAL_READ_WITH_COMMENT(var_name,var_name,item_list,-1,comment);
#define  IO__ADD_DIGITAL_WRITE__MANUAL_WITH_COMMENT(var_name,item_list,comment)					\
p_digital_io->Add__DIGITAL_WRITE_WITH_COMMENT(var_name,var_name,item_list,-1,comment);


#define  IO__ADD_DIGITAL_READ_EX(var_name,item_list,cmmd1,cmmd2,cmmd3)							\
p_digital_io->Add__DIGITAL_READ_EX(var_name,var_name,item_list,cmmd1,cmmd2,cmmd3);
#define  IO__ADD_DIGITAL_WRITE_EX(var_name,item_list,cmmd1,cmmd2,cmmd3)							\
p_digital_io->Add__DIGITAL_WRITE_EX(var_name,var_name,item_list,cmmd1,cmmd2,cmmd3);

#define  IO__ADD_DIGITAL_READ_EX_WITH_COMMENT(var_name,item_list,cmmd1,cmmd2,cmmd3,comment)						\
p_digital_io->Add__DIGITAL_READ_EX_WITH_COMMENT(var_name,var_name,item_list,cmmd1,cmmd2,cmmd3,1,comment);
#define  IO__ADD_DIGITAL_WRITE_EX_WITH_COMMENT(var_name,item_list,cmmd1,cmmd2,cmmd3,comment)					\
p_digital_io->Add__DIGITAL_WRITE_EX_WITH_COMMENT(var_name,var_name,item_list,cmmd1,cmmd2,cmmd3,1,comment);

#define  IO__ADD_DIGITAL_READ__MANUAL_EX(var_name,item_list,cmmd1,cmmd2,cmmd3)					\
p_digital_io->Add__DIGITAL_READ_EX(var_name,var_name,item_list,cmmd1,cmmd2,cmmd3,-1);
#define  IO__ADD_DIGITAL_WRITE__MANUAL_EX(var_name,item_list,cmmd1,cmmd2,cmmd3)					\
p_digital_io->Add__DIGITAL_WRITE_EX(var_name,var_name,item_list,cmmd1,cmmd2,cmmd3,-1);

#define  IO__ADD_DIGITAL_READ__MANUAL_EX_WITH_COMMENT(var_name,item_list,cmmd1,cmmd2,cmmd3,comment)				\
p_digital_io->Add__DIGITAL_READ_EX_WITH_COMMENT(var_name,var_name,item_list,cmmd1,cmmd2,cmmd3,-1,comment);
#define  IO__ADD_DIGITAL_WRITE__MANUAL_EX_WITH_COMMENT(var_name,item_list,cmmd1,cmmd2,cmmd3,comment)			\
p_digital_io->Add__DIGITAL_WRITE_EX_WITH_COMMENT(var_name,var_name,item_list,cmmd1,cmmd2,cmmd3,-1,comment);

#define  IO__ADD_DIGITAL_READ_WITH_OPTION(var_name,item_list,cmmd1,cmmd2,cmmd3,auto_polling,comment)			\
p_digital_io->Add__DIGITAL_READ_EX2(var_name,var_name,item_list,cmmd1,cmmd2,cmmd3,auto_polling,comment);
#define  IO__ADD_DIGITAL_WRITE_WITH_OPTION(var_name,item_list,cmmd1,cmmd2,cmmd3,auto_polling,comment)			\
p_digital_io->Add__DIGITAL_WRITE_EX2(var_name,var_name,item_list,cmmd1,cmmd2,cmmd3,auto_polling,comment);

#define  IO__CHANGE_DIGITAL__LOG_INTERVAL()			\
p_digital_io->Change__LOG_INTERVAL();
#define  IO__CHANGE_DIGITAL__LOG_EVENT()			\
p_digital_io->Change__LOG_EVENT();


#define  IO__ADD_STRING_READ(var_name)															\
p_string_io->Add__STRING_READ(var_name,var_name);
#define  IO__ADD_STRING_WRITE(var_name)															\
p_string_io->Add__STRING_WRITE(var_name,var_name);

#define  IO__ADD_STRING_READ_WITH_COMMENT(var_name,comment)										\
p_string_io->Add__STRING_READ_WITH_COMMENT(var_name,var_name,1,0,comment);
#define  IO__ADD_STRING_WRITE_WITH_COMMENT(var_name,comment)									\
p_string_io->Add__STRING_WRITE_WITH_COMMENT(var_name,var_name,1,0,comment);

#define  IO__ADD_STRING_READ__MANUAL(var_name)													\
p_string_io->Add__STRING_READ(var_name,var_name,-1);
#define  IO__ADD_STRING_WRITE__MANUAL(var_name)													\
p_string_io->Add__STRING_WRITE(var_name,var_name,-1);

#define  IO__ADD_STRING_READ__MANUAL_WITH_COMMENT(var_name,comment)								\
p_string_io->Add__STRING_READ_WITH_COMMENT(var_name,var_name,-1,0,comment);
#define  IO__ADD_STRING_WRITE__MANUAL_WITH_COMMENT(var_name,comment)							\
p_string_io->Add__STRING_WRITE_WITH_COMMENT(var_name,var_name,-1,0,comment);


#define  IO__ADD_STRING_READ_EX(var_name,cmmd1,cmmd2,cmmd3)										\
p_string_io->Add__STRING_READ_EX(var_name,var_name,cmmd1,cmmd2,cmmd3);
#define  IO__ADD_STRING_WRITE_EX(var_name,cmmd1,cmmd2,cmmd3)									\
p_string_io->Add__STRING_WRITE_EX(var_name,var_name,cmmd1,cmmd2,cmmd3);

#define  IO__ADD_STRING_READ_EX_WITH_COMMENT(var_name,cmmd1,cmmd2,cmmd3,comment)				\
p_string_io->Add__STRING_READ_EX_WITH_COMMENT(var_name,var_name,cmmd1,cmmd2,cmmd3,1,0,comment);
#define  IO__ADD_STRING_WRITE_EX_WITH_COMMENT(var_name,cmmd1,cmmd2,cmmd3,comment)				\
p_string_IO->Add__STRING_WRITE_EX_WITH_COMMENT(var_name,var_name,cmmd1,cmmd2,cmmd3,1,0,comment);

#define  IO__ADD_STRING_READ__MANUAL_EX(var_name,cmmd1,cmmd2,cmmd3)								\
p_string_io->Add__STRING_READ_EX(var_name,var_name,cmmd1,cmmd2,cmmd3,-1);
#define  IO__ADD_STRING_WRITE__MANUAL_EX(var_name,cmmd1,cmmd2,cmmd3)							\
p_string_io->Add__STRING_WRITE_EX(var_name,var_name,cmmd1,cmmd2,cmmd3,-1);

#define  IO__ADD_STRING_READ__MANUAL_EX_WITH_COMMENT(var_name,cmmd1,cmmd2,cmmd3,comment)		\
p_string_io->Add__STRING_READ_EX_WITH_COMMENT(var_name,var_name,cmmd1,cmmd2,cmmd3,-1,0,comment);
#define  IO__ADD_STRING_WRITE__MANUAL_EX_WITH_COMMENT(var_name,cmmd1,cmmd2,cmmd3,comment)		\
p_string_io->Add__STRING_WRITE_EX_WITH_COMMENT(var_name,var_name,cmmd1,cmmd2,cmmd3,-1,0,comment);

#define  IO__ADD_STRING_READ_WITH_OPTION(var_name,cmmd1,cmmd2,cmmd3,auto_polling,comment)		\
p_string_io->Add__STRING_READ_EX2(var_name,var_name,cmmd1,cmmd2,cmmd3,auto_polling,0,comment);
#define  IO__ADD_STRING_WRITE_WITH_OPTION(var_name,cmmd1,cmmd2,cmmd3,auto_polling,comment)		\
p_string_io->Add__STRING_WRITE_EX2(var_name,var_name,cmmd1,cmmd2,cmmd3,auto_polling,0,comment);

#define  IO__CHANGE_STRING__LOG_INTERVAL()			\
p_string_io->Change__LOG_INTERVAL();
#define  IO__CHANGE_STRING__LOG_EVENT()				\
p_string_io->Change__LOG_EVENT();


//------------------------------------------------------------------------------------------------
#define  DECLARE__ALARM																			\
CII_CTRL__ALARM *p_ctrl__alarm = p_alarm->pCTRL__ALARM;


#define  ADD__ALARM(alarm_id)																	\
p_ctrl__alarm->Make__ALARM(alarm_id);

#define  ADD__ALARM_EX(alarm_id,title,message,l_option)											\
p_ctrl__alarm->Make__ALARM_EX(alarm_id,title,message,l_option);

#define  ADD__ALARM_WITH_LEVEL(alarm_id,alarm_level,title,message,l_option)						\
p_ctrl__alarm->Make__ALARM_WITH_LEVEL(alarm_id,alarm_level,title,message,l_option);	

#define  ADD__ALARM_WITH_HEAVY_LEVEL(alarm_id,title,message,l_option)							\
p_ctrl__alarm->Make__ALARM_WITH_LEVEL(alarm_id,0,title,message,l_option);	

#define  ADD__ALARM_WITH_LIGHT_LEVEL(alarm_id,title,message,l_option)							\
p_ctrl__alarm->Make__ALARM_WITH_LEVEL(alarm_id,1,title,message,l_option);	

#define  ADD__ALARM_WITH_WARNING_LEVEL(alarm_id,title,message,l_option)							\
p_ctrl__alarm->Make__ALARM_WITH_LEVEL(alarm_id,2,title,message,l_option);	


#define  ENABLE__ALARM_HOST_REPORT(alarm_id,title,message,l_option)								\
p_ctrl__alarm->Set__ALARM_HOST_REPORT(alarm_id,1);	

#define  DISABLE__ALARM_HOST_REPORT(alarm_id,title,message,l_option)							\
p_ctrl__alarm->Set__ALARM_HOST_REPORT(alarm_id,-1);	
//------------------------------------------------------------------------------------------------
